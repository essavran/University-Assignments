/*
* CSE241 - HOMEWORK 2
* Emine Sultan Savran
* 1801042637
*/

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include "helper.h"
using namespace std;

// User select the "valid" board size.
int boardSize(){
	string bSize;
	int size;
	do{
		cout << endl
			 << "1. 6x6" << endl
			 << "2. 7x7" << endl
			 << "3. 8x8" << endl
			 << "4. 9x9" << endl
			 << "5. 10x10" << endl
			 << "6. 11x11" << endl
			 << "7. 12x12" << endl
			 << "Choice: ";
		getline(cin, bSize);
		if( !isBoardSizeValid(bSize) ){ // Invalid input
			cerr << "Enter a valid choice." << endl;
		}
	} while( !isBoardSizeValid(bSize) );
	size = strToInt(bSize, 0); // Type cast char-->int
	return size+6;
}
// To check that the board size is valid or not
int isBoardSizeValid(string boardSize){
	if( boardSize.size() == 1 && static_cast<int>(boardSize[0]) >= 49 && static_cast<int>(boardSize[0]) <= 55 ){
		return 1;
	}
	return 0;
}
// User selects the "valid" game mode.
int gameMode(){
	string gMode;
	int mode;
	do{
		cout << endl
			 << "1. Two players game" << endl
		 	 << "2. User versus computer game" << endl
			 << "Choice: ";
		getline(cin, gMode);
		if( !isModeValid(gMode) ){ // Invalid input
			cerr << "Enter a valid choice." << endl;
		}
	} while( !isModeValid(gMode) );
	mode = strToInt(gMode, 0) + 1; // Type cast char-->int
	return mode;
}
//To check that the game mode is valid or not
int isModeValid(string gMode){
	if( gMode.size() == 1 && static_cast<int>(gMode[0]) >= 49 && static_cast<int>(gMode[0]) <= 50 ){
		return 1;
	}
	return 0;
}
//To show instantaneous board
void showBoard(const char board[12][12], const int boardSize){
	cout << endl;
	for(int i=0; i<=boardSize; i++){
		if(i == 0){
			int temp = boardSize;
			cout << "   ";
			for(int c=97; temp>0; c++){ // a b c d e ...
				cout << static_cast<char>(c) << " ";
				temp--;
			}
		} else{
			if( i <= 9 ){
				cout << " ";
			}
			cout << i;//1 2 3 4 5 ...

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
//To fill initial board with dots
void createInitialBoard(char board[12][12], int boardSize){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			board[i][j] = static_cast<char>(cellState::dot);
		}
	}
}
//Boolean Array is used in other functions to check recursion.
void createBooleanArray(int &boardSize, bool bArray[12][12]){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			bArray[i][j] = false;
		}
	}
}

void twoPlayersGame(char board[12][12], int &boardSize, char &user){
	// User VS User
	string input;
	bool bArray[12][12],
		gameOver,
		validity;
	int gameMode = 1;
	do{
		do{
			if( user == static_cast<char>(cellState::x) ){
				cout << "-> User1 (x): ";
			} else{
				cout << "-> User2 (o): ";
			}
			getline(cin, input);
			validity = checkInput(board, boardSize, input, bArray, user, gameMode);
			if( gameMode == 2 ){ // Goes the computervsuser game mode.
				showBoard(board, boardSize);
				versusCompGame(board, boardSize, user);
				return;
			}
			if( validity == false ){ 
				cerr << "-> Invalid input. Please enter a valid input." << endl;
			} 
		}while( validity == false );
		gameOver = end(board, boardSize, bArray);
		showBoard(board, boardSize);
	} while( !gameOver );
}

/*
* Game mode:
* 1 -> user vs user game.
* 2 -> computer vs user game.
*/
void save( char board[12][12], int &boardSize, const string &input, char user, int gameMode){
	string fileName = input;
	fileName.erase(0,5);
	ofstream myfile (fileName);
	if(myfile.is_open()){
		cout << endl
			 << "-> Saving..." << endl;
		myfile << boardSize << endl;	
		myfile << gameMode << endl;	
		myfile << user << endl;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				myfile << board[i][j];
			}
			myfile << endl;			
		}
		cout << "-> Done." << endl;
	} else{
		cerr << "-> File cannot open." << endl;
	}
}

void move(char board[12][12], const string &input, char &user){
	int row = strToInt(input),
		column = static_cast<int>(input[0])-65;
	board[row][column] = user;
}

bool end(char board[12][12], int &boardSize, bool bArray[12][12]){
	return isBoardFull(board, boardSize) == 1 || win_o(board, boardSize, bArray) == 1 || win_x(board, boardSize, bArray) == 1;
}

bool isFileNameValid(const string &input){
	auto isSpaceChar = input.find( " " );
	if( isSpaceChar == 4 && input[5] != '.' ){
		for( int i=5; i<static_cast<int>(input.size())-4; i++){
			if( input[i] == ' ' || input[i] == '.' ){
				return false;
			}
		}
		return true;
	} else{
		return false;
	}
}

bool isLoadOrSave(const string &input, const string str){
	auto check = input.find( str );
	auto txt = input.find( ".txt" );
	auto TXT = input.find( ".TXT" );
	if( check == 0 && isFileNameValid(input) && (static_cast<int>(txt) != -1 || static_cast<int>(TXT) != -1) ){
		return true;
	}
	return false;
}

bool isMoveValid(char board[12][12], int &boardSize, const string &input){
	// Move must start with A,B,...
	// And the second char must be space char.
	// The last char must be 1,2,...10,11 etc.
	if( input.size() == 3 && input[1] == ' ' && input[2] != ' ' 
		&& input[2] >= '1' && input[2] <= '9' ){
		int row = strToInt(input),
		column = static_cast<int>(input[0])-65;
		return isValid(row, boardSize) && isValid(column, boardSize) && board[row][column] == static_cast<char>(cellState::dot);
	}
	if( input.size() == 4 && input[1] == ' ' && input[2] != ' ' 
		&& input[2] >= '1' && input[2] <= '9'
		&& input[3] >= '0' && input[3] <= '9'){
		int row = strToInt(input),
		column = static_cast<int>(input[0])-65;
		return isValid(row, boardSize) && isValid(column, boardSize) && board[row][column] == static_cast<char>(cellState::dot);
	}
	return false;
}

int strToInt(const string &input, int toEnd){ 
	// str ---> int 
	string str = input;
	str.erase(0,toEnd);
	return stoi(str)-1;
}

void load( char board[12][12], int &boardSize, const string &input, char &user, int &gameMode){
	string fileName = input;
	fileName.erase(0,5);
	ifstream myfile (fileName);
	
	if(myfile.is_open()){
		cout << endl
			 << "-> Loading..." << endl;
		myfile >> boardSize;
		myfile >> gameMode;	
		myfile >> user;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				myfile >> board[i][j];
			}
		}
		cout << "-> Done." << endl;
	} else{
		cerr << "-> File cannot open." << endl;
	}
}

bool checkInput(char board[12][12], int &boardSize, const string &input, bool bArray[12][12], char &user, int &gameMode){
	if( isLoadOrSave(input, "LOAD") ){ //LOAD 
		load(board, boardSize, input, user, gameMode);		
	} else if( isLoadOrSave(input, "SAVE") ){ //SAVE
		save(board, boardSize, input, user, gameMode);
	} else if( isMoveValid(board, boardSize, input) ){ //MOVE
		createBooleanArray(boardSize, bArray);
		move(board, input, user);
		if( user == static_cast<char>(cellState::x) ){
			user = static_cast<char>(cellState::o);
		} else if( user == static_cast<char>(cellState::o) ){
			user = static_cast<char>(cellState::x);
		}
	} else{ // Invalid input
		return false;
	}
	return true;
}

void versusCompGame(char board[12][12], int &boardSize, char &user){
	int moveArray[3];
	string input;
	bool bArray[12][12],
		gameOver,
		validity;
	int gameMode = 2;

	if( user == static_cast<char>(cellState::x)){
		moveArray[0] = 1;
	} else if( user == static_cast<char>(cellState::o) ){
		moveArray[0] = 2;
	}
	do{

		if( moveArray[0]%2 == 1 ){
			// Computer
			computer( board, boardSize, moveArray );
			createBooleanArray(boardSize, bArray);
			gameOver = end(board, boardSize, bArray);
			showBoard(board, boardSize);
			moveArray[0]++;

		} else if ( moveArray[0]%2 == 0 && !gameOver ){
			do{
				user = static_cast<char>(cellState::o);
				cout << "-> User (o): ";
				getline(cin, input);
				validity = checkInput(board, boardSize, input, bArray, user, gameMode);
				if( gameMode == 1 ){ // Goes the uservsuser game mode.
					showBoard(board, boardSize);
					twoPlayersGame(board, boardSize, user);
					return;
				}
				if( validity == false ){ 
					cerr << "-> Invalid input. Please enter a valid input." << endl;
				} 
			}while( validity == false );
			if(input[1] == ' '){
				moveArray[1] = strToInt(input);
				moveArray[2] = static_cast<int>(input[0])-65;
				moveArray[0]++;
				
			}
			
			gameOver = end(board, boardSize, bArray);
			showBoard(board, boardSize);
		}
	} while( !gameOver );
}

void computer(char board[12][12], int boardSize, int moveArray[3]){
	if( moveArray[0] == 1 ){ // Computer's first move
		// Select a place randomly
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937 gen(seed);
		uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
		int randomRow = dist(gen),
			randomColumn = dist(gen);
		cout << "-> Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
		board[randomRow][randomColumn] = static_cast<char>(cellState::x);
	} else{
		// To block user's movements
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
		if(count == 6){ // There is no possible moves so need random numbers
			unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			mt19937 gen(seed);
			uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
			int randomRow = dist(gen),
			randomColumn = dist(gen);
			cout << "-> Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
			board[randomRow][randomColumn] = static_cast<char>(cellState::x);
		} else{ 
			cout << "-> Computer (x): " << static_cast<char>(possibleMoves[random][1]+65) << " " << possibleMoves[random][0]+1 << endl;
			board[possibleMoves[random][0]][possibleMoves[random][1]] = static_cast<char>(cellState::x);			
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
	if( isValid(userRow-1,boardSize) && board[userRow-1][userColumn] == static_cast<char>(cellState::dot) ){ //To left-up
		possibleMoves[0][0] = userRow-1;
		possibleMoves[0][1] = userColumn;
	}
	if( isValid(userRow-1,boardSize) && isValid(userColumn+1,boardSize) && board[userRow-1][userColumn+1] == static_cast<char>(cellState::dot) ){ //To right-up
		possibleMoves[1][1] = userColumn+1;
	}
	if( isValid(userRow+1,boardSize) && board[userRow+1][userColumn] == static_cast<char>(cellState::dot) ){ //To right-down
		possibleMoves[2][0] = userRow+1;
		possibleMoves[2][1] = userColumn;
	}
	if( isValid(userRow+1,boardSize) && isValid(userColumn-1,boardSize) && board[userRow+1][userColumn-1] == static_cast<char>(cellState::dot) ){ //To left-down
		possibleMoves[3][0] = userRow+1;
		possibleMoves[3][1] = userColumn-1;
	}
	if( isValid(userColumn-1,boardSize) && board[userRow][userColumn-1] == static_cast<char>(cellState::dot) ){ //To left
		possibleMoves[4][0] = userRow;
		possibleMoves[4][1] = userColumn-1;
	}
	if( isValid(userColumn+1,boardSize) && board[userRow][userColumn+1] == static_cast<char>(cellState::dot) ){ //To right
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
// To check that board is filled
int isBoardFull(char board[12][12], int boardSize){
	int count = 0;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( board[i][j] == static_cast<char>(cellState::x) || board[i][j] == static_cast<char>(cellState::o) ){
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
		if( board[0][i] == static_cast<char>(cellState::o) ){ // There is 'o'
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
			if( counter[0] == counter[3] ){ // Winner is 'o'
				cout << endl << "---> O is winner." << endl;
				return 1;
			} else{
				convertLowerCase(board, boardSize); // Back to lower case because 'o' is not winner
			}
		}
	}
	return 0;	
}

void winRecursion_o(char board[12][12], bool bArray[12][12], int counter[4] ){
	int boardSize = counter[0],
		row = counter[1],
		column = counter[2];
	if( board[row][column] == static_cast<char>(cellState::o) ){
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
// win_x and winRecursion_x work like win_o and winRecursion_o
int win_x(char board[12][12], int boardSize, bool bArray[12][12]){
	int counter[4];
	counter[0] = boardSize;
	counter[3] = -1;
	for(int i=0; i<boardSize; i++){
		if( board[i][0] == static_cast<char>(cellState::x) ){ 
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
		if( board[row][column] == static_cast<char>(cellState::x) ){
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
// To convert to lower case elements of board
void convertLowerCase(char board[12][12], int boardSize){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( board[i][j] == 'X' || board[i][j] == 'O' ){
				board[i][j] += 32;
			}
		}
	}
}