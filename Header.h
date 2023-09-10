#include "graphics.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void rand_string(char name[], int size);
enum blocks {
	ENERGY = 1,
	MITOSIS = 2,
	FORBIDDEN = 3,
	NORMAL = 4
};
struct Cell
{
	char name[20];
	int Energy;
	int x;
	int y;
	int belongsTo;
	struct Cell* next;
};
struct Data {
	enum blocks** map;
	int** Energy;
	int n;
	int turn;
	int GamePlayerMode;//0:1player, 1 two player, 2 with cpu
	int CellCount;
	struct Cell* Root;
} ;
extern struct Data data;
extern char ERRORS[200];
void ReadMap(char name[]);
struct Cell* GetLastCell();
void AddCell( int i, int j, int energy, char name[], int turn);
void LoadUserData(char name[]);
void Init( int i);
struct Cell* SearchCell( int i, int j);
void SaveUserData(char name[]);
int CanGo( int i, int j);
void RandomMap();
int CountEnergy(int player);
int CountCells(int player);
struct Cell* GetnTh(int i);
int Move(struct Cell* t, int move);
int* MoveDirections(struct Cell* t, int move);
void SaveTXT(char name[]);
void Savebin();
void GetFromUserMap();
void PrintCell(int length, int i, int j);
void PrintMap();
void CPUPlay();
