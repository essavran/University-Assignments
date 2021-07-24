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

int main(){
	int size,
		mode;
	char board[12][12];

	cout << "******* Welcome to HEX Game *******" << endl << endl;
	cout << "Please select the board size:" << endl;
	size = boardSize(); /*Select the board size*/
	cout << endl << "Please select the game mode:" << endl;	/*It is user1vsuser2 or computervsuser*/
	mode = gameMode();

	createInitialBoard(board, size); 
	showBoard(board, size); /*Show initial board*/
	if(mode == 1){ 
		twoPlayersGame(board, size); /*user1vsuser2*/
	} else if(mode == 2){
		versusCompGame(board, size); /*computervsuser*/
	}
	cout << "Goodbye!" << endl << endl;/*Game is over. Goodbye!*/
	return 0;
}
