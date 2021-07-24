#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <deque>
#include "AbstractHex.h"
#include "Cell.h"

using namespace std;

namespace ess{

AbstractHex::AbstractHex(){
	//takes input and check it's validity
	setBoardSize();
	setGameMode();
}

AbstractHex::AbstractHex(int inputSize) : boardSize(inputSize), gameMode(2){
}

AbstractHex::AbstractHex(int inputSize, int inputGameMode) : boardSize(inputSize), gameMode(inputGameMode){
}

void AbstractHex::print() const{
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
				cout << static_cast<char>( (*this)(i-1, j).getUser() )<< " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}


void AbstractHex::writeToFile(const string &fileName) const{		
	ofstream myfile (fileName);
	if(myfile.is_open()){
		//cout << endl
		//	 << "-> Saving..." << endl;
		myfile << boardSize << endl;
		myfile << gameMode << endl;	
		myfile << player << endl;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				myfile << (*this)(i, j).getUser();
			}
			myfile << endl;			
		}
		myfile << currentRow << endl;
		myfile << currentColumn << endl;
		//cout << "-> Done." << endl;
	} else{
		cerr << "-> File cannot open." << endl;
	}
	myfile.close();
}

bool AbstractHex::isEnd(){
	//If the board is fulled or there is a winner, return true
	return isBoardFull() == true || win_o() == true || win_x() == true;
}

int AbstractHex::numberOfMoves() const{
	//count the moves of board
	int numOfMove = 0;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( (*this)(i, j).getUser() != '.' ){
				numOfMove++;
			}
		}
	}
	return numOfMove;
}

bool AbstractHex::operator==(AbstractHex * another){
	if( boardSize == another->boardSize ){
		//boardSize must be equal
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				if( (*this)(i, j).getUser() != another->operator()(i,j).getUser() ){
					//elements are not equal, so return false
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

Cell AbstractHex::lastMove() const{
	//kept the last move at the currentRow,currentColumn and player
	//To return these value, created Cell object and return the object
	Cell last;
	last.setRowColumn(currentRow, currentColumn);
	last.setUser(player);
	return last;
}

//from previous hws
void AbstractHex::playGame(void){
	//createBooleanArray();
	gameOver = isEnd();
	print();
	if( !gameOver ){
		if( gameMode == 1 ){ //User vs User
			twoPlayersGame();
		} else if( gameMode == 2 ){ //User vs Computer
			versusCompGame();
		}		
	} 
}

void AbstractHex::twoPlayersGame(void){
	// User VS User
	string input;
	bool validity;
	do{
		do{
			if( player == static_cast<char>(cellState::x) ){
				cout << "-> User1 (x): ";
			} else{
				cout << "-> User2 (o): ";
			}
			getline(cin, input);
			createBooleanArray();
			validity = checkInput(input);
			if( gameMode == 2 ){ // Goes the computervsuser game mode.
				print();
				versusCompGame();
				return;
			}
			if( validity == false ){ 
				cerr << "-> Invalid input. Please enter a valid input." << endl;
			} 
		}while( validity == false );
		gameOver = isEnd();
		print();
	} while( !gameOver );

}

bool AbstractHex::checkInput(const string &input){
	if( isLoadOrSave(input, "LOAD") ){ //LOAD
		string fileName = input;
		fileName.erase(0,5);		
		readFromFile(fileName);	
	} else if( isLoadOrSave(input, "SAVE") ){ //SAVE
		string fileName = input;
		fileName.erase(0,5);
		writeToFile(fileName);
	} else if( isMoveValid(input) ){ //MOVE
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
	} else if( isLastMove(input) ){
		Cell temp = lastMove();
		cout << endl;
		if( temp.getUser() == 'o' ){
			temp.setUser('x');
		} else if( temp.getUser() == 'x' ){
			temp.setUser('o');	}
			cout << "Last move: User (" << temp.getUser() << ") is played at (" 
				 << static_cast<char>( temp.getColumn() + 65 ) << "," << temp.getRow() + 1 << ")" << endl;
	} else if( isNumOfMoves(input) ){
		cout << "Number of moves: " << numberOfMoves() << endl;
	} else{ // Invalid input
		return false;
	}
	return true;
}

bool AbstractHex::isNumOfMoves(const string &input){
	if( input.compare("TOTALMOVES") == 0 ){
		return true;
	}
	return false;
}

bool AbstractHex::isLastMove(const string &input){
	if( input.compare("LASTMOVE") == 0 ){
		return true;
	}
	return false;
}

bool AbstractHex::isValid(const int index){
	if( index<0 || index>=boardSize ){
		return false;
	}
	return true;
}

bool AbstractHex::isMoveValid(const string &input){
	// Move must start with A,B,...
	// And the second char must be space char.
	// The last char must be 1,2,...10,11 etc.
	if( input.size() == 3 && input[1] == ' ' && input[2] != ' ' 
		&& input[2] >= '1' && input[2] <= '9' ){
		int row = strToInt(input),
		column = static_cast<int>(input[0])-65;
		return isValid(row) && isValid(column) && (*this)(row, column).getUser() == static_cast<char>(cellState::dot);
	}
	if( input.size() == 4 && input[1] == ' ' && input[2] != ' ' 
		&& input[2] >= '1' && input[2] <= '9'
		&& input[3] >= '0' && input[3] <= '9'){
		int row = strToInt(input),
		column = static_cast<int>(input[0])-65;
		return isValid(row) && isValid(column) && (*this)(row, column).getUser() == static_cast<char>(cellState::dot);
	}
	return false;
}

bool AbstractHex::isLoadOrSave(const string &input, const string str){
	auto check = input.find( str );
	auto txt = input.find( ".txt" );
	auto TXT = input.find( ".TXT" );
	if( check == 0 && isFileNameValid(input) && (static_cast<int>(txt) != -1 || static_cast<int>(TXT) != -1) ){
		return true;
	}
	return false;
}

bool AbstractHex::isFileNameValid(const string &input){
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

bool AbstractHex::isNewGame(const string &input){ //yeni oyuna mı geçmek istiyor
	auto check = input.find( "NEW" );
	if( check == 0 && input.size() == 3 ){
		return true;		
	}
	return false;
}

void AbstractHex::versusCompGame(void){
	string input;
	bool validity;

	if( player == static_cast<char>(cellState::x)){
		compMove = 1;
	} else if( player == static_cast<char>(cellState::o) ){
		compMove = 2;
	}
	do{
		if( compMove%2 == 1 ){
			// Computer
			play();
			createBooleanArray();
			gameOver = isEnd();
			print();
			compMove++;
		} else if ( compMove%2 == 0 && !gameOver ){
			do{
				player = static_cast<char>(cellState::o);
				cout << "-> User (o): ";
				getline(cin, input);
				validity = checkInput(input);
				if( gameMode == 1 ){ // Goes the uservsuser game mode.
					print();
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
			
			gameOver = isEnd();
			print();
		}
	} while( !gameOver );

}

void AbstractHex::createPossibleMoves(int possibleMoves[6][2]){
	int userRow = currentRow,
		userColumn = currentColumn;
	for(int i=0; i<6; i++){
		for(int j=0; j<2; j++){
			possibleMoves[i][j] = -1;
		}
	}
	if( isValid(userRow-1) && 
		(*this)(userRow-1, userColumn).getUser() == static_cast<char>(cellState::dot) ){ //To left-up
		possibleMoves[0][0] = userRow-1;
		possibleMoves[0][1] = userColumn;
	}
	if( isValid(userRow-1) && isValid(userColumn+1) && 
		(*this)(userRow-1, userColumn+1).getUser() == static_cast<char>(cellState::dot) ){ //To right-up
		possibleMoves[1][1] = userColumn+1;
	}
	if( isValid(userRow+1) && 
		(*this)(userRow+1, userColumn).getUser() == static_cast<char>(cellState::dot) ){ //To right-down
		possibleMoves[2][0] = userRow+1;
		possibleMoves[2][1] = userColumn;
	}
	if( isValid(userRow+1) && isValid(userColumn-1) && 
		(*this)(userRow+1, userColumn-1).getUser() == static_cast<char>(cellState::dot) ){ //To left-down
		possibleMoves[3][0] = userRow+1;
		possibleMoves[3][1] = userColumn-1;
	}
	if( isValid(userColumn-1) && 
		(*this)(userRow, userColumn-1).getUser() == static_cast<char>(cellState::dot) ){ //To left
		possibleMoves[4][0] = userRow;
		possibleMoves[4][1] = userColumn-1;
	}
	if( isValid(userColumn+1) && 
		(*this)(userRow, userColumn+1).getUser() == static_cast<char>(cellState::dot) ){ //To right
		possibleMoves[5][0] = userRow;
		possibleMoves[5][1] = userColumn+1;
	}
}

void AbstractHex::createBooleanArray(void){
	for(int i=0; i<boardSize; i++){
		checkArray.push_back( vector<int>() );

		for(int j=0; j<boardSize; j++){
			checkArray[i].push_back( int() );
			checkArray[i][j] = 0;
		}
	}
}

int AbstractHex::strToInt(const string &input, int toEnd){ 
	// str ---> int 
	string str = input;
	str.erase(0,toEnd);
	return stoi(str)-1;
}

bool AbstractHex::isBoardFull(void){
	int flag = 0;
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( (*this)(i, j).getUser() == static_cast<char>(cellState::x) || (*this)(i, j).getUser() == static_cast<char>(cellState::o) ){
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

void AbstractHex::setBoardSize(void){
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
bool AbstractHex::isBoardSizeValid(string strSize){
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

void AbstractHex::setGameMode(void){
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

bool AbstractHex::isModeValid(string strMode){
	if( strMode.size() == 1 && 
		(strMode[0] == '1' || strMode[0] <= '2') ){
		return 1;
	}
	return 0;
}

bool isValidSequence( AbstractHex * sequence[], int sizeOfSequence ){
	int flag=0,
		valid=0,
		boardSize,
		countX=0,
		countY=0;
	char last;
	if( sizeOfSequence == 1 ){ //there is only one board and it is okey
		return true;
	} else{
		for(int i=0; i<sizeOfSequence; i++){
			if( sequence[i]->isEnd() )		return false;
		}
		for(int i=0; i<sizeOfSequence-1; i++){
			//boardSize and gameMode must be same
			if( sequence[i]->getBoardSize() == sequence[i+1]->getBoardSize()
				&&
				sequence[i]->getGameMode() == sequence[i+1]->getGameMode() ){
				flag++;
			}
		}
		if( flag != sizeOfSequence-1 ) 	return false;
		else{
			boardSize = sequence[0]->getBoardSize();
			valid++;
		}
	}
	//numofmoves bakmadın
	for(int i=0; i<sizeOfSequence-1; i++){
		if( sequence[i]->numberOfMoves() > sequence[i+1]->numberOfMoves() ){
			return false;
		}
	}
	//board
	last = sequence[0]->lastMove().getUser();

	for(int i=0; i<sizeOfSequence-1; i++){
		countX=0;
		countY=0;
		for(int j=0; j<boardSize; j++){
			for(int k=0; k<boardSize; k++){
				if( sequence[i]->operator()(j,k).getUser() != sequence[i+1]->operator()(j,k).getUser() ){
					if( sequence[i+1]->operator()(j,k).getUser() == 'x' ){
						countX++;
					} else if( sequence[i+1]->operator()(j,k).getUser() == 'o' ){
						countY++;
					}
				}
			}
		}
		if( sequence[i]->numberOfMoves()+countX+countY != sequence[i+1]->numberOfMoves() ){
			return false;
		} else{
			if( countX-countY > 1 || countX-countY < 0 ){
				return false;
			}
			if( last == 'x' && countX-1==countY ){
				last = 'o';
			} else if( last == 'o' && countY-1==countX ){
				last = 'x';
			}
		}
	}
	return true;
}

}