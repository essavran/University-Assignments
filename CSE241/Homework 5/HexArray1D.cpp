#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>

#include <stdlib.h>
#include "AbstractHex.h"
#include "HexArray1D.h"

using namespace std;
namespace ess{

HexArray1D::HexArray1D() : AbstractHex() {
	setSize(boardSize);//create and reset the board
	playGame();//start game
}

HexArray1D::HexArray1D(int inputSize) : AbstractHex(inputSize) {
	setSize(boardSize);	//created board
}

HexArray1D::HexArray1D(int inputSize, int inputGameMode) : AbstractHex(inputSize, inputGameMode){
	setSize(boardSize);
	//created board
}

HexArray1D::~HexArray1D(){ //DESTRUCTOR
	//free each array elements
	if(hexCells1D){
		free( hexCells1D );
	}
}

HexArray1D::HexArray1D(const HexArray1D &hexGame){ //COPY CONSTRUCTOR
	boardSize = hexGame.boardSize;
	gameMode = hexGame.gameMode;
	hexCells1D = (Cell *)calloc(boardSize*boardSize, sizeof(Cell));
	char c;
	for(int i=0; i<hexGame.boardSize*hexGame.boardSize; i++){
		c = hexGame.hexCells1D[i].getUser();
		hexCells1D[i].setUser(c);		
	}
}

HexArray1D& HexArray1D::operator=(const HexArray1D &hexGame){ //COPY ASSIGNMENT OPERATOR
	Cell * newArray;
	char c;
	if( &hexGame != this ){
		newArray = (Cell *)calloc(boardSize*boardSize, sizeof(Cell));;
		for(int i=0; i<hexGame.boardSize*hexGame.boardSize; i++){
			c = hexGame.hexCells1D[i].getUser();
			hexCells1D[i].setUser(c);
		}
		
		free( hexCells1D );

		hexCells1D = newArray;
		boardSize = hexGame.boardSize;
		gameMode = hexGame.gameMode;
	
}
	return *this;
}

Cell HexArray1D::operator()(int row, int column) const{
	//returns Cell object which is at [index]
	return hexCells1D[boardSize*row+column];
}

void HexArray1D::setSize(int board){
	boardSize = board;
	//create the hexCells(the board)
	hexCells1D = (Cell *)calloc(boardSize*boardSize, sizeof(Cell));
	reset();//reset it
}

void HexArray1D::reset(){
	for(int i=0; i<boardSize*boardSize; i++){
		hexCells1D[i].setUser( cellState::dot );//the board is filled with dot	
	}
}

void HexArray1D::play(void){
	if( compMove == 1 ){ // Computer's first move
		// Select a place randomly and plays
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937 gen(seed);
		uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
		int randomRow = dist(gen),
			randomColumn = dist(gen);
		cout << "-> Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
		hexCells1D[boardSize*randomRow+randomColumn].setUser(cellState::x);
		currentRow = randomRow;
		currentColumn = randomColumn;
	} else{// computer's another moves
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
			hexCells1D[boardSize*randomRow+randomColumn].setUser(static_cast<char>(cellState::x));
			currentRow = randomRow;
			currentColumn = randomColumn;
		} else{ 
			cout << "-> Computer (x): " << static_cast<char>(possibleMoves[random][1]+65) << " " << possibleMoves[random][0]+1 << endl;
			hexCells1D[boardSize*possibleMoves[random][0]+possibleMoves[random][1]].setUser(cellState::x);
			currentRow = possibleMoves[random][0];
			currentColumn = possibleMoves[random][1];
		}
	}
}
void HexArray1D::play(Cell cellS){
	//plays user's move
	//and also keeps the last move
	int row = cellS.getRow();
	int column = cellS.getColumn();
	player = cellS.getUser();
	currentRow = row;
	currentColumn = column;
	cout << "user cell play " << row << " " << column << endl;
	hexCells1D[boardSize*row+column].setUser(player);
}

void HexArray1D::readFromFile(const string &fileName){ 		
	ifstream myfile (fileName);
	char c;
	if(myfile.is_open()){
		myfile >> boardSize;
		setSize(boardSize);
		createBooleanArray();
		myfile >> gameMode;	
		myfile >> player;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				myfile >> c;
				hexCells1D[boardSize*i+j].setUser(c);
			}
		}
		//print the last move
		myfile >> currentRow;
		myfile >> currentColumn;
	} else{
		cerr << "-> File cannot open." << endl;
	}
	myfile.close();
}
//previous hws
bool HexArray1D::win_o(void){
	int counter[4];
	counter[0] = boardSize;
	counter[3] = -1;
	//counter[1]; row
	//counter[2]; column
	for(int i=0; i<boardSize; i++){
		if( hexCells1D[boardSize*0+i].getUser() == static_cast<char>(cellState::o) ){ // There is 'o'
			checkArray[0][i] = 1;
			hexCells1D[boardSize*0+i].setUser(hexCells1D[boardSize*0+i].getUser()-32);
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

void HexArray1D::winRecursion_o(int counter[4]){
	int row = counter[1],
		column = counter[2];
	if( hexCells1D[boardSize*row+column].getUser() == static_cast<char>(cellState::o) ){
		checkArray[row][column] = 1;
		hexCells1D[boardSize*row+column].setUser(hexCells1D[boardSize*row+column].getUser()-32);

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
			hexCells1D[boardSize*row+column].setUser(hexCells1D[boardSize*row+column].getUser()+32);
		}
	}
}
// win_x and winRecursion_x work like win_o and winRecursion_o
bool HexArray1D::win_x(void){
	int counter[4];
	counter[0] = boardSize;
	counter[3] = -1;
	for(int i=0; i<boardSize; i++){
		if( hexCells1D[boardSize*i+0].getUser() == static_cast<char>(cellState::x) ){ 
			checkArray[i][0] = 1;
			hexCells1D[boardSize*i+0].setUser(hexCells1D[boardSize*i+0].getUser()-32);
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

void HexArray1D::winRecursion_x(int counter[4]){
	int row = counter[1],
		column = counter[2];
	if( hexCells1D[boardSize*row+column].getUser() == static_cast<char>(cellState::x) ){
		checkArray[row][column] = 1;
		hexCells1D[boardSize*row+column].setUser(hexCells1D[boardSize*row+column].getUser()-32);
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
			hexCells1D[boardSize*row+column].setUser(hexCells1D[boardSize*row+column].getUser()+32);
		}
	}
}
// To convert to lower case elements of board
void HexArray1D::convertLowerCase(void){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( hexCells1D[boardSize*i+j].getUser() == 'X' || hexCells1D[boardSize*i+j].getUser() == 'O' ){
				hexCells1D[boardSize*i+j].setUser(hexCells1D[boardSize*i+j].getUser()+32);
			}
		}
	}
}

}