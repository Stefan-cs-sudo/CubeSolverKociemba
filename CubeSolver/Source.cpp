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

    while (std::getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // CRLF fix

        if (!line.empty()) {
            scrambledCubes.push_back(line);
        }
    }
    Tables tabele;
    {
        Cubie solved;          // constructorul pune cubul rezolvat (permutări identitate, orientări 0)
        CoordCube sc(solved);  // coordonate pentru starea rezolvată

        cout << "SOLVED coords: "
            << "twist=" << sc.twist
            << " flip=" << sc.flip
            << " udslice=" << sc.udslice
            << " cp=" << sc.cp
            << " ep=" << sc.ep
            << " udslicePhase2=" << sc.udslicePhase2
            << "\n";
    }
    FaceCube StringtoCubie;
    Search Solver;


    vector<string> solutions(scrambledCubes.size());


    // #pragma omp parallel for
    for (int i = 0; i < (int)scrambledCubes.size(); ++i) {
        try {
            if (scrambledCubes[i].size() != 54) {
                std::cerr << "Linie invalida: cube " << i << " are " << scrambledCubes[i].size() << " caractere\n";
            }
            StringtoCubie.Facelets(scrambledCubes[i]);
            std::string sol = Solver.solve(StringtoCubie.toCubieCube());
            solutions[i] = sol;

            std::cout << "Cube " << i << ": " << scrambledCubes[i] << "\n";
            std::cout << "Solutie: " << sol << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare la cube " << i
                << " (len=" << scrambledCubes[i].size() << "): "
                << e.what() << "\n";
            // optional: continua la urmatorul
            solutions[i] = "ERROR";
        }
    }

    // 3. Scriem solu?iile în ordine în fi?ier
    for (const auto& sol : solutions) {
        outputFile << sol << "\n";
    }

    inputFile.close();
    outputFile.close();

    return 0;
}