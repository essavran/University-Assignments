#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include "AbstractHex.h"
#include "HexVector.h"

using namespace std;
namespace ess{

HexVector::HexVector() : AbstractHex(){
	setSize(boardSize);//create and reset the board
	playGame();//start game
}

HexVector::HexVector(int inputSize) : AbstractHex(inputSize){
	setSize(boardSize);
	//created board
}

HexVector::HexVector(int inputSize, int inputGameMode) : AbstractHex(inputSize, inputGameMode){
	setSize(boardSize);
	//created board
}

Cell HexVector::operator()(int row, int column) const{
	//returns Cell object which is at [row][column]
	return hexCells[row][column];
}

void HexVector::setSize(int board){
	boardSize = board;
	//create the hexCells(the board)
	for(int i=0; i<boardSize; i++){
		hexCells.push_back( vector<Cell>() );
		for(int j=0; j<boardSize; j++){
			hexCells[i].push_back( Cell() );
			hexCells[i][j].setRowColumn(i, j); 
		}
	}
	reset();//reset it
}

void HexVector::reset(){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			hexCells[i][j].setUser( cellState::dot );//the board is filled with dot
		}
	}
}

void HexVector::play(void){
	if( compMove == 1 ){ // Computer's first move
		// Select a place randomly and plays
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		mt19937 gen(seed);
		uniform_int_distribution<mt19937::result_type> dist(0,boardSize-1);
		int randomRow = dist(gen),
			randomColumn = dist(gen);
		cout << "-> Computer (x): " << static_cast<char>(randomColumn+65) << " " << randomRow+1 << endl;
		hexCells[randomRow][randomColumn].setUser(cellState::x);
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
			hexCells[randomRow][randomColumn].setUser(static_cast<char>(cellState::x));
			currentRow = randomRow;
			currentColumn = randomColumn;
		} else{ 
			cout << "-> Computer (x): " << static_cast<char>(possibleMoves[random][1]+65) << " " << possibleMoves[random][0]+1 << endl;
		//	cout <<possibleMoves[random][0] << "  " << possibleMoves[random][1]<< endl;
			hexCells[possibleMoves[random][0]][possibleMoves[random][1]].setUser(cellState::x);
			currentRow = possibleMoves[random][0];
			currentColumn = possibleMoves[random][1];
		}
	}
}

void HexVector::play(Cell cellS){
	//plays user's move
	//and also keeps the last move
	int row = cellS.getRow();
	int column = cellS.getColumn();
	player = cellS.getUser();
	currentRow = row;
	currentColumn = column;
	hexCells[row][column].setUser(player);
}

void HexVector::readFromFile(const string &fileName){ 		
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
				hexCells[i][j].setUser(c);
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
//---------
//last hws
bool HexVector::win_o(void){
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

void HexVector::winRecursion_o(int counter[4]){
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
bool HexVector::win_x(void){
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

void HexVector::winRecursion_x(int counter[4]){
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
void HexVector::convertLowerCase(void){
	for(int i=0; i<boardSize; i++){
		for(int j=0; j<boardSize; j++){
			if( hexCells[i][j].getUser() == 'X' || hexCells[i][j].getUser() == 'O' ){
				hexCells[i][j].setUser(hexCells[i][j].getUser()+32);
			}
		}
	}
}

}