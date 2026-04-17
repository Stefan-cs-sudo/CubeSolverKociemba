#pragma once
#include "CubieCube.h"
#include "Tables.h"

class CoordCube {
public:
    int twist;
    int flip;
    int udslice;
    int cp;
    int ep;
    int udslicePhase2;

    CoordCube(Cubie c);
    void move(int m);
};