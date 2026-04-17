#pragma once
#include <string>
#include "CubieCube.h"

class FaceCube {
public:
    char facelets[54];

    void Facelets(const std::string& scrambledCube);
    Cubie toCubieCube();
};