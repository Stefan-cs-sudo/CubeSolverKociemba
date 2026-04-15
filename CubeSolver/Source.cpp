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
std::string parseWenglorNet(const std::string& net) {
    std::string urfdlb = "";
    urfdlb.reserve(54);

    // 1. U (Up) - primele 9 caractere (0-8)
    urfdlb += net.substr(0, 9);

    // 2. R (Right) - al 3-lea bloc de 3 din fiecare rand al panglicii (L, F, R, B)
    for (int r = 0; r < 3; r++) urfdlb += net.substr(9 + r * 12 + 6, 3);

    // 3. F (Front) - al 2-lea bloc de 3 din fiecare rand
    for (int r = 0; r < 3; r++) urfdlb += net.substr(9 + r * 12 + 3, 3);

    // 4. D (Down) - ultimele 9 caractere (45-53)
    urfdlb += net.substr(45, 9);

    // 5. L (Left) - primul bloc de 3 din fiecare rand
    for (int r = 0; r < 3; r++) urfdlb += net.substr(9 + r * 12 + 0, 3);

    // 6. B (Back) - al 4-lea bloc de 3 din fiecare rand
    for (int r = 0; r < 3; r++) urfdlb += net.substr(9 + r * 12 + 9, 3);

    return urfdlb;
}
static void selfTestCoords() {
    for (int i = 0; i < 2187; i++) {
        Cubie c;
        c.setTwistCoord(i);
        if (c.getTwistCoord() != i) {
            std::cout << "Twist mismatch at " << i << "\n";
            break;
        }
    }
    for (int i = 0; i < 2048; i++) {
        Cubie c;
        c.setFlipCoord(i);
        if (c.getFlipCoord() != i) {
            std::cout << "Flip mismatch at " << i << "\n";
            break;
        }
    }
    for (int i = 0; i < 495; i++) {
        Cubie c;
        c.setUDSliceCoord(i);
        if (c.getUDSliceCoord() != i) {
            std::cout << "UDSlice mismatch at " << i << "\n";
            break;
        }
    }
    for (int i = 0; i < 24; i++) {
        Cubie c;
        c.setUDSlicePhase2Coord(i);
        if (c.getUDSlicePhase2Coord() != i) {
            std::cout << "UDSlicePhase2 mismatch at " << i << "\n";
            break;
        }
    }
}

// #include <omp.h> 

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
        if (!line.empty() && line.back() == '\r') line.pop_back(); // CRLF fix

        if (!line.empty()) {
            scrambledCubes.push_back(line);
        }
    }
    Tables tabele;
    
    selfTestCoords(); // cel pe care l-ai pus deja

    FaceCube StringtoCubie;
    Search Solver;


    vector<string> solutions(scrambledCubes.size());


    // #pragma omp parallel for
    for (int i = 0; i < (int)scrambledCubes.size(); ++i) {
        try {
            if (scrambledCubes[i].size() != 54) {
                std::cerr << "Linie invalida la " << i << "\n";
                continue;
            }

            // 1. Traducem din Wenglor (panglica) in standard Kociemba
            std::string urfdlbFormat = parseWenglorNet(scrambledCubes[i]);

            // 2. Mapeaza fetele
            StringtoCubie.Facelets(urfdlbFormat);

            // 3. Rezolva
            std::string sol = Solver.solve(StringtoCubie.toCubieCube());
            solutions[i] = sol;

            std::cout << "Cube " << i << ": " << scrambledCubes[i] << "\n";
            std::cout << "Solutie: " << sol << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare la cube " << i << ": " << e.what() << "\n";
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