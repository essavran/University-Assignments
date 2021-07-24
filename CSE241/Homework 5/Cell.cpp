#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include "Cell.h"

using namespace std;

namespace ess{

void Cell::setUser(cellState cState){
	user = static_cast<char>(cState);
}

void Cell::setUser(char c){
	user = c;
}

void Cell::setRowColumn(int i, int j){
	row = i;
	column = j;	
}

char Cell::getUser(void){
	return user;
}

int Cell::getRow(void){
	return row;
}

int Cell::getColumn(void){
	return column;
}

}