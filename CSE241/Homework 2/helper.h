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
using namespace std;

#ifndef HELPER_h
#define HELPER_h

/*
* The cell will filled with x, o, or .
*/
enum class cellState: char { x='x', o='o', dot='.' };

/*
* This function shows the user the size options. 
* It gets the size from user.
* If the input is valid, function returns the size.
*/
int boardSize();

/*
* This function returns the validity of the input that the user enters(board size).
*/
int isBoardSizeValid(string boardSize);

/*
* This function shows the user the game mode options. 
* It gets the game mode from user.
* If the input is valid, function returns the game mode.
* 1 --> user vs user game
* 2 --> computer vs user games
*/
int gameMode();

/*
* This function returns the validity of the input that the user enters(game mode).
*/
int isModeValid(string gMode);

/*
* This function prints the board.
*/
void showBoard(const char board[12][12], int boardSize);

/*
* This function fills the board with dots.
*/
void createInitialBoard(char board[12][12], int boardSize);

/*
* This function fills the boolean array with 'false'.
*/
void createBooleanArray(int &boardSize, bool bArray[12][12]);

/*
* This is primary function of the userVSuser game mode.
*/
void twoPlayersGame(char board[12][12], int &boardSize, char &user);

/*
* This function checks the input's validity.
* If the input is not valid, returns false.
* If the input is valid, the function decides LOAD,SAVE or Movement and goes to other related functions.
*/
bool checkInput(char board[12][12], int &boardSize, const string &input, bool bArray[12][12], char &user, int &gameMode);

/*
* This function checks that the string is LOAD or SAVE.
*/
bool isLoadOrSave(const string &input, const string str);

/*
* If the input is LOAD or SAVE, this function checks the filename's validity.
*/
bool isFileNameValid(const string &input);

/*
* This function checks the move's validity.
*/
bool isMoveValid(char board[12][12], int &boardSize, const string &input);

/*
* Assigns the input to temporary string. Deletes the characters in the string
* from the beginning to a certain place(to toEnd). Converts the remaining the 
* string to an integer. And returns the integer value.
* toEnd is a default argument.
* For example:
* strToInt(input); means that the first two characters will be deleted.
* strToInt(input); means that no characters will be deleted.
*/
int strToInt(const string &input, int toEnd = 2);

/*
* Takes the current move, and replaces it in the game board.
*/
void move(char board[12][12], const string &input, char &user);

/*
* Checks the game is over or not. And returns.
*/
bool end(char board[12][12], int &boardSize, bool bArray[12][12]);

/*
* Saves the current game status to the file.
* 1 -> user vs user game.
* 2 -> computer vs user game.
*/
void save(char board[12][12], int &boardSize, const string &input, char user, int gameMode); //1->pp 2->cp

/*
* Loads the current game status to the file.
* 1 -> user vs user game.
* 2 -> computer vs user game.
*/
void load(char board[12][12], int &boardSize, const string &input, char &user, int &gameMode);

/*
* This is primary function of the computerVSuser game mode.
*/
void versusCompGame(char board[12][12], int &boardSize, char &user);

/*
* This function decides which move the computer will make.
*/
void computer(char board[12][12], int boardSize, int moveArray[3]);

/*
* This function finds moves that the computer can make against the user.
* For example:
* 
*   . .
*  . o . 
*   . .
*
*	is looks like this:
*
*   1 2
*  6 o 3 
*   5 4	 
*
* If the user made this move, the computer selects one of the dots around 'o'.
* In this process, computer aims to block the user's path.
* First, computer tries to place 'x' on points in the vertical path. (1,2,4,5)
* If these are full, computer looks another points. (3,6)
*/
void createPossibleMoves( char board[12][12], int boardSize,  int moveArray[3], int possibleMoves[6][2]);

/*
* This function checks the validity of the computer's moves.
*/
int isCompMoveValid(int row, int column, int boardSize);

/*
* This function checks the fullness of the board.
*/
int isBoardFull(char board[12][12], int boardSize);

/*
* Checks the index is valid or not.
* For example:
* If boardSize=6, index cannot be -1 or 7. The function returns 0.
*/
int isValid(int index, int boardSize);

/*
* Searchs 'o' is winner or not.
*/
int win_o(char board[12][12], int boardSize, bool bArray[12][12]);

/*
* Searchs the existence of 'o' in rows one by one.
* If there is an 'o' where it is searching, it continues.
* Otherwise, the function stops.
*/
void winRecursion_o(char board[12][12], bool bArray[12][12], int counter[4]);

/*
* Searchs 'x' is winner or not.
*/
int win_x(char board[12][12], int boardSize, bool bArray[12][12]);

/*
* Searchs the existence of 'x' in rows one by one.
* If there is an 'x' where it is searching, it continues.
* Otherwise, the function stops.
*/
void winRecursion_x(char board[12][12], bool bArray[12][12], int counter[4]);

/*
* Converts uppurcase letters in the board to lowercase letters.
*/
void convertLowerCase(char board[12][12], int boardSize);

#endif