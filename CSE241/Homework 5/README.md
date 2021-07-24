> Notes:
##### 1) Gameplay:
    At the beginning of the game, you will be asked what you want to do.
    You can choose: "1" -> Play a game.
    or you can choose: "2" -> Testing class' functions.
    or you can choose: "3" -> Testing the global function.

	If you choose "1", you will be asked which derived class.
	After, you will be asked the game board size and the game mode.
	And the game will begin.
	When entering input, you can enter LOAD, SAVE, TOTALMOVES, LASTMOVE
	LOAD -> loads from the entered filename
	SAVE -> saves to the entered filename
	TOTALMOVES -> prints total moves of the board
	LASTMOVE -> prints last move of the board
	
	If you choose "2", you will be asked the function you want to test.
	When you select a function, the function is tested for HexVector, HexArray1D,
	HexAdapter< deque < deque < Cell > > >, and HexAdapter< vector < vector < Cell > > >

	If you choose "3", you will test the global function.

	NOTE: 
	The game board is square. So, when asked for the board size, enter
	the length of a single edge. For example:
	6x6 --> Enter just "6"
	15x15 --> Enter just "15"
	
##### 2) 
	User moves must be "A 2" format.
	Letters and numbers may change depends on board size.
	But if you set a board size that exceeds the letters in the alphabet,
	there will be problems in the game.

##### 3)
	'x' makes the first move,
	'o' makes the second move.
	Computer always makes the first move.

##### 4) 
	In the file names, ".txt" must be there.
	The file names cannot be ".txt" or "..txt".

	The file design is as below:
		(board size)
		(game mode)
		(the player who should make the move)
		(current board/the board array)
		(total number of moves)
		(last move's row)
		(last moves's column)

	Game mode is 1 or 2.
    - 1 is user vs user game.
	- 2 is computer vs user game.

	If there is "-1", it means that the variable does not set.
	(For example: There is no last move)

##### 5)
	When the global function is tested, the program does not print all the boards.
	If you want to print, please remove comments(/**/)

##### 6)
	Functions of the classes will be tested with "TestHexVector.TXT", "TestHexArray1D.TXT", 
	"TestHexAdapterDeque.TXT" and "TestHexAdapterVector.TXT"
	and saved to "SAVEHexVector.TXT", "SAVEHexArray1D.TXT", 
	"SAVEHexAdapterDeque.TXT" and "SAVEHexAdapterVector.TXT"
	If you want, you can change file names

##### 7)
	The contents of .txt files are considered appropriate. There cannot be invalid input.

##### 8)
	The global function is tested with test1.TXT, test2.TXT, test3.TXT, test4.TXT, test5.TXT