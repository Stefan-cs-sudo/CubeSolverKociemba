#include "CoordCube.h"
#include "Constants.h"
#include <cassert>

CoordCube::CoordCube(Cubie c) {

    twist = c.getTwistCoord();
    flip = c.getFlipCoord();
    udslice = c.getUDSliceCoord();
    cp = c.getCPCoord();
    ep = c.getEPCoord();
    udslicePhase2 = c.getUDSlicePhase2Coord();
  
}

void CoordCube::move(int m) {

    twist = Tables::TwistMove[twist * 18 + m];
    flip = Tables::FlipMove[flip * 18 + m];
    udslice = Tables::UDSliceMove[udslice * 18 + m];

    cp = Tables::CPMove[cp * 18 + m];
    ep = Tables::EPMove[ep * 18 + m];
    udslicePhase2 = Tables::UDSlicePhase2Move[udslicePhase2 * 18 + m];
    
}