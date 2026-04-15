#include "Search.h"
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <filesystem>
#include "CubieCube.h"
#include"Tables.h"
#include "Constants.h"

void Search::solve(CoordCube cc) {
    currentPath.clear();


    int initialDist = max(Tables::Slice_Twist_Prun[cc.udslice * 2187 + cc.twist],
        Tables::Slice_Flip_Prun[cc.udslice * 2048 + cc.flip]);


    for (int depth = initialDist; depth <= 12; depth++) {
        cout << "Cautam solutii de adancime " << depth << "..." << endl;

        if (searchPhase1(cc, depth, -1)) {
            cout << "Faza 1 terminata! Mutarile sunt: ";
            for (int move : currentPath) cout << move << " ";
            cout << endl;


            return;
        }
    }
}

bool Search::searchPhase1(CoordCube node, int depthToGoal, int lastMove) {


    if (depthToGoal == 0) {
        if (node.udslice == 0 && node.twist == 0 && node.flip == 0) {


            int hCP = Tables::Slice_CP_Prun[node.udslicePhase2 * 40320 + node.cp];
            int hEP = Tables::Slice_EP_Prun[node.udslicePhase2 * 40320 + node.ep];
            int initialPhase2Dist = max(hCP, hEP);


            for (int depth2 = initialPhase2Dist; depth2 <= 18; depth2++) {


                if (searchPhase2(node, depth2, lastMove)) {
                    return true;
                }
            }

        }
        return false;
    }


    for (int m = 0; m < 18; m++) {


        if (lastMove / 3 == m / 3) continue;


        CoordCube nextNode = node;
        nextNode.move(m);


        currentPath.push_back(m);


        if (searchPhase1(nextNode, depthToGoal - 1, m)) {
            return true;
        }


        currentPath.pop_back();
    }

    return false;
}

bool Search::searchPhase2(CoordCube node, int depthToGoal, int lastMove) {
    int phase2Moves[10] = { Moves::U1, Moves::U2, Moves::U3,
                   Moves::D1, Moves::D2, Moves::D3,
                   Moves::R2, Moves::L2, Moves::F2, Moves::B2 };

    if (depthToGoal == 0) {
        return (node.cp == 0 && node.ep == 0 && node.udslicePhase2 == 0);
    }


    int hCP = Tables::Slice_CP_Prun[node.udslicePhase2 * 40320 + node.cp];
    int hEP = Tables::Slice_EP_Prun[node.udslicePhase2 * 40320 + node.ep];
    int h = max(hCP, hEP);


    if (h > depthToGoal) {
        return false;
    }


    for (int i = 0; i < 10; i++) {
        int m = phase2Moves[i];


        if (lastMove != -1 && (lastMove / 3 == m / 3)) continue;


        CoordCube nextNode = node;
        nextNode.move(m);

        currentPath.push_back(m);


        if (searchPhase2(nextNode, depthToGoal - 1, m)) {
            return true;
        }


        currentPath.pop_back();
    }

    return false;
}