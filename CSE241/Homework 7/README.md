> Notes:

##### 1) Gameplay:
    At the beginning of the game, you will be asked
    the game board size and the game mode.
    And the game will begin.

	LOAD -> loads from the entered filename
	SAVE -> saves to the entered filename
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
	UNDO ->	For example:
                    x plays(1 step)
                    o plays(2 step)
                    x plays(3 step)
                    o clicks UNDO and last moves of x is deleted.
                    The board(also the game) returns 3. step and waiting for x's moves.
			NOTES: If there is no move,	the player cannot UNDO.
				To do UNDO, there is at least a move and the game wants second moves.

	RESET -> Empty the board

    !!! The game board is square. So, when asked for the board size, enter
    the length of a single edge. For example:
    6x6 --> Enter just "6"
    15x15 --> Enter just "15"

##### 2)
	'x' makes the first move,
	'o' makes the second move.
	Computer always makes the first move.

##### 3) 
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