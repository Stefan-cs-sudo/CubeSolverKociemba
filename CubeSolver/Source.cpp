#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "FaceCube.h"
#include "CubieCube.h"
#include "CoordCube.h"
#include "Search.h"
#define _CRT_SECURE_NO_WARNINGS
#include "Tables.h"
using namespace std;

// #include <omp.h> 

int main() {
   ifstream inputFile("input.txt");
   ofstream outputFile("solutions.txt");
    
    if (!inputFile.is_open()) {
      cout << "Eroare: Nu pot deschide input.txt\n";

        return 1;
    }

   vector<string> scrambledCubes;
    string line;

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            scrambledCubes.push_back(line);
        }
    }
    Tables tabele;

  
    FaceCube StringtoCubie;
    Search Solver;

    
   vector<string> solutions(scrambledCubes.size());

    
    // #pragma omp parallel for
    for (int i = 0; i < scrambledCubes.size(); ++i) {

        StringtoCubie.Facelets(scrambledCubes[i]);
        // Aici vei apela algoritmul t?u pentru fiecare cub
        // solutions[i] = Solver::solve(cubes[i]); 
        Solver.solve(StringtoCubie.toCubieCube());
        // Temporar punem un text de test
        solutions[i] = "";
    }

    // 3. Scriem solu?iile în ordine în fi?ier
    for (const auto& sol : solutions) {
        outputFile << sol << "\n";
    }

    inputFile.close();
    outputFile.close();

    return 0;
}