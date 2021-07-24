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
using namespace std;

#ifndef HELPER_h
#define HELPER_h

//The cell will filled with x, o, or .
enum class cellState: char { x='x', o='o', dot='.' };

class Hex{

public:
	//Board size and game mode are taken as input.
	Hex();
	
	//Game mode are taken as input. Board size are determined when defining class.
	Hex(int mode);
	
	//Board size and game mode are determined when defining class.
	Hex(int size, int mode);
	
	//Starting and playing the game.
	void playGame();
	
	//To say welcome and goodbye.
	void welcome() const;
	void goodbye() const;
	
	//Returns the number of marked cells in all games.
	static int numOfMarkedCells();
	
	//Returns the number of marked celles in current game
	int getCurrentCount() const;
	
	//Compares the Hex games.
	//return true->First game has more marked cells
	//otherwise it returns false
	bool compareHexGames(Hex anotherHex);
	
	//These functions return current width and height of the board
	int getWidth() const;
	int getHeight() const;
	
	//If there is more than one game, it returns the end state of the active game
	int getCurrentGameOver() const;
	
	//Set the number of active games
	//-> multiGames = active 
	void setMultiGames(int active);

	//Returns that a new game is requested or not
	int getNewGame() const;

private:
	
	//This function shows the user the size options. 
	//It gets the size from user.
	//If the input is valid, function returns the size.
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

	//This function fills the board with dots.
	void createInitialBoard();

	//Sets the width and height of the board.
	void setWidthHeight();
	
	//This function prints the board.
	void showBoard();

	//This is primary function of the userVSuser game mode.
	void twoPlayersGame();

	//This is primary function of the computerVSuser game mode.
	void versusCompGame();

	//This function checks the input's validity.
	//If the input is not valid, returns false.
	//If the input is valid, the function decides LOAD,SAVE,NEW or Movement and goes to other related functions.
	bool checkInput(const string &input);

	//This function checks that the string is LOAD or SAVE.
	bool isLoadOrSave(const string &input, const string str);

	//If the input is LOAD or SAVE, this function checks the filename's validity.
	bool isFileNameValid(const string &input);

	//Loads the current game status to the file.
	//1 -> user vs user game.
	//2 -> computer vs user game.
	void load(const string &input);

	//Saves the current game status to the file.
	//1 -> user vs user game.
	//2 -> computer vs user game.
	void save(const string &input);

	//This function checks the move's validity.
	bool isMoveValid(const string &input);

	//This function fills the boolean array with 'false'.
	inline void createBooleanArray();

	//To check that there is "NEW"
	bool isNewGame(const string &input);

	//To count marked cells of the current board
	void countMarkedCells();

	//Assigns the input to temporary string. Deletes the characters in the string
	//from the beginning to a certain place(to toEnd). Converts the remaining the 
	//string to an integer. And returns the integer value.
	//toEnd is a default argument.
	//For example:
	//strToInt(input); means that the first two characters will be deleted.
	//strToInt(input); means that no characters will be deleted.
	inline int strToInt(const string &input, int toEnd=2);

	//Checks the game is over or not. And returns.
	bool end();
	
	//This function checks the fullness of the board.
	bool isBoardFull();
	
	//Checks the index is valid or not.
	//For example:
	//If boardSize=6, index cannot be -1 or 7. The function returns 0.
	bool isValid(const int index);
	
	//Searchs 'o' is winner or not.
	bool win_o();
	
	//Searchs the existence of 'o' in rows one by one.
	//If there is an 'o' where it is searching, it continues.
	//Otherwise, the function stops.
	void winRecursion_o(int counter[4]);

	//Searchs 'x' is winner or not.
	bool win_x();

	//Searchs the existence of 'x' in rows one by one.
	//If there is an 'x' where it is searching, it continues.
	//Otherwise, the function stops.
	void winRecursion_x(int counter[4]);

	//Converts uppurcase letters in the board to lowercase letters.	
	void convertLowerCase();

	//This function decides which move the computer will make and play
	void play();
	
	//This function play user's move
	void play(int row, int column);

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

	class Cell{
	public:
		Cell(); //The cell is filled with dot
		inline void setUser(cellState cState); //Set the cell state as user
		inline void setUser(char c);//Set the char as user
		inline void setRowColumn(int row, int column);//Set row and column
		inline char getUser();//Get user value
		inline int getRow();//Get row value
		inline int getColumn();//Get column value
	private:
		char user;//x, o, .
		int row, //1, 2, 3, ...
			column;//A, B, C, ... as integer
	};
	
	int start, //To check that there is already a Hex object
		boardSize, //Size of board
		gameMode, //Game mode:
		//1 -> user vs user game.
		//2 -> computer vs user game.
		currentRow, //Current row
		currentColumn, //Current column
		compMove, //To check that this is computer's first move or not
		currentCount = 0, //To count cells that marked
		currentWidth, //Current width
		currentHeight, //Current Height
		currentGameOver = 0,// =0 -> The current game is not over, =1 -> The current game is over
		multiGames = 0, // >0 -> There are active games, =0 -> A single game
		newGame = 1; //To check "NEW", wanted to play another active game
	
	bool gameOver; //To check game is over or not
	
	char player = 'x'; //First user is always 'x'.
	
	static int totalCount; // To count marked cells of the all current active games
	
	vector< vector<Cell> > hexCells;
	
	vector < vector <int> > checkArray; //To control of the cell positions
};
#endif