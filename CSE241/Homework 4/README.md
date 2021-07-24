> Notes:
##### 1) Gameplay:
    At the beginning of the game, you will be asked what you want to play.
    You can choose: "1" -> Only one game will be played at a time.
    or you can choose: "2" -> Multiple games will be played at the same time.

	If you choose "1", you will be asked the game board size and the game mode.
	And the game will begin.

	If you choose "2", you will be asked how many games that you want to play at the same time. 
	!! NOTE: You just have to enter numbers(integers). This number has to be greater
	than 1.
	Then, for each game, you will be asked the game board size and the game mode.
	After selecting the board size and game mode for all games, Game1 will start.

	When entering input, you can enter LOAD, SAVE, NEW, or moves.
	LOAD -> loads from the entered filename
	SAVE -> saves to the entered filename
	NEW -> You have to write "NEW". After that, you will be asked the number of the game
		-> want to open. The number have to be 1,2,3 ...
		NOTE: Games are named in the order in which you enter information 
		(board size and game mode). 
		For example: 
		There are 5 active games. The first game that entered information is Game1. 
		The second is Game2. ... The fifth is Game5. 
		If you want to play the fifth game, you have to enter "5". 
		If you want to play the first game, you have to enter "1".
	SCORE -> shows the instanst score(When game is over, scores are also shown)
		NOTE: Until the game is over(until a player wins), moves are counted.
			x's score = the number of moves x in the table
			o's score = the number of moves o in the table
			(boardSize*boardSize) points are added to the winner's score.
		For example:
			boardSize=6
			the number of the x's moves = 5
			the number of the o's moves = 6
			**during game**
			score of x = 5 and score of o = 6 points
			**game is over and o is the winner**
			score of x = 5 and score of o = 6+(6*6) = 42 points
	PREUNDO -> (--HexObject)
			For example:
				x plays(1 step)
				o plays(2 step)
				x plays(3 step)
				o enters PREUNDO and last moves of x and o are deleted.
				The board(also the game) returns 2. step and waiting for o's moves.
			NOTES: If there is no move, or there is a move,	the player cannot PREUNDO.
				To do PREUNDO, there is at least 2 moves and the game wants 3. moves.
	POSTUNDO -> (HexObject--)
			For example:
				x plays(1 step)
				o plays(2 step)
				x plays(3 step)
				o enters POSTUNDO and last moves of x and o are deleted.
				The board(also the game) returns 2. step and waiting for o's moves.
			NOTES: If there is no move, or there is a move,	the player cannot POSTUNDO.
				To do POSTUNDO, there is at least 2 moves and the game wants third moves.


	When all active games are finished, total marked cells and active games are
	compared with each other.

	The program ends only when all active games are finished and prints the total score 
	of players.

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
		(moves)

	Game mode is 1 or 2.
        - 1 is user vs user game.
        - 2 is computer vs user game.
	Moves like that:
	    First index of the first move
	    Second index of the first move
	    First index of the second move
	    Second index of the second move
        ...etc