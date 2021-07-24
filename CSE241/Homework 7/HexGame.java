public interface HexGame{
	
	public void createGameFrame();//to create game frame
	public void newMainFrame();//to change the game frame
	public void save(String filename);//save the board to file
	public boolean load(String filename);//load the board from file
	public void undo();//delete a single step
	public int score(String pState, boolean gOver);// calculate scores
	/*
		I wrote these functions(play functions) as in Hw4, 
		but I could not add them to the interface
		because of the Cell inner class	
	*/
	/*
	//This function play user's move
	public void play(Cell cellPosition);//plays user
	//This function decides which move the computer will make and play
	public Cell play();//plays comp
	*/

	//This function finds moves that 
	//the computer can make against the user.
	//For example:
	//
	//  . .
	// . o . 
	//  . .
	//
	//	is looks like this:
	//
	//  1 2
	// 6 o 3 
	//  5 4	 
	//
	//If the user made this move, the computer selects one of the dots around 'o'.
	//In this process, computer aims to block the user's path.
	//First, computer tries to place 'x' on points in the vertical path. (1,2,4,5)
	//If these are full, computer looks another points. (3,6)
	public void createPossibleMoves(int[][] possibleMoves);
	public void addMoves(int row, int column);
	//This function fills the board with dots.
	public void createInitialBoard();
	//This function fills the boolean array with 'false'.
	public void createBooleanArray();
	public void createMoves();
	//Checks the game is over or not. And returns
	public boolean end();
	//This function checks the fullness of the board.
	public boolean isBoardFull();
	//Searchs 'o' is winner or not.
	public boolean win_o();
	//Searchs the existence of 'o' in rows one by one.
	//If there is an 'o' where it is searching, it continues.
	//Otherwise, the function stops.
	public void winRecursion_o(int[] counter);
	//Searchs 'x' is winner or not.
	public boolean win_x();
	//Searchs the existence of 'x' in rows one by one.
	//If there is an 'x' where it is searching, it continues.
	//Otherwise, the function stops.
	public void winRecursion_x(int[] counter);
	//Converts uppurcase letters in the board to lowercase letters.	
	public void convertLowerCase();
	//Checks the index is valid or not.
	//For example:
	//If boardSize=6, index cannot be -1 or 7. The function returns 0.
	public boolean isValid(int index);
}