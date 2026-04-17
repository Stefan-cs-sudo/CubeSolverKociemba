#include "Search.h"
#include "Constants.h"
#include <algorithm>

static inline const char* moveToString(int m) {
    switch (m) {
    case Moves::U1: return "U";
    case Moves::U2: return "U2";
    case Moves::U3: return "U'";
    case Moves::R1: return "R";
    case Moves::R2: return "R2";
    case Moves::R3: return "R'";
    case Moves::L1: return "L";
    case Moves::L2: return "L2";
    case Moves::L3: return "L'";
    case Moves::B1: return "B";
    case Moves::B2: return "B2";
    case Moves::B3: return "B'";
    case Moves::D1: return "D";
    case Moves::D2: return "D2";
    case Moves::D3: return "D'";
    case Moves::F1: return "F";
    case Moves::F2: return "F2";
    case Moves::F3: return "F'";
    default: return "?";
    }
}

static inline std::string pathToAlgorithm(const uint_fast8_t currentPath[], int size) {
    std::string out;
    out.reserve(size * 3);

    for (int i = 0; i < size; i++) {
        if (i > 0) out.push_back(' ');
        out += moveToString(currentPath[i]);
    }
    return out;
}

static const int moveFace[18] = { 0,0,0, 1,1,1, 2,2,2, 3,3,3, 4,4,4, 5,5,5 };
static const int oppFace[6] = { 4, 2, 1, 5, 0, 3 };

static inline bool pruneMove(int lastMove, int move) {   //daca ultima mutare a fost U ,nu mai are rost sa fie U1 sau U2 sau U3 urmatoarea 
    if (lastMove == -1) return false;
    int lastFace = moveFace[lastMove];    
    int movingFace = moveFace[move];

    if (lastFace == movingFace) return true; 
    if (movingFace == oppFace[lastFace] && movingFace < lastFace) return true;
        
    return false; // U D D U 
}

static inline bool pruneMove2(int prevMove, int lastMove, int m) {
    if (pruneMove(lastMove, m)) return true;
    if (prevMove == -1 || lastMove == -1) return false;

    int prevFace = moveFace[prevMove];
    int lastFace = moveFace[lastMove];
    int movingFace = moveFace[m];

    if (prevFace == movingFace && lastFace == oppFace[movingFace]) return true;    // U D U D

    return false;
}

std::string Search::solve(Cubie start) {
    startCube = start;
    path_len = 0;

    twistS[0] = start.getTwistCoord();
    flipS[0] = start.getFlipCoord();
    sliceS[0] = start.getUDSliceCoord();

    int initialDist = std::max({
        (int)Tables::Slice_Twist_Prun[sliceS[0] * 2187 + twistS[0]],
        (int)Tables::Slice_Flip_Prun[sliceS[0] * 2048 + flipS[0]],
        (int)Tables::Twist_Flip_Prun[twistS[0] * 2048 + flipS[0]]
        });

    for (int total = initialDist; total <= 30; total++) {
        int d1min = initialDist;
        int d1max = std::min(12, total);

        for (int movesForPhase1 = d1min; movesForPhase1 <= d1max; movesForPhase1++) {
            int movesforPhase2 = total - movesForPhase1;
            if (movesforPhase2 < 0 || movesforPhase2 > 18) continue;

            phase2MaxDepth = movesforPhase2;
            path_len = 0;

            if (searchPhase1(0, movesForPhase1, -1, -1)) {
                return pathToAlgorithm(currentPath, path_len);
            }
        }
    }

    return "Error: nu-sa gasit o solutie pana in 30 mutari";
}

bool Search::searchPhase1(int depth, int depthToGoal, int lastMove, int prevMove) {
    int twist = twistS[depth];
    int flip = flipS[depth];
    int slice = sliceS[depth];

    uint16_t p1 = Tables::Slice_Twist_Prun[slice * 2187 + twist];
    uint16_t p2 = Tables::Slice_Flip_Prun[slice * 2048 + flip];
    uint16_t p3 = Tables::Twist_Flip_Prun[twist * 2048 + flip];

    uint16_t heuristic = std::max({ p1, p2, p3 });
    if (heuristic > depthToGoal) return false;

    if (slice == 0 && twist == 0 && flip == 0) {
        if (depthToGoal != 0) return false;

        Cubie realCube = startCube;
        for (int i = 0; i < path_len; i++) {
            realCube.applyMove(Cubie::Mutari[currentPath[i]]);
        }

        int cp = realCube.getCPCoord();
        int ep = realCube.getEPCoord();
        int slice2 = realCube.getUDSlicePhase2Coord();

        int p4 = (int)Tables::Slice_CP_Prun[slice2 * 40320 + cp];
        int p5 = (int)Tables::Slice_EP_Prun[slice2 * 40320 + ep];
        int heuristic2 = std::max(p4, p5);

        if (phase2MaxDepth == 0) {
            return (cp == 0 && ep == 0 && slice2 == 0);
        }

        if (heuristic2 > phase2MaxDepth) return false;

        cpS[depth] = cp;
        epS[depth] = ep;
        slice2S[depth] = slice2;

        return searchPhase2(depth, phase2MaxDepth, -1);
    }

    if (depthToGoal == 0) return false;

    int twistBase = twist * 18;
    int flipBase = flip * 18;
    int sliceBase = slice * 18;
    int targetDepth = depthToGoal - 1;

    struct MoveEval {
        int m, h, n_twist, n_flip, n_slice;
    };

    MoveEval movesToTry[18];
    int validMovesCount = 0;

    for (int m = 0; m < 18; m++) {
        if (pruneMove2(prevMove, lastMove, m)) continue;

        int n_twist = Tables::TwistMove[twistBase + m];
        int n_flip = Tables::FlipMove[flipBase + m];

        int p3_eval = Tables::Twist_Flip_Prun[n_twist * 2048 + n_flip];
        if (p3_eval > targetDepth) continue;

        int n_slice = Tables::UDSliceMove[sliceBase + m];

        int p1_eval = Tables::Slice_Twist_Prun[n_slice * 2187 + n_twist];
        if (p1_eval > targetDepth) continue;

        int p2_eval = Tables::Slice_Flip_Prun[n_slice * 2048 + n_flip];
        if (p2_eval > targetDepth) continue;

        int h_next = std::max({ p1_eval, p2_eval, p3_eval });
        movesToTry[validMovesCount++] = { m, h_next, n_twist, n_flip, n_slice };
    }

    for (int i = 1; i < validMovesCount; i++) {
        MoveEval key = movesToTry[i];
        int j = i - 1;
        while (j >= 0 && movesToTry[j].h > key.h) {
            movesToTry[j + 1] = movesToTry[j];
            j--;
        }
        movesToTry[j + 1] = key;
    }

    int nd = depth + 1;
    for (int i = 0; i < validMovesCount; i++) {
        twistS[nd] = movesToTry[i].n_twist;
        flipS[nd] = movesToTry[i].n_flip;
        sliceS[nd] = movesToTry[i].n_slice;

        currentPath[path_len++] = movesToTry[i].m;

        if (searchPhase1(nd, targetDepth, movesToTry[i].m, lastMove)) return true;

        path_len--;
    }

    return false;
}

bool Search::searchPhase2(int depth, int depthToGoal, int lastMove) {
    static const int phase2Moves[10] = { U1, U2, U3, D1, D2, D3, R2, L2, F2, B2 };

    int cp = cpS[depth];
    int ep = epS[depth];
    int s2 = slice2S[depth];

    uint16_t p1 = Tables::Slice_CP_Prun[s2 * 40320 + cp];
    uint16_t p2 = Tables::Slice_EP_Prun[s2 * 40320 + ep];
    uint16_t heuristic = std::max(p1, p2);

    if (heuristic > depthToGoal) return false;

    if (depthToGoal == 0) {
        return (cp == 0 && ep == 0 && s2 == 0);
    }

    for (int i = 0; i < 10; i++) {
        int m = phase2Moves[i];
        if (pruneMove(lastMove, m)) continue;

        int nd = depth + 1;

        cpS[nd] = Tables::CPMove[cp * 18 + m];
        epS[nd] = Tables::EPMove[ep * 18 + m];
        slice2S[nd] = Tables::UDSlicePhase2Move[s2 * 18 + m];

        currentPath[path_len++] = m;
        if (searchPhase2(nd, depthToGoal - 1, m)) return true;
        path_len--;
    }

    return false;
}