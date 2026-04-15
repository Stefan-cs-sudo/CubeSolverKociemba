#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "FaceCube.h"
#include "CubieCube.h"
#include "CoordCube.h"
#include "Search.h"
 #include <omp.h> 
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
    
    

    FaceCube StringtoCubie;
    


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
            cout << sol << endl;
        }
        catch (const std::exception& e) {
            solutions[i] = "ERROR";
        }

        // Actualizam progresul in siguranta intre thread-uri
#pragma omp atomic
        solvedCount++;

        // Afisam progresul doar o data la 10 cuburi (sau 100) ca sa nu incetinim procesorul
        if (solvedCount % 10 == 0 || solvedCount == scrambledCubes.size()) {
            // '\r' face ca textul sa se suprascrie pe aceeasi linie
            std::cout << "\rProgres: " << solvedCount << " / " << scrambledCubes.size() << " cuburi rezolvate.";
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