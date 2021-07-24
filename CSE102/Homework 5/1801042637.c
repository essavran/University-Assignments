#include <stdio.h>
/*Functions are defined to be called in the main and other functions*/
void menu();/*To perform all selection operations*/
void read_news(char buffer[500], char file_path[11], int is_Only_Title);/*To read the news and the titles from the folder*/
void append_file(char* file_path, char c);/*To append a character to the file*/
void read_magic_numbers(char buffer_magic[10], char buffer_news[500]);/*For reading the magic numbers*/
double f_func(int x);/*For calculating the f(x) function*/
double g_func(double f(int x), int a);/*For calculating the g(f(x)) function*/
void readed_list(char* file_path);/*An additional function to list read news*/
int check_readed(char* file_path, char c);/*An additional function to check whether the news has been read*/

void main(){
	menu();
}

void menu(){
	char choice,/*Input - To learn what the user wants to do in general menu*/
	buffer[500],/*To send to read_news() function*/
	file_path1[11]="news/1.txt",/*To send to read_news() function*/
	file_path2[11]="news/2.txt",/*To send to read_news() function*/
	file_path3[11]="news/3.txt",/*To send to read_news() function*/
	file_path4[11]="news/4.txt",/*To send to read_news() function*/
	buffer_news[500],/*To send to read_magic_numbers() function*/
	buffer_magic[10],/*To send to read_magic_numbers() function*/
	exit='y';/*To enter Do-While loop*/
	int is_Only_Title,/*To send to read_news() function*/
	selection,/*Input - To learn which news text to read*/
	again;/*Input - To learn to read again*/

	printf("**********Daily Press**********\n\n");
	printf("Today's news are listed for you:\n\n");
	
	printf("Title of 1. news: ");
	read_news(buffer,file_path1,1);/*To show the title of first news*/
	
	printf("Title of 2. news: ");
	read_news(buffer,file_path2,1);/*To show the title of first news*/
	
	printf("Title of 3. news: ");
	read_news(buffer,file_path3,1);/*To show the title of first news*/
	
	printf("Title of 4. news: ");
	read_news(buffer,file_path4,1);/*To show the title of first news*/
	
	do{

	printf("\nWhat do you want to do?\n\n");
	printf("a. Read a new\n");
	printf("b. List the readed news\n");
	printf("c. Get decrypted information from the news\n");
	scanf(" %c",&choice);

	switch(choice){
		case 'a':
				printf("Which news text do you want to read?\n");
				scanf("%d",&selection);

				switch(selection){
					case 1:
						if(check_readed("readed_news_id.txt",'1')==1){/*The news was read*/
							printf("This new is readed. Do you want to read again? Yes(1) / No(0)\n");
							scanf("%d",&again);
							if(again==1){/*Read again*/
							read_news(buffer,"news/1.txt",0);/*To show the text of the news*/
							}
						}
						else if(check_readed("readed_news_id.txt",'1')==0){/*The news was not read*/
							read_news(buffer,"news/1.txt",0);/*To show the text of the news*/
							append_file("readed_news_id.txt",'1');/*To add the number of the read news to the file*/	
						}

						break;
					case 2:
						if(check_readed("readed_news_id.txt",'2')==1){/*The news was read*/
							printf("This new is readed. Do you want to read again? Yes(1) / No(0)\n");
							scanf("%d",&again);
							if(again==1){/*Read again*/
							read_news(buffer,"news/2.txt",0);/*To show the text of the news*/
							}
						}
						else if(check_readed("readed_news_id.txt",'2')==0){/*The news was not read*/
							read_news(buffer,"news/2.txt",0);/*To show the text of the news*/
							append_file("readed_news_id.txt",'2');/*To add the number of the read news to the file*/						
						}
						break;	
					case 3:
						if(check_readed("readed_news_id.txt",'3')==1){/*The news was read*/
							printf("This new is readed. Do you want to read again? Yes(1) / No(0)\n");
							scanf("%d",&again);
							if(again==1){/*Read again*/
							read_news(buffer,"news/3.txt",0);/*To show the text of the news*/
							}
						}
						else if(check_readed("readed_news_id.txt",'3')==0){/*The news was not read*/
							read_news(buffer,"news/3.txt",0);/*To show the text of the news*/
							append_file("readed_news_id.txt",'3');/*To add the number of the read news to the file*/						
						}
						break;
					case 4:
						if(check_readed("readed_news_id.txt",'4')==1){/*The news was read*/
							printf("This new is readed. Do you want to read again? Yes(1) / No(0)\n");
							scanf("%d",&again);
							if(again==1){/*Read again*/
							read_news(buffer,"news/4.txt",0);/*To show the text of the news*/
							}
						}
						else if(check_readed("readed_news_id.txt",'4')==0){/*The news was not read*/
							read_news(buffer,"news/1.txt",0);/*To show the text of the news*/
							append_file("readed_news_id.txt",'4');/*To add the number of the read news to the file*/						
						}
						break;
					default:/*Invalid choice*/
						printf("Invalid choice.\n");
						break;
				}
				break;
		case 'b':
				readed_list("readed_news_id.txt");
				break;
		case 'c':
				read_magic_numbers(buffer_magic,buffer_news);
				break;
		default:/*Invalid choice*/
				printf("Invalid choice.\n");
				break;
	}
	printf("\nDo you want to continue? Yes(y)/No(n)\n");
	scanf(" %c",&exit);

	if((exit!='n') && (exit!='y')){/*For invalid choice*/
		printf("Invalid choice.\n");
	}
	if(exit=='n'){/*Goodbye!*/
		printf("Goodbye!\n");
	}

	}while(exit!='n');
}

void read_news(char buffer[500], char file_path[10], int is_Only_Title){
	int inp,/*To check EOF*/
	i=0;/*To count for element of buffer*/

	FILE *fp = fopen(file_path,"r");/*To open the file*/
	inp = fscanf(fp, "%c", &buffer[i]);	

	if(is_Only_Title==0){/*To show the text of news*/
		do{ 
			printf("%c", buffer[i]);		
			i++;			
			inp = fscanf(fp, "%c", &buffer[i]);
		}while(inp!=EOF);

		printf("\n");
		fclose(fp);	
	}

	else if(is_Only_Title==1){/*To show the title of news*/
		do{ 
			printf("%c", buffer[i]);		
			i++;			
			fscanf(fp, "%c", &buffer[i]);
		}while(buffer[i]!='\n');

		printf("\n");
		fclose(fp);	
	}
}

void append_file(char* file_path, char c){
	char is_there;/*To read a character from the file*/
	int count = 1;/*To control printing to the file*/

	FILE *fp = fopen(file_path,"a+");	
	fscanf(fp, "%c", &is_there);

	do{
		if(is_there!='\n' && is_there!='\r'){/*The character should not be a new line or a carriage return*/
			if(c == is_there){ /*The character is in the file*/
					count=0;
					fclose(fp);/*Do-While loop is over*/	
			}
			else{
				fscanf(fp, "%c", &is_there);
			}
		}
	//fscanf(fp, "%c", &is_there);//gerekli mi anlamadım !!!!!!!!!!!!!!!!!!!!!!!!1111111111
	}while(fscanf(fp, "%c", &is_there)!=EOF);

	if(count==1){/*The character is not in the file*/
		fprintf(fp, "%c\n", c);	
		fclose(fp);
	}
}

void readed_list(char* file_path){
	char is_there,/*To read a character from the file*/
	c;/*To check whether the character is 1,2,3 or 4*/

	FILE *fp = fopen(file_path,"r");	
	fscanf(fp, "%c", &is_there);

	do{
		if(is_there!='\n' && is_there!='\r'){/*The character should not be a new line or a carriage return*/
			for(int i=1; i<=4; i++){
				c=i+48;/*ASCII*/
				if(c == is_there){/*The character is in the file*/
					printf("%c. new is readed.\n",c);
				}	
			}	
		fscanf(fp, "%c", &is_there);			
		}
	}while(fscanf(fp, "%c", &is_there)!=EOF);
	fclose(fp);
}

int check_readed(char* file_path, char c){
	char is_there;/*To read a character from the file*/
	int flag=0;/*To check to whether the file was read*/

	FILE *fp = fopen(file_path,"r");	
	fscanf(fp, "%c", &is_there);

	do{
		if(is_there!='\n' && is_there!='\r'){/*The character should not be a new line or a carriage return*/

			if(c == is_there){/*The character is in the file*/
				flag=1;/*If the news is read, flag is 1*/
				fclose(fp);/*EOF*/
			}

			fscanf(fp, "%c", &is_there);
		}
	}while(fscanf(fp, "%c", &is_there)!=EOF);

	if(flag==0){
		fclose(fp);
	}
	return flag;
}

void read_magic_numbers(char buffer_magic[10], char buffer_news[500]){
	int inp,/*To check EOF*/
	i=0,
	j=0,
	selection,/*Input - Which news will be decrypted*/
	number;/*To convert a character to integer value*/
	double addition=0;

	printf("Which news would you like decrypt?\n");
	scanf("%d",&selection);

	if(selection==1){

		FILE *fp = fopen("news/1.txt","r");
		inp=fscanf(fp, "%c", &buffer_news[i]);	

		do{ 
			printf("%c", buffer_news[i]);/*Print i. element of array*/		
			if(buffer_news[i] == '#'){
				i++;
				fscanf(fp, "%c", &buffer_news[i]);
				printf("%c", buffer_news[i]);/*Print i. element of array*/		
				buffer_magic[j]=buffer_news[i];/*The number after '#' is the magic number*/
				number = buffer_magic[j]-48;/*Convert to integer value*/
				addition += g_func(f_func,number);
				j++;
			}
			i++;			
			inp=fscanf(fp, "%c", &buffer_news[i]);
		}while(inp!=EOF);

		fclose(fp);	
		printf("\nNumber of tests performed = %.2lf\n",addition);
	}

	else if(selection==2){

		FILE *fp = fopen("news/2.txt","r");
		inp=fscanf(fp, "%c", &buffer_news[i]);	

		do{ 
			printf("%c", buffer_news[i]);/*Print i. element of array*/
			if(buffer_news[i]=='#'){
				i++;
				fscanf(fp, "%c", &buffer_news[i]);
				printf("%c", buffer_news[i]);/*Print i. element of array*/
				buffer_magic[j]=buffer_news[i];/*The number after '#' is the magic number*/
				number = buffer_magic[j]-48;/*Convert to integer value*/
				addition += g_func(f_func,number);
				j++;
			}
			i++;			
			inp=fscanf(fp, "%c", &buffer_news[i]);
		}while(inp!=EOF);

		fclose(fp);	
		printf("\nNumber of sick people = %.2lf\n",addition);		
	}

	else if(selection==3){

		FILE *fp = fopen("news/3.txt","r");
		inp=fscanf(fp, "%c", &buffer_news[i]);	

		do{ 
			printf("%c", buffer_news[i]);/*Print i. element of array*/	
			if(buffer_news[i]=='#'){
				i++;
				fscanf(fp, "%c", &buffer_news[i]);
				printf("%c", buffer_news[i]);/*Print i. element of array*/
				buffer_magic[j]=buffer_news[i];/*The number after '#' is the magic number*/
				number = buffer_magic[j]-48;/*Convert to integer value*/
				addition += g_func(f_func,number);
				j++;
			}
			i++;			
			inp=fscanf(fp, "%c", &buffer_news[i]);
		}while(inp!=EOF);

		fclose(fp);	
		printf("\nNumber of deaths = %.2lf\n",addition);			
	}

	else if(selection==4){

		FILE *fp = fopen("news/4.txt","r");
		inp=fscanf(fp, "%c", &buffer_news[i]);	

		do{ 
			printf("%c", buffer_news[i]);/*Print i. element of array*/
			if(buffer_news[i]=='#'){
				i++;
				fscanf(fp, "%c", &buffer_news[i]);
				printf("%c", buffer_news[i]);/*Print i. element of array*/
				buffer_magic[j]=buffer_news[i];/*The number after '#' is the magic number*/
				number = buffer_magic[j]-48;/*Convert to integer value*/
				addition += g_func(f_func,number);
				j++;
			}
			i++;			
			inp=fscanf(fp, "%c", &buffer_news[i]);
		}while(inp!=EOF);

		fclose(fp);	
		printf("\nExpected number of sick people = %.2lf\n",addition);
	}

	else{/*Invalid selection*/
		printf("Invalid selection.\n");
	}
}

double f_func(int x){
	double value;
	value = (x*x*x) - (x*x) + 2;
	return value;
}

double g_func(double f(int x), int a){
	double function;
	function= f_func(a)* f_func(a);
	return function;
}