#include <iostream> 
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <deque>
#include "AbstractHex.h"

using namespace std;
//using namespace ess;//??
#ifndef HEXADAPTER_h
#define HEXADAPTER_h

namespace ess{

template <class T>
class HexAdapter : public AbstractHex {

public:
	HexAdapter();//When object is created, base contructor is called
				//created hexCells and reset
				//and start play the game
	HexAdapter(int inputSize);//gameMode will be 2(compgame)
	HexAdapter(int inputSize, int inputGameMode);//Without taking inputs, to test the functions
	T hexCells;//board
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