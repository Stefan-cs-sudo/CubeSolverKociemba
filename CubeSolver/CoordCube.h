#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <filesystem>
#include "CubieCube.h"
#include"Tables.h"
#include "Constants.h"
class Cubie;

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