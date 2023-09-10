#include "Header.h"
void ReadMap(char name[])
{
	data.CellCount = 0;
	data.Root = NULL;
	FILE* fptr;
	fptr = fopen(name, "rb");
	if (fptr == NULL)
	{
		printf("\n Error!");
		return;
	}
	fread(&data.n, sizeof(int), 1, fptr);
	data.map = (enum blocks**)malloc(data.n * sizeof(enum blocks*));
	data.Energy = (int**)malloc(data.n * sizeof(int*));
	for (int i = 0; i < data.n; i++)
	{
		data.map[i] = (enum blocks*)malloc(data.n * sizeof(enum blocks));
		data.Energy[i] = (int*)malloc(data.n * sizeof(int));
		for (int j = 0; j < data.n; j++)
		{
			char a;
			fread(&a, sizeof(char), 1, fptr);
			switch (a)
			{
			case '1':data.map[i][j] = ENERGY; data.Energy[i][j] = 100; break;
			case '2':data.map[i][j] = MITOSIS; data.Energy[i][j] = 0; break;
			case '3':data.map[i][j] = FORBIDDEN; data.Energy[i][j] = 0; break;
			case '4':data.map[i][j] = NORMAL; data.Energy[i][j] = 0; break;
			}
		}
	}
	fclose(fptr);
	Savebin();
}
void LoadUserData(char name[])
{
	FILE* fptr;
	char temp[20];
	sprintf(temp, "energy%s", name);
	fptr = fopen(temp, "r");
	if (fptr == NULL)return;
	for (int i = 0; i < data.n; i++)
	{
		for (int j = 0; j < data.n; j++)
		{
			fscanf(fptr, "%d ", &data.Energy[i][j]);
		}
	}
	fclose(fptr);
	sprintf(temp, "user%s", name);
	fptr = fopen(temp, "r");
	struct Cell t;
	int tedad = 0;
	data.CellCount = 0;
	fscanf(fptr, "%d", &data.turn);
	fscanf(fptr, "%d", &tedad);
	fscanf(fptr, "%d", &data.GamePlayerMode);
	data.Root = NULL;
	for (int i = 0; i < tedad; i++)
	{
		fscanf(fptr, "%d\t%d\t%s\t%d\t%d\n", &t.belongsTo, &t.Energy, t.name, &t.x, &t.y);
		AddCell( t.y, t.x, t.Energy, t.name, t.belongsTo);
	}
	fclose(fptr);
}
void SaveUserData(char name[])
{
	FILE* fptr;
	char temp[20];
	sprintf(temp, "energy%s", name);
	fptr = fopen(temp, "w");
	for (int i = 0; i < data.n; i++)
	{
		for (int j = 0; j < data.n; j++)
			fprintf(fptr, "%d\t", data.Energy[i][j]);
		fprintf(fptr, "\n");
	}
	fclose(fptr);
	sprintf(temp, "user%s", name);
	fptr = fopen(temp, "w");
	struct Cell* t;
	t = data.Root;
	fprintf(fptr, "%d\n", data.turn);
	fprintf(fptr, "%d\n", data.CellCount);
	fprintf(fptr, "%d\n", data.GamePlayerMode);
	for (int i = 0; i < data.CellCount; i++)
	{
		fprintf(fptr, "%d\t%d\t%s\t%d\t%d\n", t->belongsTo, t->Energy, t->name, t->x, t->y);
		t = t->next;
	}
	fclose(fptr);
}
void SaveTXT(char name[]) {
	FILE* fptr;
	fptr = fopen(name, "w");
	fprintf(fptr, "%d\n", data.n);
	for (int i = 0; i < data.n; i++)
	{
		for (int j = 0; j < data.n; j++)
		{
			int c =data.map[i][j];
			fprintf(fptr, "%d ", c);
		}
	}
	fclose(fptr);
	printf("\nSaved  as %s", name);
}
void Savebin() {
	FILE* fptr;
	fptr = fopen("map.bin", "wb");
	fwrite(&data.n, sizeof(int), 1, fptr);
	for (int i = 0; i < data.n; i++)
	{
		for (int j = 0; j < data.n; j++)
		{
			char c = data.map[i][j] + '0';
			fwrite(&c, sizeof(char), 1, fptr);
		}
	}
	fclose(fptr);
	printf("\nSaved  as %map.bin");
}
