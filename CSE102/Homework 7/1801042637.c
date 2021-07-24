#include <stdio.h> /*Standart input output library*/
#include <string.h> /*strcmp(),strlen(), strcpy() functions*/
#include <stdlib.h> /*strtod() function*/

#define NUMNAMES 2000 /*number of names*/
#define SIZENAMES 100 /*size of names*/

#define NUMGENRES 2000 /*number of genres*/
#define SIZEGENRES 20 /*size of genres*/

#define NUMPLATFORMS 2000 /*number of platforms*/
#define SIZEPLATFORMS 20 /*size of platforms*/

#define UNIQUEGENRES 20 /*number of unique genres*/
#define UNIQUEPLATFORMS 20 /*number of unique platforms*/

#define NUMALL 2000 /*row of the float array*/
#define SIZEALL 7 /*column of the float array*/

/*Functions are defined to be called in the main and other functions*/

void menu();/*To perform all selection operations*/
void read_from_file(char names[NUMNAMES][SIZENAMES], float all[NUMALL][SIZEALL], char unique_genres[UNIQUEGENRES][SIZEGENRES], char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]);/*To read datas from the file*/
void list_genres(char unique_genres[UNIQUEGENRES][SIZEGENRES]);/*To list unique genres*/
void list_platforms(char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]);/*To list unique platforms*/
void games_through_years(float all[NUMALL][SIZEALL], char names[NUMNAMES][SIZENAMES]);/*To list the games according to an information received from the user*/
void single_game(float all[NUMALL][SIZEALL], char names[NUMNAMES][SIZENAMES], char unique_genres[UNIQUEGENRES][SIZEGENRES], char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]);/*prints all information of that game.*/
void find_unique_genres(char genres[NUMGENRES][SIZEGENRES], char unique_genres[UNIQUEGENRES][SIZEGENRES]);/*To find unique genres*/
void find_unique_platforms(char platforms[NUMPLATFORMS][SIZEPLATFORMS], char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]);/*To find unique platforms*/
void average_score(float all[NUMALL][SIZEALL]);/*To calculate and print the average of the user scores of all games*/
void na_eu(char names[NUMNAMES][SIZENAMES], float all[NUMALL][SIZEALL]);/*To ask a game name and print either the game was more populer in NA or EU according to the sales*/
void frequence_genre(float all[NUMALL][SIZEALL], char unique_genres[UNIQUEGENRES][SIZEGENRES]);/*To print the frequences of every genre*/
void frequence_platform(float all[NUMALL][SIZEALL], char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]);/*To print the frequences of every platform*/

void main(){
	menu();
}

void menu(){
	int operation;/*Input - User's selection*/
	char names[NUMNAMES][SIZENAMES];/*The array of the names*/
	char unique_genres[UNIQUEGENRES][SIZEGENRES];/*The array of the unique genres*/
	char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS];/*The array of the unique platforms*/
	float all[NUMALL][SIZEALL];/*The array of all datas*/

	read_from_file(names, all, unique_genres, unique_platforms);
	
	do{
		printf("\n");
		printf("0: List of the Genres\n");
		printf("1: List of the Platforms\n");
		printf("2: Lİst of the Games Through of Years\n");
		printf("3: All Informations of a Single Game\n");
		printf("4: Average of the User Scores\n");
		printf("5: Georographical Information of a Single Game\n");
		printf("6: Frequence of the Genres\n");
		printf("7: Frequence of the Platforms\n");
		printf("8: Exit\n");
		printf("\nPlease select an operation: ");
		scanf("%d",&operation);
		switch(operation){
			case 0:
				list_genres(unique_genres);
				break;
			case 1:
				list_platforms(unique_platforms);
				break;
			case 2:
				games_through_years(all,names);
				break;
			case 3:
				single_game(all,names,unique_genres,unique_platforms);
				break;
			case 4:
				average_score(all);
				break;
			case 5:
				na_eu(names,all);
				break;
			case 6:
				frequence_genre(all,unique_genres);
				break;
			case 7:
				frequence_platform(all,unique_platforms);
				break;
			case 8:/*Exit*/
				break;
			default:
				printf("\nInvalid operation. Try again.\n");
				break;
		}
	}while(operation!=8);
}
void read_from_file(char names[NUMNAMES][SIZENAMES], float all[NUMALL][SIZEALL], char unique_genres[UNIQUEGENRES][SIZEGENRES],char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]){
	int inp,/*To check the end of file(EOF)*/
		row_names=0, column_names=0,/*To control elements of the names array*/
		row_genres=0, column_genres=0,/*To control elements of the genres array*/
		row_platforms=0, column_platforms=0,/*To control elements of the platforms array*/
		row_all=-1, column_all=0,/*To control elements of the all data array*/
		row_sales=0, column_sales=0,/*To control elements of the global sales array*/
		comma_counter=0;/*To check where comma is*/
	char c;/*The data that read from the file*/
	char genres[NUMGENRES][SIZEGENRES];/*The array of all genres*/
	char platforms[NUMPLATFORMS][SIZEPLATFORMS];/*The array of all platforms*/
	char sales[NUMALL][SIZEALL];/*The array of global sales*/
	char *flag;/*To set by strtod() function to the next character in string after the numerical value*/
	float year, na, eu, global, score;/*To store float datas*/

	FILE *fp;
	fp = fopen("Video_Games.txt","r");	
	inp = fscanf(fp, "%c", &c);

	do{/*To read the first line but not to write to the arrays*/
		inp = fscanf(fp, "%c", &c);
	}while(c != '\n');

	do{
		column_all=0;/*Beginning of the row*/

		if(c == '\n'){/*After the '\n', read and write datas to the array of names until there is the comma*/

			row_all++;
			column_names = 0;
			inp = fscanf(fp, "%c", &c);
			while(c != ','){
				names[row_names][column_names] = c ;
				inp = fscanf(fp, "%c", &c);
				column_names++;
			}
			names[row_names][column_names]='\0';
			row_names++;
			comma_counter++;/*There is a comma*/
		}

		if(c == ','){

			if(comma_counter == 1){/*After the first comma, read and write datas to the array of genres until there is the comma*/

				inp = fscanf(fp, "%c", &c);
				column_genres = 0;

				while(c != ','){
					genres[row_genres][column_genres] = c ;
					inp = fscanf(fp, "%c", &c);
					column_genres++;
				}
				genres[row_genres][column_genres]='\0';
				row_genres++;
				column_all++;
				comma_counter++;/*There is a comma*/
			}

			if(comma_counter == 2){/*After the second comma, read and write datas to the array of platforms until there is the comma*/
				
				inp = fscanf(fp, "%c", &c);
				column_platforms = 0;

				while(c != ','){
					platforms[row_platforms][column_platforms] = c;
					inp = fscanf(fp, "%c", &c);
					column_platforms++;
				}
				platforms[row_platforms][column_platforms]='\0';
				row_platforms++;
				column_all++;
				comma_counter++;/*There is a comma*/
			}

			if(comma_counter == 3){/*After the third comma, read and write float datas to the array of all datas until there is the comma*/

				inp = fscanf(fp, "%f", &year);
				all[row_all][column_all] = year;
				column_all++;
				comma_counter++;/*There is a comma*/
			}

			inp = fscanf(fp, "%c", &c);

			if(comma_counter == 4){/*After the forth comma, read and write float datas to the array of all datas until there is the comma*/

				inp = fscanf(fp, "%f", &na);
				all[row_all][column_all] = na;
				column_all++;
				comma_counter++;/*There is a comma*/
			}

			inp = fscanf(fp, "%c", &c);

			if(comma_counter == 5){/*After the fifth comma, read and write float datas to the array of all datas until there is the comma*/

				inp = fscanf(fp, "%f", &eu);
				all[row_all][column_all] = eu;
				column_all++;
				comma_counter++;/*There is a comma*/
			}

			inp = fscanf(fp, "%c", &c);

			if(comma_counter == 6){/*After the sixth comma, read and write datas to the array of all datas until there is the comma*/

				inp = fscanf(fp, "%c", &c);/*To read in char type*/
				column_sales = 0;

				while(c != ','){
					sales[row_sales][column_sales] = c;/*To write the char to the array of global sales*/
					inp = fscanf(fp, "%c", &c);
					column_sales++;
				}
				comma_counter++;/*There is a comma*/

				if( strcmp(sales[row_sales],"not_available") == 0 ){/*To parse a string to float*/
					all[row_all][column_all] = -5.0;/*There is no float data*/
				}
				else{
					all[row_all][column_all] = strtod(sales[row_sales],&flag);/*There is float data and store it in the array of all datas*/
				}
				column_all++;
				row_sales++;
			}

			if(comma_counter == 7){/*After the seventh comma, read and write float datas to the array of all datas until the end of line*/

				inp = fscanf(fp, "%f", &score);
				all[row_all][column_all] = score ;
				column_all++;
				comma_counter=0;/*End of line*/
			}

		}
		inp = fscanf(fp, "%c", &c);

	}while(inp != EOF);
	
	fclose(fp);
	
	find_unique_genres(genres,unique_genres);
	/*The genre cell point the index of the genre array which stores the names of the related genre*/
	for(int i=0; i<NUMGENRES; i++){
		for(int j=0; j<12; j++){
			if(strcmp(genres[i],unique_genres[j])==0){
				all[i][0] = j;
			}
		} 
	}

	find_unique_platforms(platforms,unique_platforms);
	/*The platform cell point the index of the genre/platform array which stores the names of the related platform.*/
	for(int i=0; i<NUMPLATFORMS; i++){
		for(int j=0; j<10; j++){
			if(strcmp(platforms[i],unique_platforms[j])==0){
				all[i][1] = j;
			}
		} 
	}
}

void find_unique_genres(char genres[NUMGENRES][SIZEGENRES], char unique_genres[UNIQUEGENRES][SIZEGENRES]){
	char temporary[NUMGENRES][SIZEGENRES];/*To temporarily hold the strings datas*/
	int count=0	;
	
	strcpy(temporary[0], genres[0]);

	for(int i=0; i<2000; i++){
		for(int j=i+1; j<=2000; j++){
			if( strcmp(temporary[i],genres[j]) != 0 ){
				strcpy( temporary[j], genres [j] );

			}
			else{/*There are same datas*/
				strcpy(temporary[j], "\0");
			}
		}
	}

	for(int i=0; i<2000; i++){
		for(int j=i+1; j<2000; j++){
			if( strcmp(temporary[i],temporary[j]) != 0 ){
				strcpy( temporary[j], temporary [j] );	
			}
			else{/*There are same datas*/				
				strcpy(temporary[j], "\0");
			}
		}
	}

	for (int i = 0; i < 2000; i++){/*To create the unique genres array*/
		if( strcmp(temporary[i],"\0") != 0 ){
			strcpy( unique_genres[count], temporary [i] );
			count++;
		}
	}
}

void find_unique_platforms(char platforms[NUMPLATFORMS][SIZEPLATFORMS], char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]){
	char temporary[NUMPLATFORMS][SIZEPLATFORMS];/*To temporarily hold the strings datas*/
	int count=0	;
	
	strcpy(temporary[0], platforms[0]);

	for(int i=0; i<2000; i++){
		for(int j=i+1; j<=2000; j++){
			if( strcmp(temporary[i],platforms[j]) != 0 ){
				strcpy( temporary[j], platforms [j] );
			}
			else{/*There are same datas*/
				strcpy(temporary[j], "\0");
			}
		}
	}

	for(int i=0; i<2000; i++){
		for(int j=i+1; j<2000; j++){
			if( strcmp(temporary[i],temporary[j]) != 0 ){
				strcpy( temporary[j], temporary [j] );	
			}
			else{/*There are same datas*/				
				strcpy(temporary[j], "\0");
			}
		}
	}

	for (int i = 0; i < 2000; i++){/*To create the unique genres array*/
		if( strcmp(temporary[i],"\0") != 0 ){
			strcpy( unique_platforms[count], temporary [i] );
			count++;
		}
	}
}

void list_genres(char unique_genres[UNIQUEGENRES][SIZEGENRES]){
	printf("\n");
	for(int i=0; i<12; i++){/*To print elements of the unique genres array*/
		printf("%s\n",unique_genres[i]);
	}	
}

void list_platforms(char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]){
	printf("\n");
	for(int i=0; i<10; i++){/*To print elements of the unique platform array*/
		printf("%s\n",unique_platforms[i] );
	}	
}

void games_through_years(float all[NUMALL][SIZEALL],char names[NUMNAMES][SIZENAMES]){
	int year, selection,/*Input - a year and a selection*/
		count=0, index=0;

	printf("Enter a year:\n");
	scanf("%d", &year);
	printf("Until (0) of Since (1) %d: ",year );
	scanf("%d",&selection);

	while( (year > all[NUMALL-1][2]) || 
		   (year < all[0][2]) || 
		   ((selection != 0) && (selection != 1)) || /*Invalid selection*/
		   ((year == all[NUMALL-1][2]) && (selection == 1)) || 
		   ((year == all[0][2]) && (selection == 0)) ){

		printf("\nTry again.\n");
		printf("\nEnter a year:\n");
		scanf("%d", &year);
		printf("Until (0) of Since (1) %d: ",year);
		scanf("%d",&selection);
	}
		
	switch(selection){
		case 0:/*The selection is 'until'*/
			for(int i=0; i<2000; i++){
				if(all[i][2]<year){
					printf("%s\n",names[i]);
				}
			}
			break;
		case 1:/*The selection is 'since'*/
			for(int i=0; i<2000; i++){
				if(all[i][2]>year){
					printf("%s\n",names[i]);
				}
			}
			break;	
	}	
}

void single_game(float all[NUMALL][SIZEALL],char names[NUMNAMES][SIZENAMES],char unique_genres[UNIQUEGENRES][SIZEGENRES], char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS]){
	int index=0,
		genre=0,
		platform=0;
	char input[SIZENAMES];/*Input - A game name*/

	printf("\nPlease enter the name of the game:\n");
	scanf("%s", input);

	while( (strcmp(input,names[index]) != 0) && (index<2000) ){
		index++;
	}

	while(index == 2000){/*The game name is invalid*/
		printf("\nPlease enter the name of the game:\n");
		scanf("%s", input);
		index=0;
		while( (strcmp(input,names[index]) != 0) && (index<2000) ){
			index++;
		}
	}

	genre = all[index][0];
	platform = all[index][1];
	printf("\nName:\t\t%s\n", names[index]);
	printf("Genre:\t\t%s\n", unique_genres[genre]);
	printf("Platform:\t%s\n", unique_platforms[platform]);
	printf("Year:\t\t%.0f\n", all[index][2]);
	printf("Sales in NA:\t%f\n",all[index][3]);
	printf("Sales in EU:\t%f\n",all[index][4]);
	if(all[index][5] == -5){/*The data is not available*/
		printf("Total Sales:\tNot Available\n");
	}
	else{
		printf("Total Sales:\t%f\n",all[index][5]);
	}
	printf("User Score:\t%f\n",all[index][6]);
}

void average_score(float all[NUMALL][SIZEALL]){
	float addition=0.0;
	int counter=0;
	for(int i=0; i<NUMALL; i++){
		addition += all[i][6];
		counter++;
	}
	printf("Average: %f\n",(addition/counter));
}
	
void na_eu(char names[NUMNAMES][SIZENAMES], float all[NUMALL][SIZEALL]){
	int index=0;
	char input[SIZENAMES];/*Input - a game name*/

	while( (strcmp(input,names[index])) != 0 && (index<NUMNAMES)){
		index++;
	}	

	while(index == NUMNAMES){/*The game name is invalid*/
		printf("\nPlease enter the name of the game:\n");
		scanf("%s", input);
		index=0;
		while( (strcmp(input,names[index])) != 0 && (index<NUMNAMES)){
			index++;
		}
	}

	if( all[index][3] > all[index][4] ){
		printf("\nThis game was more popular in North America.\n");
	}
	else if( all[index][4] > all[index][3] ){
		printf("\nThis game was more popular in Europe.\n");
	}
	else if( all[index][4] == all[index][3] ){
		printf("\nThis game was in equal popularity in North America and Europe.\n");
	}
}

void frequence_genre(float all[NUMALL][SIZEALL],char unique_genres[UNIQUEGENRES][SIZEGENRES] ){
	int counter=0;
	printf("\n");
	for(int i=0; i<12; i++){
		for(int j=0; j<NUMALL; j++){
			if( all[j][0] == i ){
				counter++;
			}
		}
		if(strlen(unique_genres[i])<7){/*To print correctly*/
			printf("%s:\t\t%d\n",unique_genres[i],counter);
		}
		else{/*To print correctly*/
			printf("%s:\t%d\n",unique_genres[i],counter);
		}
		counter=0;
	}
}

void frequence_platform(float all[NUMALL][SIZEALL],char unique_platforms[UNIQUEPLATFORMS][SIZEPLATFORMS] ){
	int counter=0;
	printf("\n");
	for(int i=0; i<10; i++){
		for(int j=0; j<NUMALL; j++){
			if( all[j][1] == i ){
				counter++;
			}
		}	
		printf("%s:\t%d\n",unique_platforms[i],counter);
		counter=0;
	}
}

