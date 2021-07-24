/* In this code, "math.h" library is used. 
So, when you compile the code, please add "-lm".
Try this commands:

$ gcc -c 1801042637.c
$ gcc 1801042637.o -o 1801042637 -lm
$ ./1801042637

Thank you. */
#include <stdio.h>/*Standart input output library*/
#include <math.h>/*sqrt() and pow() functions*/

#define SIZEOFARRAY 500/*Size of array to use in part1*/
#define N 8/*Size of array to use in part3*/
/*Functions are defined to be called in the main and other functions*/
void generate_hofstadters_sequence (int *arr, int n);
int find_max (int arr[], int index, int max_value);
int sum_array (int arr[]);
double std_array (int arr[], double *mean, int n, int index);
char* remove_duplicates (char* str);
void install_pipes (int visited[N][N], int x, int y, int orientation, int counter);

void main(){

	int choice,/*Input - The user's selection(General menu)*/
		choice_part1,/*Input - The user's selection(Part1 menu)*/
		arr[SIZEOFARRAY],
		n,/*Input - an integer*/
		max_value=0,
		index=0,
		visited[N][N] = {0},/*Elements of the array are zero*/
		x=0,
		y=0,
		orientation=1,
		counter=0;
	double mean=0.0;
	char string[5000];/*Input - String*/
	char *str;
	str = string;

	do{
		printf("\nWelcome to Homework 8, please chose one of the parts to continue\n-------------------------\n");
		printf("1) Execute Part 1\n2) Execute Part 2\n3) Execute Part 3\n4) Exit\n");
		scanf("%d", &choice);
		switch(choice){/*General Menu*/
			case 1:
				do{
					printf("\nPlease make your choice:\n--------------------\n");
					printf("1) Fill Array\n2) Find Biggest Number\n3) Calculate Sum\n4) Calculate Standart Deviation\n5) Exit\n");
					scanf("%d", &choice_part1);
					
					switch(choice_part1){/*Part1 Menu*/
						case 1:
							printf("\nEnter an integer number:\n");
							scanf("%d", &n);
							arr[0] = 1;/*The first element of the array is one*/
							generate_hofstadters_sequence (arr, n);
							break;
						case 2:
							max_value = arr[0];
							printf("\nMax Number on Hofstadter's Q-Sequence: %d\n",find_max(arr,SIZEOFARRAY,max_value));
							break;
						case 3:
							printf("\nThe sum of items on Hofstadter's Q-Sequence: %d \n", sum_array(arr));
							arr[0] = 1;
							generate_hofstadters_sequence (arr, n);/*The elements change during the operation, so the arr[] is refilled*/
							break;
						case 4:
							index = n;/*To use is as a counter*/
							printf("\nThe standard deviation of Hofstadter's Q-Sequence: %lf \n", std_array(arr,&mean,n,index));
							printf("\nThe mean of Hofstadter's Q-Sequence: %lf \n", mean);
							break;
						case 5:/*Returns to general menu*/
							break;
						default:
							printf("\nUnsupported choice.\n");
							break;
					}
				}while(choice_part1 != 5);
				break;
			case 2:
				visited[0][0] = 1;/*(0,0) has water*/
				install_pipes(visited,x,y,orientation,counter);
				printf("\nI'm sorry, I could not complete this part of the homework.\nI developed an algorithm, but I could not figure out how to print it.\nPlease look at the code.\nThank you...\n");
				break;
			case 3:
				printf("Enter a string:\n");
				scanf(" %[^\n]",string);
				remove_duplicates(string);
				printf("\nAfter removes duplicated characters: %s\n", (str));
				break;
			case 4:/*Exit the program*/
				printf("\nGoodbye!\n");
				break;
			default:
				printf("\nUnsupported choice.\n");
				break;
		}
	}while(choice != 4);
}

void generate_hofstadters_sequence (int *arr, int n){
	/*arr[0] is used as counter*/
	if((*arr) < n){
		if((*arr)==1){
			arr[1] = 1;
			(*arr) ++;
			generate_hofstadters_sequence(arr,n);
		}
		else if((*arr) == 2){
			arr[0] = 1;
			arr[ 2 ] = arr[ (2) - arr[ (2)-1] ] + arr[ (2) - arr[ (2) -2] ];
			(*arr) = 3;
			generate_hofstadters_sequence(arr,n);
		}
		else if((*arr) > 2){
			arr[ (*arr) ] = arr[ (*arr) - arr[(*arr)-1] ] + arr[ (*arr) - arr[(*arr)-2] ];
			(*arr) ++;
			generate_hofstadters_sequence(arr,n);
		}
	}
	else if((*arr) >= n && (*arr) <= 500){/*The array items that out of the range (n) are zero*/
		arr[(*arr)] = 0;
		(*arr) ++;
		generate_hofstadters_sequence(arr,n);
	}
	else if((*arr)==501){/*After the operation is finished, arr[0] returns to the value it should be*/
		arr[0] = 1;
	}
}

int find_max (int arr[], int index, int max_value){
	/*index = 500*/
	if(arr[index] > max_value){
		max_value = arr[index];
	}
	
	if(index-1 == 0){/*The operation is finished*/
		return max_value;
	}

	else{
		return find_max(arr, index-1, max_value);
	}
}

int sum_array (int arr[]){
	/*  arr[0] is use as "sum"
		arr[1] is use as "counter" */
	if(arr[1] != 0 && arr[1] != 500){
		arr[0] += arr[arr[1]];
		arr[1]++;
		return sum_array(arr);
	}
	
	else{
		return arr[0];
	}
}

double std_array (int arr[], double *mean, int n, int index){
	
	double value = 0.0;

	if( index >= 0){
		(*mean) += ((double)arr[index] /(double) n);
		return std_array(arr,mean,n,index-1);
	}
	/* When If-Statement is done, index = -1 */

	else if( index >= (-n) ){/*Because the index variable is negative, (-n)*/
		/*Because the index variable is negative, (-index-1)*/
 		value = (*mean - (double)arr[-index-1]) * (*mean - (double)arr[-index-1]);
		return sqrt( ( value / (double) (n-1) ) + pow(std_array(arr,mean,n,index-1),2.0 )) ;
	}
}

void install_pipes (int visited[N][N], int x, int y, int orientation, int counter){
	/*
	For each orientation,
	the values X and Y should be proper and visited[X][Y]=0
	and X and Y values should not be zero at the same time
	*/
	if(orientation == 1){
				
		if( (x+2) < 8 && (x+2) >= 0 &&
			(y+1) < 8 && (y+1) >= 0 &&
			visited[x+2][y+1] == 0 ){

			x += 2;
			y += 1;
			

			visited[x][y] = 1;
			install_pipes(visited,x,y,1,counter);
			/*
			X, Y and visited[X][Y] values should return to their last value,
			when the function do not find the proper path.
			*/
			x -= 2;
			y -= 1;
			visited[x][y] = 0;
			}
			
			orientation++;/*To try other orientations*/

		}

	if(orientation == 2){
				
		if( (x+1) < 8 && (x+1) >= 0 &&
			(y-2) < 8 && (y-2) >= 0 &&
			visited[x+1][y-2] == 0  &&
			!(x+1 == 0 && y-2 == 0) ){
				
			x += 1;
			y -= 2;
				
			visited[x][y] = 2;
			install_pipes(visited,x,y,1,counter);
			/*
			X, Y and visited[X][Y] values should return to their last value,
			when the function do not find the proper path.
			*/
			x -= 1;
			y += 2;
			visited[x][y] = 0;

		}

		orientation++;/*To try other orientations*/

	}

	if(orientation == 3){
				
		if( (x-2) < 8 && (x-2) >= 0 &&
			(y-1) < 8 && (y-1) >= 0 &&
			visited[x-2][y-1] == 0 &&
			!(x-2 == 0 && y-1 == 0) ){
				
			x -= 2;
			y -= 1;
					
			visited[x][y] = 3;
			install_pipes(visited,x,y,1,counter);
			/*
			X, Y and visited[X][Y] values should return to their last value,
			when the function do not find the proper path.
			*/
			x += 2;
			y += 1;
			visited[x][y] = 0;
		}
		orientation++;/*To try other orientations*/

	}

	if(orientation == 4){
				
		if( (x-1) < 8 && (x-1) >= 0 &&
			(y+2) < 8 && (y+2) >= 0 &&
			visited[x-1][y+2] == 0 &&
			!(x-1 == 0 && y+2 == 0) ){
			
			x -= 1;
			y += 2;
					
			visited[x][y] = 4;
			install_pipes(visited,x,y,1,counter);
			/*
			X, Y and visited[X][Y] values should return to their last value,
			when the function do not find the proper path.
			*/
			x += 1;
			y -= 2;
			visited[x][y] = 0;/*To try other orientations*/

		}

		orientation++;

	}

	if(orientation == 5){
				
		if( (x+1) < 8 && (x+1) >= 0 &&
			(y+2) < 8 && (y+2) >= 0 &&
			visited[x+1][y+2] == 0 &&
			!(x+1 == 0 && y+2 == 0) ){
				
			x += 1;
			y += 2;
					
			counter++;
			visited[x][y] = 5;

			install_pipes(visited,x,y,1,counter);
			/*
			X, Y and visited[X][Y] values should return to their last value,
			when the function do not find the proper path.
			*/
			x -= 1;
			y -= 2;
			visited[x][y] = 0;/*To try other orientations*/
		}
		orientation++;

	}

	if(orientation == 6){
				
		if( (x+2) < 8 && (x+2) >= 0 &&
			(y-1) < 8 && (y-1) >= 0 &&
			visited[x+2][y-1] == 0 &&
			!(x+2 == 0 && y-1 == 0) ){
					
			x += 2;
			y -= 1;
					
			visited[x][y] = 6;
			install_pipes(visited,x,y,1,counter);
			/*
			X, Y and visited[X][Y] values should return to their last value,
			when the function do not find the proper path.
			*/
			x -= 2;
			y += 1;
			visited[x][y] = 0;
		}
		orientation++;/*To try other orientations*/

	}

	if(orientation == 7){
			
		if( (x-1) < 8 && (x-1) >= 0 &&
			(y-2) < 8 && (y-2) >= 0 &&
			visited[x-1][y-2] == 0 &&
			!(x-1 == 0 && y-2 == 0) ){
				
			x -= 1;
			y -= 2;
					
			visited[x][y] = 7;
			install_pipes(visited,x,y,1,counter);
			/*
			X, Y and visited[X][Y] values should return to their last value,
			when the function do not find the proper path.
			*/
			x += 1;
			y += 2;
			visited[x][y] = 0;
		}
		orientation++;/*To try other orientations*/

	}

	if(orientation == 8){
				
		if( (x-2) < 8 && (x-2) >= 0 &&
			(y+1) < 8 && (y+1) >= 0 &&
			visited[x-2][y+1] == 0 &&
			!(x-2 == 0 && y+1 == 0) ){

			x -= 2;
			y += 1;
					
			visited[x][y] = 8;
			install_pipes(visited,x,y,1,counter);
			/*
			X, Y and visited[X][Y] values should return to their last value,
			when the function do not find the proper path.
			*/
			x += 2;
			y -= 1;
			visited[x][y] = 0;
		}
		orientation++;

	}
		/*
			When the comment lines below are included in the code, 
			17 irrigated fields are printed on the screen. 
			But it is forbidden to use the loop in the homework,
			I got into comments on these parts. 
			I could not figure out how to print it on the screen recursively.
		*/
		/*
		counter = 0; //the counter was used to check if 64 fields were irrigated
			
		for( int i=0; i<N; i++ ){
			for( int j=0; j<N; j++ ){
				if( visited[i][j] != 0 ){
					counter++;
				}		
			}
		}

		if( counter == 64 ){
			printf("The Field:\n\n");
				for( int i=0; i<N; i++ ){
					for( int j=0; j<N; j++ ){
						printf("O%d\t",visited[i][j] );
					}
				printf("\n\n");
			}
		}
		*/
}

char* remove_duplicates (char* str){
	if( *(str) == '\0'){ /*End of the string*/
		return str;
	}
	else{
		if((*str) == *(str+1)){
			for(int i = 1; *(str+i) != '\0'; i++){/*The elements of the array are changed(sliding)*/
				*(str+i) = *(str+i+1);
			}
			return remove_duplicates(str);
		}
		return remove_duplicates(str+1);	
	}
}