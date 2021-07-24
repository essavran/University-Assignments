import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.Color;//to change panel colors
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JRadioButton;
import javax.swing.ButtonGroup;
import javax.swing.JOptionPane;
import javax.swing.JButton;
import javax.swing.JPanel;
import java.util.Random;//create random numbers
import java.util.Scanner;//to read from file
import java.io.FileWriter;   // to write to file
import java.io.IOException;  // file exceptions
import java.io.FileInputStream; //to read from file

public class PlayingHexGame implements HexGame,Cloneable{
	private int boardSize = -1;
	private int gameMode = 2;
	private StartGame startGame;
	private String player = "x";//x always plays first move
	private Cell[][] hexCells;
	private int[][] checkArray; //To control of the cell positions
	private int [][] moves; //to hold the previous moves
	private int lastRandom = -1, currentRow, currentColumn, compMove = 1, numOfMoves = 0;
	private boolean undoCheck = false;
	private boolean saveCheck = false;
	// no-argument constructor
	PlayingHexGame(){
		//To start a game, get a boardSize and gameMode
		startGame = new StartGame();
		startGame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		startGame.setSize( 500, 100 ); // set frame size
		startGame.setVisible( true ); // display frame
	}
 	@Override
    public PlayingHexGame clone() {
    	//clone arrays and classes
        try {
            PlayingHexGame c = (PlayingHexGame) super.clone();
      		c.moves = moves.clone();
            c.hexCells = hexCells.clone();
            c.checkArray = checkArray.clone();
        //  c.startGame = startGame.clone();
            return c;
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }
	//Inner private class StartGame
	private class StartGame extends JFrame{ //get boardSize and game mode. 
		//after, call the mainGameFrame
		public JTextField textField1; // text field 
		public JTextField textField2; // text field to take input
		public JRadioButton uservsuserButton;
		public JRadioButton compvsuserButton;
		public ButtonGroup gameModeButtons;
		
		public StartGame(){
			super( "Welcome to HexGame" );
			setLayout( new GridLayout( 2 , 2, 5, 5 ) ); // set frame layout
			uservsuserButton = new JRadioButton( "User VS User", false );
			compvsuserButton = new JRadioButton( "Computer VS User", true );
			add( uservsuserButton );
			add( compvsuserButton );
			gameModeButtons = new ButtonGroup();
			gameModeButtons.add( uservsuserButton );
			gameModeButtons.add( compvsuserButton );
			StartHandler handlerRadio = new StartHandler();
			uservsuserButton.addActionListener( handlerRadio );
			compvsuserButton.addActionListener( handlerRadio );
			textField1 = new JTextField( "Enter board size and press enter: ");
			textField1.setEditable( false ); // disable editing
			add( textField1 ); // add textField1 to JFrame
			textField2 = new JTextField( 10 );
			add( textField2 );
			// register event handlers
			StartHandler handlerTextField = new StartHandler();
			textField2.addActionListener( handlerTextField );
		}

		private class StartHandler implements ActionListener{
			@Override
			public void actionPerformed(ActionEvent event){  
				if( event.getSource() == textField2 ){
					try{				
						String s = event.getActionCommand();
						int tempInt = Integer.parseInt(s);
						if ( tempInt<6 ){
		  					JOptionPane.showMessageDialog(null, "Invalid input.", "ERROR", JOptionPane.ERROR_MESSAGE);				
		  				} else if( tempInt>=6 ){
							boardSize = tempInt;
							dispose();//close the input frame
							createGameFrame();//open new frame(game frame)
						}
					} catch( NumberFormatException ex ){
		  				JOptionPane.showMessageDialog(null, "Board size is not integer.", "ERROR", JOptionPane.ERROR_MESSAGE);				
					}
				} else{				
					if(uservsuserButton.isSelected()){    
						gameMode = 1;
					} else if(compvsuserButton.isSelected()){	  
						gameMode = 2;
					}
				}
			}
		}
	}
	@Override
	public void createGameFrame(){
		createInitialBoard();
		createBooleanArray();
		createMoves();
		//starting game
		MainGameFrame mainGameFrame = new MainGameFrame();
		mainGameFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		mainGameFrame.setSize( boardSize*100, boardSize*100 ); // set frame size
		mainGameFrame.setVisible( true ); // display frame
	}
	private class MainGameFrame extends JFrame{
		public JButton buttonsCell[][], buttonsFeatures[]; // array of buttons
		private BorderLayout borderLayout; // the gridlayout
		private JPanel panelRight, panelLeft;
		private FilenameFrame fnFrame;// take an input for filename

		 // no-argument constructor
		public MainGameFrame(){
			super( "HexGame" );
			borderLayout = new BorderLayout( 1, 2 ); // 2 by 3; gaps of 5
			setLayout( borderLayout ); // set JFrame layout
			buttonsCell = new JButton[ boardSize ][ boardSize ]; // create array of JButtons
			//game
			panelLeft = new JPanel( );
			panelLeft.setLayout( null );
			panelLeft.setBackground( Color.YELLOW );
			PlayHandler handlerCells = new PlayHandler();
			for(int row = 0; row < boardSize; row++){
				for(int column = 0; column < boardSize; column++){
					buttonsCell[ row ][ column ] = new JButton( hexCells[column][row].getUser() );
					buttonsCell[ row ][ column ].setBounds( row*50+column*50/2+25, column*50+25, 50, 50 );
					buttonsCell[ row ][ column ].addActionListener( handlerCells );
					panelLeft.add( buttonsCell[ row ][ column ] ); // add button to JFrame
				}
			}
			add( panelLeft, BorderLayout.CENTER );//cell buttons are at the center
			//features
			panelRight = new JPanel();
		 	panelRight.setLayout(new GridLayout( 1, 5, 5, 5 ));
			panelRight.setBackground( Color.BLACK ); 
			buttonsFeatures = new JButton[ 5 ];
			buttonsFeatures[ 0 ] = new JButton( "LOAD" );
			buttonsFeatures[ 1 ] = new JButton( "SAVE" );
			buttonsFeatures[ 2 ] = new JButton( "UNDO" );
			buttonsFeatures[ 3 ] = new JButton( "RESET" );
			buttonsFeatures[ 4 ] = new JButton( "SCORE" );
			PlayHandler handlerFeatures = new PlayHandler();
		    for (int i = 0; i < 5; i++) {
				buttonsFeatures[ i ].addActionListener( handlerFeatures );
		    	panelRight.add( buttonsFeatures[ i ] );
		    }
		    if( gameMode == 2 ) helperComp();
		    add( panelRight, BorderLayout.PAGE_START );//features are at the beginning of frame
		}// end GridLayoutFrame constructor

		private class PlayHandler implements ActionListener{
			@Override
			public void actionPerformed(ActionEvent event){
				//checking cell buttons
				createBooleanArray();
				if( gameMode == 1 ){
					for( int i = 0; i < boardSize; i++ ){
						for( int j = 0; j < boardSize; j++ ){
							if( event.getSource() == buttonsCell[i][j] ){
								if( (buttonsCell[i][j].getText()).equals( "." ) ){
									if( player.equals( "x" ) ){
										//buttonsCell[i][j].setText( "x" );
										//user
										Cell tempCell = new Cell();
										tempCell.setRowColumn( j,i );
										tempCell.setUser( "x" );
										play( tempCell );
										addMoves(j, i);
										buttonsCell[i][j].setText( "x" );
										hexCells[j][i].setUser( "x" );
										player = "o";
									} else if( player.equals( "o" ) ){
										buttonsCell[i][j].setText( "o" );
										hexCells[j][i].setUser( "o" );
										player = "x";
										addMoves(j, i);
									}
									if( end() ){
										for( int m=0; m<boardSize; m++ ){
											for( int n=0; n<boardSize; n++ ){
												buttonsCell[n][m].setText( hexCells[m][n].getUser() );
											}
										}
										if( player.equals( "x" ) ){
											JOptionPane.showMessageDialog( null, "O is the winner.\n"+"Score X: "+score("x",false)+"\nScore O: "+score("o",true), 
																			"Scores", JOptionPane.PLAIN_MESSAGE);
										} else if( player.equals( "o" ) ){
											JOptionPane.showMessageDialog( null, "X is the winner.\n"+"Score X: "+score("x",true)+"\nScore O: "+score("o",false),
																			"Scores", JOptionPane.PLAIN_MESSAGE );
										}
										//setVisible( false ); // disable editing
										dispose();
									}
								}
							}
						}
					}
				}//gamemode1end
				else if( gameMode == 2 ){
					if( player.equals( "o" ) ){
						for( int i = 0; i < boardSize; i++ ){
							for( int j = 0; j < boardSize; j++ ){	
								if( event.getSource() == buttonsCell[i][j] ){
									if( (buttonsCell[i][j].getText()).equals( "." ) ){			
										buttonsCell[i][j].setText( "o" );
										hexCells[j][i].setUser( "o" );
										currentRow = j;
										currentColumn = i;
										player = "x";
										addMoves(j, i);
									}
								}
							}	
						}
						if( end() ){//game is over
							for( int m=0; m<boardSize; m++ ){
								for( int n=0; n<boardSize; n++ ){
									buttonsCell[n][m].setText( hexCells[m][n].getUser() );
								}
							}
							if( player.equals( "x" ) ){
								JOptionPane.showMessageDialog( null, "O is the winner.\n"+"Score X: "+score("x",false)+"\nScore O: "+score("o",true), 
																"Scores", JOptionPane.PLAIN_MESSAGE );
							} else if( player.equals( "o" ) ){
								JOptionPane.showMessageDialog( null, "X is the winner.\n"+"Score X: "+score("x",true)+"\nScore O: "+score("o",false), 
																"Scores", JOptionPane.PLAIN_MESSAGE );
							}
							dispose();
						}
						helperComp();//plays comp
					}
					if( end() ){//game is over
						for( int m=0; m<boardSize; m++ ){
							for( int n=0; n<boardSize; n++ ){
								buttonsCell[n][m].setText( hexCells[m][n].getUser() );
							}
						}
						if( player.equals( "x" ) ){
							JOptionPane.showMessageDialog( null, "O is the winner.\n"+"Score X: "+score("x",false)+"\nScore O: "+score("o",true), 
															"Scores", JOptionPane.PLAIN_MESSAGE );
						} else if( player.equals( "o" ) ){
							JOptionPane.showMessageDialog( null, "X is the winner.\n"+"Score X: "+score("x",true)+"\nScore O: "+score("o",false), 
															"Scores", JOptionPane.PLAIN_MESSAGE );
						}
						dispose();
					}
				}
				//checking features
				if( event.getSource() == buttonsFeatures[0] ){
					//load
					saveCheck = false;
					//create new frame for input
					fnFrame = new FilenameFrame();
					fnFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
					fnFrame.setSize( 500, 100 ); // set frame size
					fnFrame.setVisible( true ); // display frame
					dispose();
				} else if( event.getSource() == buttonsFeatures[1] ){
					//save
					//create new frame for input
					saveCheck = true;
					fnFrame = new FilenameFrame();
					fnFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
					fnFrame.setSize( 500, 100 ); // set frame size
					fnFrame.setVisible( true ); // display frame
				} else if( event.getSource() == buttonsFeatures[2] ){
					//undo
					if( numOfMoves>0 ){
						undoCheck = true;
						int deleteRow1 = moves[numOfMoves-1][0],
							deleteColumn1 = moves[numOfMoves-1][1];
						undo();
						buttonsCell[deleteColumn1][deleteRow1].setText( "." );
						if( gameMode == 2 ){
							compMove--;
							helperComp();
						}
						undoCheck = false;
					}
				} else if( event.getSource() == buttonsFeatures[3] ){
					//reset
					createInitialBoard();
					for(int row = 0; row < boardSize; row++){
						for(int column = 0; column < boardSize; column++){
							buttonsCell[ row ][ column ].setText( "." );
						}
					}
					player = "x";
					if( gameMode == 2 )		helperComp();
				} else if( event.getSource() == buttonsFeatures[4] ){
					//score
					JOptionPane.showMessageDialog( null, "Score X: "+score("x",false)+"\nScore O: "+score("o",false), 
													"Scores", JOptionPane.PLAIN_MESSAGE );

				}
			}

		}//end playhandler class
		private class FilenameFrame extends JFrame{ //get boardSize and game mode. after, call the mainGameFrame
			public JTextField textField1; // text field with set size
			public JTextField textField2; // text field constructed with text
			
			public FilenameFrame(){
				super( "Enter filename" );
				
				setLayout( new GridLayout( 2 , 2, 5, 5 ) ); // set frame layout
				textField1 = new JTextField( "Enter filename: ");
				textField1.setEditable( false ); // disable editing
				add( textField1 ); // add textField1 to JFrame
				textField2 = new JTextField();
				add( textField2 );
				// register event handlers
				FilenameHandler handlerTextField = new FilenameHandler();
				textField2.addActionListener( handlerTextField );
			}

			private class FilenameHandler implements ActionListener{
				@Override
				public void actionPerformed(ActionEvent event){  
					if( event.getSource() == textField2 ){
						try{				
							String s = event.getActionCommand();				
							if( saveCheck )		save(s);
							else {
								if( !load(s) ){
			  						JOptionPane.showMessageDialog(null, "File cannot open.", "ERROR", JOptionPane.ERROR_MESSAGE);				
								}
								newMainFrame();
							}
							dispose();
						} catch( IllegalArgumentException ex ){
			  				JOptionPane.showMessageDialog(null, "Filename is not valid.", "ERROR", JOptionPane.ERROR_MESSAGE);				
						}
					}
				}
			}
		}
	
		private void helperComp(){//plays user
			if( player.equals( "x" ) ){
				Cell tempCell = new Cell();
				tempCell = play();
				addMoves(tempCell.getRow(), tempCell.getColumn());
				compMove++;
				buttonsCell[tempCell.getColumn()][tempCell.getRow()].setText( "x" );
				player = "o";
			}
		}
	}//end mainGameFrame class
	@Override
	public int score(String pState, boolean gOver){// calculate scores
		int scoreCount = 0;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				if( (hexCells[i][j].getUser()).equals( pState ) ){
					scoreCount++;
				}
			}
		}
		if( gOver ){//count also uppercase letters
			for(int i=0; i<boardSize; i++){
				for(int j=0; j<boardSize; j++){
					if( (hexCells[i][j].getUser()).equals( pState.toUpperCase() ) ){
						scoreCount++;
					}
				}
			}
			return scoreCount*10+boardSize*boardSize*10;
		}	
		else 	return scoreCount*10;
	}
	@Override
	public void newMainFrame(){
		//when the user clicks the load button
		//current frame is closed and create a new frame
		//and display the new frame
		//even there is no valid filename, the game is no over
		//it resumes
		MainGameFrame mainGameFrame = new MainGameFrame();
		mainGameFrame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		mainGameFrame.setSize( boardSize*100, boardSize*100 ); // set frame size
		mainGameFrame.setVisible( true ); // display frame
	}
	@Override
	public void save(String filename){
		try {
		    FileWriter myWriter = new FileWriter(filename);
		    myWriter.write(new Integer(boardSize).toString()+"\n");
		    myWriter.write(new Integer(gameMode).toString()+"\n");
		    myWriter.write(player+"\n");
			for(int i=0; i<boardSize; i++){
				for(int j=0; j<boardSize; j++){
		 			myWriter.write(hexCells[i][j].getUser());
				}
		 		myWriter.write("\n");
			}
		    myWriter.write(new Integer(numOfMoves).toString()+"\n");
			for(int i=0; i<numOfMoves; i++){
			    myWriter.write(new Integer(moves[i][0]).toString()+"\n");
			    myWriter.write(new Integer(moves[i][1]).toString());
				if(i != numOfMoves-1)	myWriter.write("\n");
			}		    
			myWriter.close();
	    } catch (IOException e) {
	    	e.printStackTrace();
   		}
   	}
   	@Override
	public boolean load(String filename){
		try{  
		//the file to be opened for reading  
			FileInputStream myWriter = new FileInputStream(filename);       
			Scanner scanner = new Scanner(myWriter);    //file to be scanned  
		//returns true if there is another line to read  
			//while(scanner.hasNextLine()){
			boardSize = Integer.parseInt( scanner.nextLine() );
			createInitialBoard();
			createBooleanArray();
			createMoves();
			gameMode = Integer.parseInt( scanner.nextLine() );
			player = scanner.nextLine();
			for( int i=0; i<boardSize; i++ ){
				String temp;
				temp = scanner.nextLine();
				//to split the line
				String[] arr = temp.split("");
				for( int j=0; j<boardSize; j++ ){
					hexCells[i][j].setUser( arr[j+1] );
				}
			}
			numOfMoves = Integer.parseInt( scanner.nextLine() );
			moves = new int[ numOfMoves ][2];
			for(int i=0; i<numOfMoves; i++){
				moves[i][0] = Integer.parseInt( scanner.nextLine() );
				moves[i][1] = Integer.parseInt( scanner.nextLine() );
			}
			scanner.close();     //closes the scanner  
		} catch(IOException e){
			//e.printStackTrace(); 
			return false;
		} 
		return true;
   	}
   	@Override
	public void undo(){
		int deleteRow1 = moves[numOfMoves-1][0],
			deleteColumn1 = moves[numOfMoves-1][1];
		if( gameMode == 2 ){
			hexCells[deleteRow1][deleteColumn1].setUser("."); //o yeri . yaptım
		} else{
			hexCells[deleteRow1][deleteColumn1].setUser("."); //o yeri . yaptım
		}

		numOfMoves--;
		if( player.equals( "x" ) ){
			player = "o";
		} else if( player.equals( "o" ) ){
			player = "x";
		}	
	}

	public void play(Cell cellPosition){//plays user
		hexCells[ cellPosition.getRow() ][ cellPosition.getColumn() ].setUser( cellPosition.getUser() );
	}

	public Cell play(){//plays comp
		Cell changed = new Cell(); //değişiklik yaptığım şeyi tuttuğum Cell
		if( compMove == 1 ){ // Computer's first move
			// Select a place randomly
			int randomRow ,
				randomColumn;
			do{
				Random randomR = new Random();
				Random randomC = new Random();
				randomRow = randomR.nextInt(boardSize);
				randomColumn = randomC.nextInt(boardSize);
			} while( !isValid(randomRow) || !isValid(randomColumn) );
			hexCells[randomRow][randomColumn].setUser("x"); //tabloda değişiklik yapıyorum
			changed.setRowColumn(randomRow, randomColumn);
			changed.setUser("x");
		} else{
			// To block user's movements
			int[][] possibleMoves = new int[6][2];
			createPossibleMoves(possibleMoves);
			int random=0,
				flag=0;
			do{
				if( possibleMoves[random][0] == -1 ){
					random++;
				}
				if( undoCheck && lastRandom == random )		random++;
			} while( (random<6 && possibleMoves[random][0] == -1) );
			
			for(int i=0; i<6; i++){
				if(possibleMoves[i][0] == -1)	flag++;
			}
			if(flag == 6){ // There is no possible moves so need random numbers
				int randomRow ,
					randomColumn;
				do{
					Random randomR = new Random();
					Random randomC = new Random();
					randomRow = randomR.nextInt(boardSize);
					randomColumn = randomC.nextInt(boardSize);
				} while( !isValid(randomRow) || !isValid(randomColumn) || !(hexCells[randomRow][randomColumn].getUser()).equals(".") );
				hexCells[randomRow][randomColumn].setUser("x");
				changed.setRowColumn(randomRow, randomColumn);
				changed.setUser("x");
			} else{
				hexCells[possibleMoves[random][0]][possibleMoves[random][1]].setUser("x");
				changed.setRowColumn(possibleMoves[random][0], possibleMoves[random][1]);
				changed.setUser("x");
				lastRandom = random;
			}
		}
		return changed;
	}
	@Override
	public void createPossibleMoves(int[][] possibleMoves){
		int userRow = currentRow,
			userColumn = currentColumn;
		for(int i=0; i<6; i++){
			for(int j=0; j<2; j++){
				possibleMoves[i][j] = -1;
			}
		}
		if( isValid(userRow-1) && 
			(hexCells[userRow-1][userColumn].getUser()).equals( "." ) ){ //To left-up
			possibleMoves[0][0] = userRow-1;
			possibleMoves[0][1] = userColumn;
		}
		if( isValid(userRow-1) && isValid(userColumn+1) && 
			(hexCells[userRow-1][userColumn+1].getUser()).equals( "." ) ){ //To right-up
			possibleMoves[1][1] = userColumn+1;
		}
		if( isValid(userRow+1) && 
			(hexCells[userRow+1][userColumn].getUser()).equals( "." ) ){ //To right-down
			possibleMoves[2][0] = userRow+1;
			possibleMoves[2][1] = userColumn;
		}
		if( isValid(userRow+1) && isValid(userColumn-1) && 
			(hexCells[userRow+1][userColumn-1].getUser()).equals( "." ) ){ //To left-down
			possibleMoves[3][0] = userRow+1;
			possibleMoves[3][1] = userColumn-1;
		}
		if( isValid(userColumn-1) && 
			(hexCells[userRow][userColumn-1].getUser()).equals( "." ) ){ //To left
			possibleMoves[4][0] = userRow;
			possibleMoves[4][1] = userColumn-1;
		}
		if( isValid(userColumn+1) && 
			(hexCells[userRow][userColumn+1].getUser()).equals( "." ) ){ //To right
			possibleMoves[5][0] = userRow;
			possibleMoves[5][1] = userColumn+1;
		}
	}
	@Override
	public void addMoves(int row, int column){
		if( numOfMoves == 0 ){

			moves[0][0] = row;
			moves[0][1] = column;		
			
		} else{
			int[][] temp = new int[numOfMoves+1][2];
			for(int i=0; i<numOfMoves; i++){
				for(int j=0; j<2; j++){
					temp[i][j] = moves[i][j];
				}
			}
			temp[numOfMoves][0] = row;
			temp[numOfMoves][1] = column;
			moves = temp;
		}
		numOfMoves++;
	}
	//Inner Cell class
	public class Cell{
		private int row;//1, 2, 3, ...
		private int column;//A, B, C, ... as integer
		private int size;
		private String user;
		public Cell(){ //The cell is filled with dot
			user = ".";
		}
		public void setUser(String c){//Set the string as user
			user = c;
		}
		public void setRowColumn(int row, int column){//Set row and column
			this.row = row;
			this.column = column;
		}
		public String getUser(){//Get user value
			return user;
		}
		public int getRow(){//Get row value
			return row;
		}
		public int getColumn(){//Get column value
			return column;
		}
		public void setSizeCell(int nSize){
			size = nSize;
		}
		public int getSizeCell(){
			return size;
		}

	}//End Cell class
	@Override
	public void createInitialBoard(){
		hexCells = new Cell[boardSize][boardSize];
		String c = ".";
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				hexCells[i][j] = new Cell();
				hexCells[i][j].setSizeCell(boardSize);
				hexCells[i][j].setUser(c);
				hexCells[i][j].setRowColumn(i, j); 
			}
		}
	}
	@Override
	public void createBooleanArray(){
		checkArray = new int[boardSize][boardSize];
		for(int i=0; i<boardSize; i++){
		//	checkArray[i] = new int[boardSize];
			for(int j=0; j<boardSize; j++){
				checkArray[i][j] = 0;
			}
		}
	}
	@Override
	public void createMoves(){
		moves = new int[1][2]; //first element
	}
	@Override
	public boolean end(){
		return isBoardFull() == true || win_o() == true || win_x() == true;
	}
	@Override
	public boolean isBoardFull(){
		int flag = 0;
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				if( (hexCells[i][j].getUser()).equals("x") || (hexCells[i][j].getUser()).equals("o") ){
					flag++;
				}
			}
		}
		if(flag == boardSize*boardSize){
			return true;
		} else {
			return false;
		}
	}
	@Override
	public boolean win_o(){
		int[] counter = new int[4];
		counter[0] = boardSize;
		counter[3] = -1;
		//counter[1]; row
		//counter[2]; column
		for(int i=0; i<boardSize; i++){
			if( (hexCells[0][i].getUser()).equals("o") ){ // There is 'o'
				checkArray[0][i] = 1;
				
				hexCells[0][i].setUser((hexCells[0][i].getUser()).toUpperCase());
				if( isValid(i-1) ){ // To down
					counter[1] = 1;
					counter[2] = i-1;
					winRecursion_o(counter);
				}
				if( isValid(i) ){ // To left-down
					counter[1] = 1;
					counter[2] = i;
					winRecursion_o(counter);
				}
				if( counter[0] == counter[3] ){ // Winner is 'o'
					return true;
				} else{
					convertLowerCase(); // Back to lower case because 'o' is not winner
				}
			}
		}
		return false;	
	}
	@Override
	public void winRecursion_o(int[] counter){
		int row = counter[1],
			column = counter[2];
		if( (hexCells[row][column].getUser()).equals("o") ){
			checkArray[row][column] = 1;
			hexCells[row][column].setUser((hexCells[row][column].getUser()).toUpperCase());

			if( isValid(column+1) && checkArray[row][column+1] != 1 ){ //To right
				counter[2]++;
				winRecursion_o(counter);
				counter[2]--;
			}
			if( isValid(column-1) && checkArray[row][column-1] != 1 ){ // To left
				counter[2]--;
				winRecursion_o(counter);
				counter[2]++;
			}
			if( isValid(column-1) && isValid(row+1) ){  //To left-down
				counter[1]++;
				counter[2]--;
				winRecursion_o(counter);
				counter[1]--;
				counter[2]++;
			}
			if( isValid(row+1) ){ //To right-down
				counter[1]++;
				winRecursion_o(counter);
				counter[1]--;
			}
			if( counter[0]-1 == counter[1] ){ 
				counter[3] = counter[0];
			} else if( counter[3] != counter[0] && checkArray[row][column+1] != 1 ){
				checkArray[row][column] = 0;
				hexCells[row][column].setUser((hexCells[row][column].getUser()).toLowerCase());
			}
		}
	}
	// win_x and winRecursion_x work like win_o and winRecursion_o
	@Override
	public boolean win_x(){
		int[] counter = new int[4];
		counter[0] = boardSize;
		counter[3] = -1;
		for(int i=0; i<boardSize; i++){
			if( (hexCells[i][0].getUser()).equals("x") ){ 
				checkArray[i][0] = 1;
				hexCells[i][0].setUser((hexCells[i][0].getUser()).toUpperCase());
				if( isValid(i-1) ){ 
					counter[1] = i-1;
					counter[2] = 1;
					winRecursion_x(counter);
				}
				if( isValid(i) ){ 
					counter[1] = i;
					counter[2] = 1;
					winRecursion_x(counter);
				}
				if( counter[0] == counter[3] ){//x winner
					return true;

				} else{
					convertLowerCase();
				}
			}
		}
		return false;	
	}
	@Override
	public void winRecursion_x(int[] counter){
		int row = counter[1],
			column = counter[2];
		if( (hexCells[row][column].getUser()).equals("x")  ){
			checkArray[row][column] = 1;
			hexCells[row][column].setUser((hexCells[row][column].getUser()).toUpperCase());
			if( isValid(column+1) && isValid(row-1) ){ 
				counter[2]++;
				counter[1]--;
				winRecursion_x(counter);
				counter[2]--;
				counter[1]++;
			}
			if( isValid(row-1)){
				if( checkArray[row-1][column] != 1 ){
					counter[1]--;
					winRecursion_x(counter);
					counter[1]++;					
				}
			}
			if( isValid(row+1)  ){
				if( checkArray[row+1][column] != 1 ){
					counter[1]++;
					winRecursion_x(counter);
					counter[1]--;					
					}
			}
			if( isValid(column+1) ){
				counter[2]++;
				winRecursion_x(counter);
				counter[2]--;
			}
			if( counter[0]-1 == counter[2] ){
				counter[3] = counter[0];
			} else if( counter[3] != counter[0] && checkArray[row][column+1] != 1){
				checkArray[row][column] = 0;
				hexCells[row][column].setUser((hexCells[row][column].getUser()).toLowerCase());
			}
		}
	}
// To convert to lower case elements of board
	@Override
	public void convertLowerCase(){
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				if( (hexCells[i][j].getUser()).equals("X")|| (hexCells[i][j].getUser()).equals("O") ){
					hexCells[i][j].setUser((hexCells[i][j].getUser()).toLowerCase());
				}
			}
		}
	}
	@Override
	public boolean isValid(int index){
		if( index<0 || index>=boardSize ){
			return false;
		}
		return true;
	}
}