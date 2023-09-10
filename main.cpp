#include "Header.h"
struct Data data;
char ERRORS[200];
int UndeoMax = 0;
void PlayMenu_ChooseCell() {
	while (1)
	{
		if (data.GamePlayerMode == 0)
		{
			data.turn = -1;
		}
		PrintMap();
		sprintf(ERRORS, "");
		if (data.GamePlayerMode == 2 && data.turn == 1)
		{
			CPUPlay();
			data.turn = -1;
			continue;
		}
		if (data.GamePlayerMode != 0)
			outtextxy(500, 300, "Please choose one of your cells:");
		if (data.GamePlayerMode == 0)
		{
			data.turn = -1;
			outtextxy(500, 300, "Please choose one of your cells:(z for undo)");
		}
		for (size_t i = 0; i < CountCells(data.turn); i++)
		{
			struct Cell* t = GetnTh(i);
			char temp[100];
			sprintf(temp, "\n[%d]\t %s\t (%d, %d), energy is: %d", i, t->name, t->x, data.n - t->y - 1, t->Energy);
			outtextxy(500, 330 + i * 30, temp);
		}
		int index = getch() - '0';

		if (index == 74 && data.GamePlayerMode == 0 && UndeoMax > 0)
		{
			char temp[20];
			sprintf(temp, "%d", UndeoMax);
			//SaveUserData(temp);
			LoadUserData(temp);
			UndeoMax--;
			continue;
		}
		else if (data.GamePlayerMode == 0)
		{
			char temp[20];
			UndeoMax++;
			sprintf(temp, "%d", UndeoMax);
			SaveUserData(temp);
		}

		if (index < 0 || index >= CountCells(data.turn))
			sprintf(ERRORS, "NOT VALID CHOISE!");
		else
		{
			struct Cell* selectedCell = GetnTh(index);
			PrintMap();
			outtextxy(500, 300, "[1]Move [2]Split a cell");
			outtextxy(500, 320, "[3]Boost Energy [4]Save [5]Exit");
			int choose = getch() - '0';

			if (choose == 1)
			{
				PrintMap();
				outtextxy(500, 320, "[1]North [2]South [3]Northeast");
				outtextxy(500, 340, "[4]Northwest [5]Southeast [6]Southwest");
				int moveChoose = getch() - '0';
				int isMoved = Move(selectedCell, moveChoose);
				if (isMoved == 1)
				{
					printf("%d %d %d", index, choose, moveChoose);

					data.turn *= -1;
					continue;
				}
			}
			else if (choose == 2)
			{
				if (selectedCell->Energy < 80)
				{
					sprintf(ERRORS, "ERROR! energy is less than 80");
					continue;
				}
				else if (data.map[selectedCell->y][selectedCell->x] != MITOSIS)
				{
					sprintf(ERRORS, "ERROR! is not a MITOSIS ");
					continue;
				}
				else
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
							selectedCell->Energy = 40;
							char tt[20];
							rand_string(tt, 5);
							AddCell(ii, jj, 40, tt, data.turn);
							data.turn *= -1;
							break;
						}
					}
				}
			}
			else if (choose == 3)
			{
				if (data.Energy[selectedCell->y][selectedCell->x] >= 15)
				{
					selectedCell->Energy += 15;
					data.Energy[selectedCell->y][selectedCell->x] -= 15;
					if (data.Energy[selectedCell->y][selectedCell->x] < 0)
						data.Energy[selectedCell->y][selectedCell->x] = 0;
					data.turn *= -1;
				}
				else if (data.Energy[selectedCell->y][selectedCell->x] >= 0)
				{
					selectedCell->Energy += data.Energy[selectedCell->y][selectedCell->x];
					data.Energy[selectedCell->y][selectedCell->x] = 0;
					data.turn *= -1;
				}
				else
					sprintf(ERRORS, "ERROR! No energy here!");
			}
			else if (choose == 4)
			{
				SaveUserData("User.txt");
			}
			else if (choose == 5)
			{
				return;
			}
		}
	}
}
void PlayMenu() {
	initwindow(800, 900, "game");
	data.turn = -1;
	while (!kbhit())
	{
		PlayMenu_ChooseCell();
	}
	closegraph();
}
int main()
{
	srand(time(NULL));
	ReadMap("map.bin");
	char temp[20];
	int ismaploaded = 0;
	while (1)
	{
		printf("\n[1]Load map.bin\n[2]Load other map\n[3]Generate Random map\n[4]New Map\n");
		if (ismaploaded == 1)
			printf("\n[5]Load User Data\n[6]New single player game\n[7]new Multiplayer game\n[8]new Multiplayer game with CPU\n[0]exit");
		char c = '2';
		int i = 3;
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			ReadMap("map.bin"); ismaploaded = 1;
			break;
		case '2':
			printf("\nEnter Map Name");
			scanf("%s", temp);
			ReadMap(temp); ismaploaded = 1;
			break;
		case '3':
			RandomMap();
			Savebin();
			SaveTXT("Rand.txt"); ismaploaded = 1;
			break;
		case '4':
			GetFromUserMap();
			Savebin();
			SaveTXT("new.txt"); ismaploaded = 1;
			break;
		case '5': LoadUserData("User.txt"); PlayMenu(); break;
		case '6':
			data.GamePlayerMode = 0;
			printf("\nPlease Enter Count Of Cells For Each Player:\t");
			scanf("%d", &i);
			data.turn = -1;
			Init(i);
			PlayMenu();
			break;
		case '7':
			data.GamePlayerMode = 1;
			printf("\nPlease Enter Count Of Cells For Each Player:\t");
			scanf("%d", &i);
			data.turn = -1;
			Init(i);
			data.turn = 1;
			Init(i);
			PlayMenu();
			break;
		case '8':
			data.GamePlayerMode = 2;
			printf("\nPlease Enter Count Of Cells For Each Player:\t");
			scanf("%d", &i);
			data.turn = -1;
			Init(i);
			data.turn = 1;
			Init(i);
			PlayMenu();
			break;
		case '0':return 0;

		default:
			break;
		}
	}
	return 0;
}
