#include"CoordCube.h"
#define _CRT_SECURE_NO_WARNINGS


CoordCube::CoordCube(Cubie c)
 {
     twist = c.getTwistCoord();
     flip = c.getFlipCoord();
     udslice = c.getUDSliceCoord();
     cp = c.getCPCoord();
     ep = c.getEPCoord();
     udslicePhase2 = c.getUDSlicePhase2Coord();
    }

void CoordCube::move(int m)
 {
     Tables temp;
     twist = Tables::TwistMove[twist * 18 + m];
     flip = Tables::FlipMove[flip * 18 + m];
     udslice = Tables::UDSliceMove[udslice * 18 + m];


     if (m == U1 || m == U2 || m == U3 || m == D1 || m == D2 || m == D3 ||
         m == R2 || m == L2 || m == F2 || m == B2) {
         cp = Tables::CPMove[cp * 18 + m];
         ep = Tables::EPMove[ep * 18 + m];
         udslicePhase2 = Tables::UDSlicePhase2Move[udslicePhase2 * 18 + m];
     }
 }