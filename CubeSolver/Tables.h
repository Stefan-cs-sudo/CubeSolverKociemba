#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <filesystem>
#include "CubieCube.h"
#include "Constants.h"
using namespace std;
class Cubie; 
class CoordCube;



class Tables {
public:
	inline static vector<int> TwistMove;

	inline static vector<int> FlipMove;

	inline static vector<int> UDSliceMove;

	inline static vector<int> CPMove;

	inline static	vector<int>EPMove;


	inline static vector<int >UDSlicePhase2Move;

	inline static std::vector<uint8_t> Slice_Twist_Prun; // size 495*2187
	inline static std::vector<uint8_t> Slice_Flip_Prun;  // size 495*2048
	inline static std::vector<uint8_t> Twist_Flip_Prun;  // size 2187*2048 (NEW)

	inline static std::vector<uint8_t> Slice_CP_Prun;    // size 24*40320
	inline static std::vector<uint8_t> Slice_EP_Prun;


	Tables();
	
		void BuildTwistMove();
	
	void BuildFlipMove();
	void BuildUDSliceMove();
	
	void BuildCPMove();
	void BuildEPMove();
	void BuildSlice_Twist_Prun();
	void BuildSlice_Flip_Prun();
	void BuildTwist_Flip_Prun(); // NEW
	

	void BuildUDSlicePhase2Move();

	void BuildSlice_CP_Prun();
	void BuildSlice_EP_Prun();

	void BuildingTables();
		
	


};