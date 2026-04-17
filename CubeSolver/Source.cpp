#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h> 

#include "FaceCube.h"
#include "CubieCube.h"
#include "Search.h"
#include "Tables.h"

using namespace std;

std::string parseWenglorNet(const std::string& net) {
    std::string urfdlb = "";
    urfdlb.reserve(54);

    urfdlb += net.substr(0, 9);
    for (int r = 0; r < 3; r++) urfdlb += net.substr(9 + r * 12 + 6, 3);
    for (int r = 0; r < 3; r++) urfdlb += net.substr(9 + r * 12 + 3, 3);
    urfdlb += net.substr(45, 9);
    for (int r = 0; r < 3; r++) urfdlb += net.substr(9 + r * 12 + 0, 3);
    for (int r = 0; r < 3; r++) urfdlb += net.substr(9 + r * 12 + 9, 3);

    return urfdlb;
}

int main() {
    Cubie initHelper;
    initHelper.initMoves();

    ifstream inputFile("input.txt");
    ofstream outputFile("solutions.txt");

    if (!inputFile.is_open()) {
        cout << "Eroare: Nu pot deschide input.txt\n";
        return 1;
    }

    vector<string> scrambledCubes;
    string line;

    while (std::getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (!line.empty()) {
            scrambledCubes.push_back(line);
        }
    }

    Tables::init();
    vector<string> solutions(scrambledCubes.size());
    int solvedCount = 0;

#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < (int)scrambledCubes.size(); ++i) {
        try {
            FaceCube localFaceCube;
            Search localSolver;

            std::string urfdlbFormat = parseWenglorNet(scrambledCubes[i]);
            localFaceCube.Facelets(urfdlbFormat);

            std::string sol = localSolver.solve(localFaceCube.toCubieCube());
            solutions[i] = sol;
            cout << solutions[i] << endl;
        }
        catch (const std::exception& e) {
            solutions[i] = "ERROR";
        }

#pragma omp atomic
        solvedCount++;

     
    }
    std::cout << "\n";

    for (const auto& sol : solutions) {
        outputFile << sol << "\n";
    }

    inputFile.close();
    outputFile.close();

    return 0;
}