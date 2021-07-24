#include <iostream> 
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include "AbstractHex.h"

#include <stdlib.h>

using namespace std;
//using namespace ess;//??
#ifndef HEXARRAY1D_h
#define HEXARRAY1D_h

namespace ess{

class HexArray1D : public AbstractHex {

public:
	HexArray1D();//When object is created, base contructor is called
				//created hexCells and reset
				//and start play the game
	HexArray1D(int inputSize);//gameMode will be 2(compgame)
	HexArray1D(int inputSize, int inputGameMode);//Without taking inputs, to test the functions 
	HexArray1D(const HexArray1D &hexGame);//copy constructor
	~HexArray1D();//destructor
	HexArray1D& operator=(const HexArray1D &hexGame);//assignment operator
	Cell * hexCells1D;//board
	//There are pure virtual functions
	//from base class
	virtual Cell operator()(int row, int column) const;
	virtual void setSize(int board);
	virtual void reset();
	virtual void play();
	virtual void play(Cell cellS);
	virtual void readFromFile(const string &fileName);

//------
//previous hws
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