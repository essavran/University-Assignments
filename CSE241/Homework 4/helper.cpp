/*
*cCSE241 - HOMEWORK 3
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

void Hex::setStart(int n){
	start = n;
}

Hex::Hex(void){ 
	createInitialBoard();
	createBooleanArray();
	createMoves();
}

Hex::Hex(bool flag){
	start = 0;
	playGame();
}


Hex::Hex(int size, int mode) : boardSize(size), gameMode(mode){
	createInitialBoard();
	createBooleanArray();
	createMoves();
}

Hex::~Hex(){ //DESTRUCTOR
	//free each array elements
	if(hexCells[0]){
		for(int i=0; i<boardSize; i++){
			delete [] hexCells[i];
		}
		delete [] hexCells;
	}
	if(checkArray[0]){
		for(int i=0; i<boardSize; i++){
			delete [] checkArray[i];
		}
		delete [] checkArray;		
	}
	if(moves[0]){
		for(int i=0; i<numOfMoves; i++){
			delete [] moves[i];
		}
		delete [] moves;		
	}
}

Hex::Hex(const Hex &hexGame){ //COPY CONSTRUCTOR
	boardSize = hexGame.boardSize;
	gameMode = hexGame.gameMode;
	hexCells = new Cell*[hexGame.boardSize];
	currentGameOver = hexGame.currentGameOver;
	multiGames = hexGame.currentGameOver;
	newGame = hexGame.newGame;
	char c;
	for(int i=0; i<hexGame.boardSize; i++){
		hexCells[i] = new Cell[boardSize];
		for(int j=0; j<boardSize; j++){
			hexCells[i][j].setSize(boardSize);
			c = hexGame.hexCells[i][j].getUser();
			hexCells[i][j].setUser(c);
			hexCells[i][j].setRowColumn(i, j); 
		}
	}
	
	checkArray = new int*[boardSize];
	for(int i=0; i<boardSize; i++){
		checkArray[i] = new int[boardSize];
		for(int j=0; j<boardSize; j++){
			checkArray[i][j] = hexGame.checkArray[i][j];
		}
	}

	moves = new int*[numOfMoves+1];
	for(int i=0; i<numOfMoves+1; i++){
		moves[i] = new int[2];
		for(int j=0; j<2; j++){
			moves[i][j] = hexGame.moves[i][j];
		}
	}
}

Hex& Hex::operator=(const Hex &hexGame){ //COPY ASSIGNMENT OPERATOR
		cout <<"minnos5" << endl;

	Cell ** newArray;
	int ** newArray2;
	int ** newArray3;
	char c;
	if( &hexGame != this ){
		currentGameOver = hexGame.currentGameOver;
		currentGameOver = hexGame.currentGameOver;
		multiGames = hexGame.currentGameOver;
		newGame = hexGame.newGame;
		newArray = new Cell*[hexGame.boardSize];
		for(int i=0; i<hexGame.boardSize; i++){
			newArray[i] = new Cell[hexGame.boardSize];
			for(int j=0; j<boardSize; j++){
				hexCells[i][j].setSize(boardSize);
				c = hexGame.hexCells[i][j].getUser();
				hexCells[i][j].setUser(c);
				hexCells[i][j].setRowColumn(i, j); 
			}
		}
		//copy( hexGame.hexCells, hexGame.hexCells+hexGame.boardSize, newArray );
		//copy
		newArray2 = new int*[boardSize];
		for(int i=0; i<boardSize; i++){
			newArray2[i] = new int[boardSize];
			for(int j=0; j<boardSize; j++){
				newArray2[i][j] = hexGame.checkArray[i][j];
			}
		}
		numOfMoves = hexGame.numOfMoves;
		newArray3 = new int*[numOfMoves+1];
		for(int i=0; i<numOfMoves+1; i++){
			newArray3[i] = new int[2];
			for(int j=0; j<2; j++){
				newArray3[i][j] = hexGame.moves[i][j];
			}
		}

		for(int i=0; i<hexGame.boardSize; i++){
			delete [] hexGame.hexCells[i];
		}
		delete [] hexGame.hexCells;

		hexCells = newArray;
		boardSize = hexGame.boardSize;
		gameMode = hexGame.gameMode;

		for(int i=0; i<hexGame.boardSize; i++){
			delete [] hexGame.checkArray[i];
		}
		delete [] hexGame.checkArray;
		checkArray = newArray2;
	
		for(int i=0; i<numOfMoves; i++){
			delete [] hexGame.moves[i];
		}
		delete [] hexGame.moves;
		moves = newArray3;	
}
	return *this;
}

void Hex::playGame(void){
	if( start == 0 ){
	//	welcome();
		setBoardSize();
		setGameMode();
		createInitialBoard();
		createBooleanArray();
		createMoves();
		start = 1;		
	} else if( start == 1 ){
		cout << hexCells;
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
	hexCells = new Cell*[boardSize];
	char c = '.';
	for(int i=0; i<boardSize; i++){
		hexCells[i] = new Cell[boardSize];
		for(int j=0; j<boardSize; j++){
			hexCells[i][j].setSize(boardSize);
			hexCells[i][j].setUser(c);
			hexCells[i][j].setRowColumn(i, j); 
		}
	}
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
				cout << hexCells;
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
		cout << hexCells;
		if( multiGames > 0 ){
			if( newGame ){ //There is "NEW" 
				return;
			}
			if( gameOver ){
				currentGameOver = 1;
				printLastScore();
				countMarkedCells();
				cout << "Current game is over."<< endl;
				return;		
			}	
		} else if( multiGames == 0 && gameOver == true ){ //game is over print the scores
			printLastScore();
		}
	} while( !gameOver );
}

void Hex::printLastScore(){
	int totalScore = 0;
	if( player == 'o' ){ //x is winner
		gOver = true;
		totalScore = score(cellState::x);
		cout << "For player 'x': " << totalScore << " points" <<endl;
		gOver = false;
		totalScore = score(cellState::o);
		cout << "For player 'o': " << totalScore << " points" << endl;				
	} else if( player == 'x' ){ //o is winner
		gOver = false;
		totalScore = score(cellState::x);
		cout << "For player 'x': " << totalScore << " points" << endl;
		gOver = true;
		totalScore = score(cellState::o);
		cout << "For player 'o': " << totalScore << " points" << endl;				
	}
}

void Hex::versusCompGame(void){
	string input;
	bool validity;
	Cell changed;
	if( player == static_cast<char>(cellState::x)){
		compMove = 1;
	} else if( player == static_cast<char>(cellState::o) ){
		compMove = 2;
	}
	do{
		newGame = 0;
		if( compMove%2 == 1 ){
			// Computer
			changed = play();
			cout << "-> Computer (x): " << static_cast<char>(changed.getColumn()+65) << " " << changed.getRow()+1 << endl;
			addMoves(changed.getRow(), changed.getColumn());
			createBooleanArray();
			gameOver = end();
			if( gameOver )		player = 'o';
			cout << hexCells;
			compMove++;
		} else if ( compMove%2 == 0 && !gameOver ){
			do{
				player = static_cast<char>(cellState::o);
				cout << "-> User (o): ";
				getline(cin, input);
				validity = checkInput(input);
				if( gameMode == 1 ){ // Goes the uservsuser game mode.
					cout << hexCells;
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
			cout << hexCells;
		}
		if( multiGames > 0 ){
			if( newGame ){ //There is "NEW" command
				return;
			}
			if( gameOver ){
				currentGameOver = 1;
				printLastScore();
				countMarkedCells();
				cout << "Current game is over."<< endl;
				return;		
			}	
		} else if( multiGames == 0 && gameOver == true ){ //game is over print the scores
			printLastScore();

		}
	} while( !gameOver );

}

Hex::Cell Hex::play(void){ //COMPUTER PLAYS
	Cell changed; //değişiklik yaptığım şeyi tuttuğum Cell
	if( compMove == 1 ){ // Computer's first move
		// Select a place randomly
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937 gen(seed);
		uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
		int randomRow = dist(gen),
			randomColumn = dist(gen);
		//cout << "-> Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
		hexCells[randomRow][randomColumn].setUser(cellState::x); //tabloda değişiklik yapıyorum
		changed.setRowColumn(randomRow, randomColumn);
		changed.setUser(cellState::x);
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
			//cout << "-> Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
			hexCells[randomRow][randomColumn].setUser(static_cast<char>(cellState::x));
			changed.setRowColumn(randomRow, randomColumn);
			changed.setUser(cellState::x);
		} else{ 
			//cout << "-> Computer (x): " << static_cast<char>(possibleMoves[random][1]+65) << " " << possibleMoves[random][0]+1 << endl;
		//	cout <<possibleMoves[random][0] << "  " << possibleMoves[random][1]<< endl;
			hexCells[possibleMoves[random][0]][possibleMoves[random][1]].setUser(cellState::x);
			changed.setRowColumn(possibleMoves[random][0], possibleMoves[random][1]);
			changed.setUser(cellState::x);
		}
	}
	return changed;
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
			Cell cellS;
			cellS.setRowColumn(row, column);
			cellS.setUser(player);
			play(cellS);
		if( player == static_cast<char>(cellState::x) ){
			player = static_cast<char>(cellState::o);
		} else if( player == static_cast<char>(cellState::o) ){
			player = static_cast<char>(cellState::x);
		}
	} else if( isScore(input) ){ //SCORE
		int totalScore = 0;
		totalScore = score(cellState::x);
		cout << "For player 'x': " << totalScore << " points" << endl;
		totalScore = score(cellState::o);
		cout << "For player 'o': " << totalScore << " points" << endl;
	}else if( isPreUndo(input) ){ //PREUNDO
		if( numOfMoves == 0 || numOfMoves == 1 ){//invalid input
			return false;
		}
		--(*this);
	}else if( isPostUndo(input) ){ //POSTUNDO
		if( numOfMoves == 0 || numOfMoves == 1 ){//invalid input
			return false;
		}
		
		(*this)--;
	}else if( isNewGame(input) ){ //yeni oyuna geçmek istiyor
		newGame = 1;
	} else{ // Invalid input
		return false;
	}
	return true;
}

bool Hex::isScore(const string &input){
	auto check = input.find( "SCORE" );
	if( check == 0 && input.size() == 5 ){
		return true;		
	}
	return false;
}

bool Hex::isPreUndo(const string &input){
	auto check = input.find( "PREUNDO" );
	if( check == 0 && input.size() == 7 ){
		return true;		
	}
	return false;
}

bool Hex::isPostUndo(const string &input){
	auto check = input.find( "POSTUNDO" );
	if( check == 0 && input.size() == 8 ){
		return true;		
	}
	return false;
}

bool Hex::isNewGame(const string &input){ //yeni oyuna mı geçmek istiyor
	auto check = input.find( "NEW" );
	if( check == 0 && input.size() == 3 ){
		return true;		
	}
	return false;
}

void Hex::play(Cell cellS){
	int row = cellS.getRow();
	int column = cellS.getColumn();
	player = cellS.getUser();
	hexCells[row][column].setUser(player);
	addMoves(row, column);
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

	if(myfile.is_open()){
		cout << endl
			 << "-> Loading..." << endl;
		myfile >> (*this);
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
		myfile << (*this);
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
	checkArray = new int*[boardSize];
	for(int i=0; i<boardSize; i++){
		checkArray[i] = new int[boardSize];
		for(int j=0; j<boardSize; j++){
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

bool operator==(Hex hexGame1, Hex hexGame2){ //compera two hex games
	if( hexGame1.getCurrentCount() > hexGame2.getCurrentCount() ) return true;
	else return false;
}

ostream& operator<<(ostream& outputStream, const Hex& hexGame){//write to the file
	outputStream << hexGame.boardSize << endl;	
	outputStream << hexGame.gameMode << endl;	
	outputStream << hexGame.player << endl;
	char c;
	for(int i=0; i<hexGame.boardSize; i++){
		for(int j=0; j<hexGame.boardSize; j++){
			c = hexGame.hexCells[i][j].getUser();

			outputStream << c;
		}
		outputStream << endl;			
	}
	outputStream << hexGame.numOfMoves << endl;
	for(int i=0; i<hexGame.numOfMoves; i++){
		outputStream << hexGame.moves[i][0] << endl;
		outputStream << hexGame.moves[i][1];
		if(i != hexGame.numOfMoves-1)	outputStream << endl;			
	}
	return outputStream;
}

istream& operator>>(istream& inputStream, Hex& hexGame){//read from the file
	inputStream >> hexGame.boardSize;
	
	hexGame.createInitialBoard();
	hexGame.createBooleanArray();
		
	inputStream >> hexGame.gameMode;	
	inputStream >> hexGame.player;
	char c;
	for(int i=0; i<hexGame.boardSize; i++){
		for(int j=0; j<hexGame.boardSize; j++){
			inputStream >> c;
			hexGame.hexCells[i][j].setUser(c);
		}
	}
	inputStream >> hexGame.numOfMoves;
	int ** temp = new int*[hexGame.numOfMoves];
	for(int i=0; i<hexGame.numOfMoves; i++){
		temp[i] = new int[2];
		inputStream >> temp[i][0] >> temp[i][1];
	}
	hexGame.moves = temp;
	return inputStream;
}

Hex& Hex::operator--(int ignore){ //postfix
	int deleteRow1 = moves[numOfMoves-1][0],
		deleteColumn1 = moves[numOfMoves-1][1],
		deleteRow2 = moves[numOfMoves-2][0],
		deleteColumn2 = moves[numOfMoves-2][1];
		//delete last moves
	hexCells[deleteRow1][deleteColumn1].setUser(cellState::dot); //o yeri . yaptım
	hexCells[deleteRow2][deleteColumn2].setUser(cellState::dot); //o yeri . yaptım
	numOfMoves -= 2;
	return (*this); //returns unmodified object
}

Hex& Hex::operator--(){ //prefix
	int deleteRow1 = moves[numOfMoves-1][0],
		deleteColumn1 = moves[numOfMoves-1][1],
		deleteRow2 = moves[numOfMoves-2][0],
		deleteColumn2 = moves[numOfMoves-2][1];
		//delete last moves
	hexCells[deleteRow1][deleteColumn1].setUser(cellState::dot); //o yeri . yaptım
	hexCells[deleteRow2][deleteColumn2].setUser(cellState::dot); //o yeri . yaptım
	
	numOfMoves -= 2;
	return (*this);
}

void Hex::createMoves(){
	moves = new int*[1]; //first element
	moves[0] = new int[2]; //row and column
}

void Hex::addMoves(int row, int column){
	if( numOfMoves == 0 ){
		int **p = nullptr;
		p = &moves[0];
		if(p){	//is there moves[][]
			//yes
			//fill
			moves[0][0] = row;
			moves[0][1] = column;		
		} else{
			//no
			createMoves();
			//create and fill
			moves[0][0] = row;
			moves[0][1] = column;
		}

	} else{
		int ** temp = new int*[numOfMoves+1];
		for(int i=0; i<numOfMoves; i++){
			temp[i] = new int[2];
			for(int j=0; j<2; j++){
				temp[i][j] = moves[i][j];
			}
		}
		temp[numOfMoves] = new int[2];
		temp[numOfMoves][0] = row;
		temp[numOfMoves][1] = column;
		moves = temp;
	}
	numOfMoves++;
}

ostream& operator<<(ostream& outputStream, Hex::Cell **hexCells){ //prints the board
	int boardSize = hexCells[0][0].getSize();
		outputStream << endl;
	for(int i=0; i<=boardSize; i++){
		if(i == 0){
			int temp = boardSize;
			outputStream << "   ";
			for(int c=97; temp>0; c++){ // a b c d e ...
				outputStream << static_cast<char>(c) << " ";
				temp--;
			}
		} else{
			if( i <= 9 ){
				outputStream << " ";
			}
			outputStream << i;//1 2 3 4 5 ...

			for(int k=i; k>0; k--){ 
				outputStream << " ";
			}
			for(int j=0; j<boardSize; j++){
				char c = hexCells[i-1][j].getUser();
				outputStream << c << " ";
			}
		}
		outputStream << endl;
	}
	outputStream << endl;
	return outputStream;
}

void Hex::Cell::setSize(int nSize){
	size = nSize;
}

int Hex::Cell::getSize(){
	return size;
}

int Hex::score(cellState pState){// calculate scores
	int scoreCount = 0;
	char c = static_cast<char>(pState);
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( hexCells[i][j].getUser() == c ){
				scoreCount++;
			}
		}
	}
	if( gOver ){//count also uppercase letters
		c = static_cast<char>(pState)-32;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				if( hexCells[i][j].getUser() == c ){
					scoreCount++;
				}
			}
		}
		return scoreCount*10+boardSize*boardSize*10;
	}	
	else 	return scoreCount*10;
}