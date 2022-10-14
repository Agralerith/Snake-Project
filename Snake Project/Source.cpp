#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

bool isGameOver;

const int width0 = 10;
const int width1 = 20;
const int width2 = 30;

const int height0 = 10;
const int height1 = 20;
const int height2 = 30;

int headXPos;
int headYPos;

int foodXPos;
int foodYPos;
int poisonFoodXPos0;
//int poisonFoodXPos1;
int poisonFoodYPos0;
//int poisonFoodYPos1;

int mapWidth;
int mapHeight;
int snakeType;

int score;

int tailX[100];
int tailY[100];
int tailLength;

bool isChooseCompleted = false;

enum eDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

eDirection dir;

int SetMapWidth(char choice);
int SetMapHeight(char choice);
int SetSnakeType(char choice);

//void gotoxy(int x, int y)
//{
//	COORD coord;
//	coord.X = x;
//	coord.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}

void PlayerChoice()
{
	char playerChoiceWidth, playerChoiceHeight, playerChoiceSnake;

	do
	{
		cout << "Choose the width of the map." << endl;
		cout << "Press 'Q' key for 10." << endl;
		cout << "Press 'W' key for 20." << endl;
		cout << "Press 'E' key for 30." << endl;
		cin >> playerChoiceWidth;
	} while (playerChoiceWidth != 'q' && playerChoiceWidth != 'w' && playerChoiceWidth != 'e'
		&& playerChoiceWidth != 'Q' && playerChoiceWidth != 'W' && playerChoiceWidth != 'E');

	mapWidth = SetMapWidth(playerChoiceWidth);

	do
	{
		cout << "Choose the height of the map." << endl;
		cout << "Press 'Q' key for 10." << endl;
		cout << "Press 'W' key for 20." << endl;
		cout << "Press 'E' key for 30." << endl;
		cin >> playerChoiceHeight;
	} while (playerChoiceHeight != 'q' && playerChoiceHeight != 'w' && playerChoiceHeight != 'e'
		&& playerChoiceHeight != 'Q' && playerChoiceHeight != 'W' && playerChoiceHeight != 'E');

	mapHeight = SetMapHeight(playerChoiceHeight);

	cout << "The map size is " << mapWidth << " X " << mapHeight << endl;

	do
	{
		cout << "Choose the snake that you want." << endl;
		cout << "Press 'Q' to choose @ snake that moves 4 steps in a second" << endl;
		cout << "Press 'W' to choose # snake that moves 5 steps in a second" << endl;
		cout << "Press 'E' to choose $ snake that moves 6 steps in a second" << endl;
		cin >> playerChoiceSnake;
	} while (playerChoiceSnake != 'q' && playerChoiceSnake != 'w' && playerChoiceSnake != 'e'
		&& playerChoiceSnake != 'Q' && playerChoiceSnake != 'W' && playerChoiceSnake != 'E');

	snakeType = SetSnakeType(playerChoiceSnake);
	cout << "The snake you choose moves " << snakeType << " steps in a second" << endl;

	isChooseCompleted = true;
}

int SetMapWidth(char choice)
{
	int caseWidth;
	switch (choice)
	{
	case 'Q': case 'q':
		caseWidth = 10;
		break;
	case 'W': case 'w':
		caseWidth = 20;
		break;
	case 'E': case 'e':
		caseWidth = 30;
		break;
	}
	return caseWidth;
}

int SetMapHeight(char choice)
{
	int caseHeight;
	switch (choice)
	{
	case 'Q': case 'q':
		caseHeight = 10;
		break;
	case 'W': case 'w':
		caseHeight = 20;
		break;
	case 'E': case 'e':
		caseHeight = 30;
		break;
	}
	return caseHeight;
}

int SetSnakeType(char choice)
{
	int snakeType;
	switch (choice)
	{
	case 'Q': case 'q':
		snakeType = 4;
		break;
	case 'W': case 'w':
		snakeType = 5;
		break;
	case 'E': case 'e':
		snakeType = 6;
		break;
	}
	return snakeType;
}

void Setup()
{
	srand(time(0));
	isGameOver = false;
	dir = UP;
	//gotoxy(mapWidth / 2, mapHeight / 2);
	headXPos = mapWidth / 2;
	headYPos = mapHeight / 2;
	foodXPos = rand() % mapWidth;
	foodYPos = rand() % mapHeight;
	poisonFoodXPos0 = rand() % mapWidth / 2;
	poisonFoodYPos0 = rand() % mapHeight / 2;
	//poisonFoodXPos1 = rand() % mapWidth / 3;
	//poisonFoodYPos1 = rand() % mapHeight / 3;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < mapWidth + 47; ++i)
	{
		if (i >= 45)
		{
			cout << "#";
		}
		else if (i < 45)
		{
			cout << " ";
		}
	}
	cout << endl;

	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth + 45; ++j)
		{
			if (j == 45)
			{
				cout << "#";
			}

			if (i == headYPos && j == headXPos + 45)
			{
				if (snakeType == 4)
				{
					cout << "@";
				}
				else if (snakeType == 5)
				{
					cout << "#";
				}
				else if (snakeType == 6)
				{
					cout << "$";
				}
			}
			else if (i == foodYPos && j == foodXPos + 45)
			{
				if (snakeType == 4)
				{
					cout << "@";
				}
				else if (snakeType == 5)
				{
					cout << "#";
				}
				else if (snakeType == 6)
				{
					cout << "$";
				}
			}
			else if (i == poisonFoodYPos0 && j == poisonFoodXPos0  + 45)
			{
				if (snakeType == 4)
				{
					cout << "!";
				}
				else if (snakeType == 5)
				{
					cout << "+";
				}
				else if (snakeType == 6)
				{
					cout << "&";
				}
			}
			else
			{
				bool print = false;
				for (int u = 0; u < tailLength; ++u)
				{
					if (tailX[u] + 45 == j && tailY[u] == i)
					{
						cout << "*";
						print = true;
					}
				}
				if (!print)
				{
				cout << " ";
			}
			}

			if (j == mapWidth + 44)
			{
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < mapWidth + 47; ++i)
	{
		if (i >= 45)
		{
			cout << "#";
		}
		else if (i < 45)
		{
			cout << " ";
		}
	}

	cout << endl;

	for (int i = 0; i < mapWidth + 26; ++i)
	{
		if (i >= mapWidth + 25)
		{
			cout << "Score: " << score << endl;
		}
		else if (i < mapWidth + 25)
		{
			cout << " ";
		}
	}
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (dir != DOWN)
			{
				dir = UP;
			}
			break;
		case 's':
			if (dir != UP)
			{
				dir = DOWN;
			}
			break;
		case 'd':
			if (dir != LEFT)
			{
				dir = RIGHT;
			}
			break;
		case 'a':
			if (dir != RIGHT)
			{
				dir = LEFT;
			}
			break;
		}
	}
}


void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prevTwoX;
	int prevTwoY;
	tailX[0] = headXPos;
	tailY[0] = headYPos;

	for (int i = 1; i < tailLength; ++i)
	{
		prevTwoX = tailX[i];
		prevTwoY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevTwoX;
		prevY = prevTwoY;
	}

	switch (dir)
	{
	case LEFT:
		if (snakeType == 4)
		{
			--headXPos;
		}
		else if (snakeType == 5)
		{
			//headXPos -= 2;
			--headXPos;
		}
		else if (snakeType == 6)
		{
			//headXPos -= 3;
			--headXPos;
		}
		break;

	case RIGHT:
		if (snakeType == 4)
		{
			++headXPos;
		}
		else if (snakeType == 5)
		{
			//headXPos += 2;
			++headXPos;
		}
		else if (snakeType == 6)
		{
			//headXPos += 3;
			++headXPos;
		}
		break;

	case UP:
		if (snakeType == 4)
		{
			--headYPos;
		}
		else if (snakeType == 5)
		{
			//headYPos -= 2;
			--headYPos;
		}
		else if (snakeType == 6)
		{
			//headYPos -= 3;
			--headYPos;
		}
		break;

	case DOWN:
		if (snakeType == 4)
		{
			++headYPos;
		}
		else if (snakeType == 5)
		{
			//headYPos += 2;
			++headYPos;
		}
		else if (snakeType == 6)
		{
			//headYPos += 3;
			++headYPos;
		}
		break;

	default:
		break;
	}

	if (headXPos == poisonFoodXPos0 && headYPos == poisonFoodYPos0)
	{
		isGameOver = true;
	}

	if (headXPos >= mapWidth)
	{
		headXPos = 0;
	}
	else if (headXPos < 0)
	{
		headXPos = mapWidth - 1;
	}

	if (headYPos >= mapHeight)
	{
		headYPos = 0;
	}
	else if (headYPos < 0)
	{
		headYPos = mapHeight - 1;
	}

	for (int i = 0; i < tailLength; ++i)
	{
		if (tailX[i] == headXPos && tailY[i] == headYPos)
	{
		isGameOver = true;
	}
	}

	if (headXPos == foodXPos && headYPos == foodYPos)
	{
		++tailLength;
		score += 10;
		//srand(time(0));
		foodXPos = rand() % mapWidth;
		foodYPos = rand() % mapHeight;
	}
}

int main() 
{
	PlayerChoice();

	if (isChooseCompleted)
	{
		Setup();
	}

	while (!isGameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(60);
	}
	return 0;
}