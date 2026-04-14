#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "FaceCube.h"
#include "CubieCube.h"
#include "CoordCube.h"
#include "Search.h"
#include "Tables.h"
using namespace std;

// #include <omp.h> // Pentru multithreading mai târziu

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
    Tables tabele();

  
    FaceCube StringtoFacelets();

    // Vom salva solu?iile aici pentru a le scrie în ordine la final
   vector<string> solutions(scrambledCubes.size());

    // 2. MAGIC TRICK: Aceast? linie paralelizeaz? bucla for pe toate nucleele procesorului!
    // #pragma omp parallel for
    for (int i = 0; i < scrambledCubes.size(); ++i) {
        // Aici vei apela algoritmul t?u pentru fiecare cub
        // solutions[i] = Solver::solve(cubes[i]); 

        // Temporar punem un text de test
        solutions[i] = "U R2 F B R B2 R U2 L B2 R U' D' R2 F R' L B2 U2 F2";
    }

    // 3. Scriem solu?iile în ordine în fi?ier
    for (const auto& sol : solutions) {
        outputFile << sol << "\n";
    }

    inputFile.close();
    outputFile.close();

    return 0;
}