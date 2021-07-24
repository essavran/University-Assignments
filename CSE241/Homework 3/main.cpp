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

int main(){
	string choice, sActive; // To take input
	int	finishedGameCounter = 0,
		currentGame = 0,
		active, // To take input
		number = 0,
		selectGame = 0;
	cout << endl << "******* WELCOME TO HEX GAME *******" << endl << endl;
	cout << "What do you want to play?" << endl
		 << "1. A single game" << endl
		 << "2. Multiple games at the same time" << endl
		 << "Choice: ";
	do{
		getline(cin, choice);
		if( choice[0] != '1' && choice[0] != '2' ){
			cerr << "Enter a valid input: ";
		}
	} while( choice[0] != '1' && choice[0] != '2' );

	if( choice[0] == '1' ){ // a single game
		Hex game1;
		game1.playGame();
	} else if( choice[0] == '2' ){ // multiple games
		vector < Hex > activeGames;
		cout << "How many games do you want to play? "; // Have to be 2,3,... etc
		do{
			getline(cin, sActive);
			if( sActive[0] < '2' ){
				cerr << "Enter a valid input: ";
			}
		} while( sActive[0] < '2' );
		active = stoi(sActive);
		for(int i=0; i<active; i++){
			cout << endl << "----> For the Game" << i+1 << ":" << endl; //creating the Hex vector and the game board
			activeGames.push_back( Hex() );
		}
		do{
			cout << endl << "----> Let's play the Game" << currentGame+1 << endl;
			activeGames[currentGame].setMultiGames(active);
			activeGames[currentGame].playGame();
		
			if( activeGames[currentGame].getCurrentGameOver() == 1 ){ // The current game is over
				//cout << "The Current game is over." << endl;
				finishedGameCounter++;
			} else if( activeGames[currentGame].getNewGame() == 1 ){ // User wants to play an another games
				cout << "You want to play an another game." << endl;
			}
			if( finishedGameCounter != active ){
				do{
					cout << "Enter a number of the game that you want to play: "; // Have to be 1,2,3,... etc
					cin >> selectGame;
					cin.clear();
					cin.ignore(10000,'\n');
					if( activeGames[selectGame-1].getCurrentGameOver() == 1 ){
						cout << "This game is over. Please select another." << endl;
						selectGame = -1;
					}	
				} while( !(selectGame > 0 && selectGame <= active) );
				currentGame = selectGame-1;
			}
		} while( finishedGameCounter != active );

		number = activeGames[currentGame].numOfMarkedCells();
		cout << endl << "----> Active all games are over. " << endl;
		for(int i=0; i<active; i++){ //Compares Hexs
			cout << endl
				 << "-> Game" << i+1 << " has " << activeGames[i].getCurrentCount() << " marked cells. " << endl;
			for(int j=0; j<active; j++){
				if( i != j ){
					cout << "-> Game" << j+1 << " has " << activeGames[j].getCurrentCount() << " marked cells. ";
					if( activeGames[i].compareHexGames(activeGames[j]) ){
						cout << "	-> Game" << i+1 << " has more." << endl;
					} else{
						cout << "	-> Game" << i+1 << " has equal or less." << endl;
					}					
				}
			}
		}
		cout << endl << "---> Number of total marked cells: " << number << endl; //Total marked cells
		cout << endl << "GOODBYE!" << endl << endl;
	}
	return 0;
}
