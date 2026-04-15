#include "FaceCube.h"



#include <string>
#include <stdexcept>



void FaceCube::Facelets(const std::string& net)
{
    if (net.size() != 54) {
        throw std::runtime_error("Input invalid: trebuie exact 54 caractere (net2D).");
    }

    // net layout:
    // U: [0..8]
    // middle: [9..44] 3 rows x 12 cols, with faces per row: L F R B (each 3 cols)
    // D: [45..53]
    auto mid = [&](int r, int c) { return 9 + r * 12 + c; };

    // Construim un buffer "raw" în ordinea Kociemba URFDLB,
    // dar cu caracterele de culoare din input (W/Y/R/O/B/G).
    char raw[54];

    // U -> raw[0..8]
    for (int i = 0; i < 9; i++) raw[i] = net[i];

    // R -> raw[9..17]  (în net, R este al 3-lea bloc de 3 coloane: col 6..8)
    {
        int k = 9;
        for (int r = 0; r < 3; r++)
            for (int c = 6; c < 9; c++)
                raw[k++] = net[mid(r, c)];
    }

    // F -> raw[18..26] (în net, F este al 2-lea bloc: col 3..5)
    {
        int k = 18;
        for (int r = 0; r < 3; r++)
            for (int c = 3; c < 6; c++)
                raw[k++] = net[mid(r, c)];
    }

    // D -> raw[27..35]
    for (int i = 0; i < 9; i++) raw[27 + i] = net[45 + i];

    // L -> raw[36..44] (în net, L este primul bloc: col 0..2)
    {
        int k = 36;
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                raw[k++] = net[mid(r, c)];
    }

    // B -> raw[45..53] (în net, B este ultimul bloc: col 9..11)
    // Ai zis c? NU e rotit?, deci citim normal.
    {
        int k = 45;
        for (int r = 0; r < 3; r++)
            for (int c = 9; c < 12; c++)
                raw[k++] = net[mid(r, c)];
    }

    // Acum centrele sunt în pozi?iile Kociemba standard:
    // U center raw[4], R center raw[13], F center raw[22], D center raw[31], L center raw[40], B center raw[49]
    char colorU = raw[4];
    char colorR = raw[13];
    char colorF = raw[22];
    char colorD = raw[31];
    char colorL = raw[40];
    char colorB = raw[49];

    // Convertim culorile in litere U/R/F/D/L/B in facelets[] (tot URFDLB indices)
    for (int i = 0; i < 54; i++) {
        if (raw[i] == colorU) facelets[i] = 'U';
        else if (raw[i] == colorR) facelets[i] = 'R';
        else if (raw[i] == colorF) facelets[i] = 'F';
        else if (raw[i] == colorD) facelets[i] = 'D';
        else if (raw[i] == colorL) facelets[i] = 'L';
        else if (raw[i] == colorB) facelets[i] = 'B';
        else{
         std::string msg = "Culoare necunoscuta la i=" + std::to_string(i) +
                      " raw[i]='" + std::string(1, raw[i]) + "'" +
                      " centre(U,R,F,D,L,B)=(" + std::string(1,colorU) + "," +
                                                std::string(1,colorR) + "," +
                                                std::string(1,colorF) + "," +
                                                std::string(1,colorD) + "," +
                                                std::string(1,colorL) + "," +
                                                std::string(1,colorB) + ")";
                    throw std::runtime_error(msg);
        }
    }
}

//UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB
//yyyyyyyyyrrrgggooobbbrrrgggooobbbrrrgggooobbbwwwwwwwww
Cubie FaceCube::toCubieCube() {
    Cubie rez;


    int cornerIndices[8][3] = {
        {8, 9, 20},
        {6, 18, 38},
        {0, 36, 47},
        {2, 45, 11},
        {29, 26, 15},
        {27, 44, 24},
        {33, 53, 42},
        {35, 17, 51}
    };

    int edgeIndices[12][2] = {
    { 5, 10 }, // UR: U5, R1
    { 7, 19 }, // UF: U7, F1
    { 3, 37 }, // UL: U3, L1
    { 1, 46 }, // UB: U1, B1

    { 32, 16 }, // DR: D5, R7
    { 28, 25 }, // DF: D1, F7
    { 30, 43 }, // DL: D3, L7
    { 34, 52 }, // DB: D7, B7

    { 23, 12 }, // FR: F5, R3
    { 21, 41 }, // FL: F3, L5
    { 50, 39 }, // BL: B5, L3
    { 48, 14 }  // BR: B3, R5
    };

    string cornerColors[8] = { "URF", "ULF", "ULB", "URB", "DRF", "DLF", "DLB", "DRB" };

    for (int i = 0; i < 8; i++) {

        char f1 = facelets[cornerIndices[i][0]];
        char f2 = facelets[cornerIndices[i][1]];
        char f3 = facelets[cornerIndices[i][2]];


        uint8_t orientation = 0;
        if (f1 == 'U' || f1 == 'D') orientation = 0;
        else if (f2 == 'U' || f2 == 'D') orientation = 1;
        else if (f3 == 'U' || f3 == 'D') orientation = 2;

        rez.CornerOrientation[i] = orientation;


        string pieceName = "";
        if (orientation == 0) pieceName = string(1, f1) + f2 + f3;
        else if (orientation == 1) pieceName = string(1, f2) + f3 + f1;
        else if (orientation == 2) pieceName = string(1, f3) + f1 + f2;


        for (int p = 0; p < 8; p++) {

            if (pieceName.find(cornerColors[p][0]) != string::npos &&
                pieceName.find(cornerColors[p][1]) != string::npos &&
                pieceName.find(cornerColors[p][2]) != string::npos) {
                rez.CornerPermutation[i] = p;
                break;
            }
        }
    }
    string edgeColors[12] = { "UR","UF","UL","UB","DR","DF","DL","DB","FR","FL","BL","BR" };

    for (int i = 0; i < 12; i++) {
        char a = facelets[edgeIndices[i][0]];
        char b = facelets[edgeIndices[i][1]];

        // determin? ce pies? este (care dintre cele 12)
        int piece = -1;
        int ori = 0;

        for (int p = 0; p < 12; p++) {
            // orientare 0: (a,b) = (X,Y)
            if (a == edgeColors[p][0] && b == edgeColors[p][1]) { piece = p; ori = 0; break; }
            // orientare 1: (a,b) = (Y,X)
            if (a == edgeColors[p][1] && b == edgeColors[p][0]) { piece = p; ori = 1; break; }
        }
        if (piece == -1) {
            throw std::runtime_error("Edge invalid/unrecognized at index " + std::to_string(i));
        }
        bool usedE[12] = { false };
        
            if (usedE[piece]) throw std::runtime_error("Edge permutation duplicate: " + std::to_string(piece));
        usedE[piece] = true;
        rez.EdgePermutation[i] = piece;
        rez.EdgeOrientation[i] = ori;
    }


    return rez;
}
