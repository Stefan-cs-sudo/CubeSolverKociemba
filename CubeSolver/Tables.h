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
	inline static vector<short> TwistMove;

	inline static vector<short> FlipMove;

	inline static vector<short> UDSliceMove;

	inline static vector<short> CPMove;

	inline static	vector<short>EPMove;

	inline static	vector<short> Slice_Twist_Prun;

	inline static vector<short> Slice_Flip_Prun;

	inline static vector<short> Slice_CP_Prun;

	inline static vector<short> Slice_EP_Prun;

	inline static vector<short >UDSlicePhase2Move;




	Tables();
	
		void BuildTwistMove();
	
	void BuildFlipMove();
	void BuildUDSliceMove();
	
	void BuildCPMove();
	void BuildEPMove();
	void BuildSlice_Twist_Prun();
	void BuildSlice_Flip_Prun();
	

	void BuildUDSlicePhase2Move();

	void BuildSlice_CP_Prun();
	void BuildSlice_EP_Prun();

	void BuildingTables();
		
	


};