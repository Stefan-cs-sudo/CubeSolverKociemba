#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <filesystem>
#include "CubieCube.h"
#include"Tables.h"
#include "Constants.h"
using namespace std;

class Search {
    
    vector<int> currentPath;

public:
    Search() {}

    
    void solve(CoordCube cc);

private:
   
    bool searchPhase1(CoordCube node, int depthToGoal, int lastMove);

    bool searchPhase2(CoordCube node, int depthToGoal, int lastMove);
};