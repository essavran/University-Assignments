/* In this code, "math.h" library is used. 
So, when you compile the code, please add "-lm".
Try this commands:

$ gcc -c 1801042637.c
$ gcc 1801042637.o -o 1801042637 -lm
$ ./1801042637

Thank you. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/*For part2,
* Size of array and linkedlist are assumed as below.
* Intervals of numbers are assumed as below.
* If you want, you can change them.
*/
#define SIZE 30
#define INTERVAL 1000000

typedef struct node_s {
	int data;
	struct node_s *next;	
} nodes;

typedef struct number_s{
	int n1, n2;
} numbers;

int * read_array(char * filename, int * byte_array); /*To read the file, to calculate total memory usage, and to fill the array dynamicaly*/
float * stats_array(int * p); /*To calculate max, min, mean, std deviation with using the array*/
nodes * read_linkedlist(char *filename, int * byte_linkedlist); /*To read the file, to calculate total memory usage, and to fill the linkedlist dynamicaly*/
float * stats_linkedlist(nodes * head); /*To calculate max, min, mean, std deviation with using the linkedlist*/
int * fill_array(); /*To fill the array dynamicaly to be used in part2*/
nodes * fill_linkedlist(int * array); /*To fill the linkedlist dynamicaly to be used in part2*/
numbers * differences(int * array, nodes * list); /*To find different entries*/

void main(){ 

	nodes * head, * list, * temp;
	numbers * dif;
	int * array,
		* ptr_array;
	int byte_array = 0,
		byte_linkedlist = 0,
		choice,
		flag=0, 
		total_wrong=0, 
		count_wrong=0;
	float * ptr_float_array, * ptr_float_ll;
	clock_t start_a, end_a, start_ll, end_ll, start_a2, end_a2, start_ll2, end_ll2;
	double time_a, time_ll, time_a2, time_ll2;
	srand(time(NULL));
	do{
		printf("\nWelcome to Homework 11, please chose one of the parts to continue\n");
		printf("1) Execute Part 1\n2) Execute Part 2\n3) Exit\n");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				time_a = 0.0; time_ll = 0.0; time_a2 = 0.0; time_ll2 = 0.0;
				
				start_a = clock();
				ptr_array = read_array("list.txt", &byte_array);
				end_a = clock();
				time_a += ( (double)(end_a-start_a)) / CLOCKS_PER_SEC;

				start_ll = clock();
				head = read_linkedlist("list.txt", &byte_linkedlist);
				end_ll = clock();
				time_ll += ( (double)(end_ll-start_ll)) / CLOCKS_PER_SEC;

				start_a2 = clock();
				ptr_float_array = stats_array(ptr_array);
				end_a2 = clock();
				time_a2 += ( (double)(end_a2-start_a2)) / CLOCKS_PER_SEC;

				start_ll2 = clock();
				ptr_float_ll = stats_linkedlist(head);
				end_ll2 = clock();
				time_ll2 += ( (double)(end_ll2-start_ll2)) / CLOCKS_PER_SEC;

				start_ll = clock();
				head = read_linkedlist("list.txt", &byte_linkedlist);
				end_ll = clock();
				time_ll += ( (double)(end_ll-start_ll)) / CLOCKS_PER_SEC;

				start_a = clock();
				ptr_array = read_array("list.txt", &byte_array);
				end_a = clock();
				time_a += ( (double)(end_a-start_a)) / CLOCKS_PER_SEC;

				start_a2 = clock();
				ptr_float_array = stats_array(ptr_array);
				end_a2 = clock();
				time_a2 += ( (double)(end_a2-start_a2)) / CLOCKS_PER_SEC;

				start_ll = clock();
				head = read_linkedlist("list.txt", &byte_linkedlist);
				end_ll = clock();
				time_ll += ( (double)(end_ll-start_ll)) / CLOCKS_PER_SEC;

				start_a = clock();
				ptr_array = read_array("list.txt", &byte_array);
				end_a = clock();
				time_a += ( (double)(end_a-start_a)) / CLOCKS_PER_SEC;

				start_a2 = clock();
				ptr_float_array = stats_array(ptr_array);
				end_a2 = clock();
				time_a2 += ( (double)(end_a2-start_a2)) / CLOCKS_PER_SEC;

				start_ll2 = clock();
				ptr_float_ll = stats_linkedlist(head);
				end_ll2 = clock();
				time_ll2 += ( (double)(end_ll2-start_ll2)) / CLOCKS_PER_SEC;

				start_a2 = clock();
				ptr_float_array = stats_array(ptr_array);
				end_a2 = clock();
				time_a2 += ( (double)(end_a2-start_a2)) / CLOCKS_PER_SEC;

				start_ll2 = clock();
				ptr_float_ll = stats_linkedlist(head);
				end_ll2 = clock();
				time_ll2 += ( (double)(end_ll2-start_ll2)) / CLOCKS_PER_SEC;

				start_a = clock();
				ptr_array = read_array("list.txt", &byte_array);
				end_a = clock();
				time_a += ( (double)(end_a-start_a)) / CLOCKS_PER_SEC;

				start_ll = clock();
				head = read_linkedlist("list.txt", &byte_linkedlist);
				end_ll = clock();
				time_ll += ( (double)(end_ll-start_ll)) / CLOCKS_PER_SEC;

				start_ll2 = clock();
				ptr_float_ll = stats_linkedlist(head);
				end_ll2 = clock();
				time_ll2 += ( (double)(end_ll2-start_ll2)) / CLOCKS_PER_SEC;

				printf("\n\t\tread_array()\tread_linkedlist()\n");
				printf("->total memory:\t%d\t\t%d\n", byte_array, byte_linkedlist);
				printf("->average time:\t%lf\t%lf\n\n", time_a/4.0,time_ll/4.0);
				
				printf("\t\tstats_array()\tstats_linkedlist()\n");
				printf("->max value:\t%f\t%f\n",*ptr_float_array,*ptr_float_ll );
				printf("->min value:\t%f\t%f\n",*(ptr_float_array+1),*(ptr_float_ll+1) );
				printf("->mean value:\t%f\t%f\n",*(ptr_float_array+2),*(ptr_float_ll+2));
				printf("->std value:\t%f\t%f\n",*(ptr_float_array+3),*(ptr_float_ll+3));
				printf("->average time:\t%lf\t%lf\n\n", time_a2/4.0,time_ll2/4.0);
				
				free(ptr_float_array);
				free(ptr_float_ll);
				free(ptr_array);
				free(head);	
				break;
			case 2:
				array = fill_array();
				list = fill_linkedlist(array);
				/*some entrys are changed*/
				total_wrong = 1 + rand()%SIZE;					
				for(int i=0; i < total_wrong; i++){
					temp = list;
					count_wrong = rand()%SIZE;
					* (array + count_wrong) = 1 + rand()%INTERVAL;
					for(int j=0; j<count_wrong; j++){
						temp = temp->next;
					}
					temp->data = 1 + rand()%INTERVAL;
					while(temp->data == * (array + count_wrong)){
						temp->data = 1 + rand()%INTERVAL;
					}
				}
				/*print the array and the linkedlist*/
				printf("\n%10s%5s%18s\n","The Array","VS","The Linkedlist");
				temp = list;
				flag = 0;
				while(* (array+flag) != -1){
					printf("%10d%5s%10d\n",*(array+flag),"VS", temp->data);
					flag++;
					temp=temp->next;
				}
				/*find different entries and print them*/
				dif = differences(array, list);
				printf("\nDifferent Numbers:\n");
				for(int i=0; dif[i].n1 != -1; i++){
					printf("%10d%5s%10d\n", dif[i].n1,"and", dif[i].n2);
				}	
					
				free(array);
				free(list);
				free(temp);
				free(dif);
				break;
			case 3:
				printf("Goodbye!\n");
				break;
			default:
				printf("\nUnsupported choice.\n");
				break;
		}
	}while(choice != 3);
}

int * read_array(char * filename, int * byte_array){
	
	int index,
		temp,
		count = 0,
		* p = NULL;
	char c;
	*byte_array = 0;
	FILE *fp = fopen(filename,"r"); 

	fscanf(fp, "%d", &temp);
	p = (int *)malloc(sizeof(int));
	* byte_array += 4;
	* p = temp;
	fscanf(fp, "%c", &c);

	while( fscanf(fp, "%d", &temp) != EOF ){
		count++;
		index = count + 1;
		p = (int *)realloc(p, sizeof(int)*index);
		* byte_array += 4;
		* (p + count) = temp;
		fscanf(fp, "%c", &c);
	}
	* (p + index) = -1;
	return p; /*return the array*/
} 

float * stats_array(int *p){

	float * array;
	int max, min, size = 0;
	double  value = 0.0, std = 0.0, mean = 0.0, sum = 0.0;
	array = (float *)calloc(4, sizeof(float));
	/* Mean */
	while(*(p+size) != -1){
		sum += *(p+size);
		size++;
	}
	mean = sum/(double)size;
	/*Max, min, std*/
	max = * p;
	min = * p;
	for(int i=0; i<size; i++){
		if(* (p+i) > max){
			max = * (p+i);
		}
		if(* (p+i) < min){
			min = * (p+i);
		}
		value += ( (mean - (double)*(p+i)) * (mean - (double)*(p+i)) ) / (double)(size-1);
	}
	std = sqrt(value);
	/*fill the float array*/
	*array = (float)max;
	*(array+1) = (float)min;
	*(array+2) = (float)mean;
	*(array+3) = (float)std;
	return array;
}

nodes * read_linkedlist(char *filename, int * byte_linkedlist){

	nodes *head, *temp, *new_node;
	int num;
	char c;
	*byte_linkedlist = 0;
	FILE *fp = fopen(filename,"r"); 

	fscanf(fp, "%d", &num);
	head = (nodes *)malloc(sizeof(nodes));
	*byte_linkedlist += 8;
	head->data = num;
	head->next = NULL;
	fscanf(fp, "%c", &c);
	temp = head;
	
	while( fscanf(fp, "%d", &num) != EOF ){
		new_node = (nodes *)malloc(sizeof(nodes));
		*byte_linkedlist += 8;
		new_node->data = num;
		temp->next = new_node;
		temp = new_node;
		new_node->next = NULL;
		fscanf(fp, "%c", &c);
	}
	return head; /*return the first element of the linkedlist so return the linkedlist*/
}

float * stats_linkedlist(nodes * head){

	nodes * temp;
	float * array;
	int max, min, size = 0;
	double  value = 0.0, std = 0.0, mean = 0.0, sum = 0.0;
	array = (float *)calloc(4, sizeof(float));
	/*Mean*/
	temp = head;
	while (temp!=NULL) {
		size++;
		sum += temp->data;
		temp = temp->next;
	}
	mean = sum / size;
	/*Max, min, std*/
	temp = head;
	max = temp->data;
	min = temp->data;
	while(temp != NULL){
		if(temp->data > max){
			max = temp->data;
		}
		if(temp->data < min){
			min = temp->data;
		}
		value += ( (mean - (double)(temp->data)) * (mean - (double)(temp->data)) ) / (double)(size-1);
		temp = temp->next;
	}
	std = sqrt(value);
	/*Fill the float array*/
	*array = (float)max;
	*(array+1) = (float)min;
	*(array+2) = (float)mean;
	*(array+3) = (float)std;
	return array;
}

int * fill_array(){

	int * array, count = 0;
	srand(time(NULL));
	array = (int *)malloc(sizeof(int));
	*array = 1 + rand()%INTERVAL;
	while(count < SIZE){
		count++;
		array = (int *)realloc(array, sizeof(int)*(count+1));
		* (array + count) = 1 + rand()%INTERVAL; /*fill the array random integers*/
	};
	* (array + count) = -1;
	return array;
}

nodes * fill_linkedlist(int * array){
/*This function equalizes the array and the linkedlist*/
	nodes * list, * temp, * new;
	int count = 0;
	list = (nodes *)malloc(sizeof(nodes));
	list->data = * array;
	list->next = NULL;
	temp = list;
	for(count=1; *(array + count ) != -1; count++){
		new = (nodes *)malloc(sizeof(nodes));
		new->data = * (array + count);
		temp->next = new;
		temp = new;
		new->next = NULL;
	}
	return list;
}

numbers * differences(int * array, nodes * list){

	int count = 0, flag = 0;
	nodes * temp;
	numbers * difference;
	temp = list;
	while(*(array+count) != -1){
		if(*(array+count) != temp->data ){ /*There are different entries*/
			if(flag==0){
				difference = (numbers *)malloc(sizeof(numbers));
				(difference+flag)->n1 = *(array+count);
				(difference+flag)->n2 = temp->data;
				flag++;
			}
			else{
				difference = (numbers *)realloc(difference,sizeof(numbers)*(flag+1));
				(difference+flag)->n1 = *(array+count);
				(difference+flag)->n2 = temp->data;
				flag++;
			}	
		}
		count++;
		temp=temp->next;
	}
	difference = (numbers *)realloc(difference,sizeof(numbers)*(flag+1));
	(difference+flag)->n1 = -1; /*the last element is -1 because of check the end of struct array*/
	return difference;
}