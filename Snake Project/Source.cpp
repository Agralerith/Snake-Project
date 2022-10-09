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
	dir = STOP;
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

	for (int i = 0; i < mapWidth + 1; ++i)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapHeight; ++j)
		{
			if (j == 0)
			{
				cout << "#";
			}

			if (i == headYPos && j == headXPos)
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
			else if (i == foodYPos && j == foodXPos)
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
			else if (i == poisonFoodYPos0/* && i == poisonFoodYPos1*/
				&& j == poisonFoodXPos0 /*&& j == poisonFoodXPos1*/)
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
				cout << " ";
			}

			if (j == mapWidth - 1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < mapWidth + 1; ++i)
	{
		cout << "#";
	}
	cout << endl;
	cout << snakeType;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'a':
			dir = LEFT;
			break;
		}
	}
}


void Logic()
{
	switch (dir)
	{
	case LEFT:
		if (snakeType == 4)
		{
			--headXPos;
		}
		else if (snakeType == 5)
		{
			headXPos -= 2;
		}
		else if (snakeType == 6)
		{
			headXPos -= 3;
		}
		break;

	case RIGHT:
		if (snakeType == 4)
		{
			++headXPos;
		}
		else if (snakeType == 5)
		{
			headXPos += 2;
		}
		else if (snakeType == 6)
		{
			headXPos += 3;
		}
		break;

	case UP:
		if (snakeType == 4)
		{
			--headYPos;
		}
		else if (snakeType == 5)
		{
			headYPos -= 2;
		}
		else if (snakeType == 6)
		{
			headYPos -= 3;
		}
		break;

	case DOWN:
		if (snakeType == 4)
		{
			++headYPos;
		}
		else if (snakeType == 5)
		{
			headYPos += 2;
		}
		else if (snakeType == 6)
		{
			headYPos += 3;
		}
		break;

	default:
		break;
	}

	if (headXPos > mapWidth || headXPos < 0 || headYPos > mapHeight || headYPos < 0
		|| (headXPos == poisonFoodXPos0 && headYPos == poisonFoodYPos0))
	{
		isGameOver = true;
	}

	if (headXPos == foodXPos && headYPos == foodYPos)
	{
		srand(time(0));
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
	}
	return 0;
}