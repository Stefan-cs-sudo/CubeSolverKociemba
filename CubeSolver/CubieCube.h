#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "CoordCube.h"
#include <vector>
#include <filesystem>
#include "Constants.h"
class Cubie;






class Cubie
{

    public:
        short CornerPermutation[8] = {};
    uint8_t CornerOrientation[8] = {};
    short EdgePermutation[12] = {};
    uint8_t EdgeOrientation[12] = {};


     static Cubie Mutari[18];
     Cubie();



    void initMoves();
   
    void  applyMove(Cubie mutare);
    
    void  multiply(Cubie mul);
    



   

    int getTwistCoord();

    int getFlipCoord();


   
    int combinations(int n, int k);

    int getUDSliceCoord();

    int factorial(int n);

    int getCPCoord();
    

    int getEPCoord();


    int getUDSlicePhase2Coord();
    



    void setTwistCoord(int twistToUnpack);

    void setFlipCoord(int FlipToUnpack);

    void setCPCoord(int CPtoUnpack);
   
    void setUDSliceCoord(int index);

    void setEPCoord(int EPtoUnpack);

    void setUDSlicePhase2Coord(int UDMidPhase2ToUnpack);

    void setUDSliceRestPhase2Coord(int UDSliceRestToUnpack);

    

     



    //    var j, k, s, x: Integer; i, e: Edge; arr: array[0..3] of Edge;
    //    begin
    //        j : = 0;
    //    for i: = UR to BR do
    //        begin
    //        e : = PEdge ^ [i].e;
    //    if (e = FR) or (e = FL) or (e = BL) or (e = BR) then begin arr[j]: = e; Inc(j); end;
    //    end; kociemba site

    //x: = 0;
    //    for j: = 3 downto 1 do
    //        begin
    //        s : = 0;
    //    for k: = j - 1 downto 0 do
    //        begin
    //        if arr[k] > arr[j] then Inc(s);
    //    end;
    //x: = (x + s) * j;
    //    end;
    //Result: = UDSliceCoord * 24 + x;
    //    end;





};
