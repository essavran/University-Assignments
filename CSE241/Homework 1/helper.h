/*
* CSE241 - HOMEWORK 1
* Emine Sultan Savran
* 1801042637
*/

#include <iostream> 
#include <string>
#include <random>
#include <chrono>
using namespace std;

#ifndef HELPER_h
#define HELPER_h

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
void showBoard(char board[12][12], int boardSize);

/*
* This function fills the board with dots.
*/
void createInitialBoard(char board[12][12], int boardSize);

/*
* This function fills the boolean array with 'false'.
*/
void createBooleanArray(int boardSize, bool bArray[12][12]);

/*
* This is primary function of the userVSuser game mode.
*/
void twoPlayersGame(char board[12][12], int boardSize);

/*
* This is primary function of the computerVSuser game mode.
*/
void versusCompGame(char board[12][12], int boardSize);

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
int isCompMoveValid( int row, int column, int boardSize);

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