/* In this code, "math.h" library is used. 
So, when you compile the code, please add "-lm".
Try this commands:

$ gcc -c 1801042637.c
$ gcc 1801042637.o -o 1801042637 -lm
$ ./1801042637

Thank you. */
#include <stdio.h>/*printf,scanf definitions*/
#include <stdlib.h>/*srand() and rand() functions*/
#include <time.h>/*time(NULL) function*/
#include <math.h>/*sqrt() function*/
/*Functions are defined to be called in the main and other functions*/
void menu();/*to operate all parts*/
void decrypt_and_print (char* file_path);/*to decrypt and visualize the secret messages in file*/
char decrypt_numbers (int number);/*a helper function for decryption of characters*/
void deep_decrypt_and_print (char* file_path);/*to decrypt and visualize the secret messages in file*/
void track_machine ();/*to track the position of the enemy camp*/
void refresh_position (int *X, int *Y, double *D, double *R);/*to refresh parameters*/
void encrypt_messages (char* file_path);/*to take a message string as input and encrypts the message*/
int encrypt_character(char symbol);/*a helper function for encryption of characters*/

void main(){
	menu();
}

void menu(){
	int choice;/*input - choice*/

	do{
		printf("\n");
		printf("1-) Decrypt and print encrypt_p1.img\n");
		printf("2-) Decrypt and print encrypt_p2.img\n");
		printf("3-) Switch on the tracking machine\n");
		printf("4-) Encrypt the message\n");
		printf("5-) Switch off\n");
		printf("Please make your choice:\n");
		scanf("%d", &choice);		
		switch(choice){
			case 1:
				decrypt_and_print("encrypted_p1.img");
				break;
			case 2:
				deep_decrypt_and_print("encrypted_p2.img");
				break;			
			case 3:
				track_machine();
				break;
			case 4:
				encrypt_messages("decrypted_p4.img");
				break;
		} 
	} while( choice != 5 );	
}

void decrypt_and_print (char* file_path){
	int number, /*to convert between char and int values*/
	inp;/*to check end of file*/
	char c;/*get character from file*/

	FILE *fp;
	fp = fopen(file_path,"r");
	inp = fscanf(fp,"%c", &c);	
	do{
		if(c == '\n'){/*to check new lines*/
			printf("\n");
			inp = fscanf(fp,"%c", &c);
		}
		else{
			number = (int)(c-48);/*ASCII*/
			printf("%c",decrypt_numbers(number));	
			inp = fscanf(fp,"%c", &c);	
		}
	}while(inp!=EOF);
	fclose(fp);
}

char decrypt_numbers (int number){
	char symbol;
/*0, 1, 2, 3, 4, 5, 6 are ‘ ’, ‘-’, ‘_’, ‘|’, ‘/’, ‘\’, ‘O‘*/
	switch(number){
		case 0:
			symbol = ' ';
			break;
		case 1:
			symbol = '-';
			break;
		case 2:
			symbol = '_';
			break;
		case 3:
			symbol = '|';
			break;
		case 4:
			symbol = '/';
			break;
		case 5:
			symbol = '\\';
			break;
		case 6:
			symbol = 'O';
			break;
	}
	return (symbol);
}

void deep_decrypt_and_print (char* file_path){
	int number, inp, 
	addition=0, 
	count=0;/*to check data position in the file*/
	char c;

	FILE *fp;
	fp = fopen(file_path,"r");
	do{
		if(c == '\n'){
			printf("\n");
			inp = fscanf(fp,"%c", &c);
			count += 2;
		}
		else{
			for(int i=0;i<3;i++){				
				fseek(fp,(count),SEEK_SET);/*to change data position*/
				inp = fscanf(fp,"%c",&c);
				number= (int)(c-48);/*ASCII*/
				addition += number;
				count++;
			}
			printf("%c",decrypt_numbers(addition%7));
			addition = 0;
			count -= 2;/*to return to the data*/
		}
	}while(inp!=EOF);
	fclose(fp);
}

void track_machine (){
	int X=0, Y=0;
	double R=0, D=0;
	char command = 'R';	

	do{		
		if(command == 'R'){
			refresh_position(&X,&Y,&D,&R);
			for(int i=1; i<=11; i++){ /*to print the map*/
				for(int j=1; j<=11;j++){
					while((i==6)&&(j==6)){/*our camp*/
						printf("O\t");		
						j++;
					}
					if(X==i && Y==j){/*enemy position*/
						printf("E\t");
					}
					else{
						printf(".\t");
					}
				}
				printf("\n");
			}			
			printf("Enemies X position: %d, Y position: %d, Displacement: %f, Distance to our camp: %f\n",X,Y,R,D );
		}
		else{
			printf("Invalid command.\n");
		}	
	printf("Command waiting...:\n");
	scanf(" %c",&command);
	}while(command != 'E');
}

void refresh_position (int *X, int *Y, double *D, double *R){
	int old_X=0,old_Y=0;/*to keep X and Y values*/

	old_X=*X;
	old_Y=*Y;
	srand(time(NULL));/*to refresh X and Y values*/	
	*X=1+rand()%11;/*X is between 1 and 11*/
	*Y=1+rand()%11;/*Y is between 1 and 11*/
	*R= sqrt( (double)(((*X-old_X)*(*X-old_X))+((*Y-old_Y)*(*Y-old_Y))) );
	*D = sqrt( (double)(((*X-6)*(*X-6))+((*Y-6)*(*Y-6))) );		
}

void encrypt_messages (char* file_path){
	int  inp,
	addition=0,
	count=0,/*to check data position in the file*/
	flag=2,/*to check data at beginning of the line*/ 
	number,/*first data at the line*/
	number_last,/*second data at the line*/
	value;
	char c;

	FILE *fp1;
	FILE *fp2;
	fp1= fopen(file_path,"r");
	fp2= fopen("encrypted_p4.img","w");	
	inp = fscanf(fp1,"%c",&c);
	do{
		if(c=='\n'){/*to check new line*/
			fprintf(fp2, "\n");
			inp = fscanf(fp1,"%c",&c);
			count++;
			flag=2;
		}
		else{
			if(flag==2){
				fseek(fp1,count,SEEK_SET);/*to change data position*/
				inp = fscanf(fp1,"%c",&c);
				number = encrypt_character(c);
				addition=number;
				number_last=number;
				value = (addition%7);
				fprintf(fp2, "%d",value );			
				addition=0;
				inp = fscanf(fp1,"%c",&c);
				number = encrypt_character(c);
				addition = number+number_last;
				value = (addition%7);
				fprintf(fp2, "%d",value );
				addition=0;
				count+=2;
				flag=1;/*now, data is not first or second data at the line*/
				inp = fscanf(fp1,"%c",&c);	
			}
			else{
				for(int i=0; i<3;i++){
					fseek(fp1,count-2,SEEK_SET);/*to change data position*/
					inp = fscanf(fp1,"%c",&c);
					number = encrypt_character(c);
					addition += number;
					count++;
				}
				value = (addition%7);
				fprintf(fp2, "%d",value );
				addition=0;
				inp = fscanf(fp1,"%c",&c);
				count -= 2;/*to return to the data*/
			}
		}
	}while(inp!=EOF);	
	fclose(fp1);
	fclose(fp2);
}

int encrypt_character(char symbol){
	int number;
/* ‘ ’, ‘-’, ‘_’, ‘|’, ‘/’, ‘\’, ‘O‘ are 0, 1, 2, 3, 4, 5, 6 */
	switch(symbol){
		case ' ':
			number=0;
			break;
		case '-':
			number=1;
			break;
		case '_':
			number=2;
			break;
		case '|':
			number=3;
			break;
		case '/':
			number=4;
			break;
		case '\\':
			number=5;
			break;
		case 'O':
			number=6;
			break;						
	}
	return number;
}
