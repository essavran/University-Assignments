/*
* CSE241 - HOMEWORK 1
* Emine Sultan Savran
* 1801042637
*/

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include "helper.h"
using namespace std;

/*
* User select the "valid" board size.
*/
int boardSize(){
	string bSize;
	int size;
	do{
		cout << endl;
		cout << "1. 6x6" << endl;
		cout << "2. 7x7" << endl;
		cout << "3. 8x8" << endl;
		cout << "4. 9x9" << endl;
		cout << "5. 10x10" << endl;
		cout << "6. 11x11" << endl;
		cout << "7. 12x12" << endl;
		cout << "Choice: ";
		getline(cin, bSize);
		if( !isBoardSizeValid(bSize) ){ /*Invalid input*/
			cout << "Enter a valid choice." << endl;
		}
	} while( !isBoardSizeValid(bSize) );
	size = static_cast<int>(bSize[0])-49; /*Type cast char-->int*/
	return size+6;
}
/*To check that the board size is valid or not*/
int isBoardSizeValid(string boardSize){
	if( boardSize.size() == 1 && static_cast<int>(boardSize[0]) >= 49 && static_cast<int>(boardSize[0]) <= 55 ){
		return 1;
	}
	return 0;
}
/*
* User selects the "valid" game mode.
*/
int gameMode(){
	string gMode;
	int mode;
	do{
		cout << endl;
		cout << "1. A two player game" << endl;
		cout << "2. User versus computer game" << endl;
		cout << "Choice: ";
		getline(cin, gMode);
		if( !isModeValid(gMode) ){ /*Invalid input*/
			cout << "Enter a valid choice." << endl;
		}
	} while( !isModeValid(gMode) );
	mode = static_cast<int>(gMode[0])-48; /*Type cast char-->int*/
	return mode;
}
/*To check that the game mode is valid or not*/
int isModeValid(string gMode){
	if( gMode.size() == 1 && static_cast<int>(gMode[0]) >= 49 && static_cast<int>(gMode[0]) <= 50 ){
		return 1;
	}
	return 0;
}
/*To show instantaneous board*/
void showBoard(char board[12][12], int boardSize){
	cout << endl;
	for(int i=0; i<=boardSize; i++){
		if(i == 0){
			int temp = boardSize;
			cout << "   ";
			for(int c=97; temp>0; c++){ /*a b c d e ...*/
				cout << static_cast<char>(c) << " ";
				temp--;
			}
		} else{
			if( i <= 9 ){
				cout << " ";
			}
			cout << i;/*1 2 3 4 5 ...*/

			for(int k=i; k>0; k--){ 
				cout << " ";
			}
			for(int j=0; j<boardSize; j++){
				cout << board[i-1][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
/*To fill initial board with dots*/
void createInitialBoard(char board[12][12], int boardSize){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			board[i][j] = '.';
		}
	}
}
/*
Boolean Array is used in other functions to check recursion.
*/
void createBooleanArray(int boardSize, bool bArray[12][12]){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			bArray[i][j] = false;
		}
	}
}

void twoPlayersGame(char board[12][12], int boardSize){
	/*User VS User*/
	int row,
		validity;
	char column;
	bool bArray[12][12],
		end;
	do{
		do{
			cout << "User1 (x): ";
			cin >> column >> row;
			validity = isValid(row-1, boardSize) && isValid(static_cast<int>(column)-65, boardSize) && board[row-1][static_cast<int>(column)-65] == '.';

			if( validity == 0 ){ 
				cout << "Enter a valid move." << endl;
			}
		} while( validity != 1 );
		board[row-1][static_cast<int>(column)-65] = 'x';
		createBooleanArray(boardSize, bArray);
		end = isBoardFull(board, boardSize) != 1 && win_o(board, boardSize, bArray) != 1 && win_x(board, boardSize, bArray) != 1;
		showBoard(board, boardSize);	
		if( end ){
			do{
				cout << "User2 (o): ";
				cin >> column >> row;
				validity = isValid(row-1, boardSize) && isValid(static_cast<int>(column)-65, boardSize) && board[row-1][static_cast<int>(column)-65] == '.';

				if( validity == 0 ){ 
					cout << "Enter a valid move." << endl;
				}
			} while( validity != 1 );
			board[row-1][static_cast<int>(column)-65] = 'o';
			createBooleanArray(boardSize, bArray);
			end = isBoardFull(board, boardSize) != 1 && win_o(board, boardSize, bArray) != 1 && win_x(board, boardSize, bArray) != 1;
			showBoard(board, boardSize);
		}
	} while( end );
}

void versusCompGame(char board[12][12], int boardSize){
	int moveArray[3],
		validity, row;
	char column;
	bool bArray[12][12],
		end;
	moveArray[0] = 1;
	do{
		if( moveArray[0]%2 == 1 ){
			//Computer
			computer( board, boardSize, moveArray );
			createBooleanArray(boardSize, bArray);
			end = isBoardFull(board, boardSize) != 1 && win_o(board, boardSize, bArray) != 1 && win_x(board, boardSize, bArray) != 1;
			showBoard(board, boardSize);
		} else if ( moveArray[0]%2 == 0 ){
			//User
			if( end ){
				do{
					cout << "User (o): ";
					cin >> column >> row;
					validity = isValid(row-1, boardSize) && isValid(static_cast<int>(column)-65, boardSize) && board[row-1][static_cast<int>(column)-65] == '.';

					if( validity == 0 ){ 
						cout << "Enter a valid move." << endl;
					}
				} while( validity != 1 );
				board[row-1][static_cast<int>(column)-65] = 'o';
				moveArray[1] = row-1;
				moveArray[2] = static_cast<int>(column)-65;
				createBooleanArray(boardSize, bArray);
				end = isBoardFull(board, boardSize) != 1 && win_o(board, boardSize, bArray) != 1 && win_x(board, boardSize, bArray) != 1;
				showBoard(board, boardSize);				
			}
		}
		moveArray[0]++;
	} while( end );
}

void computer(char board[12][12], int boardSize, int moveArray[3]){
	if( moveArray[0] == 1 ){ //Computer's first move
		/*Select a place randomly*/
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937 gen(seed);
		uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
		int randomRow = dist(gen),
			randomColumn = dist(gen);
		cout << "Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
		board[randomRow][randomColumn] = 'x';
	} else{
		/*To block user's movements*/
		int possibleMoves[6][2];
		createPossibleMoves( board,boardSize,moveArray,possibleMoves );
		int random=0,
			count=0;
		do{
			if( possibleMoves[random][0] == -1 ){
				random++;
			}
		} while( possibleMoves[random][0] == -1 && random<6 );
		
		for(int i=0; i<6; i++){
			if(possibleMoves[i][0] == -1)	count++;
		}
		if(count == 6){ /*There is no possible moves so need random numbers*/
			unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			mt19937 gen(seed);
			uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
			int randomRow = dist(gen),
			randomColumn = dist(gen);
			cout << "Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
			board[randomRow][randomColumn] = 'x';
		} else{ 
			cout << "Computer (x): " << static_cast<char>(possibleMoves[random][1]+65) << " " << possibleMoves[random][0]+1 << endl;
			board[possibleMoves[random][0]][possibleMoves[random][1]] = 'x';			
		}
	}
}

void createPossibleMoves( char board[12][12], int boardSize,  int moveArray[3], int possibleMoves[6][2] ){
	int userRow = moveArray[1],
		userColumn = moveArray[2];
	for(int i=0; i<6; i++){
		for(int j=0; j<2; j++){
			possibleMoves[i][j] = -1;
		}
	}
	if( isValid(userRow-1,boardSize) && board[userRow-1][userColumn] == '.' ){ //To left-up
		possibleMoves[0][0] = userRow-1;
		possibleMoves[0][1] = userColumn;
	}
	if( isValid(userRow-1,boardSize) && isValid(userColumn+1,boardSize) && board[userRow-1][userColumn+1] == '.' ){ //To right-up
		possibleMoves[1][1] = userColumn+1;
	}
	if( isValid(userRow+1,boardSize) && board[userRow+1][userColumn] == '.' ){ //To right-down
		possibleMoves[2][0] = userRow+1;
		possibleMoves[2][1] = userColumn;
	}
	if( isValid(userRow+1,boardSize) && isValid(userColumn-1,boardSize) && board[userRow+1][userColumn-1] == '.' ){ //To left-down
		possibleMoves[3][0] = userRow+1;
		possibleMoves[3][1] = userColumn-1;
	}
	if( isValid(userColumn-1,boardSize) && board[userRow][userColumn-1] == '.' ){ //To left
		possibleMoves[4][0] = userRow;
		possibleMoves[4][1] = userColumn-1;
	}
	if( isValid(userColumn+1,boardSize) && board[userRow][userColumn+1] == '.' ){ //To right
		possibleMoves[5][0] = userRow;
		possibleMoves[5][1] = userColumn+1;
	}
}

int isCompMoveValid( int row, int column, int boardSize ){
	if( row>=0 && row<boardSize &&
		column >=0 && column<boardSize){
		return 1;
	} else {
		return 0;
	}
}
/*To check that board is filled*/
int isBoardFull(char board[12][12], int boardSize){
	int count = 0;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( board[i][j] == 'x' || board[i][j] == 'o' ){
				count++;
			}
		}
	}
	if(count == boardSize*boardSize){
		cout << endl << "---> Board is filled." << endl;
		return 1;
	} else {
		return 0;
	}
}

int isValid(int index, int boardSize){
	if( index<0 || index>=boardSize ){
		return 0;
	}
	return 1;
}

int win_o(char board[12][12], int boardSize, bool bArray[12][12]){
	int counter[4];
	counter[0] = boardSize;
	counter[3] = -1;
	//counter[1]; row
	//counter[2]; column
	for(int i=0; i<boardSize; i++){
		if( board[0][i] == 'o' ){ /*There is 'o'*/
			bArray[0][i] = true;
			board[0][i] -= 32;
			if( isValid(i-1, boardSize) ){ // To down
				counter[1] = 1;
				counter[2] = i-1;
				winRecursion_o( board, bArray, counter);
			}
			if( isValid(i, boardSize) ){ // To left-down
				counter[1] = 1;
				counter[2] = i;
				winRecursion_o( board, bArray, counter);
			}
			if( counter[0] == counter[3] ){ /*Winner is 'o'*/
				cout << endl << "---> O is winner." << endl;
				return 1;
			} else{
				convertLowerCase(board, boardSize); /*Back to lower case because 'o' is not winner*/
			}
		}
	}
	return 0;
	
}

void winRecursion_o(char board[12][12], bool bArray[12][12], int counter[4] ){
	int boardSize = counter[0],
		row = counter[1],
		column = counter[2];
	if( board[row][column] == 'o' ){
		bArray[row][column] = true;
		board[row][column] -= 32;

		if( isValid(column+1, boardSize) && bArray[row][column+1] != true ){ //To right
			counter[2]++;
			winRecursion_o( board, bArray, counter );
			counter[2]--;
		}
		if( isValid(column-1, boardSize && bArray[row][column-1] != true ) ){ // To left
			counter[2]--;
			winRecursion_o( board, bArray, counter );
			counter[2]++;
		}
		if( isValid(column-1, boardSize) && isValid(row+1, boardSize) ){  //To left-down
			counter[1]++;
			counter[2]--;
			winRecursion_o( board, bArray, counter );
			counter[1]--;
			counter[2]++;
		}
		if( isValid(row+1, boardSize) ){ //To right-down
			counter[1]++;
			winRecursion_o( board, bArray, counter );
			counter[1]--;
		}
		if( counter[0]-1 == counter[1] ){ 
			counter[3] = counter[0];
		} else if( counter[3] != counter[0] && bArray[row][column+1] != true ){
			bArray[row][column] = false;
			board[row][column] += 32;

		}
	}
}
/*
* win_x and winRecursion_x work like win_o and winRecursion_o
*/
int win_x(char board[12][12], int boardSize, bool bArray[12][12]){
	int counter[4];
	counter[0] = boardSize;
	counter[3] = -1;
	for(int i=0; i<boardSize; i++){
		if( board[i][0] == 'x' ){ 
			bArray[i][0] = true;
			board[i][0] -= 32;
			if( isValid(i-1, boardSize) ){ 
				counter[1] = i-1;
				counter[2] = 1;
				winRecursion_x( board, bArray, counter);
			}
			if( isValid(i, boardSize) ){ 
				counter[1] = i;
				counter[2] = 1;
				winRecursion_x( board, bArray, counter);

			}
			if( counter[0] == counter[3] ){
				cout << endl << "---> X is winner." << endl;
				return 1;

			} else{
				convertLowerCase(board, boardSize);
			}
		}
	}
	return 0;
	
}

void winRecursion_x(char board[12][12], bool bArray[12][12], int counter[4] ){
	int boardSize = counter[0],
		row = counter[1],
		column = counter[2];
		if( board[row][column] == 'x' ){
			bArray[row][column] = true;
			board[row][column] -= 32;
			if( isValid(column+1, boardSize) && isValid(row-1, boardSize) ){ 
				counter[2]++;
				counter[1]--;
				winRecursion_x( board, bArray, counter );
				counter[2]--;
				counter[1]++;
			}
			if( isValid(row-1, boardSize && bArray[row-1][column] != true ) ){
				counter[1]--;
				winRecursion_x( board, bArray, counter );
				counter[1]++;
			}
			if( isValid(row+1, boardSize) && bArray[row+1][column] != true ){
				counter[1]++;
				winRecursion_x( board, bArray, counter );
				counter[1]--;
			}
			if( isValid(column+1, boardSize) ){
				counter[2]++;
				winRecursion_x( board, bArray, counter );
				counter[2]--;
			}
			if( counter[0]-1 == counter[2] ){
				counter[3] = counter[0];
			} else if( counter[3] != counter[0] && bArray[row-1][column+1] != true){
				bArray[row][column] = false;
				board[row][column] += 32;

			}
	}
}
/*
* To convert to lower case elements of board
*/
void convertLowerCase(char board[12][12], int boardSize){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( board[i][j] == 'X' || board[i][j] == 'O' ){
				board[i][j] += 32;
			}
		}
	}
}