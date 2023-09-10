#include "Header.h"
struct Cell* GetLastCell(struct Data& data)
{
	if (data.Root == NULL)
		return NULL;
	if (data.Root->next == NULL)
		return data.Root;
	struct Cell* t;
	t = data.Root;
	while (t->next != NULL)
	{
		t = t->next;
	}
	return t;
}
void AddCell(int i, int j, int energy, char name[], int turn) {
	struct Cell* t;
	t = (struct Cell*)malloc(sizeof(struct Cell));
	t->x = j;
	t->y = i;
	t->belongsTo = turn;
	t->Energy = energy;
	strcpy(t->name, name);
	t->next = NULL;
	if (data.Root == NULL)
	{
		data.Root = t;
	}
	else {
		GetLastCell(data)->next = t;
	}
	data.CellCount++;
}
struct Cell* SearchCell(int i, int j)
{
	if (data.Root == NULL)
		return NULL;
	struct Cell* t;
	t = data.Root;
	while (t != NULL)
	{
		if (t->x == j && t->y == i)
			return t;
		t = t->next;
	}
	return NULL;
}
struct Cell* GetnTh(int i) {
	struct Cell* t;
	int c = 0;
	t = data.Root;
	while (t != NULL)
	{
		if (t->belongsTo == data.turn)
		{
			if (c == i)
				return t;
			c++;
		}
		t = t->next;
	}
	return NULL;
}
int CountCells(int player) {
	struct Cell* t;
	int c = 0;
	t = data.Root;
	while (t != NULL)
	{
		if (t->belongsTo == player)
		{
			c++;
		}
		t = t->next;
	}
	return c;
}
int CountEnergy(int player) {
	struct Cell* t;
	int c = 0;
	t = data.Root;
	while (t != NULL)
	{
		if (t->belongsTo == player)
		{
			c += t->Energy;
		}
		t = t->next;
	}
	return c;
}
