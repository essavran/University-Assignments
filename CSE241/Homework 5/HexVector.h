#include <iostream> 
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include "AbstractHex.h"

using namespace std;
#ifndef HEXVECTOR_h
#define HEXVECTOR_h

namespace ess{

class HexVector : public AbstractHex {

public:
	HexVector();//When object is created, base contructor is called
				//created hexCells and reset
				//and start play the game
	HexVector(int inputSize);//gameMode will be 2(compgame)
	HexVector(int inputSize, int inputGameMode);//Without taking inputs, to test the functions 
	vector< vector<Cell> > hexCells;//board
	//There are pure virtual functions
	//from base class
	virtual Cell operator()(int row, int column) const;
	virtual void setSize(int board);
	virtual void reset();
	virtual void play();
	virtual void play(Cell cellS);
	virtual void readFromFile(const string &fileName);

//from previous hws
private:
	//Converts uppurcase letters in the board to lowercase letters.	
	void convertLowerCase();
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
};

}

#endif