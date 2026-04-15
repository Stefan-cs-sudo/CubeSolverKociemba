// CoordCube.cpp (sau unde ai implementarea)

#include "CoordCube.h"
#include "Constants.h"
#include <cassert>

static inline void assertCoordCube(const CoordCube& s) {
    assert(0 <= s.cp && s.cp < 40320);
    assert(0 <= s.ep && s.ep < 40320);
    assert(0 <= s.udslice && s.udslice < 495);
    assert(0 <= s.twist && s.twist < 2187);
    assert(0 <= s.flip && s.flip < 2048);
    assert(0 <= s.udslicePhase2 && s.udslicePhase2 < 24);
}

CoordCube::CoordCube(Cubie c) {
    twist = c.getTwistCoord();
    flip = c.getFlipCoord();
    udslice = c.getUDSliceCoord();
    cp = c.getCPCoord();
    ep = c.getEPCoord();
    udslicePhase2 = c.getUDSlicePhase2Coord();
    assertCoordCube(*this);
}

void CoordCube::move(int m) {
    twist = Tables::TwistMove[twist * 18 + m];
    flip = Tables::FlipMove[flip * 18 + m];
    udslice = Tables::UDSliceMove[udslice * 18 + m];

    if (m == U1 || m == U2 || m == U3 ||
        m == D1 || m == D2 || m == D3 ||
        m == R2 || m == L2 || m == F2 || m == B2) {
        cp = Tables::CPMove[cp * 18 + m];
        ep = Tables::EPMove[ep * 18 + m];
        udslicePhase2 = Tables::UDSlicePhase2Move[udslicePhase2 * 18 + m];
    }
    assertCoordCube(*this);
}