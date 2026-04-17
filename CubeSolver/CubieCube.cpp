#include "CubieCube.h"

Cubie Cubie::Mutari[18];

Cubie::Cubie() {
    for (size_t i = 0; i < 8; i++) {
        CornerPermutation[i] = i;
        CornerOrientation[i] = 0;
    }
    for (size_t i = 0; i < 12; i++) {
        EdgePermutation[i] = i;
        EdgeOrientation[i] = 0;
    }
}

void Cubie::initMoves() {
    Cubie U1;
    U1.CornerPermutation[URF] = URB; U1.CornerPermutation[ULF] = URF; U1.CornerPermutation[ULB] = ULF; U1.CornerPermutation[URB] = ULB;
    U1.EdgePermutation[UF] = UR; U1.EdgePermutation[UL] = UF; U1.EdgePermutation[UB] = UL; U1.EdgePermutation[UR] = UB;
    Mutari[Moves::U1] = U1;

    Cubie U2;
    U2.CornerPermutation[URF] = ULB; U2.CornerPermutation[ULF] = URB; U2.CornerPermutation[ULB] = URF; U2.CornerPermutation[URB] = ULF;
    U2.EdgePermutation[UF] = UB; U2.EdgePermutation[UL] = UR; U2.EdgePermutation[UB] = UF; U2.EdgePermutation[UR] = UL;
    Mutari[Moves::U2] = U2;

    Cubie U3;
    U3.CornerPermutation[URF] = ULF; U3.CornerPermutation[ULF] = ULB; U3.CornerPermutation[ULB] = URB; U3.CornerPermutation[URB] = URF;
    U3.EdgePermutation[UF] = UL; U3.EdgePermutation[UL] = UB; U3.EdgePermutation[UB] = UR; U3.EdgePermutation[UR] = UF;
    Mutari[Moves::U3] = U3;

    Cubie R1;
    R1.CornerPermutation[URF] = DRF; R1.CornerPermutation[DRF] = DRB; R1.CornerPermutation[DRB] = URB; R1.CornerPermutation[URB] = URF;
    R1.CornerOrientation[URF] = 2; R1.CornerOrientation[URB] = 1; R1.CornerOrientation[DRF] = 1; R1.CornerOrientation[DRB] = 2;
    R1.EdgePermutation[FR] = DR; R1.EdgePermutation[DR] = BR; R1.EdgePermutation[BR] = UR; R1.EdgePermutation[UR] = FR;
    Mutari[Moves::R1] = R1;

    Cubie R2;
    R2.CornerPermutation[URF] = DRB; R2.CornerPermutation[DRF] = URB; R2.CornerPermutation[DRB] = URF; R2.CornerPermutation[URB] = DRF;
    R2.EdgePermutation[FR] = BR; R2.EdgePermutation[DR] = UR; R2.EdgePermutation[BR] = FR; R2.EdgePermutation[UR] = DR;
    Mutari[Moves::R2] = R2;

    Cubie R3;
    R3.CornerPermutation[URF] = URB; R3.CornerPermutation[DRF] = URF; R3.CornerPermutation[DRB] = DRF; R3.CornerPermutation[URB] = DRB;
    R3.CornerOrientation[URF] = 2; R3.CornerOrientation[URB] = 1; R3.CornerOrientation[DRF] = 1; R3.CornerOrientation[DRB] = 2;
    R3.EdgePermutation[FR] = UR; R3.EdgePermutation[DR] = FR; R3.EdgePermutation[BR] = DR; R3.EdgePermutation[UR] = BR;
    Mutari[Moves::R3] = R3;

    Cubie L1;
    L1.CornerPermutation[ULF] = ULB; L1.CornerPermutation[ULB] = DLB; L1.CornerPermutation[DLB] = DLF; L1.CornerPermutation[DLF] = ULF;
    L1.CornerOrientation[ULF] = 1; L1.CornerOrientation[ULB] = 2; L1.CornerOrientation[DLB] = 1; L1.CornerOrientation[DLF] = 2;
    L1.EdgePermutation[FL] = UL; L1.EdgePermutation[UL] = BL; L1.EdgePermutation[BL] = DL; L1.EdgePermutation[DL] = FL;
    Mutari[Moves::L1] = L1;

    Cubie L2;
    L2.CornerPermutation[ULF] = DLB; L2.CornerPermutation[ULB] = DLF; L2.CornerPermutation[DLB] = ULF; L2.CornerPermutation[DLF] = ULB;
    L2.EdgePermutation[FL] = BL; L2.EdgePermutation[UL] = DL; L2.EdgePermutation[BL] = FL; L2.EdgePermutation[DL] = UL;
    Mutari[Moves::L2] = L2;

    Cubie L3;
    L3.CornerPermutation[ULF] = DLF; L3.CornerPermutation[DLF] = DLB; L3.CornerPermutation[DLB] = ULB; L3.CornerPermutation[ULB] = ULF;
    L3.CornerOrientation[ULF] = 1; L3.CornerOrientation[ULB] = 2; L3.CornerOrientation[DLB] = 1; L3.CornerOrientation[DLF] = 2;
    L3.EdgePermutation[FL] = DL; L3.EdgePermutation[UL] = FL; L3.EdgePermutation[BL] = UL; L3.EdgePermutation[DL] = BL;
    Mutari[Moves::L3] = L3;

    Cubie B1;
    B1.CornerPermutation[URB] = DRB; B1.CornerPermutation[DRB] = DLB; B1.CornerPermutation[DLB] = ULB; B1.CornerPermutation[ULB] = URB;
    B1.CornerOrientation[URB] = 2; B1.CornerOrientation[DRB] = 1; B1.CornerOrientation[DLB] = 2; B1.CornerOrientation[ULB] = 1;
    B1.EdgePermutation[BL] = UB; B1.EdgePermutation[UB] = BR; B1.EdgePermutation[BR] = DB; B1.EdgePermutation[DB] = BL;
    B1.EdgeOrientation[BL] = 1; B1.EdgeOrientation[DB] = 1; B1.EdgeOrientation[BR] = 1; B1.EdgeOrientation[UB] = 1;
    Mutari[Moves::B1] = B1;

    Cubie B2;
    B2.CornerPermutation[URB] = DLB; B2.CornerPermutation[DLB] = URB; B2.CornerPermutation[ULB] = DRB; B2.CornerPermutation[DRB] = ULB;
    B2.EdgePermutation[BL] = BR; B2.EdgePermutation[BR] = BL; B2.EdgePermutation[UB] = DB; B2.EdgePermutation[DB] = UB;
    Mutari[Moves::B2] = B2;

    Cubie B3;
    B3.CornerPermutation[URB] = ULB; B3.CornerPermutation[ULB] = DLB; B3.CornerPermutation[DLB] = DRB; B3.CornerPermutation[DRB] = URB;
    B3.CornerOrientation[URB] = 2; B3.CornerOrientation[DRB] = 1; B3.CornerOrientation[DLB] = 2; B3.CornerOrientation[ULB] = 1;
    B3.EdgePermutation[BL] = DB; B3.EdgePermutation[DB] = BR; B3.EdgePermutation[BR] = UB; B3.EdgePermutation[UB] = BL;
    B3.EdgeOrientation[BL] = 1; B3.EdgeOrientation[DB] = 1; B3.EdgeOrientation[BR] = 1; B3.EdgeOrientation[UB] = 1;
    Mutari[Moves::B3] = B3;

    Cubie D1;
    D1.CornerPermutation[DRF] = DLF; D1.CornerPermutation[DLF] = DLB; D1.CornerPermutation[DLB] = DRB; D1.CornerPermutation[DRB] = DRF;
    D1.EdgePermutation[DF] = DL; D1.EdgePermutation[DL] = DB; D1.EdgePermutation[DB] = DR; D1.EdgePermutation[DR] = DF;
    Mutari[Moves::D1] = D1;

    Cubie D2;
    D2.CornerPermutation[DRF] = DLB; D2.CornerPermutation[DLB] = DRF; D2.CornerPermutation[DRB] = DLF; D2.CornerPermutation[DLF] = DRB;
    D2.EdgePermutation[DF] = DB; D2.EdgePermutation[DB] = DF; D2.EdgePermutation[DR] = DL; D2.EdgePermutation[DL] = DR;
    Mutari[Moves::D2] = D2;

    Cubie D3;
    D3.CornerPermutation[DRF] = DRB; D3.CornerPermutation[DRB] = DLB; D3.CornerPermutation[DLB] = DLF; D3.CornerPermutation[DLF] = DRF;
    D3.EdgePermutation[DF] = DR; D3.EdgePermutation[DR] = DB; D3.EdgePermutation[DB] = DL; D3.EdgePermutation[DL] = DF;
    Mutari[Moves::D3] = D3;

    Cubie F1;
    F1.CornerPermutation[URF] = ULF; F1.CornerPermutation[ULF] = DLF; F1.CornerPermutation[DLF] = DRF; F1.CornerPermutation[DRF] = URF;
    F1.CornerOrientation[URF] = 1; F1.CornerOrientation[ULF] = 2; F1.CornerOrientation[DLF] = 1; F1.CornerOrientation[DRF] = 2;
    F1.EdgePermutation[FR] = UF; F1.EdgePermutation[UF] = FL; F1.EdgePermutation[FL] = DF; F1.EdgePermutation[DF] = FR;
    F1.EdgeOrientation[FR] = 1; F1.EdgeOrientation[UF] = 1; F1.EdgeOrientation[FL] = 1; F1.EdgeOrientation[DF] = 1;
    Mutari[Moves::F1] = F1;

    Cubie F2;
    F2.CornerPermutation[URF] = DLF; F2.CornerPermutation[DLF] = URF; F2.CornerPermutation[ULF] = DRF; F2.CornerPermutation[DRF] = ULF;
    F2.EdgePermutation[FR] = FL; F2.EdgePermutation[FL] = FR; F2.EdgePermutation[UF] = DF; F2.EdgePermutation[DF] = UF;
    Mutari[Moves::F2] = F2;

    Cubie F3;
    F3.CornerPermutation[URF] = DRF; F3.CornerPermutation[DRF] = DLF; F3.CornerPermutation[DLF] = ULF; F3.CornerPermutation[ULF] = URF;
    F3.CornerOrientation[URF] = 1; F3.CornerOrientation[ULF] = 2; F3.CornerOrientation[DLF] = 1; F3.CornerOrientation[DRF] = 2;
    F3.EdgePermutation[UF] = FR; F3.EdgePermutation[FR] = DF; F3.EdgePermutation[DF] = FL; F3.EdgePermutation[FL] = UF;
    F3.EdgeOrientation[FR] = 1; F3.EdgeOrientation[UF] = 1; F3.EdgeOrientation[FL] = 1; F3.EdgeOrientation[DF] = 1;
    Mutari[Moves::F3] = F3;
}

void Cubie::applyMove(Cubie mutare) {
    this->multiply(mutare);
}

void Cubie::multiply(Cubie mul) {
    Cubie result;
    for (size_t i = 0; i < 8; i++) {
        result.CornerOrientation[i] = (CornerOrientation[mul.CornerPermutation[i]] + mul.CornerOrientation[i]) % 3;
        result.CornerPermutation[i] = CornerPermutation[mul.CornerPermutation[i]];
    }

    for (size_t i = 0; i < 12; i++) {
        result.EdgeOrientation[i] = (EdgeOrientation[mul.EdgePermutation[i]] + mul.EdgeOrientation[i]) % 2;
        result.EdgePermutation[i] = EdgePermutation[mul.EdgePermutation[i]];
    }

    for (size_t i = 0; i < 8; i++) {
        this->CornerOrientation[i] = result.CornerOrientation[i];
        this->CornerPermutation[i] = result.CornerPermutation[i];
    }

    for (size_t i = 0; i < 12; i++) {
        this->EdgeOrientation[i] = result.EdgeOrientation[i];
        this->EdgePermutation[i] = result.EdgePermutation[i];
    }
}

int Cubie::getTwistCoord() {
    int twist = 0;
    for (int i = 0; i < 7; i++) twist = 3 * twist + CornerOrientation[i];
    return twist;
}

int Cubie::getFlipCoord() {
    int flip = 0;
    for (int i = 0; i < 11; i++) flip = 2 * flip + EdgeOrientation[i];
    return flip;
}

int Cubie::combinations(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    int c = 1;
    for (int i = 0; i < k; i++) c = c * (n - i) / (i + 1);
    return c;
}

int Cubie::getUDSliceCoord() {
    int UDSliceCoord = 0;
    int k = 3;
    for (int i = 11; i >= 0; i--) {
        if (EdgePermutation[i] >= 8 && EdgePermutation[i] <= 11) {
            k--;
        }
        else {
            UDSliceCoord += combinations(i, k);
        }
    }
    return UDSliceCoord;
}

int Cubie::getCPCoord() {
    int cp = 0;
    for (int i = 0; i < 7; i++) {
        int d = 0;
        for (int j = i + 1; j < 8; j++) {
            if (CornerPermutation[j] < CornerPermutation[i]) d++;
        }
        cp = cp * (8 - i) + d;
    }
    return cp;
}

int Cubie::getEPCoord() {
    int ep = 0;
    for (int i = 0; i < 7; i++) {
        int d = 0;
        for (int j = i + 1; j < 8; j++) {
            if (EdgePermutation[j] < EdgePermutation[i]) d++;
        }
        ep = ep * (8 - i) + d;
    }
    return ep;
}

int Cubie::getUDSlicePhase2Coord() {
    int arr[4];
    for (int i = 0; i < 4; i++) arr[i] = EdgePermutation[8 + i] - 8;

    int x = 0;
    for (int i = 0; i < 4; i++) {
        int s = 0;
        for (int j = i + 1; j < 4; j++) if (arr[j] < arr[i]) s++;
        x = x * (4 - i) + s;
    }
    return x;
}

void Cubie::setTwistCoord(int twist) {
    int parity = 0;
    for (int i = 6; i >= 0; i--) {
        CornerOrientation[i] = twist % 3;
        parity += CornerOrientation[i];
        twist /= 3;
    }
    CornerOrientation[7] = (3 - parity % 3) % 3;
}

void Cubie::setFlipCoord(int flip) {
    int parity = 0;
    for (int i = 10; i >= 0; i--) {
        EdgeOrientation[i] = flip % 2;
        parity += EdgeOrientation[i];
        flip /= 2;
    }
    EdgeOrientation[11] = (2 - parity % 2) % 2;
}

void Cubie::setUDSliceCoord(int index) {
    int k = 3;
    int sliceEdges[4] = { 8, 9, 10, 11 };
    int otherEdges[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    int sliceIdx = 0, otherIdx = 0;

    for (int i = 11; i >= 0; i--) {
        int comb = combinations(i, k);
        if (index - comb >= 0) {
            EdgePermutation[i] = otherEdges[otherIdx++];
            index -= comb;
        }
        else {
            EdgePermutation[i] = sliceEdges[sliceIdx++];
            k--;
        }
    }
}

void Cubie::setCPCoord(int cp) {
    int arr[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    int fact[8] = { 1, 1, 2, 6, 24, 120, 720, 5040 };
    for (int i = 0; i < 7; i++) {
        int d = cp / fact[7 - i];
        cp %= fact[7 - i];
        CornerPermutation[i] = arr[d];
        for (int j = d; j < 7 - i; j++) arr[j] = arr[j + 1];
    }
    CornerPermutation[7] = arr[0];
}

void Cubie::setEPCoord(int ep) {
    int arr[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    int fact[8] = { 1, 1, 2, 6, 24, 120, 720, 5040 };
    for (int i = 0; i < 7; i++) {
        int d = ep / fact[7 - i];
        ep %= fact[7 - i];
        EdgePermutation[i] = arr[d];
        for (int j = d; j < 7 - i; j++) arr[j] = arr[j + 1];
    }
    EdgePermutation[7] = arr[0];

    EdgePermutation[8] = 8;
    EdgePermutation[9] = 9;
    EdgePermutation[10] = 10;
    EdgePermutation[11] = 11;
}

static void setPermutationFromIndex4(int idx, int out[4]) {
    int elems[4] = { 0,1,2,3 };
    for (int i = 0; i < 4; i++) {
        int fact = 1;
        for (int k = 2; k <= (3 - i); k++) fact *= k;
        int pos = idx / fact;
        idx %= fact;

        out[i] = elems[pos];
        for (int j = pos; j < 3 - i; j++) elems[j] = elems[j + 1];
    }
}

void Cubie::setUDSlicePhase2Coord(int idx) {
    int perm[4];
    setPermutationFromIndex4(idx, perm);
    for (int i = 0; i < 4; i++) EdgePermutation[8 + i] = perm[i] + 8;
}

void Cubie::setUDSliceRestPhase2Coord(int UDSliceRestToUnpack) {
    int tempEP[8] = { 0 };
    for (int i = 1; i <= 7; i++) {
        tempEP[i] = UDSliceRestToUnpack % (i + 1);
        UDSliceRestToUnpack /= (i + 1);
    }
    for (int i = 7; i >= 0; i--) {
        EdgePermutation[i] = tempEP[i];
        for (int j = i + 1; j < 8; j++) {
            if (EdgePermutation[j] >= EdgePermutation[i]) {
                EdgePermutation[j]++;
            }
        }
    }
}