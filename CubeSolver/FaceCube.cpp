#include "FaceCube.h"



void  FaceCube::Facelets(string scrambledCube)
{


    char colorU = scrambledCube[4];
    char colorR = scrambledCube[13];
    char colorF = scrambledCube[22];
    char colorD = scrambledCube[31];
    char colorL = scrambledCube[40];
    char colorB = scrambledCube[49];


    for (int i = 0; i < 54; i++) {
        if (scrambledCube[i] == colorU) facelets[i] = 'U';
        else if (scrambledCube[i] == colorR) facelets[i] = 'R';
        else if (scrambledCube[i] == colorF) facelets[i] = 'F';
        else if (scrambledCube[i] == colorD) facelets[i] = 'D';
        else if (scrambledCube[i] == colorL) facelets[i] = 'L';
        else if (scrambledCube[i] == colorB) facelets[i] = 'B';
    }
}
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



    return rez;
}
