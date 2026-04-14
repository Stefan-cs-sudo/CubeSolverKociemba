#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <filesystem>
#include "CubieCube.h"
using namespace std;

enum Colors {

	U, F, R, B, L, D

};

enum Moves {
	U1, U2, U3,
	R1, R2, R3,
	L1, L2, L3,
	B1, B2, B3,
	D1, D2, D3,
	F1, F2, F3
};

enum Corners {

	URF,ULF,ULB,ULR,
	DRF,DLF,DLB,DRB


};

Cubie Mutari;

enum Edges {


	UR, UF, UL, UB,
	DR, DF, DL, DB,
	FR, FL, BL, BR

};


class Tables {
	
	static vector<short> TwistMove;
	static vector<short> FlipMove;
	static vector<short> UDSliceMove;
	static vector<short> CPMove;
	static	vector<short>EPMove;
	static	vector<short> Slice_Twist_Prun;

		static vector<short> Slice_Flip_Prun;

		static vector<short> Slice_CP_Prun;

		static vector<short> Slice_EP_Prun;


public:

	Tables()
	{
		
		TwistMove.resize(2187 * 18);
		FlipMove.resize(2048 * 18);
		UDSliceMove.resize(495 * 18);
		CPMove.resize(40320);
		EPMove.resize(40320);
		Slice_Flip_Prun.resize(2187 * 18);
		Slice_CP_Prun.resize(2187 * 18);
		Slice_EP_Prun.resize(2187 * 18);

		FILE* file = fopen("kociemba_tables.bin", "rb");
		if (file != NULL) {
			
			fread(TwistMove.data(), sizeof(short), TwistMove.size(), file);
			fread(FlipMove.data(), sizeof(short), FlipMove.size(), file);
			fread(UDSliceMove.data(), sizeof(short), UDSliceMove.size(), file);
			fread(CPMove.data(), sizeof(short), CPMove.size(), file);
			fread(EPMove.data(), sizeof(short), EPMove.size(), file);
			fread(Slice_Twist_Prun.data(), sizeof(short), Slice_Twist_Prun.size(), file);
			fread( Slice_Flip_Prun.data(), sizeof(short), Slice_Flip_Prun.size(), file);
			fread(Slice_CP_Prun.data(), sizeof(short),Slice_CP_Prun.size(), file);
			fread(Slice_EP_Prun.data(), sizeof(short), Slice_EP_Prun.size(), file);

			
			fclose(file);
		}
		else {
			cout << "Nu s-au gasit tabelele necesare pentru rezolvarea rapida \n";
			cout << "Trebuie generate toate  tabelele:\n";
			cout << "Vrei sa se genereze tabele noi( asigura-te ca tabelele nu sunt create deja in alta parte ,daca sunt doar muta-le  in folder-ul programului ) cele vechi o sa fie sterse ";
			cout << endl << " Y/N?\n";
			string answer;
			cin >> answer;
			if (answer == "y" || answer == "Y")
			{
				

				FILE* file = fopen("kociemba_tables.bin", "wb");
				if (file != NULL) {
					
					fwrite(TwistMove.data(), sizeof(short), TwistMove.size(), file);
					fwrite(FlipMove.data(), sizeof(short), FlipMove.size(), file);
					fwrite(UDSliceMove.data(), sizeof(short), UDSliceMove.size(), file);
					fwrite(CPMove.data(), sizeof(short), CPMove.size(), file);
					fwrite(EPMove.data(), sizeof(short), EPMove.size(), file);
					fwrite(Slice_Twist_Prun.data(), sizeof(short), Slice_Twist_Prun.size(), file);
					fwrite(Slice_Flip_Prun.data(), sizeof(short), Slice_Flip_Prun.size(), file);
					fwrite(Slice_CP_Prun.data(), sizeof(short), Slice_CP_Prun.size(), file);
					fwrite(Slice_EP_Prun.data(), sizeof(short), Slice_EP_Prun.size(), file);


					fclose(file);
				}
			}
			else
			{
				cout << "nu s-au generat tabele";
				

			}
		}
	//exista fisiere necesare?
		
	
		
		
	}
	void BuildTwistMove()
	{
		Cubie cub;
		cub.initMoves();
		for (int i = 0; i < 2187; i++)
		{
			for (int m=Moves::U1 ; m < Moves::F3; m++)
			{
			   cub.setTwistCoord(i);
				cub.applyMove(Cubie::Mutari[m]);
		      
				
				
				TwistMove[i * 18 + m] = cub.getTwistCoord();
			}
		}

	}
	void BuildFlipMove()
	{
		Cubie cub;
		cub.initMoves();
		for (size_t i = 0; i < 2048; i++)
		{
			for (int m = Moves::U1; m < Moves::F3; m++)
			{
				cub.setFlipCoord(i);
				cub.applyMove(Cubie::Mutari[m]);

				FlipMove[i * 18 + m] = cub.getFlipCoord();


			}
		}

		
	}
	void BuildUDSliceMove()
	{

		Cubie cub;
		cub.initMoves();
		for (size_t i = 0; i < 495; i++)
		{
			for (int m = Moves::U1; m < Moves::F3; m++)
			{
				cub.setUDSliceCoord(i);
				cub.applyMove(Cubie::Mutari[m]);

				UDSliceMove[i * 18 + m] = cub.getUDSliceCoord();


			}
		}

	}
	void BuildCPMove()
	{
		Cubie cub;
		cub.initMoves();
		for (size_t i = 0; i < 40320; i++)
		{
			for (size_t m = Moves::U1; m < Moves::F3; m++)
			{
				cub.setCPCoord(i);
				cub.applyMove(Cubie::Mutari[m]);
				CPMove[18 * i + m] = cub.getCPCoord();

			}
		}
		



	}
	void BuildEPMove()
	{
		Cubie cub;
		cub.initMoves();
		for (size_t i = 0; i < 40320; i++)
		{
			for (size_t m = Moves::U1; m < Moves::F3; m++)
			{
				cub.setEPCoord(i);
				cub.applyMove(Cubie::Mutari[m]);
				EPMove[18 * i + m] = cub.getEPCoord();

			}
		}
	}
	void BuildSlice_Twist_Prun() {
		
		int totalStates = 495 * 2187;
		Slice_Twist_Prun.resize(totalStates);

	
		for (int i = 0; i < totalStates; i++) {
			Slice_Twist_Prun[i] = -1;
		}

		
		Slice_Twist_Prun[0] = 0;

		int depth = 0;
		int done = 1; 

		cout << "Generam Slice_Twist_Prun..." << endl;

	
		while (done < totalStates) {
			
			for (int i = 0; i < totalStates; i++) {

				
				if (Slice_Twist_Prun[i] == depth) {

					
					int slice = i / 2187;
					int twist = i % 2187;

					
					for (int m = 0; m < 18; m++) {

						
						int newSlice = UDSliceMove[slice * 18 + m];
						int newTwist = TwistMove[twist * 18 + m];

						
						int newIndex = newSlice * 2187 + newTwist;

						
						if (Slice_Twist_Prun[newIndex] == -1) {
							
							Slice_Twist_Prun[newIndex] = depth + 1;
							done++;
						}
					}
				}
			}
			depth++;
			cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari." << endl;
		}
	}
	void BuildSlice_Flip_Prun()
	{

	}
	void BuildSlice_CP_Prun()
	{

	}
	void BuildSlice_EP_Prun()
	{

	}

	void BuildingTables()
	{
		BuildTwistMove();
		


	}
	
	


};