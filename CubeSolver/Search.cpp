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
std::string Search::solve(CoordCube cc) {
    currentPath.clear();

    twistS[0] = cc.twist;
    flipS[0] = cc.flip;
    sliceS[0] = cc.udslice;
    cpS[0] = cc.cp;
    epS[0] = cc.ep;
    slice2S[0] = cc.udslicePhase2;

    int initialDist = std::max({
        (int)Tables::Slice_Twist_Prun[sliceS[0] * 2187 + twistS[0]],
        (int)Tables::Slice_Flip_Prun[sliceS[0] * 2048 + flipS[0]],
        (int)Tables::Twist_Flip_Prun[twistS[0] * 2048 + flipS[0]]
        });
    std::cout << "Start solve, initialDist=" << initialDist << "\n";
    for (int depth = initialDist; depth <= 12; depth++) {
        nodes1 = 0;
        nodes2 = 0;
        std::cout << "Incerc depth=" << depth << "\n";
        if (searchPhase1(0, depth, -1, -1)) {
            // currentPath conține Phase1 + Phase2 (pentru că phase2 face push în același vector)
            return pathToAlgorithm(currentPath);
        }
    }

    return "Error: no solution found (depth<=12)";
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

    // dacă am ajuns în G1 (Phase1 goal), încercăm Phase2
    if (slice == 0 && twist == 0 && flip == 0) {
        int slice2 = slice2S[depth];
        int cp = cpS[depth];
        int ep = epS[depth];

        int h2 = std::max(
            (int)Tables::Slice_CP_Prun[slice2 * 40320 + cp],
            (int)Tables::Slice_EP_Prun[slice2 * 40320 + ep]
        );

        // Phase2 trebuie să încapă în pașii rămași din Phase1 (depthToGoal)
        // aici noi tratăm depthToGoal ca "câți pași mai ai voie în Phase1 până la limita curentă"
        if (h2 > depthToGoal) return false;

        // IMPORTANT:
        // dacă depthToGoal > 0 și ești deja în G1, nu mai extinde Phase1.
        // return false și lasă IDDFS să găsească altă intrare în G1 la lungimea potrivită.
        if (depthToGoal != 0) return false;

        // depthToGoal == 0: rulează Phase2
        for (int d2 = h2; d2 <= 18; d2++) {
            if (searchPhase2(depth, d2, -1)) return true;
        }
        return false;
    }

    if (depthToGoal == 0) return false;

    for (int m = 0; m < 18; m++) {
        if (pruneMove2(prevMove, lastMove, m)) continue;

        int nd = depth + 1;

        twistS[nd] = Tables::TwistMove[twist * 18 + m];
        flipS[nd] = Tables::FlipMove[flip * 18 + m];
        sliceS[nd] = Tables::UDSliceMove[slice * 18 + m];

        if (isPhase2Move(m)) {
            cpS[nd] = Tables::CPMove[cpS[depth] * 18 + m];
            epS[nd] = Tables::EPMove[epS[depth] * 18 + m];
            slice2S[nd] = Tables::UDSlicePhase2Move[slice2S[depth] * 18 + m];
        }
        else {
            cpS[nd] = cpS[depth];
            epS[nd] = epS[depth];
            slice2S[nd] = slice2S[depth];
        }

        currentPath.push_back(m);
        if (searchPhase1(nd, depthToGoal - 1, m, lastMove)) return true;
        currentPath.pop_back();
    }

    return false;
}
bool Search::searchPhase2(int depth, int depthToGoal, int lastMove) {
    int phase2Moves[10] = { U1, U2, U3, D1, D2, D3, R2, L2, F2, B2 };
    nodes2++;
    if ((nodes2 & ((1ull << 22) - 1)) == 0) std::cout << "nodes1=" << nodes2 << "\n"; // la ~4M
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