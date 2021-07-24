#include <iostream> 
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

#ifndef CELL_h
#define CELL_h

namespace ess{

enum class cellState: char { x='x', o='o', dot='.' };

class Cell{
public:

	void setUser(cellState cState); //Set the cell state as user
	void setUser(char c);//Set the char as user
	void setRowColumn(int row, int column);//Set row and column
	char getUser();//Get user value
	int getRow();//Get row value
	int getColumn();//Get column value
private:
	char user;//x, o, .
	int row, //1, 2, 3, ...
		column;//A, B, C, ... as integer
};
}

#endif