/* In this code, "math.h" library is used. 
So, when you compile the code, please add "-lm".
Try this commands:

$ gcc -c 1801042637_part2.c
$ gcc 1801042637_part2.o -o 1801042637_part2 -lm
$ ./1801042637_part2

Thank you. */
#include <stdio.h> /*printf,scanf definitions*/
#include <math.h> /*sqrt() function*/
/*Function is defined to be called in the main function*/
int isprime (int a);/*to the primality testing*/

void main(){
	int n; /*input - an integer*/
	printf("Please enter an integer:\n"); /*Get the integer*/
	scanf("%d",&n);
	/*There is a loop to check every numbers from 2 to the integer(n)*/
	for(int i=2; i<n; i++){
		if(isprime(i)==1){ 
			printf("\n%d is a prime number\n",i);
		}
		else{
			printf("\n%d is not prime number, it is dividible by %d\n",i,isprime(i));
		}
	}
}

int isprime (int a){
	/* The primality testing is the following information:
	A is prime if A is not dividible by any integer X where X is;
	1 < X <= (A)^(1/2) */
	int flag=0,/*the value to return*/
		square; 
	double d_a,/*to convert "a" from integer to double*/
		   d_square;/*to convert "square" from integer to double*/

	d_a = (double)a; /*type casting to write "a" into the function sqrt*/
	d_square = sqrt(d_a);
	square = (int)d_square;/*"d_square" is a double but it must be an integer*/

	if(square >= 2){
		for(int i=2; i<=square; i++){
			if((a%i)==0){
				flag = i; /*flag is the least divisor of that integer if it is not a prime*/
				i = square + 1;
			}
			else{
				flag = 0;
				flag++; /*flag = 1, if the integer is prime*/
			}
		}
	}
	else{
		flag++; /*flag = 1, if the integer is prime*/
	}
return (flag);
}