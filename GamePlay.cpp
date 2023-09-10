#include "Header.h"
int CanGo(int i, int j) {
	if (i < 0)return 0;
	if (j < 0)return 0;
	if (i > data.n - 1)return 0;
	if (j > data.n - 1)return 0;
	if (data.map[i][j] == FORBIDDEN)return 0;
	if (SearchCell(i, j) != NULL)return 0;
	return 1;
}
void Init(int i) {
	while (i > 0)
	{
		int r = rand() % data.n;
		int c = rand() % data.n;
		if (data.map[r][c] != 3 && SearchCell(r, c) == NULL)
		{
			char tt[20];
			rand_string(tt, 5);
			AddCell(r, c, 0, tt, data.turn);
			i--;
		}
	}
}
int* MoveDirections(struct Cell* t, int move) {
	int movesList[2] = { 0,0 };
	if (move == 1)
	{
		movesList[0]--;
	}
	if (move == 2)
	{
		movesList[0]++;
	}
	if (move == 3)
	{
		movesList[1]++;
		if (t->x % 2 == 1)
		{
			movesList[0]--;
		}
	}
	if (move == 4)
	{
		movesList[1]--;
		if (t->x % 2 == 1)
		{
			movesList[0]--;
		}
	}
	if (move == 5)
	{
		movesList[1]++;
		if (t->x % 2 == 0)
		{
			movesList[0]++;
		}
	}
	if (move == 6)
	{
		movesList[1]--;
		if (t->x % 2 == 0)
		{
			movesList[0]++;
		}
	}

	return movesList;
}
int Move(struct Cell* t, int move) {
	int* movesList;
	movesList = MoveDirections(t, move);
	int newx = t->x + movesList[1];
	int newy = t->y + movesList[0];
	if (!CanGo(newy, newx))
	{
		sprintf(ERRORS, "\nImpossible!");
		return 0;
	}
	t->y = newy;
	t->x = newx;
	return 1;
}
void RandomMap() {
	data.n = 6;
	data.map = (enum blocks**)malloc(data.n * sizeof(enum blocks*));
	data.Energy = (int**)malloc(data.n * sizeof(int*));
	for (int i = 0; i < data.n; i++)
	{
		data.map[i] = (enum blocks*)malloc(data.n * sizeof(enum blocks));
		data.Energy[i] = (int*)malloc(data.n * sizeof(int));
		for (int j = 0; j < data.n; j++)
		{
			if (rand() % 2 == 1)
			{
				data.map[i][j] = NORMAL; data.Energy[i][j] = 0;
			}
			else {
				char c = rand() % 4 + '1';
				switch (c)
				{
				case '1':data.map[i][j] = ENERGY; data.Energy[i][j] = 100; break;
				case '2':data.map[i][j] = MITOSIS; data.Energy[i][j] = 0; break;
				case '3':data.map[i][j] = FORBIDDEN; data.Energy[i][j] = 0; break;
				case '4':data.map[i][j] = NORMAL; data.Energy[i][j] = 0; break;
				}
			}
		}
	}
}
void GetFromUserMap() {
	printf("\n please enter n:\t");
	scanf("%d", &data.n);
	data.map = (enum blocks**)malloc(data.n * sizeof(enum blocks*));
	data.Energy = (int**)malloc(data.n * sizeof(int*));
	for (int i = 0; i < data.n; i++)
	{
		data.map[i] = (enum blocks*)malloc(data.n * sizeof(enum blocks));
		data.Energy[i] = (int*)malloc(data.n * sizeof(int));
		for (int j = 0; j < data.n; j++)
		{
			printf("please enter mode of cell %d, %d(1:energy, 2: mitosis, 3: forbidden, 4: normal)\t", j, data.n - i + 1);
			char temp;
			scanf(" %c", &temp);
			switch (temp)
			{
			case '1':data.map[i][j] = ENERGY;  break;
			case '2':data.map[i][j] = MITOSIS;  break;
			case '3':data.map[i][j] = FORBIDDEN;break;
			case '4':data.map[i][j] = NORMAL;    break;
			}
		}
	}
	Savebin();
}

void PrintCell(int length, int i, int j) {
	//https://www.quora.com/How-can-you-find-the-coordinates-in-a-hexagon
	int x = length + length + j * length * 1.55;
	int y = 200 + length + i * length * 2;
	if (j % 2 == 0)
	{
		y = y + length;
	}
	int points[14];
	//A
	points[0] = x + length;
	points[1] = y + 0;
	//B
	points[2] = x + length / 2;
	points[3] = y + (sqrt(3) * length) / 2;
	//C
	points[4] = x - (length / 2);
	points[5] = y + (sqrt(3) * length) / 2;
	//D
	points[6] = x - length;
	points[7] = y + 0;
	//E
	points[8] = x - (length / 2);
	points[9] = y + -(sqrt(3) * length) / 2;
	//F
	points[10] = x + (length / 2);
	points[11] = y + -(sqrt(3) * length) / 2;

	points[12] = points[0];
	points[13] = points[1];
	drawpoly(7, points);

	struct Cell* c;
	c = SearchCell(i, j);
	if (c != NULL)
	{
		if (c->belongsTo == -1)
			setfillstyle(HATCH_FILL, RED);
		if (c->belongsTo == +1)
			setfillstyle(HATCH_FILL, BLUE);
	}
	else
	{
		if (data.map[i][j] == ENERGY)
			setfillstyle(SOLID_FILL, GREEN);
		if (data.map[i][j] == MITOSIS)
			setfillstyle(SOLID_FILL, YELLOW);
		if (data.map[i][j] == FORBIDDEN)
			setfillstyle(SOLID_FILL, BLACK);
		if (data.map[i][j] == NORMAL)
			setfillstyle(SOLID_FILL, LIGHTGRAY);
	}
	floodfill(x, y, WHITE);
	settextstyle(SMALL_FONT, HORIZ_DIR, 4);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	if (c != NULL)
	{
		outtextxy(x, y, c->name);
		char temp[10];
		sprintf(temp, "%d", c->Energy);
		outtextxy(x, y + 10, temp);
	}
	else
	{
		if (data.map[i][j] == ENERGY)
		{
			char temp[10];
			sprintf(temp, "%d", data.Energy[i][j]);
			outtextxy(x, y, temp);
		}
	}
}
void PrintMap() {
	cleardevice();
	setcolor(WHITE);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	rectangle(200, 10, 250, 30);
	if (data.turn == -1)
	{
		outtextxy(10, 10, "Player1's turn");
		setfillstyle(SOLID_FILL, RED);
	}
	if (data.turn == 1)
	{
		if (data.GamePlayerMode == 2)
			outtextxy(10, 10, "CPU's turn");
		else
			outtextxy(10, 10, "Player2's turn");
		setfillstyle(SOLID_FILL, BLUE);
	}
	floodfill(201, 11, WHITE);

	char str[20];
	outtextxy(10, 40, "Player1");
	outtextxy(100, 40, "Cells: ");
	sprintf(str, "%d", CountCells(-1));
	outtextxy(180, 40, str);
	outtextxy(250, 40, "Energy: ");
	sprintf(str, "%d", CountEnergy(-1));
	outtextxy(320, 40, str);


	if (data.GamePlayerMode == 2)
		outtextxy(10, 80, "CPU");
	else
		outtextxy(10, 80, "Player2");
	outtextxy(100, 80, "Cells: ");
	sprintf(str, "%d", CountCells(1));
	outtextxy(180, 80, str);
	outtextxy(250, 80, "Energy: ");
	sprintf(str, "%d", CountEnergy(1));
	outtextxy(320, 80, str);





	rectangle(100, 140, 150, 160); setfillstyle(SOLID_FILL, GREEN); floodfill(101, 141, WHITE);
	rectangle(250, 140, 300, 160); setfillstyle(SOLID_FILL, YELLOW); floodfill(251, 141, WHITE);
	rectangle(400, 140, 450, 160); setfillstyle(SOLID_FILL, BLACK); floodfill(401, 141, WHITE);
	rectangle(550, 140, 600, 160); setfillstyle(SOLID_FILL, LIGHTGRAY); floodfill(551, 141, WHITE);
	outtextxy(10, 140, "ENERGY");
	outtextxy(160, 140, "MITOSIS");
	outtextxy(310, 140, "FORBIDDEN");
	outtextxy(460, 140, "NORMAL");
	int length = 500 / (data.n * 2 + 1);
	for (int i = 0; i < data.n; i++)
	{
		for (int j = 0; j < data.n; j++)
		{
			PrintCell(length, i, j);
		}
	}

	setcolor(RED);
	outtextxy(500, 500, ERRORS);
	setcolor(WHITE);

	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	settextjustify(LEFT_TEXT, TOP_TEXT);
}

void CPUPlay()
{
	while (1)
	{
		int index = rand() % CountCells(data.turn);
		struct Cell* selectedCell = GetnTh(index);
		int choose = rand() % 4;
		if (choose == 1)
		{
			int moveChoose = rand() % 6;
			int isMoved = Move(selectedCell, moveChoose);
			if (isMoved)
			{
				return;
			}
		}
		if (choose == 2)
		{
			if (selectedCell->Energy > 80 && data.map[selectedCell->y][selectedCell->x] == MITOSIS)
			{
				for (int k = 1; k <= 6; k++)
				{
					int* tempDirection;
					tempDirection = MoveDirections(selectedCell, k);
					int fff = tempDirection[1];
					int ii = selectedCell->y + tempDirection[0];
					int jj = selectedCell->x + tempDirection[1];
					if (CanGo(ii, jj))
					{
						char tt[20];
						rand_string(tt, 5);
						AddCell(ii, jj, 40, tt, data.turn);
						return;
					}
				}
			}
		}
		if (choose == 3)
		{
			if (data.Energy[selectedCell->y][selectedCell->x] >= 15)
			{
				selectedCell->Energy += 15;
				data.Energy[selectedCell->y][selectedCell->x] -= 15;
				if (data.Energy[selectedCell->y][selectedCell->x] < 0)
					data.Energy[selectedCell->y][selectedCell->x] = 0;
				return;
			}
			else if (data.Energy[selectedCell->y][selectedCell->x] >= 0)
			{
				selectedCell->Energy += data.Energy[selectedCell->y][selectedCell->x];
				data.Energy[selectedCell->y][selectedCell->x] = 0;
				return;
			}
		}
		if (choose == 4)
		{
			SaveUserData("User.txt");
			return;
		}
	}
}
