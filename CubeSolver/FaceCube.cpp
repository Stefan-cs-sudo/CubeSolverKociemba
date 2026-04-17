#include "FaceCube.h"
#include <stdexcept>

void FaceCube::Facelets(const std::string& urfdlbStr) {
    if (urfdlbStr.size() != 54) {
        throw std::runtime_error("Eroare: Cubul nu are 54 de caractere!");
    }

    char colorU = urfdlbStr[4];
    char colorR = urfdlbStr[13];
    char colorF = urfdlbStr[22];
    char colorD = urfdlbStr[31];
    char colorL = urfdlbStr[40];
    char colorB = urfdlbStr[49];

    for (int i = 0; i < 54; i++) {
        if (urfdlbStr[i] == colorU) facelets[i] = 'U';
        else if (urfdlbStr[i] == colorR) facelets[i] = 'R';
        else if (urfdlbStr[i] == colorF) facelets[i] = 'F';
        else if (urfdlbStr[i] == colorD) facelets[i] = 'D';
        else if (urfdlbStr[i] == colorL) facelets[i] = 'L';
        else if (urfdlbStr[i] == colorB) facelets[i] = 'B';
        else throw std::runtime_error("Culoare necunoscuta pe cub!");
    }
}

Cubie FaceCube::toCubieCube() {
    Cubie rez;

    int cornerIndices[8][3] = {
        {8, 9, 20}, {6, 18, 38}, {0, 36, 47}, {2, 45, 11},
        {29, 26, 15}, {27, 44, 24}, {33, 53, 42}, {35, 17, 51}
    };

    int edgeIndices[12][2] = {
        {5, 10}, {7, 19}, {3, 37}, {1, 46},
        {32, 16}, {28, 25}, {30, 43}, {34, 52},
        {23, 12}, {21, 41}, {50, 39}, {48, 14}
    };

    std::string cornerColors[8] = { "URF", "ULF", "ULB", "URB", "DRF", "DLF", "DLB", "DRB" };
    std::string edgeColors[12] = { "UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR" };

    for (int i = 0; i < 8; i++) {
        char f1 = facelets[cornerIndices[i][0]];
        char f2 = facelets[cornerIndices[i][1]];
        char f3 = facelets[cornerIndices[i][2]];

        uint8_t orientation = 0;
        if (f1 == 'U' || f1 == 'D') orientation = 0;
        else if (f2 == 'U' || f2 == 'D') orientation = 1;
        else if (f3 == 'U' || f3 == 'D') orientation = 2;

        rez.CornerOrientation[i] = orientation;

        std::string pieceName = "";
        if (orientation == 0) pieceName = std::string(1, f1) + f2 + f3;
        else if (orientation == 1) pieceName = std::string(1, f2) + f3 + f1;
        else if (orientation == 2) pieceName = std::string(1, f3) + f1 + f2;

        for (int p = 0; p < 8; p++) {
            if (pieceName.find(cornerColors[p][0]) != std::string::npos &&
                pieceName.find(cornerColors[p][1]) != std::string::npos &&
                pieceName.find(cornerColors[p][2]) != std::string::npos) {
                rez.CornerPermutation[i] = p;
                break;
            }
        }
    }

    bool usedE[12] = { false };
    for (int i = 0; i < 12; i++) {
        char a = facelets[edgeIndices[i][0]];
        char b = facelets[edgeIndices[i][1]];

        int piece = -1;
        int ori = 0;

        for (int p = 0; p < 12; p++) {
            if (a == edgeColors[p][0] && b == edgeColors[p][1]) { piece = p; ori = 0; break; }
            if (a == edgeColors[p][1] && b == edgeColors[p][0]) { piece = p; ori = 1; break; }
        }
        if (piece == -1) throw std::runtime_error("Edge invalid at index " + std::to_string(i));
        if (usedE[piece]) throw std::runtime_error("Edge permutation duplicate: " + std::to_string(piece));

        usedE[piece] = true;
        rez.EdgePermutation[i] = piece;
        rez.EdgeOrientation[i] = ori;
    }

    return rez;
}