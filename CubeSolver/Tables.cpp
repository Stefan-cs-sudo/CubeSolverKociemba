
#define _CRT_SECURE_NO_WARNINGS
#include "Tables.h"



using namespace std;







Tables::Tables()
{
	// 1. Alocam intotdeauna memorie inainte sa citim/generam
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

	// 2. Incarcam fisierul
	FILE* file = fopen("kociemba_tables.bin", "rb");
	if (file != NULL) {
		bool ok = true;
		// Citim si verificam exact cati bytes s-au citit ca sa nu incarcam fisiere corupte
		ok &= (fread(TwistMove.data(), sizeof(uint16_t), TwistMove.size(), file) == TwistMove.size());
		ok &= (fread(FlipMove.data(), sizeof(uint16_t  ), FlipMove.size(), file) == FlipMove.size());
		ok &= (fread(UDSliceMove.data(), sizeof(uint16_t), UDSliceMove.size(), file) == UDSliceMove.size());
		ok &= (fread(UDSlicePhase2Move.data(), sizeof(uint16_t), UDSlicePhase2Move.size(), file) == UDSlicePhase2Move.size());
		ok &= (fread(CPMove.data(), sizeof(uint16_t), CPMove.size(), file) == CPMove.size());
		ok &= (fread(EPMove.data(), sizeof(uint16_t), EPMove.size(), file) == EPMove.size());

		ok &= (fread(Slice_Twist_Prun.data(), sizeof(uint8_t), Slice_Twist_Prun.size(), file) == Slice_Twist_Prun.size());
		ok &= (fread(Slice_Flip_Prun.data(), sizeof(uint8_t), Slice_Flip_Prun.size(), file) == Slice_Flip_Prun.size());
		ok &= (fread(Twist_Flip_Prun.data(), sizeof(uint8_t), Twist_Flip_Prun.size(), file) == Twist_Flip_Prun.size());
		ok &= (fread(Slice_CP_Prun.data(), sizeof(uint8_t), Slice_CP_Prun.size(), file) == Slice_CP_Prun.size());
		ok &= (fread(Slice_EP_Prun.data(), sizeof(uint8_t), Slice_EP_Prun.size(), file) == Slice_EP_Prun.size());

		fclose(file);

		if (ok) {
		//	cout << "Tabelele au fost incarcate cu succes din fisier!\n";
		}
		else {
			cout << "Eroare: Fisierul .bin este corupt sau incomplet. Regeneram...\n";
			file = NULL; // Fortam generarea
		}
	}

	// 3. Daca nu exista fisierul sau e corupt -> Generam
	if (file == NULL) {
		BuildingTables();

		FILE* outFile = fopen("kociemba_tables.bin", "wb");
		if (outFile != NULL) {
			// AICI ERA GRESEALA! Acum folosim sizeof(uint16_t)
			fwrite(TwistMove.data(), sizeof(uint16_t), TwistMove.size(), outFile);
			fwrite(FlipMove.data(), sizeof(uint16_t), FlipMove.size(), outFile);
			fwrite(UDSliceMove.data(), sizeof(uint16_t), UDSliceMove.size(), outFile);
			fwrite(UDSlicePhase2Move.data(), sizeof(uint16_t), UDSlicePhase2Move.size(), outFile);
			fwrite(CPMove.data(), sizeof(uint16_t), CPMove.size(), outFile);
			fwrite(EPMove.data(), sizeof(uint16_t), EPMove.size(), outFile);

			// Astea erau deja corecte (uint8_t)
			fwrite(Slice_Twist_Prun.data(), sizeof(uint8_t), Slice_Twist_Prun.size(), outFile);
			fwrite(Slice_Flip_Prun.data(), sizeof(uint8_t), Slice_Flip_Prun.size(), outFile);
			fwrite(Twist_Flip_Prun.data(), sizeof(uint8_t), Twist_Flip_Prun.size(), outFile);
			fwrite(Slice_CP_Prun.data(), sizeof(uint8_t), Slice_CP_Prun.size(), outFile);
			fwrite(Slice_EP_Prun.data(), sizeof(uint8_t), Slice_EP_Prun.size(), outFile);

			fclose(outFile);
			//cout << "Tabelele au fost salvate in kociemba_tables.bin!\n";
		}
		else {
			std::cout << "EROARE CRITICA: Nu am putut salva fisierul kociemba_tables.bin! Verifica permisiunile.\n";
		}
	}

	
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

	//cout << "Generam Slice_Twist_Prun...\n";
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
		//cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}
void Tables::BuildSlice_Flip_Prun() {
	const int totalStates = 495 * 2048;
	Slice_Flip_Prun.assign(totalStates, 255);
	Slice_Flip_Prun[0] = 0;

	int depth = 0;
	int done = 1;

	//cout << "Generam Slice_Flip_Prun...\n";
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
		//cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}
void Tables::BuildTwist_Flip_Prun()
{
	const int totalStates = 2187 * 2048;
	Twist_Flip_Prun.assign(totalStates, 255);
	Twist_Flip_Prun[0] = 0;

	int depth = 0;
	int done = 1;

	//cout << "Generam Twist_Flip_Prun...\n";

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
		//cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
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

	//cout << "Generam Slice_CP_Prun (Faza 2)...\n";

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
		//cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}void Tables::BuildSlice_EP_Prun()
{
	const int totalStates = 40320 * 24;

	Slice_EP_Prun.assign(totalStates, 255);
	Slice_EP_Prun[0] = 0;

	int depth = 0;
	int done = 1;
	int last_done = 0;

	//cout << "Generam Slice_EP_Prun (Faza 2)...\n";

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
		//cout << "Adancime " << depth << " terminata. Am gasit " << done << " stari.\n";
	}
}

void Tables::BuildingTables()
{
	//cout << "Asteapta, se genereaza tabelele... (Va dura cateva minute)\n";

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