#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CubieCube.h"
#include "Tables.h"
#include "Constants.h"
using namespace std;

class Search {
    std::vector<int> currentPath;
    uint64_t nodes1 = 0, nodes2 = 0;

    static constexpr int MAXD = 32;
    int twistS[MAXD], flipS[MAXD], sliceS[MAXD];
    int cpS[MAXD], epS[MAXD], slice2S[MAXD];

    int phase2MaxDepth = 0;
    Cubie startCube; // Salvam cubul real de la inceput

public:
    std::string solve(Cubie start); // Primeste Cubie in loc de CoordCube

private:
    bool searchPhase1(int depth, int depthToGoal, int lastMove, int prevMove);
    bool searchPhase2(int depth, int depthToGoal, int lastMove);
};