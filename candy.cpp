#include<stdio.h>
#include"conio.c"
#include<queue>

using namespace std;

const int rows = 5;
const int columns = 5;
const int itemsNumber = 3;
int board[rows][columns];


typedef struct $
{
int Row;
int Column;	
}Coord;

Coord setCoord(int row, int column){
	Coord c;
	c.Row = row;
	c.Column = column;
	return c;
}

queue <Coord> toRemove;

void printBoard(){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			printf("%d", board[i][j]);

		}
		printf("\n");	
	}
}

void printBoard(int row, int column){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			textcolor(board[i][j]);
			if(i == row && column == j){
				textcolor(14);
			}
			//printf("%d", board[i][j]);
			
			printf("%c", 254);
			if(j != columns - 1){
			
				printf(" ");
			}
		}
		printf("\n");	
	}
}

void build(){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			board[i][j] = 1 + rand() % itemsNumber;
		}
	}
}

void printSpaces(int spaces){
	for (int i = 0; i < spaces; ++i)
	{
		printf("\n");
	}
}




void spawn(int column){	
	board[0][column] = 1 + rand() % itemsNumber;
	//verifyGravityColumn(column);
}

void gravity(int row, int column){
	while(board[row + 1][column] == 0 && row < rows - 1){
		board[row + 1][column] = board[row][column];
		board[row][column] = 0;
		row++;
	}
	while(board[0][column] == 0){
		spawn(column);
		gravity(row, column);
	}
}



void verifyGravity(){
	for (int i = rows - 2; i >= 0; i--){
		
		for (int j = 0; j < columns; j++){
			if(board[i][j] != 0 && board[i + 1][j] == 0){
				gravity(i, j);
			}	
		}
	}
}

void verifyGravityColumn(int column){	
	for (int j = 0; j < columns; j++){
		if(board[j][column] != 0 && board[j + 1][column] == 0){
			gravity(j, column);
		}	
	}	
}




void removeInColumn(int column, int start, int finish){
	for (int i = start; i <= finish; ++i)
	{
		toRemove.push(setCoord(i, column));
	}

	/*for (int i = 0; i < rows; ++i)
	{
		verifyGravity();
		spawn(column);
	}*/
}

void checkColumn(int column){
	int color = board[0][column];
	int contColor = 1;
	for (int i = 1; i < rows; i++){
		if(board[i][column] == color){
			contColor++;
		}else{
			if(contColor > 2){
				removeInColumn(column, i - contColor, i - 1);			
			}
			color = board[i][column];
			contColor = 1;
		}
		
	}
}

void checkColumns(){
	for (int i = 0; i < columns; ++i)
	{
		checkColumn(i);
	}
}

void removeInRow(int row, int start, int finish){
	for (int i = start; i <= finish; ++i)
	{
		toRemove.push(setCoord(row, i));
	}

	/*for (int i = 0; i < rows; ++i)
	{
		verifyGravity();
		spawn(column);
	}*/
}

void checkRow(int row){
	int color = board[row][0];
	int contColor = 1;
	for (int i = 1; i < rows; ++i)
	{
		if(board[row][i] == color){
			contColor++;
		}else{
			if(contColor > 2){
				removeInRow(row, i - contColor, i - 1);			
			}
			color = board[row][i];
			contColor = 1;
		}	
	}
}

void checkRows(){
	for (int i = 0; i < rows; ++i){
		checkRow(i);
	}
}

void removeRow(int row){
	for (int i = 0; i < columns; ++i){
		board[row][i] = 0;
	}
	verifyGravity();
}

void removeColumn(int column){
	for (int i = 0; i < columns; ++i){
		board[i][column] = 0;
	}

	for (int i = 0; i < rows; ++i)
	{
		spawn(column);
		verifyGravity();
	}		
}

void remove(){
	Coord c;
	while(!toRemove.empty()){
		c = toRemove.front();
		toRemove.pop();		
		board[c.Row][c.Column] = 12;
	}

}

void switchItens(int row1, int column1){
	int row2 = row1;
	int column2 = column1;
	int selection = 0;
	while(selection != 93){ //]
		selection = getch();
		switch(selection){
			case 97: //A
				if(column2 == 0){
					column2 = columns - 1;
				}else{
					column2 = (column2 - 1);	
				}
				
			break;
			case 100://D
				column2 = (column2 + 1) % columns;
			break;
			case 115://S
				row2 = (row2 + 1) % rows;
			break;
			case 119: //W
				if(row2 == 0){
					row2 = rows - 1;
				}else{
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

	checkColumns();
	//checkRows();
	remove();
	verifyGravity();

}



void game(int row, int column){
	clrscr();
	printBoard(row, column);

	int selection = 0;
	while(selection != 13 && selection != 8){ //Enter
		selection = getch();
		switch(selection){
			case 97: //A
				if(column == 0){
					column = columns - 1;
				}else{
					column = (column - 1);	
				}
				
			break;
			case 100://D
				column = (column + 1) % columns;
			break;
			case 115://S
				row = (row + 1) % rows;
			break;
			case 119: //W
				if(row == 0){
					row = rows - 1;
				}else{
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
		}
		
		clrscr();		
		printBoard(row,column);
		
	}
	if(selection == 13){
		board[row][column] = 0;
		if(row == 0){
			spawn(column);
		}
		verifyGravity();
		game(row, column);
	}
}


/*
void remove(){
	int row, column;
	printf("type the row and the column of the cell that you want to remove");
	scanf("%d %d", &row, &column);
	board[row][column] = 0;
	verifyGravity();
}


void menu(){
	int op = 20;
	
	while(op != 0){
		scanf("%d", &op);		
		switch(op){
			case 1:
				remove();
				break;
			case 2:
				printSpaces(2);
				printBoard();
				break;

		}
	}	
}*/

int main(){
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
	*/

	
}
