#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>

using namespace std;
char start;
void map(int A[][100], int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			A[i][j] = 1;
			A[0][1] = 0;
			A[size - 1][size - 2] = 0;
			A[size][size - 2] = 2;
			A[-1][1] = 1;
		}
	}


	for (i = 0; i < size; i++)
	{
		for (j = 1; j < size - 1; j++)
		{
			if (i == 1 || i == size - 2)
				A[i][j] = 0;
		}
	}
	for (i = 1; i < size / 3; i++)
		A[i][size / 2] = 0;

	for (j = size / 3; j < 3 * size / 4; j++)
		A[size / 3][j] = 0;
	for (i = size / 6; i < 2 * size / 3; i++)
		A[i][size / 3] = 0;
	A[size / 6][size / 3] = 3;
	for (j = size / 4; j < 2 * size / 3; j++)
		A[2 * size / 3][j - 1] = 0;
	for (i = 2 * size / 3; i < size - 2; i++)
		A[i][2 * size / 3 - 1] = 0;
	for (i = 1; i < size / 2; i++)
		A[i][size - 2] = 0;
	for (j = 3 * size / 4; j < size - 1; j++)
		A[size / 2][j] = 0;
	A[size / 2][3 * size / 4] = 3;
	for (i = 1; i < size / 2; i++)
		A[i][2] = 0;
	A[size / 2 - 1][2] = 3;

	int a;
	srand(time(NULL));
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			a = rand() % 6 + 4;
			if (a == 5 && A[i][j] == 0)
			{
				A[i][j] = 5;
			}
		}
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (A[i][j] == 5)
				cout << "$";
			if (A[i][j] == 3)
				cout << "*";
			if (A[i][j] == 0)
				cout << " ";
			if (A[i][j] == 1)
				cout << char(219);
			if (A[i][j] == 2)
				cout << " ";
		}
		cout << endl;
	}
}
void gogo(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y + 3;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void move(int A[][100], int size)
{
	int x = 1;
	int y = 0;
	int xcln = 1;
	int ycln = 0;
	int k = 0;
	int M1[200], M2[200], i = 0;

	int movecounter = 0;

	ofstream coordinat;
	coordinat.open("Coordinat.txt");
	coordinat << "x|y\n";

	while (true)
	{
		gogo(xcln, ycln);
		cout << " ";
		gogo(x, y);
		cout << 'M';
		start = _getch();
		xcln = x;
		ycln = y;


		if (start == 'w')
		{
			y -= 1;
			M1[i] = y;
			M2[i] = x - 1;
			i++;
			movecounter++;
		}
		else if (start == 's')
		{
			y += 1;
			M1[i] = y;
			M2[i] = x - 1;
			i++;
			movecounter++;
		}
		else if (start == 'a')
		{
			x -= 1;
			M2[i] = x - 1;
			M1[i] = y;
			i++;
			movecounter++;
		}
		else if (start == 'd')
		{
			x += 1;
			M2[i] = x - 1;
			M1[i] = y;
			i++;
			movecounter++;
		}

		M1[0] = 0;
		M2[0] = 1;

		if (A[y][x] == 5)
		{
			A[y][x] = 0;
			k++;
		}
		if (A[y][x] == 1)
		{
			x = xcln;
			y = ycln;
		}
		else if (A[y][x] == 3)
		{
			system("cls");
			x = 1;
			y = 0;
			k = 0;
			cout << "\n\n\n";
			map(A, size);
		}
		else if (A[y][x] == 2)
		{
			cout << endl << endl << "\nYou Win" << endl;
			cout << "Gold: " << k << endl;


			M2[movecounter - 3] = size - 2;
			M2[movecounter - 2] = size - 2;

			for (i = 0; i < movecounter - 1; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					if (j == 0)
						coordinat << M1[i];
					if (j == 0)
						coordinat << "|";
					if (j == 1)
						coordinat << M2[i];
				}
				coordinat << "\n";
			}
			coordinat.close();
			break;
		}

	}
}
int main()
{
	int size;
	cout << "Please use w, a, s, d to move. * is monster, $ is gold. \n";
	cout << "Enter dimension of the game: ";
	int A[100][100];
	cin >> size;
	cout << endl;
	map(A, size);
	move(A, size);
	system("color A");
	_getch;
	cout << endl << endl << endl;
	system("pause");
	return 0;
}