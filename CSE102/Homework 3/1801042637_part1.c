/*The program calculates the sum/multiplication of 
the odd/even integers between the range of [1,N].*/
#include <stdio.h> /*printf,scanf definitions*/
/*Functions are defined to be called in the main function*/
int sum (int n, int flag); /*to calculate the sum of the odd/even integers between the range of [1,N]*/
int mult (int n, int flag); /*to calculate the multiplication the odd/even integers between the range of [1,N]*/

int main(){
	int n, /*input - an integer*/
		flag, /*to determine operation */
		flag2, /*to determine odd/even*/
		turning = 1; /*to set the value to return*/

	printf("Enter an integer:\n"); /*Get the integer*/
	scanf("%d",&n);
	printf("Please enter '0' for sum, '1' for multiplication\n"); /*Get the operation*/
	scanf("%d",&flag);

	switch (flag){ 
		
		case 0: /*The operation is "sum"*/
			/*Get the odd/even selection*/
			printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n"); 
			scanf("%d",&flag2);
			
			switch(flag2){
				
				case 0: /*sum for even numbers*/
					printf("2");
					for(int i=4; i<=n; i+=2){
						printf(" + %d", i);
					}
					printf(" = %d\n",sum(n,flag2));
					break;

				case 1: /*sum for odd numbers*/
					printf("1");
					for(int i=3; i<=n; i+=2){
						printf(" + %d", i);
					}
					printf(" = %d\n",sum(n,flag2));
					break;

				default: /*Invalid value for odd/even selection*/
					printf("Invalid value for odd/even selection\n");
					turning -= 1; /*the value to return is 0*/
					break;
			}
			break;

		case 1: /*The operation is "sum"*/
			/*Get the odd/even selection*/
			printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
			scanf("%d",&flag2);
			
			switch(flag2){
				
				case 0: /*multiplication for even numbers*/
					printf("2");
					for(int i=4; i<=n; i+=2){
						printf(" * %d", i);
					}
					printf(" = %d\n",mult(n,flag2));
					break;

				case 1: /*multiplication for odd numbers*/
					printf("1");
					for(int i=3; i<=n; i+=2){
						printf(" + %d", i);
					}
					printf(" = %d\n",mult(n,flag2));
					break;

				default: /*Invalid value for odd/even selection*/
					printf("Invalid value for odd/even selection\n");
					turning -= 1; /*the value to return is 0*/
					break;
			}
			break;
		
		default: /*Unsupported operation*/
			/*Get the odd/even section*/
			printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
			scanf("%d",&flag2);
			printf("Unsupported operation\n");
			turning -= 1; /*the value to return is 0*/
			break;
			
	}
return (turning); /*If the program works well, the value to return is 1*/
}

int sum (int n, int flag){ /*the sum function*/
	int addition=0;

	switch(flag){
		case 0: /*sum for even numbers*/
			for(int i=2; i<=n; i += 2){
				addition += i;
			}
			break;
		case 1: /*sum for odd numbers*/
			for(int i=1; i<=n; i += 2){
				addition += i;
			}
			break;
	}
return (addition); /*return the answer*/
}

int mult (int n, int flag){ /*the multiplication funciton*/
	int multiplication=1;

	switch(flag){
		case 0: /*multiplication for even numbers*/
			for(int i=2; i<=n; i += 2){
				multiplication *= i;
			}
			break;
		case 1: /*multiplication for odd numbers*/
			for(int i=1; i<=n; i += 2){
				multiplication *= i;
			}
			break;
	}
return (multiplication); /*return the answer*/
}