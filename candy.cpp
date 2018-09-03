#include<stdio.h>
#include"conio.c"
#include<queue>

using namespace std;

const int ROWS = 5;
const int COLUMNS = 5;
const int ITEMSNUMBER = 3;
int board[ROWS][COLUMNS];


typedef struct $
{
	int Row;
	int Column;
} Coord;

Coord setCoord(int row, int column) {
	Coord c;
	c.Row = row;
	c.Column = column;
	return c;
}

queue <Coord> toRemove;

void printBoard() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			printf("%d", board[i][j]);

		}
		printf("\n");
	}
}


void printBoard(int row, int column) {
	int borderColor;
	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLUMNS; j++) {

			if (i == row && column == j) {
				borderColor = 15;
			} else {
				borderColor = 0;
			}
			textcolor(borderColor);
			printf("%c%c%c%c", 201, 205, 205, 187);
		}
		printf("\n");
		for (int j = 0; j < COLUMNS; j++) {

			if (i == row && column == j) {
				borderColor = 15;
			} else {
				borderColor = 0;
			}
			textcolor(borderColor);
			printf("%c", 186);
			textcolor(board[i][j]);
			printf("%c%c", 219, 219);
			textcolor(borderColor);
			printf("%c", 186);
		}
		printf("\n");
		for (int j = 0; j < COLUMNS; j++) {

			if (i == row && column == j) {
				borderColor = 15;
			} else {
				borderColor = 0;
			}
			textcolor(borderColor);
			printf("%c%c%c%c", 200, 205, 205, 188);
		}
		printf("\n");
	}
}

void build() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			board[i][j] = 1 + rand() % ITEMSNUMBER;
		}
	}
}

void printSpaces(int spaces) {
	for (int i = 0; i < spaces; ++i)
	{
		printf("\n");
	}
}

void spawn(int column) {
	board[0][column] = 1 + rand() % ITEMSNUMBER;

}

void gravity(int row, int column) {
	while (board[row + 1][column] == 0 && row < ROWS - 1) {
		board[row + 1][column] = board[row][column];
		board[row][column] = 0;
		row++;
	}
	while (board[0][column] == 0) {
		spawn(column);
		gravity(0, column);
	}
}

void verifyGravity() {
	for (int i = ROWS - 2; i >= 0; i--) {

		for (int j = 0; j < COLUMNS; j++) {
			if (board[i][j] != 0 && board[i + 1][j] == 0) {
				gravity(i, j);
			}
		}
	}
}

void verifyGravityColumn(int column) {
	for (int j = 0; j < COLUMNS; j++) {
		if (board[j][column] != 0 && board[j + 1][column] == 0) {
			gravity(j, column);
		}
	}
}

void removeInColumn(int column, int start, int finish) {
	for (int i = start; i <= finish; i++) {
		toRemove.push(setCoord(i, column));
	}
}

void checkColumn(int column) {
	int color = board[0][column];
	int contColor = 1;
	for (int i = 1; i < ROWS; i++) {
		textcolor(15);

		if (board[i][column] == color) {
			contColor++;
			if (i == ROWS - 1 && contColor > 2) {
				removeInColumn(column, i - contColor + 1, i);
			}
		} else {
			if (contColor > 2) {
				removeInColumn(column, i - contColor, i - 1);
			}
			color = board[i][column];
			contColor = 1;
		}

		/*
				printf("%d %d\n", i, column);
				printf("%d\n", color);
				printf("%d\n\n", contColor);
				for (int c = 1; c <= 32767; c++)
					for (int d = 1; d <= 32767; d++)
					{}*/

	}
}

void checkColumns() {
	for (int i = 0; i < COLUMNS; i++) {
		checkColumn(i);
	}
}

void removeInRow(int row, int start, int finish) {
	for (int i = start; i <= finish; i++) {
		toRemove.push(setCoord(row, i));
	}
}

void checkRow(int row) {
	int color = board[row][0];
	int contColor = 1;
	for (int i = 1; i < ROWS; ++i)
	{
		if (board[row][i] == color) {
			contColor++;
			if (i == COLUMNS - 1 && contColor > 2) {
				removeInRow(row, i - contColor + 1, i);
			}
		} else {
			if (contColor > 2) {
				removeInRow(row, i - contColor, i - 1);
			}
			color = board[row][i];
			contColor = 1;
		}
	}
}

void checkRows() {
	for (int i = 0; i < ROWS; ++i) {
		checkRow(i);
	}
}

void removeRow(int row) {
	for (int i = 0; i < COLUMNS; ++i) {
		board[row][i] = 0;
	}
	verifyGravity();
}

void removeColumn(int column) {
	for (int i = 0; i < COLUMNS; ++i) {
		board[i][column] = 0;
	}

	for (int i = 0; i < ROWS; ++i)
	{
		spawn(column);
		verifyGravity();
	}
}

void remove() {
	Coord c;
	while (!toRemove.empty()) {
		c = toRemove.front();
		toRemove.pop();
		board[c.Row][c.Column] = 0;//12;
	}

}

void switchItens(int row1, int column1) {
	int row2 = row1;
	int column2 = column1;
	int selection = 0;
	while (selection != 93) { //]
		selection = getch();
		switch (selection) {
		case 97: //A
			if (column2 == 0) {
				column2 = COLUMNS - 1;
			} else {
				column2 = (column2 - 1);
			}

			break;
		case 100://D
			column2 = (column2 + 1) % COLUMNS;
			break;
		case 115://S
			row2 = (row2 + 1) % ROWS;
			break;
		case 119: //W
			if (row2 == 0) {
				row2 = ROWS - 1;
			} else {
				row2 = (row2 - 1);
			}
			break;
		}
		clrscr();
		printBoard(row2, column2);
	}
	int aux = board[row1][column1];
	board[row1][column1] = board[row2][column2];
	board[row2][column2] = aux;

	checkColumn(column1);
	checkColumn(column2);
	checkRow(row1);
	checkRow(row2);
	remove();
	verifyGravity();

}



void game(int row, int column) {
	clrscr();
	printBoard(row, column);

	int selection = 0;
	while (selection != 13 && selection != 8) { //Enter
		selection = getch();
		switch (selection) {
		case 97: //A
			if (column == 0) {
				column = COLUMNS - 1;
			} else {
				column = (column - 1);
			}

			break;
		case 100://D
			column = (column + 1) % COLUMNS;
			break;
		case 115://S
			row = (row + 1) % ROWS;
			break;
		case 119: //W
			if (row == 0) {
				row = ROWS - 1;
			} else {
				row = (row - 1);
			}

			break;
		case 45: //-
			build();
			break;
		case 44: //,
			removeRow(row);
			break;
		case 46: //.
			removeColumn(column);
			break;
		case 93: //]
			switchItens(row, column);

			break;
		case 91: //[
			checkColumn(column);
			break;
		}

		clrscr();
		printBoard(row, column);

	}
	if (selection == 13) {
		board[row][column] = 0;
		if (row == 0) {
			spawn(column);
		}
		verifyGravity();
		game(row, column);
	}
}




int main() {
	build();
	game(0, 0);
	textcolor(WHITE);
	printBoard();

	//menu();
	/*
	a = 97
	s = 115
	w = 119
	d = 100
	enter = 13
	backspace = 8
	╔ = 201
	═ = 205
	╗ = 187
	║ = 186
	╝ = 188
	╚ = 200
	█ = 219
	╔═══╗
	║███║
	║███║
	╚═══╝
	▓▓▓
	╔═══╗
	║╔═╗║
	║╚═╝║
	╚═══╝

	╔══╗
	║██║
	╚══╝
	*/


}
