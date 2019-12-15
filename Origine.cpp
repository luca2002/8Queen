#include <iostream>
using namespace std;
#define N 8
//PROBLEMA FLAGOPERATION HO CREATO PROTOTIPO QUI
bool Trajectory(int r, int c, int flag, int ChessBoard[N][N]);
void StartChessBoard(int ChessBoard[N][N]) {
	//INIZIALIZZAZIONE SCACCHIERA
	for (int i = 0; i < N; i++) {
		for (int a = 0; a < N; a++) {
			ChessBoard[i][a] = 0;
		}
	}
}
void OutChessBoard(int ChessBoard[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int a = 0; a < N; a++) {
			if (ChessBoard[i][a] != 2) cout << "[" << "0" << "]" << " "; else cout << "[" << "1" << "]" << " ";
			if (a == 7) { cout << endl << endl; }
		}
	}
}
bool FlagOperation(int r, int c, int flag, int ChessBoard[N][N]) {
	bool check;
	check = Trajectory(r, c, 2, ChessBoard);
	if (check == 1) return 1;
	else if (check == 0) ChessBoard[r][c] = 0;
	return 0;
}
bool Trajectory(int r, int c, int flag, int ChessBoard[N][N]) {
	int r1 = r, c1 = c;
	bool check = 0, final = 0;
	//ORIZZONTALE E VERTICALE
	for (int i = 0; i < N; i++) {
		//VERTICALE
		if (flag == 0) ChessBoard[i][c] = 1;
		if (flag == 1) if (FlagOperation(i, c, 1, ChessBoard) == 1) final = 1;
		if (flag == 2 && ChessBoard[i][c] == 2) return 1;
	}
	//OBLIQUA DA ALTO-SX a REGINA
	while (!(r == 0 || c == 0)) {
		c--; r--;
		if (flag == 0) ChessBoard[r][c] = 1;
		if (flag == 1) if (FlagOperation(r, c, 1, ChessBoard) == 1) final = 1;
		if (flag == 2 && ChessBoard[r][c] == 2) return 1;
	}
	//CONTINUAZIONE OBLIQUA DA REGINA A BASSO-DX
	r = r1; c = c1;
	while (!(r == 7 || c == 7)) {
		r++; c++;
		if (flag == 0) ChessBoard[r][c] = 1;
		if (flag == 1) if (FlagOperation(r, c, 1, ChessBoard) == 1) final = 1;
		if (flag == 2 && ChessBoard[r][c] == 2) return 1;
	}
	//OBLIQUA DA BASSO-SX A REGINA
	r = r1; c = c1;
	while (!(r == 7 || c == 0)) {
		c--; r++;
		if (flag == 0) ChessBoard[r][c] = 1;
		if (flag == 1) if (FlagOperation(r, c, 1, ChessBoard) == 1) final = 1;
		if (flag == 2 && ChessBoard[r][c] == 2) return 1;
	}
	//CONTINUAZIONE OBLIQUA DA REGINA A L'ALTO-DX
	r = r1; c = c1;
	while (!(r == 0 || c == 7)) {
		r--; c++;
		if (flag == 0) ChessBoard[r][c] = 1;
		if (flag == 1) if (FlagOperation(r, c, 1, ChessBoard) == 1) final = 1;
		if (flag == 2 && ChessBoard[r][c] == 2) return 1;
	}
	return final;
}
void PlaceQueen(int r, int c, int ChessBoard[N][N]) {
	bool null = Trajectory(r, c, 0, ChessBoard);
	ChessBoard[r][c] = 2;
}
void DeleteQueen(int r, int c, int ChessBoard[N][N]) {
	ChessBoard[r][c] = 0;
	bool null = Trajectory(r, c, 1, ChessBoard);
}
int findPlace(int r, int indice, int ChessBoard[N][N]) {
	for (int i = indice + 1; i < N; i++) {
		if (ChessBoard[r][i] != 1) return i;
	}
	return -1;
}
void main() {
	int ChessBoard[N][N], Moves[N] = { -1, -1, -1, -1, -1, -1, -1, -1 }, pos = 0, indice = -1, solution = 0;
	bool check = 0;
	StartChessBoard(ChessBoard);
	for (int i = 0; i < N + 1;) {
		pos = findPlace(i, indice, ChessBoard);
		if (pos != -1) {
			PlaceQueen(i, pos, ChessBoard); //TROVATA POSIZIONE
			Moves[i] = pos;
			indice = -1;
			i++;
			//ARRIVATO A 8 STAMPA SOLUZIONE E CONTINUA
			if (i == 8) {
				solution++;
				OutChessBoard(ChessBoard);
				cout << endl;
				i--;
				DeleteQueen(i, Moves[i], ChessBoard);
				indice = Moves[i];
				Moves[i] = -1;
			}
		}
		else { //ARRETRAMENTO DI UNA RIGA
			i--;
			if (i < 0) break; //TERMINA IL PROGRAMMA AL TERMINE DELLE SOLUZIONI
			DeleteQueen(i, Moves[i], ChessBoard);
			indice = Moves[i];
			Moves[i] = -1;
		}
	}
	cout << "SOLUZIONI: " << solution << endl;
	system("PAUSE");
}