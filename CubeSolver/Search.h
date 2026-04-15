#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CubieCube.h"
#include "Tables.h"
#include "Constants.h"
using namespace std;

class Search {
    uint_fast8_t currentPath[32];
    uint_fast8_t path_len=0;
   

    static constexpr int MAXD = 32;
    int twistS[MAXD], flipS[MAXD], sliceS[MAXD];
    int cpS[MAXD], epS[MAXD], slice2S[MAXD];

    int phase2MaxDepth = 0;
    Cubie startCube; 

public:
  string solve(Cubie start); 

private:
    bool searchPhase1(int depth, int depthToGoal, int lastMove, int prevMove);
    bool searchPhase2(int depth, int depthToGoal, int lastMove);
};