
#define _CRT_SECURE_NO_WARNINGS
#include "Tables.h"



using namespace std;






Tables::Tables()
{
	
	TwistMove.resize(2187 * 18);
	FlipMove.resize(2048 * 18);
	UDSliceMove.resize(495 * 18);
	UDSlicePhase2Move.resize(24 * 18); 
	CPMove.resize(40320 * 18);         
	EPMove.resize(40320 * 18);       

	Twist_Flip_Prun.resize(2187 * 2048);
	Slice_Twist_Prun.resize(495 * 2187);
	Slice_Flip_Prun.resize(495 * 2048);
	Slice_CP_Prun.resize(40320 * 24);
	Slice_EP_Prun.resize(40320 * 24);

	FILE* file = fopen("kociemba_tables.bin", "rb");
	if (file != NULL) {
		fread(TwistMove.data(), sizeof(int), TwistMove.size(), file);
		fread(FlipMove.data(), sizeof(int), FlipMove.size(), file);
		fread(UDSliceMove.data(), sizeof(int), UDSliceMove.size(), file);
		fread(UDSlicePhase2Move.data(), sizeof(int), UDSlicePhase2Move.size(), file);
		fread(CPMove.data(), sizeof(int), CPMove.size(), file);
		fread(EPMove.data(), sizeof(int), EPMove.size(), file);
		fread(Slice_Twist_Prun.data(), sizeof(uint8_t), Slice_Twist_Prun.size(), file);
		fread(Slice_Flip_Prun.data(), sizeof(uint8_t), Slice_Flip_Prun.size(), file);
		fread(Twist_Flip_Prun.data(), sizeof(uint8_t), Twist_Flip_Prun.size(), file);
		fread(Slice_CP_Prun.data(), sizeof(uint8_t), Slice_CP_Prun.size(), file);
		fread(Slice_EP_Prun.data(), sizeof(uint8_t), Slice_EP_Prun.size(), file);

		fclose(file);
		cout << "Tabelele au fost incarcate cu succes din fisier!\n";
	}
	else {
		
			BuildingTables(); 

			FILE* file = fopen("kociemba_tables.bin", "wb");
			if (file != NULL) {
				fwrite(TwistMove.data(), sizeof(int), TwistMove.size(), file);
				fwrite(FlipMove.data(), sizeof(int), FlipMove.size(), file);
				fwrite(UDSliceMove.data(), sizeof(int), UDSliceMove.size(), file);
				fwrite(UDSlicePhase2Move.data(), sizeof(int), UDSlicePhase2Move.size(), file);
				fwrite(CPMove.data(), sizeof(int), CPMove.size(), file);
				fwrite(EPMove.data(), sizeof(int), EPMove.size(), file);
				fwrite(Slice_Twist_Prun.data(), sizeof(uint8_t), Slice_Twist_Prun.size(), file);
				fwrite(Slice_Flip_Prun.data(), sizeof(uint8_t), Slice_Flip_Prun.size(), file);
				fwrite(Twist_Flip_Prun.data(), sizeof(uint8_t), Twist_Flip_Prun.size(), file);
				fwrite(Slice_CP_Prun.data(), sizeof(uint8_t), Slice_CP_Prun.size(), file);
				fwrite(Slice_EP_Prun.data(), sizeof(uint8_t), Slice_EP_Prun.size(), file);
				fclose(file);
			}
	
	}
	std::cout << "Slice_Twist_Prun size=" << Tables::Slice_Twist_Prun.size() << "\n";
	std::cout << "Slice_Flip_Prun size=" << Tables::Slice_Flip_Prun.size() << "\n";
	std::cout << "Twist_Flip_Prun size=" << Tables::Twist_Flip_Prun.size() << "\n";
	std::cout << "Slice_CP_Prun size=" << Tables::Slice_CP_Prun.size() << "\n";
	std::cout << "Slice_EP_Prun size=" << Tables::Slice_EP_Prun.size() << "\n";
}

void Tables::BuildTwistMove() {
	
	for (int i = 0; i < 2187; i++)
	{
		for (int m = 0; m < 18; m++)
		{
			Cubie cub;
			cub.setTwistCoord(i);
			cub.applyMove(Cubie::Mutari[m]);



			TwistMove[i * 18 + m] = cub.getTwistCoord();
		}
	}

}


void Tables::BuildFlipMove()
{


	for (size_t i = 0; i < 2048; i++)
	{
		for (int m = 0; m < 18; m++)
		{
			Cubie cub;
			cub.setFlipCoord(i);
			cub.applyMove(Cubie::Mutari[m]);

			FlipMove[i * 18 + m] = cub.getFlipCoord();


		}
	}


}

void Tables::BuildUDSliceMove()
{

	
	for (size_t i = 0; i < 495; i++)
	{
		for (int m = 0; m < 18; m++)
		{
			Cubie cub;
			cub.setUDSliceCoord(i);
			cub.applyMove(Cubie::Mutari[m]);

			UDSliceMove[i * 18 + m] = cub.getUDSliceCoord();


		}
	}

}



void Tables::BuildCPMove()
{
	
	for (size_t i = 0; i < 40320; i++)
	{
		for (int m = 0; m < 18; m++)
		{
			Cubie cub;
			cub.setCPCoord(i);
			cub.applyMove(Cubie::Mutari[m]);
			CPMove[18 * i + m] = cub.getCPCoord();

		}
	}




}

void Tables::BuildEPMove()
{

	for (size_t i = 0; i < 40320; i++)
	{
		for (int m = 0; m < 18; m++)
		{
			Cubie cub;
			cub.setEPCoord(i);
			cub.applyMove(Cubie::Mutari[m]);
			EPMove[18 * i + m] = cub.getEPCoord();

		}
	}
}

void Tables::BuildSlice_Twist_Prun() {
	const int totalStates = 495 * 2187;
	Slice_Twist_Prun.assign(totalStates, 255);
	Slice_Twist_Prun[0] = 0;

	int depth = 0;
	int done = 1;

	std::cout << "Generam Slice_Twist_Prun...\n";
	while (done < totalStates) {
		for (int i = 0; i < totalStates; i++) {
			if (Slice_Twist_Prun[i] == depth) {
				int slice = i / 2187;
				int twist = i % 2187;

				for (int m = 0; m < 18; m++) {
					int newSlice = UDSliceMove[slice * 18 + m];
					int newTwist = TwistMove[twist * 18 + m];
					int newIndex = newSlice * 2187 + newTwist;

					if (Slice_Twist_Prun[newIndex] == 255) {
						Slice_Twist_Prun[newIndex] = (uint8_t)(depth + 1);
						done++;
					}
				}
			}
		}
		depth++;
		std::cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}
void Tables::BuildSlice_Flip_Prun() {
	const int totalStates = 495 * 2048;
	Slice_Flip_Prun.assign(totalStates, 255);
	Slice_Flip_Prun[0] = 0;

	int depth = 0;
	int done = 1;

	std::cout << "Generam Slice_Flip_Prun...\n";
	while (done < totalStates) {
		for (int i = 0; i < totalStates; i++) {
			if (Slice_Flip_Prun[i] == depth) {
				int slice = i / 2048;
				int flip = i % 2048;

				for (int m = 0; m < 18; m++) {
					int newSlice = UDSliceMove[slice * 18 + m];
					int newFlip = FlipMove[flip * 18 + m];
					int newIndex = newSlice * 2048 + newFlip;

					if (Slice_Flip_Prun[newIndex] == 255) {
						Slice_Flip_Prun[newIndex] = (uint8_t)(depth + 1);
						done++;
					}
				}
			}
		}
		depth++;
		std::cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}
void Tables::BuildTwist_Flip_Prun()
{
	const int totalStates = 2187 * 2048;
	Twist_Flip_Prun.assign(totalStates, 255);
	Twist_Flip_Prun[0] = 0;

	int depth = 0;
	int done = 1;

	std::cout << "Generam Twist_Flip_Prun...\n";

	while (done < totalStates) {
		for (int i = 0; i < totalStates; i++) {
			if (Twist_Flip_Prun[i] == depth) {
				int twist = i / 2048;
				int flip = i % 2048;

				for (int m = 0; m < 18; m++) {
					int newTwist = TwistMove[twist * 18 + m];
					int newFlip = FlipMove[flip * 18 + m];
					int newIndex = newTwist * 2048 + newFlip;

					if (Twist_Flip_Prun[newIndex] == 255) {
						Twist_Flip_Prun[newIndex] = (uint8_t)(depth + 1);
						done++;
					}
				}
			}
		}
		depth++;
		std::cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}

void Tables::BuildUDSlicePhase2Move() {
	UDSlicePhase2Move.assign(24 * 18, 0);

	int phase2Moves[10] = { U1,U2,U3, D1,D2,D3, R2,L2,F2,B2 };

	for (int i = 0; i < 24; i++) {
		for (int k = 0; k < 10; k++) {
			int m = phase2Moves[k];
			Cubie cub;
			cub.setUDSlicePhase2Coord(i);
			cub.applyMove(Cubie::Mutari[m]);
			UDSlicePhase2Move[i * 18 + m] = cub.getUDSlicePhase2Coord();
		}
	}
}void Tables::BuildSlice_CP_Prun()
{
	const int totalStates = 40320 * 24;

	// toate = 255 (neatins)
	Slice_CP_Prun.assign(totalStates, 255);
	Slice_CP_Prun[0] = 0;

	int depth = 0;
	int done = 1;
	int last_done = 0;

	std::cout << "Generam Slice_CP_Prun (Faza 2)...\n";

	int phase2Moves[10] = { Moves::U1, Moves::U2, Moves::U3,
							Moves::D1, Moves::D2, Moves::D3,
							Moves::R2, Moves::L2, Moves::F2, Moves::B2 };

	while (done < totalStates && done > last_done) {
		last_done = done;

		for (int i = 0; i < totalStates; i++) {
			if (Slice_CP_Prun[i] == depth) {
				int slice = i / 40320;
				int cp = i % 40320;

				for (int mi = 0; mi < 10; mi++) {
					int m = phase2Moves[mi];

					int newSlice = UDSlicePhase2Move[slice * 18 + m];
					int newCP = CPMove[cp * 18 + m];
					int newIndex = newSlice * 40320 + newCP;

					if (Slice_CP_Prun[newIndex] == 255) {
						Slice_CP_Prun[newIndex] = (uint8_t)(depth + 1);
						done++;
					}
				}
			}
		}

		depth++;
		std::cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}void Tables::BuildSlice_EP_Prun()
{
	const int totalStates = 40320 * 24;

	Slice_EP_Prun.assign(totalStates, 255);
	Slice_EP_Prun[0] = 0;

	int depth = 0;
	int done = 1;
	int last_done = 0;

	std::cout << "Generam Slice_EP_Prun (Faza 2)...\n";

	int phase2Moves[10] = { Moves::U1, Moves::U2, Moves::U3,
							Moves::D1, Moves::D2, Moves::D3,
							Moves::R2, Moves::L2, Moves::F2, Moves::B2 };

	while (done < totalStates && done > last_done) {
		last_done = done;

		for (int i = 0; i < totalStates; i++) {
			if (Slice_EP_Prun[i] == depth) {
				int slice = i / 40320;
				int ep = i % 40320;

				for (int mi = 0; mi < 10; mi++) {
					int m = phase2Moves[mi];

					int newSlice = UDSlicePhase2Move[slice * 18 + m];
					int newEP = EPMove[ep * 18 + m];
					int newIndex = newSlice * 40320 + newEP;

					if (Slice_EP_Prun[newIndex] == 255) {
						Slice_EP_Prun[newIndex] = (uint8_t)(depth + 1);
						done++;
					}
				}
			}
		}

		depth++;
		std::cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}

void Tables::BuildingTables()
{
	cout << "Asteapta, se genereaza tabelele... (Va dura cateva minute)\n";

	Cubie setup;
	setup.initMoves(); 

	BuildTwistMove();
	BuildFlipMove();
	BuildUDSliceMove();
	BuildUDSlicePhase2Move();
	BuildCPMove();
	BuildEPMove();

	BuildSlice_Twist_Prun();
	BuildSlice_Flip_Prun();
	BuildTwist_Flip_Prun();
	BuildSlice_CP_Prun();
	BuildSlice_EP_Prun();
}