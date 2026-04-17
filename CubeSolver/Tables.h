#pragma once
#include <vector>
#include <cstdint>
#include "CubieCube.h"
#include "Constants.h"
#include <array> 

class Cubie;

class Tables {
public:
    inline static std::array<uint16_t, 2187 * 18> TwistMove;
    inline static std::array<uint16_t, 2048 * 18> FlipMove;
    inline static std::array<uint16_t, 495 * 18> UDSliceMove;
    inline static std::array<uint16_t, 40320 * 18> CPMove;
    inline static std::array<uint16_t, 40320 * 18> EPMove;
    inline static std::array<uint16_t, 24 * 18> UDSlicePhase2Move;

    
    inline static std::array<uint8_t, 495 * 2187> Slice_Twist_Prun;
    inline static std::array<uint8_t, 495 * 2048> Slice_Flip_Prun;
    inline static std::array<uint8_t, 2187 * 2048> Twist_Flip_Prun;
    inline static std::array<uint8_t, 40320 * 24> Slice_CP_Prun;
    inline static std::array<uint8_t, 40320 * 24> Slice_EP_Prun;

  

    static void init();
    static void BuildTwistMove();
    static void BuildFlipMove();
    static void BuildUDSliceMove();
    static void BuildCPMove();
    static void BuildEPMove();
    static  void BuildUDSlicePhase2Move();

    static void BuildSlice_Twist_Prun();
    static void BuildSlice_Flip_Prun();
    static void BuildTwist_Flip_Prun();
    static void BuildSlice_CP_Prun();
    static void BuildSlice_EP_Prun();

    static void BuildingTables();
};