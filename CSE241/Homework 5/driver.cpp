#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"
#include "HexAdapter.cpp"

using namespace std;
using namespace ess;

void testing();//to test the functions
void testingGlobalFunction();//to create an array for the global func and call the global func

int main(){
	string choice;

	cout << endl << "******* WELCOME TO HEX GAME *******" << endl << endl;
	cout << "What do you want to do?" << endl;
	cout << "1) Play a game" << endl
		 << "2) Testing functions of classes" << endl
		 << "3) Testing the global function" << endl
		 << "Enter 0(zero) to quit" << endl;
	do{	
		getline(cin, choice);
		if( choice.compare( "1" ) == 0 ){ //plays the game
			string start;
			do{
				cout << "Select derived class: " << endl;
				cout << "1) HexVector" << endl
					 << "2) HexArray1D" << endl
					 << "3) HexAdapter(deque)" << endl
					 << "4) HexAdapter(vector)" << endl
					 << "Enter 0(zero) to quit" << endl;
				getline(cin, start);
				if( start.compare( "1" ) == 0 ){
					HexVector game;
					start = '0';
				} else if( start.compare( "2" ) == 0 ){
					HexArray1D game;
					start = '0';
				} else if( start.compare( "3" ) == 0 ){
					HexAdapter< deque < deque < Cell > > > game;					
					start = '0';
				} else if( start.compare( "4" ) == 0 ){
					HexAdapter< vector < vector < Cell > > > game;
					start = '0';
				} else{
					if( start.compare( "0" ) != 0 )
						cout << "Please enter valid input: ";
				}
			} while( choice.compare( "0" ) != 0 );
			
		} else if( choice.compare( "2" ) == 0 ){//testing class' functions
			testing();
			choice = '0';
		} else if( choice.compare( "3" ) == 0 ){//testing the global function
			testingGlobalFunction();//this will call the global function
			choice = '0';
		} else{
			if( choice.compare( "0" ) != 0 )
				cout << "Please enter valid input: ";
		}
	} while( choice.compare( "0" ) != 0 );
	return 0;
}

void testingGlobalFunction(){
	AbstractHex * sequence1[1],
				* sequence2[2],
				* sequence3[3],
				* sequence4[4],
				* sequence5[5];
	//creating arrays
	cout << "*******************************************" << endl;
	//First sequence
	cout << "-> 1st sequence: " << endl;
	sequence1[0] = new HexVector(6,2);//create
	sequence1[0]->readFromFile("test1.TXT");//filled
	//If you want, you can print them
	/*
	cout << "Board of 1st Sequence: " << endl;
	sequence1[0]->print();
	*/
	if( isValidSequence(sequence1,1) ){
		cout << "A valid sequence of moves for a game" << endl;
	} else{
		cout << "Not a valid sequence of moves for a game" << endl;
	}
	cout << "*******************************************" << endl;
	//Second sequence
	cout << "-> 2nd sequence: " << endl;
	sequence2[0] = new HexVector(6,2);
	sequence2[1] = new HexArray1D(6,2);
	sequence2[0]->readFromFile("test1.TXT");//filled
	sequence2[1]->readFromFile("test2.TXT");//filled
	//If you want, you can print them
	/*
	cout << "Boards of 2nd Sequence: " << endl;
	sequence2[0]->print();
	sequence2[1]->print();
	*/
	if( isValidSequence(sequence2,2) ){
		cout << "A valid sequence of moves for a game" << endl;
	} else{
		cout << "Not a valid sequence of moves for a game" << endl;
	}
	cout << "*******************************************" << endl;
	//Third sequence
	cout << "-> 3rd sequence: " << endl;
	sequence3[0] = new HexVector(6,2);
	sequence3[1] = new HexArray1D(6,2);
	sequence3[2] = new HexAdapter< deque < deque < Cell > > > (8,2);
	sequence3[0]->readFromFile("test1.TXT");//filled
	sequence3[1]->readFromFile("test2.TXT");//filled
	sequence3[2]->readFromFile("test3.TXT");//filled
	//If you want, you can print them
	/*
	cout << "Boards of 3rd Sequence: " << endl;
	sequence3[0]->print();
	sequence3[1]->print();
	sequence3[2]->print();
	*/
	if( isValidSequence(sequence3,3) ){
		cout << "A valid sequence of moves for a game" << endl;
	} else{
		cout << "Not a valid sequence of moves for a game" << endl;
	}
	cout << "*******************************************" << endl;
	//4th sequence
	cout << "-> 4th sequence: " << endl;
	sequence4[0] = new HexVector(6,2);
	sequence4[1] = new HexArray1D(6,2);
	sequence4[2] = new HexAdapter< deque < deque < Cell > > > (8,2);
	sequence4[3] = new HexAdapter< vector < vector < Cell > > > (9,2);
	sequence4[0]->readFromFile("test1.TXT");//filled
	sequence4[1]->readFromFile("test2.TXT");//filled
	sequence4[2]->readFromFile("test3.TXT");//filled
	sequence4[3]->readFromFile("test4.TXT");//filled
	//If you want, you can print them
	/*
	cout << "Boards of 4th Sequence: " << endl;
	sequence4[0]->print();
	sequence4[1]->print();
	sequence4[2]->print();
	sequence4[3]->print();
	*/
	if( isValidSequence(sequence4,4) ){
		cout << "A valid sequence of moves for a game" << endl;
	} else{
		cout << "Not a valid sequence of moves for a game" << endl;
	}
	cout << "*******************************************" << endl;
	//5th sequence
	cout << "-> 5th sequence: " << endl;
	sequence5[0] = new HexVector(6,2);
	sequence5[1] = new HexArray1D(6,2);
	sequence5[2] = new HexAdapter< deque < deque < Cell > > > (8,2);
	sequence5[3] = new HexAdapter< vector < vector < Cell > > > (9,2);
	sequence5[4] = new HexVector(6,2);
	sequence5[0]->readFromFile("test1.TXT");//filled
	sequence5[1]->readFromFile("test2.TXT");//filled
	sequence5[2]->readFromFile("test3.TXT");//filled
	sequence5[3]->readFromFile("test4.TXT");//filled
	sequence5[4]->readFromFile("test5.TXT");//filled
	//If you want, you can print them
	/*
	cout << "Boards of 5th Sequence: " << endl;
	sequence5[0]->print();
	sequence5[1]->print();
	sequence5[2]->print();
	sequence5[3]->print();
	sequence5[4]->print();
	*/
	if( isValidSequence(sequence5,5) ){
		cout << "A valid sequence of moves for a game" << endl;
	} else{
		cout << "Not a valid sequence of moves for a game" << endl;
	}
	cout << "*******************************************" << endl;
}

void testing(){
	string choice;
	//creating abstracthex* vector
	vector < AbstractHex * > hexGames( 4 ); 

	do{	
		hexGames[ 0 ] = new HexVector(6,2);
		hexGames[ 1 ] = new HexArray1D(7,2);
		hexGames[ 2 ] = new HexAdapter< deque < deque < Cell > > > (8,2);
		hexGames[ 3 ] = new HexAdapter< vector < vector < Cell > > > (9,2);

		cout <<  endl 
		 << "Select the function you want to test:" << endl
		 << "1) print" << endl
		 << "2) readFromFile" << endl
		 << "3) writeToFile" << endl
		 << "4) reset" << endl
		 << "5) setSize" << endl
		 << "6) play()" << endl
		 << "7) play(Cell)" << endl
		 << "8) isEnd" << endl
		 << "9) operator()" << endl
		 << "10) operator==" << endl
		 << "11) lastMove" << endl
		 << "12) numberOfMoves" << endl	
		 << "Enter 0(zero) to quit" << endl;
		getline(cin, choice);


		if( choice.compare( "1" ) == 0 ){ //test print()
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				if( i == 0 ){
					cout << endl << "print() of HexVector" << endl;
				} else if( i == 1 ){
					cout << "print() of HexArray1D" << endl;
				} else if( i == 2 ){
					cout << "print() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					cout << "print() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->print();
				cout << endl;
			}
		} else if( choice.compare( "2" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl

				<< "***************************************" << endl;
				cout << "Before reading: " << endl;
				hexGames[i]->print();
				cout << endl;
				if( i == 0 ){
					hexGames[ i ]->readFromFile("TestHexVector.TXT");
					cout << endl << "readFromFile() of HexVector" << endl;
				} else if( i == 1 ){
					hexGames[ i ]->readFromFile("TestHexArray1D.TXT");
					cout << "readFromFile() of HexArray1D" << endl;
				} else if( i == 2 ){
					hexGames[ i ]->readFromFile("TestHexAdapterDeque.TXT");
					cout << "readFromFile() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					hexGames[ i ]->readFromFile("TestHexAdapterVector.TXT");
					cout << "readFromFile() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->print();
				cout << endl;
			}
		} else if( choice.compare( "3" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				if( i == 0 ){
					hexGames[ i ]->writeToFile("SAVEHexVector.TXT");
					cout << endl << "writeToFile() of HexVector" << endl;
				} else if( i == 1 ){
					hexGames[ i ]->writeToFile("SAVEHexArray1D.TXT");
					cout << "writeToFile() of HexArray1D" << endl;
				} else if( i == 2 ){
					hexGames[ i ]->writeToFile("SAVEHexAdapterDeque.TXT");
					cout << "writeToFile() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					hexGames[ i ]->writeToFile("SAVEHexAdapterVector.TXT");
					cout << "writeToFile() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->print();
				cout << endl;
				cout << "!!! Please look the files" << endl;
			}	
		}else if( choice.compare( "4" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				cout << "Before reset()" << endl;
				hexGames[i]->print();
				if( i == 0 ){
					cout << "reset() of HexVector" << endl;
				} else if( i == 1 ){
					cout << "reset() of HexArray1D" << endl;
				} else if( i == 2 ){
					cout << "reset() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					cout << "reset() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->reset();
				hexGames[i]->print();
				cout << endl;
			}	
		}else if( choice.compare( "5" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				cout << "Before setSize()" << endl;
				hexGames[i]->print();
				if( i == 0 ){
					cout << "setSize() of HexVector" << endl;
				} else if( i == 1 ){
					cout << "setSize() of HexArray1D" << endl;
				} else if( i == 2 ){
					cout << "setSize() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					cout << "setSize() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->setSize(9);
				hexGames[i]->print();
				cout << endl;
			}

		}else if( choice.compare( "6" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				cout << "Before play()" << endl;
				hexGames[i]->print();
				if( i == 0 ){
					cout << "play() of HexVector" << endl;
				} else if( i == 1 ){
					cout << "play() of HexArray1D" << endl;
				} else if( i == 2 ){
					cout << "play() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					cout << "play() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->play();
				hexGames[i]->print();
				cout << endl;
			}

		}else if( choice.compare( "7" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				cout << "Before play()" << endl;
				hexGames[i]->print();
				if( i == 0 ){
					cout << "play() of HexVector" << endl;
				} else if( i == 1 ){
					cout << "play() of HexArray1D" << endl;
				} else if( i == 2 ){
					cout << "play() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					cout << "play() of HexAdapter(vector)" << endl;
				}
				Cell temp;
				temp.setRowColumn(1,2);
				temp.setUser('x');
				hexGames[i]->play(temp);
				cout << "User (" << temp.getUser() <<") is played at (" << temp.getRow() + 1 << "," << static_cast<char>( temp.getColumn() + 65 ) << ")" << endl;
				hexGames[i]->print();
				cout << endl;
			}

		}else if( choice.compare( "8" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				if( i == 0 ){
					hexGames[ i ]->readFromFile("TestHexVector.TXT");
					cout << "isEnd() of HexVector" << endl;
				} else if( i == 1 ){
					hexGames[ i ]->readFromFile("TestHexArray1D.TXT");
					cout << "isEnd() of HexArray1D" << endl;
				} else if( i == 2 ){
					hexGames[ i ]->readFromFile("TestHexAdapterDeque.TXT");
					cout << "isEnd() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					hexGames[ i ]->readFromFile("TestHexAdapterVector.TXT");
					cout << "isEnd() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->print();
				if( hexGames[i]->isEnd() ){
					cout << "Game is over" << endl;
				} else{
					cout << "Game is not over" << endl;
				}
			}

		}else if( choice.compare( "9" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl << "The index(wanted) is (" << static_cast<char>( 2 + 65 )
					 << "," 
					 << 1 + 1  << ") : " << endl;
				cout << endl;
				if( i == 0 ){
					hexGames[ i ]->readFromFile("TestHexVector.TXT");
					cout << "operator() of HexVector" << endl;
				} else if( i == 1 ){
					hexGames[ i ]->readFromFile("TestHexArray1D.TXT");
					cout << "operator() of HexArray1D" << endl;
				} else if( i == 2 ){
					hexGames[ i ]->readFromFile("TestHexAdapterDeque.TXT");
					cout << "operator() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					hexGames[ i ]->readFromFile("TestHexAdapterVector.TXT");
					cout << "operator() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->print();
				cout << "User (" << hexGames[i]->operator()(1,2).getUser() <<") is played at (" << static_cast<char>( hexGames[i]->operator()(1,2).getColumn() + 65 )
					 << "," 
					 << hexGames[i]->operator()(1,2).getRow() + 1  << ")" << endl;
			}
		}else if( choice.compare( "10" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				if( i == 0 ){
					hexGames[ i ]->readFromFile("TestHexVector.TXT");
					cout << endl << "operator== of HexVector" << endl;
				} else if( i == 1 ){
					hexGames[ i ]->readFromFile("TestHexArray1D.TXT");
					cout << "operator== of HexArray1D" << endl;
				} else if( i == 2 ){
					hexGames[ i ]->readFromFile("TestHexAdapterDeque.TXT");
					cout << "operator== of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					hexGames[ i ]->readFromFile("TestHexAdapterVector.TXT");
					cout << "operator== of HexAdapter(vector)" << endl;
				}
				cout << "Board A: " << endl;
				hexGames[0]->print();
				cout << "Board B: " << endl;
				hexGames[i]->print();
				if( hexGames[i]->operator== (hexGames[0]) ){
					cout << "Board A and Board B are equal" << endl;;
				} else{
					cout << "Board A and Board B are not equal" << endl;
				}
				cout << endl;
			}
		}else if( choice.compare( "11" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				if( i == 0 ){
					hexGames[ i ]->readFromFile("TestHexVector.TXT");
					cout << endl << "lastMove of HexVector" << endl;
				} else if( i == 1 ){
					hexGames[ i ]->readFromFile("TestHexArray1D.TXT");
					cout << "lastMove of HexArray1D" << endl;
				} else if( i == 2 ){
					hexGames[ i ]->readFromFile("TestHexAdapterDeque.TXT");
					cout << "lastMove of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					hexGames[ i ]->readFromFile("TestHexAdapterVector.TXT");
					cout << "lastMove of HexAdapter(vector)" << endl;
				}
				hexGames[i]->print();
				Cell temp = hexGames[i]->lastMove();
				cout << endl;
				if( temp.getUser() == 'o' ){
					temp.setUser('x');
				} else if( temp.getUser() == 'x' ){
					temp.setUser('o');
				}
				cout << "Last move: User (" << temp.getUser() <<") is played at (" <<  static_cast<char>( temp.getColumn() + 65 ) << "," << temp.getRow() + 1 << ")" << endl;
			}	
		}else if( choice.compare( "12" ) == 0 ){
			for( auto i = 0; i<hexGames.size(); i++ ){
				cout << endl
				<< "***************************************" << endl;
				cout << endl;
				if( i == 0 ){
					hexGames[ i ]->readFromFile("TestHexVector.TXT");
					cout << "numberOfMoves() of HexVector" << endl;
				} else if( i == 1 ){
					hexGames[ i ]->readFromFile("TestHexArray1D.TXT");
					cout << "numberOfMoves() of HexArray1D" << endl;
				} else if( i == 2 ){
					hexGames[ i ]->readFromFile("TestHexAdapterDeque.TXT");
					cout << "numberOfMoves() of HexAdapter(deque)" << endl;
				} else if( i == 3 ){
					hexGames[ i ]->readFromFile("TestHexAdapterVector.TXT");
					cout << "numberOfMoves() of HexAdapter(vector)" << endl;
				}
				hexGames[i]->print();
				cout << "Number of moves: " << hexGames[i]->numberOfMoves() << endl;
			}
		}else{
			if( choice.compare( "0" ) != 0 )
				cout << "Please enter valid input.";
		}

		for( auto j = 0; j<hexGames.size(); j++ ){
			delete hexGames[j];
		}
	} while( choice.compare( "0" ) != 0 );
}

