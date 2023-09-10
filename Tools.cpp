#include "Header.h"

void rand_string(char name[], int size)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < size; i++)
	{
		int key = rand() % (sizeof(charset) / sizeof(char) - 1);
		name[i] = charset[key];
	}
	name[size] = '\0';
}

//
//char GetPlayerChar(int turn) {
//	if (turn == 0) return 'u';
//	if (turn == 1) return '0';
//	if (turn == -1) return 'x';
//}
//void Print_one_Cell(int i, int j)
//{
//	int x = j * 3 + 1;
//	int y = i * 2 + 1;
//	if (j % 2 == 0)
//	{
//		y = y + 1;
//	}
//	printf("%c[%d;%df", 0x1B, y, x + 1);
//	printf("__");
//	printf("%c[%d;%df", 0x1B, y + 1, x);
//	//printf("/%2d\\", (y_*15 + x_)%100);
//	struct Cell* t = SearchCell(i, j);
//	if (t != NULL)
//	{
//		printf("/%c \\", GetPlayerChar(t->belongsTo));
//	}
//	else
//	{
//		////if (data.map[i][j] == 1)		printf("/ e\\");
//		////if (data.map[i][j] == 2)		printf("/ m\\");
//		////if (data.map[i][j] == 3)		printf("/ _\\");
//		/*	if (data.map[i][j] == 4)*/		printf("/  \\");
//	}
//
//	printf("%c[%d;%df", 0x1B, y + 2, x);
//	printf("\\__/");
//}
//void Print_All_Cells()
//{
//	for (int i = 0; i < data.n; i++)
//	{
//		for (int j = 0; j < data.n; j++)
//		{
//			Print_one_Cell(i, j);
//		}
//	}
//	printf("%c[%d;%df", 0x1B, 2 * data.n + 3, 0);
//}
//void WriteTest() {
//	FILE* fptr;
//	fptr = fopen("map.bin", "wb");
//	int a = 6;
//	fwrite(&a, sizeof(int), 1, fptr);
//	for (int i = 0; i < 100; i++)
//	{
//		char c = rand() % 4 + '1';
//		c = '4';
//		fwrite(&c, sizeof(char), 1, fptr);
//	}
//	fclose(fptr);
//}





//void printMap() {
//	for (int i = 0; i < data.n; i++)
//	{
//		for (int j = 0; j < data.n; j++)
//		{
//			printf("%3d ", data.map[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//	for (int i = 0; i < data.n; i++)
//	{
//		for (int j = 0; j < data.n; j++)
//		{
//			printf("%3d ", data.Energy[i][j]);
//		}
//		printf("\n");
//	}
//}




//void PrintCells()
//{
//	int i = 0;
//	while (1)
//	{
//		struct Cell* t = GetnTh(i);
//		if (t != NULL)
//		{
//			printf("\n[%d]\t %s\t (%d, %d), energy is: %d", i, t->name, t->x, data.n - t->y - 1, t->Energy);
//			i++;
//		}
//		else
//			return;
//	}
//}
