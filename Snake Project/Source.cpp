#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>

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
int poisonFoodYPos0;

int mapWidth;
int mapHeight;
int snakeType;

int score;

int tailX[100];
int tailY[100];
int tailLength;

bool isChooseCompleted = false;

int snakeSpeed;

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
void GameOverScene(bool snakePoisoned, bool snakeCollided);
void RestartGame();
void main();

//void gotoxy(int x, int y)
//{
//	COORD coord;
//	coord.X = x;
//	coord.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}

void PlayerChoice()
{
	char playerChoiceSnake;
	int  playerChoiceWidth, playerChoiceHeight;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	do
	{
		cout << "Enter the width of the map." << endl;
		cout << "From 10 - 30." << endl;
		cin >> playerChoiceWidth;
		cout << endl << endl << endl;
	} while (playerChoiceWidth < 10 || playerChoiceWidth > 30);

	mapWidth = playerChoiceWidth;

	do
	{
		cout << "Enter the height of the map." << endl;
		cout << "From 10 - 30." << endl;
		cin >> playerChoiceHeight;
		cout << endl << endl << endl;
	} while (playerChoiceHeight < 10 || playerChoiceHeight > 30);

	mapHeight = playerChoiceHeight;

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
	main();
}

int SetSnakeType(char choice)
{
	int snakeType;
	switch (choice)
	{
	case 'Q': case 'q':
		snakeType = 4;
		snakeSpeed = 175;
		break;
	case 'W': case 'w':
		snakeType = 5;
		snakeSpeed = 162;
		break;
	case 'E': case 'e':
		snakeType = 6;
		snakeSpeed = 150;
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
}

void Draw()
{
	system("cls");

	for (int i = 0; i < mapWidth + 47; ++i)
	{
		if (i >= 45)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				cout << "#";
			}

			if (i == headYPos && j == headXPos + 45)
			{
				if (snakeType == 4)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "@";
				}
				else if (snakeType == 5)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "#";
				}
				else if (snakeType == 6)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "$";
				}
			}
			else if (i == foodYPos && j == foodXPos + 45)
			{
				if (snakeType == 4)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "@";
				}
				else if (snakeType == 5)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "#";
				}
				else if (snakeType == 6)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "$";
				}
			}
			else if (i == poisonFoodYPos0 && j == poisonFoodXPos0  + 45)
			{
				if (snakeType == 4)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << "!";
				}
				else if (snakeType == 5)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << "+";
				}
				else if (snakeType == 6)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
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
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < mapWidth + 47; ++i)
	{
		if (i >= 45)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
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
	bool isSnakePoisoned = false;
	bool isHeadHitTail = false;
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
		isSnakePoisoned = true;
		GameOverScene(isSnakePoisoned, isHeadHitTail);
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
			isHeadHitTail = true;
			GameOverScene(isSnakePoisoned, isHeadHitTail);
		}
	}

	if (headXPos == foodXPos && headYPos == foodYPos)
	{
		++tailLength;
		score += 10;
		foodXPos = rand() % mapWidth;
		foodYPos = rand() % mapHeight;
	}
}

void GameOverScene(bool snakePoisoned, bool snakeCollided)
{
	system("cls");
	wprintf(L"\x1b[34;46m\r\n");
	cout << "YOU LOST!!!" << endl << endl;
	cout << "Your Score is " << score << endl << endl << endl;
	wprintf(L"\x1b[0m\r\n");
	wprintf(L"\x1b[39m\r\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	if (snakePoisoned && !snakeCollided)
	{
		cout << "You lose, snake has been poisoned." << endl;
	}
	else if (!snakePoisoned && snakeCollided)
	{
		cout << "You lose, snake has collided with its tail." << endl;
	}
	isGameOver = true;
}

void main() 
{
	int restartKey; 

	if (!isChooseCompleted)
	{
		PlayerChoice();
	}

	if (isChooseCompleted)
	{
		Setup();
	}

	while (!isGameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(snakeSpeed);
	}

	while (isGameOver)
	{
		cout << "Press any number key between 0 - 9 to restart the game" << endl;
		cin >> restartKey;
		cout << endl << endl << endl;
		if (restartKey >= 0 && restartKey <= 9)
		{
			RestartGame();
		}
		else
		{
			cout << "Press any number key to restart the game" << endl;
			cin >> restartKey;
			cout << endl << endl << endl;
		}
	}
}

void RestartGame()
{
	tailLength = 0;
	score = 0;
	isChooseCompleted = false;
	isGameOver = false;
	PlayerChoice();
}