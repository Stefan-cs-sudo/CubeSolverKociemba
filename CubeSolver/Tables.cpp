
#define _CRT_SECURE_NO_WARNINGS
#include "Tables.h"



using namespace std;






Tables::Tables()
{

	TwistMove.resize(2187 * 18);
	FlipMove.resize(2048 * 18);
	UDSliceMove.resize(495 * 18);
	CPMove.resize(40320);
	EPMove.resize(40320);
	Slice_EP_Prun.resize(2187 * 18);

	FILE* file = fopen("kociemba_tables.bin", "rb");
	if (file != NULL) {

		fread(TwistMove.data(), sizeof(short), TwistMove.size(), file);
		fread(FlipMove.data(), sizeof(short), FlipMove.size(), file);
		fread(UDSliceMove.data(), sizeof(short), UDSliceMove.size(), file);
		fread(CPMove.data(), sizeof(short), CPMove.size(), file);
		fread(EPMove.data(), sizeof(short), EPMove.size(), file);
		fread(Slice_Twist_Prun.data(), sizeof(short), Slice_Twist_Prun.size(), file);
		fread(Slice_Flip_Prun.data(), sizeof(short), Slice_Flip_Prun.size(), file);
		fread(Slice_CP_Prun.data(), sizeof(short), Slice_CP_Prun.size(), file);
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

void Tables::BuildTwistMove() {
	Cubie cub;
	cub.initMoves();
	for (int i = 0; i < 2187; i++)
	{
		for (int m = Moves::U1; m < Moves::F3; m++)
		{
			cub.setTwistCoord(i);
			cub.applyMove(Cubie::Mutari[m]);



			TwistMove[i * 18 + m] = cub.getTwistCoord();
		}
	}

}


void Tables::BuildFlipMove()
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

void Tables::BuildUDSliceMove()
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



void Tables::BuildCPMove()
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

void Tables::BuildEPMove()
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


void Tables::BuildSlice_Twist_Prun()
{

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


					if (Slice_Twist_Prun[newIndex] == -1)
					{

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

void Tables::BuildSlice_Flip_Prun()
{


	int totalStates = 495 * 2048;
	Slice_Flip_Prun.resize(totalStates);


	for (int i = 0; i < totalStates; i++) {
		Slice_Flip_Prun[i] = -1;
	}


	Slice_Flip_Prun[0] = 0;

	int depth = 0;
	int done = 1;

	cout << "Generam Slice_Twist_Prun..." << endl;


	while (done < totalStates) {

		for (int i = 0; i < totalStates; i++) {


			if (Slice_Flip_Prun[i] == depth) {


				int slice = i / 2048;
				int twist = i % 2048;


				for (int m = 0; m < 18; m++) {


					int newSlice = UDSliceMove[slice * 18 + m];
					int newTwist = FlipMove[twist * 18 + m];


					int newIndex = newSlice * 2048 + newTwist;


					if (Slice_Flip_Prun[newIndex] == -1) {

						Slice_Flip_Prun[newIndex] = depth + 1;
						done++;
					}
				}
			}
		}
		depth++;
		cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari." << endl;
	}


}


void Tables::BuildUDSlicePhase2Move()
{
	UDSlicePhase2Move.resize(24 * 18);
	Cubie cub;
	cub.initMoves();

	for (int i = 0; i < 24; i++)
	{
		for (int m = Moves::U1; m <= Moves::B3; m++)
		{
			cub.setUDSlicePhase2Coord(i);
			cub.applyMove(Cubie::Mutari[m]);

			UDSlicePhase2Move[18 * i + m] = cub.getUDSlicePhase2Coord();
		}
	}

}


void Tables::BuildSlice_CP_Prun()
{
	int totalStates = 40320 * 24;
	Slice_CP_Prun.resize(totalStates);

	for (int i = 0; i < totalStates; i++) {
		Slice_CP_Prun[i] = -1;
	}

	Slice_CP_Prun[0] = 0;
	int depth = 0;
	int done = 1;

	cout << "Generam Slice_CP_Prun (Faza 2)..." << endl;


	int phase2Moves[10] = { Moves::U1, Moves::U2, Moves::U3,
						   Moves::D1, Moves::D2, Moves::D3,
						   Moves::R2, Moves::L2, Moves::F2, Moves::B2 };

	while (done < totalStates) {
		for (int i = 0; i < totalStates; i++) {

			if (Slice_CP_Prun[i] == depth) {

				int slice = i / 40320;
				int cp = i % 40320;


				for (int mIndex = 0; mIndex < 10; mIndex++) {
					int m = phase2Moves[mIndex];


					int newSlice = UDSlicePhase2Move[slice * 18 + m];
					int newCP = CPMove[cp * 18 + m];

					int newIndex = newSlice * 40320 + newCP;

					if (Slice_CP_Prun[newIndex] == -1) {
						Slice_CP_Prun[newIndex] = depth + 1;
						done++;
					}
				}
			}
		}
		depth++;
		cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari." << endl;
	}
}


void Tables::BuildSlice_EP_Prun()
{


	int totalStates = 40320 * 24;
	Slice_EP_Prun.resize(totalStates);

	for (int i = 0; i < totalStates; i++) {
		Slice_EP_Prun[i] = -1;
	}

	Slice_EP_Prun[0] = 0;
	int depth = 0;
	int done = 1;

	cout << "Generam Slice_CP_Prun (Faza 2)..." << endl;


	int phase2Moves[10] = { Moves::U1, Moves::U2, Moves::U3,
						   Moves::D1, Moves::D2, Moves::D3,
						   Moves::R2, Moves::L2, Moves::F2, Moves::B2 };

	while (done < totalStates) {
		for (int i = 0; i < totalStates; i++) {

			if (Slice_CP_Prun[i] == depth) {

				int slice = i / 40320;
				int ep = i % 40320;


				for (int mIndex = 0; mIndex < 10; mIndex++) {
					int m = phase2Moves[mIndex];


					int newSlice = UDSlicePhase2Move[slice * 18 + m];
					int newCP = EPMove[ep * 18 + m];

					int newIndex = newSlice * 40320 + newCP;

					if (Slice_EP_Prun[newIndex] == -1) {
						Slice_EP_Prun[newIndex] = depth + 1;
						done++;
					}
				}
			}
		}
		depth++;
		cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari." << endl;
	}


}


void Tables::BuildingTables()
{
	BuildTwistMove();



}
