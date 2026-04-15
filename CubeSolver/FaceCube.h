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



class FaceCube {
    public:
    char facelets[54];

public:
   

    void  Facelets(string scrambledCube);
    Cubie toCubieCube();
};