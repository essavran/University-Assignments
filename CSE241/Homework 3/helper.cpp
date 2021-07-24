/*
* CSE241 - HOMEWORK 3
* Emine Sultan Savran
* 1801042637
*/

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include "helper.h"
using namespace std;

Hex::Hex(void){ 
	start = 0;
	playGame();
}

Hex::Hex(int size) : boardSize(size){
	setGameMode();
}

Hex::Hex(int size, int mode) : boardSize(size), gameMode(mode){
//bilerek boş
}

void Hex::playGame(void){
	if( start == 0 ){
	//	welcome();
		setBoardSize();
		setGameMode();
		createInitialBoard();
		start = 1;		
	} else if( start == 1 ){
		showBoard();
		if( gameMode == 1 ){ //User vs User
			twoPlayersGame();
		} else if( gameMode == 2 ){ //User vs Computer
			versusCompGame();
		}
	//	goodbye();		
	}
}

void Hex::welcome(void) const{
	cout << endl << "******* Welcome to HEX Game *******" << endl << endl;
}

void Hex::goodbye(void) const{
	cout << "Goodbye!" << endl << endl;/*Game is over. Goodbye!*/
}
// User select the "valid" board size.
void Hex::setBoardSize(void){
	string strSize;
	do{
		cout << endl
			 << "Please enter edge length of the game board." << endl
			 << "Choice: ";
		getline(cin, strSize);
		if( !isBoardSizeValid(strSize) ){ // Invalid input
			cerr << "Enter a valid choice." << endl;
		}
	} while( !isBoardSizeValid(strSize) );
	boardSize = stoi(strSize); // Type cast char-->int
}
// To check that the board size is valid or not
bool Hex::isBoardSizeValid(string strSize){
	if( strSize.size() == 1 && //input's size is 1. So input must be 6,7,8, or 9
		strSize[0] > '5' &&
		strSize[0] <= '9' ){
		return true;
	} else if( 	strSize.size() == 2 && //input's size is 2. So input must be 10,11,...
				strSize[0] >= '1' &&
				strSize[0] <= '9' &&
				strSize[1] >= '0' &&
				strSize[1] <= '9' ){
		return true;
	}
	return false;
}

void Hex::setGameMode(void){
	string strMode;
	do{
		cout << endl
			 << "1. Two players game" << endl
		 	 << "2. User versus computer game" << endl
			 << "Choice: ";
		getline(cin, strMode);
		if( !isModeValid(strMode) ){ // Invalid input
			cerr << "Enter a valid choice." << endl;
		}
	} while( !isModeValid(strMode) );
	gameMode = stoi(strMode); // Type cast char-->int
}

bool Hex::isModeValid(string strMode){
	if( strMode.size() == 1 && 
		(strMode[0] == '1' || strMode[0] <= '2') ){
		return 1;
	}
	return 0;
}

void Hex::createInitialBoard(void){
	for(int i=0; i<boardSize; i++){
		hexCells.push_back( vector<Cell>() );

		for(int j=0; j<boardSize; j++){
			hexCells[i].push_back( Cell() );//Filled with dot
			hexCells[i][j].setRowColumn(i, j); 
		}
	}
}

void Hex::showBoard(void){
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
				cout << hexCells[i-1][j].getUser() << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Hex::setWidthHeight(void){
	currentWidth = currentHeight = boardSize;
}

int Hex::getWidth(void) const{
	return currentWidth;
}

int Hex::getHeight(void) const{
	return currentHeight;
}

int Hex::getCurrentGameOver(void) const{
	return currentGameOver;
}

void Hex::setMultiGames(int active){
	multiGames = active;
}

int Hex::getNewGame() const{
	return newGame;
}

int Hex::getCurrentCount(void) const{ 
	return currentCount;
}

Hex::Cell::Cell() : user(static_cast<char>(cellState::dot)){
//inentionally empty
}

void Hex::Cell::setUser(cellState cState){
	user = static_cast<char>(cState);
}

void Hex::Cell::setUser(char c){
	user = c;
}

void Hex::Cell::setRowColumn(int i, int j){
	row = i;
	column = j;	
}

char Hex::Cell::getUser(void){
	return user;
}

int Hex::Cell::getRow(void){
	return row;
}

int Hex::Cell::getColumn(void){
	return column;
}

void Hex::twoPlayersGame(void){
	// User VS User
	string input;
	bool validity;
	do{
		do{
			newGame = 0;

			if( player == static_cast<char>(cellState::x) ){
				cout << "-> User1 (x): ";
			} else{
				cout << "-> User2 (o): ";
			}
			getline(cin, input);
			validity = checkInput(input);
			if( gameMode == 2 ){ // Goes the computervsuser game mode.
				showBoard();
				versusCompGame();
				return;
			}
			if( newGame ){ //There is "NEW"
				return;
			}
			if( validity == false ){ 
				cerr << "-> Invalid input. Please enter a valid input." << endl;
			} 
		}while( validity == false );
		gameOver = end();
		showBoard();
		if( multiGames > 0 ){
			if( newGame ){ //There is "NEW" 
				return;
			}
			if( gameOver ){
				currentGameOver = 1;
				countMarkedCells();
				cout << "Current game is over."<< endl;
				return;		
			}	
		}
	} while( !gameOver );

}

void Hex::versusCompGame(void){
	string input;
	bool validity;

	if( player == static_cast<char>(cellState::x)){
		compMove = 1;
	} else if( player == static_cast<char>(cellState::o) ){
		compMove = 2;
	}
	do{
		newGame = 0;
		if( compMove%2 == 1 ){
			// Computer
			play();
			createBooleanArray();
			gameOver = end();
			showBoard();
			compMove++;
		} else if ( compMove%2 == 0 && !gameOver ){
			do{
				player = static_cast<char>(cellState::o);
				cout << "-> User (o): ";
				getline(cin, input);
				validity = checkInput(input);
				if( gameMode == 1 ){ // Goes the uservsuser game mode.
					showBoard();
					twoPlayersGame();
					return;
				}
				if( validity == false ){ 
					cerr << "-> Invalid input. Please enter a valid input." << endl;
				} 
			}while( validity == false );
		
			if(input[1] == ' '){
				currentRow = strToInt(input);
				currentColumn = static_cast<int>(input[0])-65;
				compMove++;
			}
			
			gameOver = end();
			showBoard();
		}
		if( multiGames > 0 ){
			if( newGame ){ //There is "NEW" command
				return;
			}
			if( gameOver ){
				currentGameOver = 1;
				countMarkedCells();
				cout << "Current game is over."<< endl;
				return;		
			}	
		}
	} while( !gameOver );

}

void Hex::play(void){
	if( compMove == 1 ){ // Computer's first move
		// Select a place randomly
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937 gen(seed);
		uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
		int randomRow = dist(gen),
			randomColumn = dist(gen);
		cout << "-> Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
		hexCells[randomRow][randomColumn].setUser(cellState::x);
	} else{
		// To block user's movements
		int possibleMoves[6][2];
		createPossibleMoves(possibleMoves);
		int random=0,
			flag=0;
		do{
			if( possibleMoves[random][0] == -1 ){
				random++;
			}
		} while( possibleMoves[random][0] == -1 && random<6 );
		
		for(int i=0; i<6; i++){
			if(possibleMoves[i][0] == -1)	flag++;
		}
		if(flag == 6){ // There is no possible moves so need random numbers
			unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			mt19937 gen(seed);
			uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
			int randomRow = dist(gen),
			randomColumn = dist(gen);
			cout << "-> Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
			hexCells[randomRow][randomColumn].setUser(static_cast<char>(cellState::x));
		} else{ 
			cout << "-> Computer (x): " << static_cast<char>(possibleMoves[random][1]+65) << " " << possibleMoves[random][0]+1 << endl;
		//	cout <<possibleMoves[random][0] << "  " << possibleMoves[random][1]<< endl;
			hexCells[possibleMoves[random][0]][possibleMoves[random][1]].setUser(cellState::x);	
		}
	}
}

void Hex::createPossibleMoves(int possibleMoves[6][2]){
	int userRow = currentRow,
		userColumn = currentColumn;
	for(int i=0; i<6; i++){
		for(int j=0; j<2; j++){
			possibleMoves[i][j] = -1;
		}
	}
	if( isValid(userRow-1) && 
		hexCells[userRow-1][userColumn].getUser() == static_cast<char>(cellState::dot) ){ //To left-up
		possibleMoves[0][0] = userRow-1;
		possibleMoves[0][1] = userColumn;
	}
	if( isValid(userRow-1) && isValid(userColumn+1) && 
		hexCells[userRow-1][userColumn+1].getUser() == static_cast<char>(cellState::dot) ){ //To right-up
		possibleMoves[1][1] = userColumn+1;
	}
	if( isValid(userRow+1) && 
		hexCells[userRow+1][userColumn].getUser() == static_cast<char>(cellState::dot) ){ //To right-down
		possibleMoves[2][0] = userRow+1;
		possibleMoves[2][1] = userColumn;
	}
	if( isValid(userRow+1) && isValid(userColumn-1) && 
		hexCells[userRow+1][userColumn-1].getUser() == static_cast<char>(cellState::dot) ){ //To left-down
		possibleMoves[3][0] = userRow+1;
		possibleMoves[3][1] = userColumn-1;
	}
	if( isValid(userColumn-1) && 
		hexCells[userRow][userColumn-1].getUser() == static_cast<char>(cellState::dot) ){ //To left
		possibleMoves[4][0] = userRow;
		possibleMoves[4][1] = userColumn-1;
	}
	if( isValid(userColumn+1) && 
		hexCells[userRow][userColumn+1].getUser() == static_cast<char>(cellState::dot) ){ //To right
		possibleMoves[5][0] = userRow;
		possibleMoves[5][1] = userColumn+1;
	}
}

bool Hex::checkInput(const string &input){
	if( isLoadOrSave(input, "LOAD") ){ //LOAD 
		load(input);	
	} else if( isLoadOrSave(input, "SAVE") ){ //SAVE
		save(input);
	} else if( isMoveValid(input) ){ //MOVE
		createBooleanArray();
		int row = strToInt(input),
			column = static_cast<int>(input[0])-65;
			play(row, column);
		if( player == static_cast<char>(cellState::x) ){
			player = static_cast<char>(cellState::o);
		} else if( player == static_cast<char>(cellState::o) ){
			player = static_cast<char>(cellState::x);
		}
	} else if( isNewGame(input) ){ //yeni oyuna geçmek istiyor
		newGame = 1;
	} else{ // Invalid input
		return false;
	}
	return true;
}

bool Hex::isNewGame(const string &input){ //yeni oyuna mı geçmek istiyor
	auto check = input.find( "NEW" );
	if( check == 0 && input.size() == 3 ){
		return true;		
	}
	return false;
}

void Hex::play(int row, int column){
	hexCells[row][column].setUser(player);
}

bool Hex::isLoadOrSave(const string &input, const string str){
	auto check = input.find( str );
	auto txt = input.find( ".txt" );
	auto TXT = input.find( ".TXT" );
	if( check == 0 && isFileNameValid(input) && (static_cast<int>(txt) != -1 || static_cast<int>(TXT) != -1) ){
		return true;
	}
	return false;
}

bool Hex::isFileNameValid(const string &input){
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

void Hex::load(const string &input){ 
	string fileName;
	fileName = input;
	fileName.erase(0,5);		
	ifstream myfile (fileName);
	char c;
	if(myfile.is_open()){
		cout << endl
			 << "-> Loading..." << endl;
		myfile >> boardSize;
		
		createInitialBoard();
		createBooleanArray();
		
		myfile >> gameMode;	
		myfile >> player;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				myfile >> c;
				hexCells[i][j].setUser(c);
			}
		}
		cout << "-> Done." << endl;
	} else{
		cerr << "-> File cannot open." << endl;
	}
	myfile.close();
}

void Hex::save(const string &input){
	string fileName;
	fileName = input;
	fileName.erase(0,5);		
	ofstream myfile (fileName);
	if(myfile.is_open()){
		cout << endl
			 << "-> Saving..." << endl;
		myfile << boardSize << endl;	
		myfile << gameMode << endl;	
		myfile << player << endl;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				myfile << hexCells[i][j].getUser();
			}
			myfile << endl;			
		}
		cout << "-> Done." << endl;
	} else{
		cerr << "-> File cannot open." << endl;
	}
	myfile.close();
}

bool Hex::isMoveValid(const string &input){
	// Move must start with A,B,...
	// And the second char must be space char.
	// The last char must be 1,2,...10,11 etc.
	if( input.size() == 3 && input[1] == ' ' && input[2] != ' ' 
		&& input[2] >= '1' && input[2] <= '9' ){
		int row = strToInt(input),
		column = static_cast<int>(input[0])-65;
		//burası karışmış olai li
		return isValid(row) && isValid(column) && hexCells[row][column].getUser() == static_cast<char>(cellState::dot);
	}
	if( input.size() == 4 && input[1] == ' ' && input[2] != ' ' 
		&& input[2] >= '1' && input[2] <= '9'
		&& input[3] >= '0' && input[3] <= '9'){
		int row = strToInt(input),
		column = static_cast<int>(input[0])-65;
		return isValid(row) && isValid(column) && hexCells[row][column].getUser() == static_cast<char>(cellState::dot);
	}
	return false;
}

void Hex::createBooleanArray(void){
	for(int i=0; i<boardSize; i++){
		checkArray.push_back( vector<int>() );

		for(int j=0; j<boardSize; j++){
			checkArray[i].push_back( int() );
			checkArray[i][j] = 0;
		}
	}
}

inline int Hex::strToInt(const string &input, int toEnd){ 
	// str ---> int 
	string str = input;
	str.erase(0,toEnd);
	return stoi(str)-1;
}

bool Hex::end(void){
	return isBoardFull() == true || win_o() == true || win_x() == true;
}

bool Hex::isBoardFull(void){
	int flag = 0;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( hexCells[i][j].getUser() == static_cast<char>(cellState::x) || hexCells[i][j].getUser() == static_cast<char>(cellState::o) ){
				flag++;
			}
		}
	}
	if(flag == boardSize*boardSize){
		cout << endl << "---> Board is filled." << endl;
		return true;
	} else {
		return false;
	}
}

bool Hex::isValid(const int index){
	if( index<0 || index>=boardSize ){
		return false;
	}
	return true;
}

bool Hex::win_o(void){
	int counter[4];
	counter[0] = boardSize;
	counter[3] = -1;
	//counter[1]; row
	//counter[2]; column
	for(int i=0; i<boardSize; i++){
		if( hexCells[0][i].getUser() == static_cast<char>(cellState::o) ){ // There is 'o'
			checkArray[0][i] = 1;
			hexCells[0][i].setUser(hexCells[0][i].getUser()-32);
			if( isValid(i-1) ){ // To down
				counter[1] = 1;
				counter[2] = i-1;
				winRecursion_o(counter);
			}
			if( isValid(i) ){ // To left-down
				counter[1] = 1;
				counter[2] = i;
				winRecursion_o(counter);
			}
			if( counter[0] == counter[3] ){ // Winner is 'o'
				cout << endl << "---> O is winner." << endl;
				return true;
			} else{
				convertLowerCase(); // Back to lower case because 'o' is not winner
			}
		}
	}
	return false;	
}

void Hex::winRecursion_o(int counter[4]){
	int row = counter[1],
		column = counter[2];
	if( hexCells[row][column].getUser() == static_cast<char>(cellState::o) ){
		checkArray[row][column] = 1;
		hexCells[row][column].setUser(hexCells[row][column].getUser()-32);

		if( isValid(column+1) && checkArray[row][column+1] != 1 ){ //To right
			counter[2]++;
			winRecursion_o(counter);
			counter[2]--;
		}
		if( isValid(column-1) && checkArray[row][column-1] != 1 ){ // To left
			counter[2]--;
			winRecursion_o(counter);
			counter[2]++;
		}
		if( isValid(column-1) && isValid(row+1) ){  //To left-down
			counter[1]++;
			counter[2]--;
			winRecursion_o(counter);
			counter[1]--;
			counter[2]++;
		}
		if( isValid(row+1) ){ //To right-down
			counter[1]++;
			winRecursion_o(counter);
			counter[1]--;
		}
		if( counter[0]-1 == counter[1] ){ 
			counter[3] = counter[0];
		} else if( counter[3] != counter[0] && checkArray[row][column+1] != 1 ){
			checkArray[row][column] = 0;
			hexCells[row][column].setUser(hexCells[row][column].getUser()+32);
		}
	}
}
// win_x and winRecursion_x work like win_o and winRecursion_o
bool Hex::win_x(void){
	int counter[4];
	counter[0] = boardSize;
	counter[3] = -1;
	for(int i=0; i<boardSize; i++){
		if( hexCells[i][0].getUser() == static_cast<char>(cellState::x) ){ 
			checkArray[i][0] = 1;
			hexCells[i][0].setUser(hexCells[i][0].getUser()-32);
			if( isValid(i-1) ){ 
				counter[1] = i-1;
				counter[2] = 1;
				winRecursion_x(counter);
			}
			if( isValid(i) ){ 
				counter[1] = i;
				counter[2] = 1;
				winRecursion_x(counter);
			}
			if( counter[0] == counter[3] ){
				cout << endl << "---> X is winner." << endl;
				return true;

			} else{
				convertLowerCase();
			}
		}
	}
	return false;	
}

void Hex::winRecursion_x(int counter[4]){
	int row = counter[1],
		column = counter[2];
		if( hexCells[row][column].getUser() == static_cast<char>(cellState::x) ){
			checkArray[row][column] = 1;
			hexCells[row][column].setUser(hexCells[row][column].getUser()-32);
			if( isValid(column+1) && isValid(row-1) ){ 
				counter[2]++;
				counter[1]--;
				winRecursion_x(counter);
				counter[2]--;
				counter[1]++;
			}
			if( isValid(row-1)){
				if( checkArray[row-1][column] != 1 ){
					counter[1]--;
					winRecursion_x(counter);
					counter[1]++;					
				}
			}
			if( isValid(row+1)  ){
				if( checkArray[row+1][column] != 1 ){
					counter[1]++;
					winRecursion_x(counter);
					counter[1]--;					
				}
			}
			if( isValid(column+1) ){
				counter[2]++;
				winRecursion_x(counter);
				counter[2]--;
			}
			if( counter[0]-1 == counter[2] ){
				counter[3] = counter[0];
			} else if( counter[3] != counter[0] && checkArray[row][column+1] != 1){
				checkArray[row][column] = 0;
				hexCells[row][column].setUser(hexCells[row][column].getUser()+32);
			}
	}
}
// To convert to lower case elements of board
void Hex::convertLowerCase(void){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( hexCells[i][j].getUser() == 'X' || hexCells[i][j].getUser() == 'O' ){
				hexCells[i][j].setUser(hexCells[i][j].getUser()+32);
			}
		}
	}
}

int Hex::totalCount = 0;

int Hex::numOfMarkedCells(void){
	return totalCount;
}

void Hex::countMarkedCells(void){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( hexCells[i][j].getUser() != static_cast<char>(cellState::dot) ){
				totalCount++;
				currentCount++;
			}
		}
	}
}

bool Hex::compareHexGames(Hex anotherHex){
	if( getCurrentCount() > anotherHex.getCurrentCount() ) return true;
	else return false;
}