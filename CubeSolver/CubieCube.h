#pragma once
#include <cstdint>
#include "Constants.h"

class Cubie {
public:
    short CornerPermutation[8] = {};
    uint8_t CornerOrientation[8] = {};
    short EdgePermutation[12] = {};
    uint8_t EdgeOrientation[12] = {};

    static Cubie Mutari[18];

    Cubie();

    void initMoves();
    void applyMove(Cubie mutare);
    void multiply(Cubie mul);

    int getTwistCoord();
    int getFlipCoord();
    int getUDSliceCoord();
    int getCPCoord();
    int getEPCoord();
    int getUDSlicePhase2Coord();

    void setTwistCoord(int twistToUnpack);
    void setFlipCoord(int FlipToUnpack);
    void setUDSliceCoord(int index);
    void setCPCoord(int CPtoUnpack);
    void setEPCoord(int EPtoUnpack);
    void setUDSlicePhase2Coord(int UDMidPhase2ToUnpack);
    void setUDSliceRestPhase2Coord(int UDSliceRestToUnpack);

private:
    int combinations(int n, int k);
};