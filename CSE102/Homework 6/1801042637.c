#include <stdio.h>/*Standart input output library*/
#include <string.h>/*stpcmp(),strlen() functions*/
#include <stdlib.h>/*srand() and rand() functions*/
#include <time.h>/*time(NULL) function*/

#define NUMWORDS 10/*number of words*/
#define SIZEWORDS 20/*length of words*/
#define NUMNUMBERS 10/*number of numbers*/
#define NUMROWS 20/*number of rows*/
#define NUMCOLS 20/*number of columns*/
/*Functions are defined to be called in the main and other functions*/
void read_from_text(char* file_path);/*To choose 10 random words from the file*/
void find_direction(char keep_words[NUMWORDS][SIZEWORDS]);/*To find the random coordinates for the words*/
void print_words(char keep_words[NUMWORDS][SIZEWORDS]);/*To print "Hidden Words"*/
int position_column();/*To find random column for the word*/
int position_row();/*To find random row for the word*/
void place_words(char keep_words[NUMWORDS][SIZEWORDS], char rows[NUMNUMBERS], int columns[NUMNUMBERS]);/*To place the words in the puzzle table with random directions and positions*/
int is_there(char game[NUMROWS][NUMCOLS], char keep_words[NUMWORDS][SIZEWORDS], int direction, int row, int column, int i);/*To check if there is another word in the selected coordinates*/
void print_game_screen(char game[NUMROWS][NUMCOLS]);/*To print the game table*/
void users_choice(char game[NUMROWS][NUMCOLS],char keep_words[NUMWORDS][SIZEWORDS]);/*To read the user's inputs*/
int check_true_or_not(char game[NUMROWS][NUMCOLS], char row, int column, char word[20],char keep_words[NUMWORDS][SIZEWORDS]);/*To check the accuracy of the user's answer*/
void full_dot(char game[NUMROWS][NUMCOLS]);/*A helper function that fills the game table with dots to control the words inside the game table*/
int	 length_word(char keep_words[NUMWORDS][SIZEWORDS], int index);/*A helper function that finds the length of the (index)th value in the array*/
void uppercase(char keep_words[NUMWORDS][SIZEWORDS], char word[20],char upper_word[20]);/*To upper the letters of correct answers in the game table*/
char full_letter(char game[NUMROWS][NUMCOLS]);/*A helper function to fill random letters to the empty coordinates*/

void main(){
	srand(time(NULL));
	read_from_text("words.txt");
}

void read_from_text(char* file_path){/*To choose 10 random words from the file*/
	int count,/*To store random numbers temporarily*/
		numbers[NUMNUMBERS];/*The array of random numbers*/
	char keep_words[NUMWORDS][SIZEWORDS];/*The array of random words*/

	FILE *fp = fopen(file_path,"r");

	for(int i=0; i<10; i++){/*To find random numbers and store them in the array*/
		count=1+rand()%100;
		numbers[i]=count;
	}

	for(int i=0; i<10; i++){/*To check if the numbers in the array are the same*/
		for(int k=i+1; k<10; k++){		
			while(numbers[k]==numbers[i]){/*If same values exist, find new random numbers and check if the numbers in the array are the same*/
				count=1+rand()%100;
				numbers[k]=count;
				i=0;
			}
		}	
	}	
	
	for(int i=0; i<10; i++){/*To read string from the file until reachs random number*/
		for(int j=0; j<numbers[i]; j++){
			fgets(keep_words[i], 80, fp);
		}
		rewind(fp);/*To return the beginning of the file*/
	}	
	print_words(keep_words);
	find_direction(keep_words);
	fclose(fp);
}

void print_words(char keep_words[NUMWORDS][SIZEWORDS]){/*To print "Hidden Words"*/
	int length;
	printf("Hidden Words:\n");/*Hidden Words are elements of keep_words[][]*/
	for(int i=0;i<10;i++){
		length=length_word(keep_words,i);
		printf("-> ");
		for(int j=0;j<=length;j++){
			printf("%c",keep_words[i][j]);
		}
		printf("\n");
	}
}

void find_direction(char keep_words[NUMWORDS][SIZEWORDS]){/*To find the random coordinates for the words*/
	char game[NUMROWS][NUMCOLS];/*The array of the game table*/
	int row,
		column,
		direction,
		length;

	full_dot(game);

	for(int count=0; count<NUMWORDS; count++){
		row = position_row();
		column = position_column();
		length = length_word(keep_words,count);	
		direction = 1+rand()%8;

		switch (direction){
			case 1: /*From the point to right*/
				while( length > 20-column ){/*To check whether the word fits*/
					column = position_column();	/**/
				}		
				if( (is_there(game,keep_words,direction,row,column,count)) == 0){/*Coordinates are not appropriate, return to the beginning of the loop*/
					count=-1;
					full_dot(game);/*To clear letters*/			
				}
				break;

			case 2: /*From the point to left*/
				while( column+1 < length){/*To check whether the word fits*/
					column = position_column();
					
				}
				if( (is_there(game,keep_words,direction,row,column,count)) == 0){/*Coordinates are not appropriate, return to the beginning of the loop*/
					count=-1;
					full_dot(game);/*To clear letters*/	
				}
				break;

			case 3: /*From the point to up*/
				while( length > row+1){/*To check whether the word fits*/
					row = position_row();
				}
				if( (is_there(game,keep_words,direction,row,column,count)) == 0){/*Coordinates are not appropriate, return to the beginning of the loop*/
					count=-1;
					full_dot(game);/*To clear letters*/	
				}
				break;

			case 4: /*From the point to down*/
				while( length > 20-row){/*To check whether the word fits*/
					row = position_row();
				}
				if( (is_there(game,keep_words,direction,row,column,count)) == 0){/*Coordinates are not appropriate, return to the beginning of the loop*/
					count=-1;
					full_dot(game);/*To clear letters*/	
				}
				break;	
			
			case 5: /*From the point to top-right*/
				while((length > 20-column) || (length > row+1)){/*To check whether the word fits*/
					if( (length > 20-column) ){
						column = position_column();	
					}
					else if( (length > row+1) ){
						row = position_row();
					}
				}
				if( (is_there(game,keep_words,direction,row,column,count)) == 0){/*Coordinates are not appropriate, return to the beginning of the loop*/
					count=-1;
					full_dot(game);/*To clear letters*/	
				}
				break;

			case 6: /*From the point to top-left*/
				while( ( length > column+1) || ( length > row+1 ) ){/*To check whether the word fits*/
					if(( length > column+1)){
						column = position_column();	
					}
					else if(( length > row+1 )){
						row = position_row();
					}
				}
				if( (is_there(game,keep_words,direction,row,column,count)) == 0){/*Coordinates are not appropriate, return to the beginning of the loop*/
					count=-1;
					full_dot(game);/*To clear letters*/	
				}
				break;

			case 7: /*From the point to down-right*/
				while( (length > 20-column) || ( length > 20-row ) ){/*To check whether the word fits*/
					if(( length > 20-row )){
						row = position_row();
					}
					else if((length > 20-column)){
						column = position_column();
					}
				}	
				if( (is_there(game,keep_words,direction,row,column,count)) == 0){
					count=-1;
					full_dot(game);/*To clear letters*/	
				}
				break;

			case 8: /*From the point to down-left*/
				while( ( length > column+1	 ) || ( length > 20-row ) ){/*To check whether the word fits*/
					if(( length > column+1	 )){
						column = position_column();	
					}
					else if(( length > 20-row )){
						row = position_row();
					}
				}	
				if( (is_there(game,keep_words,direction,row,column,count)) == 0){
					count=-1;
					full_dot(game);	/*To clear letters*/
				}
				break;	
		}
	}
	print_game_screen(game);
	users_choice(game,keep_words);
}

int position_row(){/*To find random row for the word*/
	int row;
	row = rand()%20;
	return row;
}

int position_column(){/*To find random column for the word*/
	int column;
	column = rand()%20;
	return column;
}

void full_dot(char game[NUMROWS][NUMCOLS]){/*A helper function that fills the game table with dots to control the words inside the game table*/
	for(int i=0; i<NUMROWS; i++){
		for(int j=0; j<NUMCOLS; j++){
			game[i][j]='.';
		}
	}
}

int is_there(char game[NUMROWS][NUMCOLS], char keep_words[NUMWORDS][SIZEWORDS], int direction, int row, int column, int i){/*To check if there is another word in the selected coordinates*/
	int length,
		flag=1, 
		count=0,
		j;/*for loops*/

	length=length_word(keep_words,i);

	switch (direction){
		case 1: /*From the point to right*/		
			for( j=0; j<length; j++){
				if (game[row][column+j]>= 'a' && game[row][column+j]<='z' ){/*There is a letter*/
					count--;
				}
				else{
					count++;
				}
			}
			if(length==count){/*Coordinates are okey, store the word*/
				for(j=0; j<length; j++){
					game[row][column+j] = keep_words[i][j];

				}
			}
			else{
				flag=0;
			}
			break;

		case 2:  /*From the point to left*/
			for( j=0; j<length; j++){
				if( game[row][column-j]>='a' && game[row][column-j]<='z' ){/*There is a letter*/
					count--;
				}
				else{
					count++;
				}
			}
			if(length==count){/*Coordinates are okey, store the word*/
				for(j=0; j<length; j++){
					game[row][column-j] = keep_words[i][j];
				}
			}
			else{
				flag=0;
			}
			break;		

		case 3: /*From the point to up*/		
			for( j=0; j<length; j++){
				if( game[row-j][column]>='a' && game[row-j][column]<='z' ){/*There is a letter*/
					count--;
				}
				else{
					count++;
				}
			}
			if(length==count){/*Coordinates are okey, store the word*/
				for(j=0; j<length; j++){
					game[row-j][column] = keep_words[i][j];

				}
			}
			else{
				flag=0;
			}
			break;

		case 4: /*From the point to down*/		
			for( j=0; j<length; j++){
				if( game[row+j][column]>='a' && game[row+j][column]<='z' ){/*There is a letter*/
					count--;
				}	
				else{
					count++;
				}
			}
			if(length==count){/*Coordinates are okey, store the word*/
				for(j=0; j<length; j++){
					game[row+j][column] = keep_words[i][j];

				}
			}
			else{
				flag=0;
			}
			break;	
			
		case 5: /*From the point to top-right*/
			for( j=0; j<length; j++){
				if(game[row-j][column+j]>='a' && game[row-j][column+j]<='z' ){/*There is a letter*/
					count--;
				}
				else{
					count++;
				}
			}	
			if(length==count){/*Coordinates are okey, store the word*/
				for(j=0; j<length; j++){
					game[row-j][column+j] = keep_words[i][j];

				}
			}
			else{
				flag=0;
			}
			break;

		case 6: /*From the point to top-left*/	
			for(int j=0; j<length; j++){
				if(game[row-j][column-j]>='a' && game[row-j][column-j]<='z'){/*There is a letter*/
					count--;
				}
				else{
					count++;
				}
			}	
			if(length==count){/*Coordinates are okey, store the word*/
				for(j=0; j<length; j++){
					game[row-j][column-j] = keep_words[i][j];

				}
			}
			else{
				flag=0;
			}
			break;

		case 7: /*From the point to down-right*/
			for(int j=0; j<length; j++){
				if(game[row+j][column+j]>='a' && game[row+j][column+j]<= 'z'){/*There is a letter*/
					count--;
				}
				else{
					count++;
				}
			}	
			if(length==count){/*Coordinates are okey, store the word*/
				for(j=0; j<length; j++){
					game[row+j][column+j] = keep_words[i][j];

				}
			}
			else{
				flag=0;
			}
			break;

		case 8:/*From the point to down-left*/
			for(int j=0; j<length; j++){
				if(game[row+j][column-j]>='a' && game[row+j][column-j]<='z'){/*There is a letter*/
					count--;
				}
				else{
					count++;
				}
			}
			if(length==count){/*Coordinates are okey, store the word*/
				for(j=0; j<length; j++){
					game[row+j][column-j] = keep_words[i][j];

				}
			}
			else{
				flag=0;
			}
			break;	
	}
	return flag;/*If flag is 0, coordinates are not true
				  If flag is 1, coordinates are true*/
}

int length_word(char keep_words[NUMWORDS][SIZEWORDS],int index){/*A helper function that finds the length of the (index)th value in the array*/
	int length;
	if(keep_words[index][0]=='b'&&keep_words[index][1]=='a'&&keep_words[index][2]=='i'&&keep_words[index][3]=='t'){/*When the 'bait' word is in strlen(), it gives 4*/
		length = strlen(keep_words[index]);
	}
	else{/*When other words are in strlen(), they give (length of word + 2)*/
		length = strlen(keep_words[index])-2;
	}
	return length;
}

void print_game_screen(char game[NUMROWS][NUMCOLS]){/*To print the game table*/
	char letter = 'A';
	printf("\n");

	for(int i=0;i<10;i++){
		printf("   %d", i);
	}
	for(int i=10;i<20;i++){
		printf("  %d", i);
	}

	printf("\n\n");

	for(int i=0; i<20; i++){
		printf("%c- ",letter );
		letter++;
		for(int j=0; j<20; ++j){
			if(game[i][j]=='.'){
				printf("%c   ", full_letter(game));
			}
			else{
				printf("%c   ",game[i][j]);
			}			
		}
		printf("\n\n");
	}
}

void users_choice(char game[NUMROWS][NUMCOLS],char keep_words[NUMWORDS][SIZEWORDS]){/*To read the user's inputs*/
	char word[20],
		 upper_word[20],
		 word_s[50],
		 row;
	int column;
	int flag=1,/*To enter the do-while loop*/
		count=0;
	do{
		printf("Please enter the coordinate and the word (Write 'Exit' to finish the game):\n");
		scanf(" %49[^\n]",word_s);
		sscanf(word_s, " %c%d %s", &row, &column, word);
		row += 32;
		if(strcmp(word_s,"Exit")==0){
			flag=0;	
		}
		else{
			if(check_true_or_not(game,row,column,word,keep_words)==1){
				uppercase(keep_words,word,upper_word);
				count++;
				if(count==10){
					printf("Well Done!\n");
					flag=0;
				}
			}
			else if (check_true_or_not(game,row,column,word,keep_words)==0){
				printf("It was wrong, try again.\n");
			}
		}
	}while(flag!=0);
}

int check_true_or_not(char game[NUMROWS][NUMCOLS], char row, int column, char word[20],char keep_words[NUMWORDS][SIZEWORDS]){/*To check the accuracy of the user's answer*/
	int length,
		direction,
		flag=0,
		turning;
	for(int i=0;i<10;i++){
		length = length_word(keep_words,i);
		for(direction=1;direction<=8;direction++){
			flag=0;
			switch(direction){
				case 1:/*From the point to right*/
					for(int j=0; j<=length; j++){
						if(game[row-97][column+j]==word[j] && length == strlen(word)){
							flag++;
						}
					}
					break;

				case 2: /*From the point to left*/
					for(int j=0; j<=length; j++){
						if(game[row-97][column-j]==word[j] && length == strlen(word)){
							flag++;
						}
					}
					break;

				case 3:/*From the point to up*/
					for(int j=0; j<=length; j++){
						if(game[row-97-j][column]==word[j] && length == strlen(word)){
							flag++;
						}
					}
					break;
				case 4:/*From the point to down*/
					for(int j=0; j<=length; j++){
						if(game[row-97+j][column]==word[j] && length == strlen(word)){
							flag++;
						}
					}
					break;

				case 5:/*From the point to top-right*/
					for(int j=0; j<=length; j++){
						if(game[row-97-j][column+j]==word[j] && length == strlen(word)){
							flag++;
						}
					}
					break;
				case 6:/*From the point to top-left*/
					for(int j=0; j<=length; j++){
						if(game[row-97-j][column-j]==word[j] && length == strlen(word)){
							flag++;
						}
					}
					break;

				case 7: /*From the point to down-right*/
					for(int j=0; j<=length; j++){
						if(game[row-97+j][column+j]==word[j] && length == strlen(word)){
							flag++;
						}
					}
					break;

				case 8:/*From the point to down-left*/
					for(int j=0; j<=length; j++){
						if(game[row-97+j][column-j]==word[j] && length == strlen(word)){
							flag++;
						}
					}
					break;
			}	
			if(flag==length){/*The answer is correct*/
				switch(direction){
					case 1:/*From the point to right*/
						for(int j=0;j<length;j++){
							game[row-97][column+j] = (game[row-97][column+j])-32;/*ASCII to convert between letter and integer AND ASCII to convert between lowercase and uppercase*/
						}
						print_game_screen(game);
						break;

					case 2: /*From the point to left*/
						for(int j=0;j<length;j++){
							game[row-97][column-j] = (game[row-97][column-j])-32;
						}
						print_game_screen(game);
						break;

					case 3:/*From the point to up*/
						for(int j=0;j<length;j++){
							game[row-97-j][column] = (game[row-97-j][column])-32;
						}
						print_game_screen(game);
						break;

					case 4:/*From the point to down*/
						for(int j=0;j<length;j++){
							game[row-97+j][column]=(game[row-97+j][column])-32;
						}
						print_game_screen(game);
						break;

					case 5:/*From the point to top-right*/
						for(int j=0;j<length;j++){
							game[row-97-j][column+j]=(game[row-97-j][column+j])-32;
						}
						print_game_screen(game);
						break;

					case 6:/*From the point to top-left*/
						for(int j=0;j<length;j++){
							game[row-97-j][column-j]=(game[row-97-j][column-j])-32;
						}
						print_game_screen(game);
						break;

					case 7: /*From the point to down-right*/
						for(int j=0;j<length;j++){
							game[row-97+j][column+j]=(game[row-97+j][column+j])-32;
						}
						print_game_screen(game);
						break;

					case 8:/*From the point to down-left*/
						for(int j=0;j<length;j++){
							game[row-97+j][column-j]=(game[row-97+j][column-j])-32;
						}
						print_game_screen(game);
						break;
				}
				turning=1;
				i=11;
				direction=11;
			}
			else{
				turning=0;
			}
		}
	}
return turning;/*If answer is correct, the value of turning is 1
				 If answer is not correct, the value of turning is 0*/
}

void uppercase(char keep_words[NUMWORDS][SIZEWORDS],char word[20],char upper_word[20]){/*To upper the letters of correct answers in the game table*/
	int length,
		flag=11;
	printf("Hidden Words:\n");
	for(int i=0;i<10;i++){
		printf("-> ");
		length=length_word(keep_words,i);
		if(keep_words[i][0]==word[0] && keep_words[i][1]==word[1] && keep_words[i][2]==word[2] ){/*The words are same*/
			for(int j=0; j<length; j++){
				upper_word[j]=keep_words[i][j]-32;/*ASCII to convert between uppercase and lowercase*/
				keep_words[i][j]=keep_words[i][j]-32;
			}
			for(int j=0; j<length; j++){
				printf("%c",upper_word[j]);
			}
		}
		else{
			for(int j=0; j<length; j++){
				printf("%c",keep_words[i][j] );
			}
		}
	printf("\n");
	}
}

char full_letter(char game[NUMROWS][NUMCOLS]){/*A helper function to fill random letters to the empty coordinates*/
	int number;
	char letter='a';
	number = rand()%26;	
	for(int i=0;i<number;i++){
		letter++;
	}
	return letter;
}