#include <iostream>
using namespace std;
int grid[9][9] =
{
{ 3, 0, 6, 5, 0, 8, 4, 0, 0 },
{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };


static bool isGridValid(int r, int c, int num) {
	int count = 0;

	for (int i = 0; i < 9; i++) {
		if (grid[r][i] == num)
			count++;
	}
	if (count > 1)
		return false;


	count = 0;
	for (int i = 0; i < 9; i++) {
		if (grid[i][c] == num)
			count++;
	}
	if (count > 1)
		return false;


	int row = r - r % 3, col = c - c % 3;
	count = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (grid[i+row][j+col] == num)
				count++;
	if (count > 1)
		return false;
	return true;
}

static bool fill(int r, int c) {
	int nextR, nextC;
	if (c == 8) {
		nextC = 0;
		nextR = r + 1;
	}
	else {
		nextC = c + 1;
		nextR = r;
	}

	if (grid[r][c]) {
		//non empty 
		return fill(nextR, nextC);
	}
	
	for (int i = 1; i <= 9; i++) {
		grid[r][c] = i;

		if (isGridValid(r, c, i) == false)
			continue;

		//grid is valid
		if (r == 8 && c == 8)
			return true;
		
		if (fill(nextR, nextC))
			return true;
	}
	grid[r][c] = 0;
	return false;
}

static void printGrid() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

int main_sudoku() {
	
	fill(0, 0);
	printGrid();

	return 0;
}