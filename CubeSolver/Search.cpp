#include "Search.h"
#include "Constants.h"


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

static inline std::string pathToAlgorithm(const std::vector<int>& path) {
    std::string out;
    out.reserve(path.size() * 3);

    for (size_t i = 0; i < path.size(); i++) {
        if (i) out.push_back(' ');
        out += moveToString(path[i]);
    }
    return out;
}




static inline int faceOfMove(int m) {
    // Moves: U(0..2), R(3..5), L(6..8), B(9..11), D(12..14), F(15..17)
    return m / 3; // 0..5
}

static inline int oppositeFace(int f) {
    // U(0) <-> D(4), R(1) <-> L(2), B(3) <-> F(5)
    static const int opp[6] = { 4, 2, 1, 5, 0, 3 };
    return opp[f];
}

static inline bool pruneMove(int lastMove, int m) {
    if (lastMove == -1) return false;

    int lf = faceOfMove(lastMove);
    int mf = faceOfMove(m);

    // same face twice in a row
    if (lf == mf) return true;

    // opposite face pruning (safe one-direction rule)
    if (mf == oppositeFace(lf) && mf < lf) return true;

    return false;
}

static inline bool pruneMove2(int prevMove, int lastMove, int m) {
    if (pruneMove(lastMove, m)) return true;
    if (prevMove == -1 || lastMove == -1) return false;

    int pf = faceOfMove(prevMove);
    int lf = faceOfMove(lastMove);
    int mf = faceOfMove(m);

    // X - opposite(X) - X  => taie
    if (pf == mf && lf == oppositeFace(mf)) return true;

    return false;
}

static inline bool isPhase2Move(int m) {
    return (m == U1 || m == U2 || m == U3 ||
        m == D1 || m == D2 || m == D3 ||
        m == R2 || m == L2 || m == F2 || m == B2);
}
std::string Search::solve(Cubie start) {
    startCube = start;
    currentPath.clear();

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

        for (int d1 = d1min; d1 <= d1max; d1++) {
            int d2 = total - d1;
            if (d2 < 0 || d2 > 18) continue;

            nodes1 = 0; nodes2 = 0;
            phase2MaxDepth = d2;
            currentPath.clear();

            if (searchPhase1(0, d1, -1, -1)) {
                return pathToAlgorithm(currentPath);
            }
        }
    }

    return "Error: no solution found (totalDepth<=30)";
}

bool Search::searchPhase1(int depth, int depthToGoal, int lastMove, int prevMove) {
    nodes1++;

    int twist = twistS[depth];
    int flip = flipS[depth];
    int slice = sliceS[depth];

    int h = std::max({
        (int)Tables::Slice_Twist_Prun[slice * 2187 + twist],
        (int)Tables::Slice_Flip_Prun[slice * 2048 + flip],
        (int)Tables::Twist_Flip_Prun[twist * 2048 + flip]
        });
    if (h > depthToGoal) return false;

    // Am ajuns in G1 (Phase1 goal)
    if (slice == 0 && twist == 0 && flip == 0) {
        if (depthToGoal != 0) return false; // Trebuie sa respectam exact d1

        // RECONSTRUIM CUBUL REAL PENTRU COORDONATE PHASE 2
        Cubie realCube = startCube;
        for (int move : currentPath) {
            realCube.applyMove(Cubie::Mutari[move]);
        }

        int cp = realCube.getCPCoord();
        int ep = realCube.getEPCoord();
        int slice2 = realCube.getUDSlicePhase2Coord();

        int h2 = std::max(
            (int)Tables::Slice_CP_Prun[slice2 * 40320 + cp],
            (int)Tables::Slice_EP_Prun[slice2 * 40320 + ep]
        );

        if (phase2MaxDepth == 0) {
            return (cp == 0 && ep == 0 && slice2 == 0);
        }

        if (h2 > phase2MaxDepth) return false;

        // Punem coordonatele reale ca sa le poata prelua Phase 2
        cpS[depth] = cp;
        epS[depth] = ep;
        slice2S[depth] = slice2;

        return searchPhase2(depth, phase2MaxDepth, -1);
    }

    if (depthToGoal == 0) return false;

    for (int m = 0; m < 18; m++) {
        if (pruneMove2(prevMove, lastMove, m)) continue;

        int nd = depth + 1;
        twistS[nd] = Tables::TwistMove[twist * 18 + m];
        flipS[nd] = Tables::FlipMove[flip * 18 + m];
        sliceS[nd] = Tables::UDSliceMove[slice * 18 + m];

        // FARA cp/ep/slice2 false aici.

        currentPath.push_back(m);
        if (searchPhase1(nd, depthToGoal - 1, m, lastMove)) return true;
        currentPath.pop_back();
    }

    return false;
}
bool Search::searchPhase2(int depth, int depthToGoal, int lastMove) {
    int phase2Moves[10] = { U1, U2, U3, D1, D2, D3, R2, L2, F2, B2 };
    nodes2++;
   
    int cp = cpS[depth];
    int ep = epS[depth];
    int s2 = slice2S[depth];

    int h = std::max(
        Tables::Slice_CP_Prun[s2 * 40320 + cp],
        Tables::Slice_EP_Prun[s2 * 40320 + ep]
    );
    if (h > depthToGoal) return false;

    if (depthToGoal == 0) {
        return (cp == 0 && ep == 0 && s2 == 0);
    }

    for (int i = 0; i < 10; i++) {
        int m = phase2Moves[i];
        if (pruneMove(lastMove, m)) continue;

        int nd = depth + 1;

        // phase2 moves sunt toate în subset, deci update complet:
        twistS[nd] = Tables::TwistMove[twistS[depth] * 18 + m];
        flipS[nd] = Tables::FlipMove[flipS[depth] * 18 + m];
        sliceS[nd] = Tables::UDSliceMove[sliceS[depth] * 18 + m];

        cpS[nd] = Tables::CPMove[cp * 18 + m];
        epS[nd] = Tables::EPMove[ep * 18 + m];
        slice2S[nd] = Tables::UDSlicePhase2Move[s2 * 18 + m];

        currentPath.push_back(m);
        if (searchPhase2(nd, depthToGoal - 1, m)) return true;
        currentPath.pop_back();
    }

    return false;
}