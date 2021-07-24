#include <iostream> 
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include "Cell.h"

using namespace std;

#ifndef ABSTRACTHEX_h
#define ABSTRACTHEX_h

namespace ess{

class AbstractHex {
public:
	AbstractHex();//When object is created, takes boardSize and gameMode
	AbstractHex(int inputSize);//Object is created with default gameMode
	AbstractHex(int inputSize, int inputGameMode);//Object is created with inputSize and inputGameMode
	void print() const;//Prints the board on the screen by sending it to cout
	virtual	void readFromFile(const string &fileName) = 0;//Reads the board from the file given as function parameter
	void writeToFile(const string &fileName) const;//Writes the board to the file given as function parameter
	virtual void reset() = 0;//Resets the board to the beginning
	virtual void setSize(int board) = 0;//Sets the board size to given values
	virtual void play() = 0; //plays the computer
	virtual void play(Cell cellS) = 0; //plays the user
	bool isEnd(void); //Returns true if the board is a game end
	virtual Cell operator()(int row, int column) const = 0; //returns the corresponding cell content
	bool operator==(AbstractHex * another);//Two boards are equal, if the boards are the same
	Cell lastMove() const;//Returns the last move
	int numberOfMoves() const;//Returns the number of steps (moves)
	int getBoardSize() const{
		return boardSize;
	}
	int getGameMode() const{
		return gameMode;
	}
protected:
	//This function checks the input's validity.
	//If the input is not valid, returns false.
	//If the input is valid, the function decides LOAD,SAVE,NEW or Movement and goes to other related functions.
	bool checkInput(const string &input);
	//checks that the string is LASTMOVE
	bool isLastMove(const string &input);
	//checks that the string is TOTALMOVES
	bool isNumOfMoves(const string &input);
	//This function checks that the string is LOAD or SAVE.
	bool isLoadOrSave(const string &input, const string str);
	//If the input is LOAD or SAVE, this function checks the filename's validity.
	bool isFileNameValid(const string &input);
	//This function checks the move's validity.
	bool isMoveValid(const string &input);
	//To check that there is "NEW"
	bool isNewGame(const string &input);
	//Assigns the input to temporary string. Deletes the characters in the string
	//from the beginning to a certain place(to toEnd). Converts the remaining the 
	//string to an integer. And returns the integer value.
	//toEnd is a default argument.
	//For example:
	//strToInt(input); means that the first two characters will be deleted.
	//strToInt(input); means that no characters will be deleted.
	int strToInt(const string &input, int toEnd=2);
	bool isBoardFull();
	//Checks the index is valid or not.
	//For example:
	//If boardSize=6, index cannot be -1 or 7. The function returns 0.
	bool isValid(const int index);
	//Searchs 'o' is winner or not.
	virtual bool win_o() = 0;
	//Searchs 'x' is winner or not.
	virtual bool win_x() = 0;
	//This function finds moves that the computer can make against the user.
	//For example:
	//
	//  . .
	// . o . 
	//  . .
	//
	//	is looks like this:
	//
	//  1 2
	// 6 o 3 
	//  5 4	 
	//
	//If the user made this move, the computer selects one of the dots around 'o'.
	//In this process, computer aims to block the user's path.
	//First, computer tries to place 'x' on points in the vertical path. (1,2,4,5)
	//If these are full, computer looks another points. (3,6)
	void createPossibleMoves(int possibleMoves[6][2]);
	//This function fills the boolean array with 'false'.
	void createBooleanArray();
	//This is primary function of the userVSuser game mode.
	void twoPlayersGame();
	//This is primary function of the computerVSuser game mode.
	void versusCompGame();
	void playGame();
	void setBoardSize();
	//This function returns the validity of the input that the user enters(board size).
	bool isBoardSizeValid(string strSize);
	//This function shows the user the game mode options. 
	//It gets the game mode from user.
	//If the input is valid, function returns the game mode.
	//1 --> user vs user game
	//2 --> computer vs user games
	void setGameMode();
	//This function returns the validity of the input that the user enters(game mode).
	bool isModeValid(string strMode);
	char player = 'x', //First user is always 'x'.
		 currentState;
	int start, //To check that there is already a Hex object
		boardSize,//boardSize, //Size of board
		gameMode = -1,//1 -> user vs user game.
		//2 -> computer vs user game.
		currentRow = -1, //Current row
		currentColumn = -1, //Current column
		compMove; //To check that this is computer's first move or not	
	bool gameOver; //To check game is over or not
	vector < vector <int> > checkArray; //To control of the cell positions
};

bool isValidSequence(AbstractHex * sequence[], int sizeOfSequence);//the global func

}

#endif