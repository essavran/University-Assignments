/* In this code, I used "math.h" library. 
So, when you compile the code, please add "-lm".
Try this commands:

$ gcc -c 1801042637_part2.c
$ gcc 1801042637_part2.o -o 1801042637_part2 -lm
$ ./1801042637_part2

Thank you. */

#include <stdio.h> /*printf,scanf definitions*/
#include <math.h> /*log10() and pow() functions*/

/*Functions are defined to be called in the main function*/
int number_length(int number);
int find_digit(int number, int index);

void main(){
	int number, /*input - number*/
		index; /*input - digit of the number*/
	/*Get the number*/
	printf("Enter a number (maximum 6 digits):\n");
	scanf("%d",&number);
	/*Function is called to find the length of the number and print it*/
	printf("Your number has %d digits\n", number_length(number));
	/*Get the index*/
	printf("When your number is written 100 times next to each other,\nwhich digit of this number would you like to see? :\n");
	scanf("%d",&index);
	/*Function is called to find the number in the specified index and print it*/
	printf("%d.th digit of the big number sequence: %d\n", index, find_digit(number,index));
}

int number_length(int number){
	double d_number, /*to convert from integer to double*/
		   d_length; /*to convert from integer to double*/
	int length; /*to return the answer*/
	d_number = (double)number; /*Type casting for "log10" function*/
	d_length = log10(d_number);
	length = ((int)d_length) + 1;

	return (length);
}

int find_digit(int number, int index){
	/*When the number is divided by 10,
	the quotient(must be integer) is the new number which is created by deleting 1 digit from the number.
	When the number is divided by 10,
	the remainder is which number is in the last digit.*/
	int length, 
		remainder,
		power, 
		answer,
		quotient,
		difference;
			
	double d_difference;
	/*Function is called to find the length of the number*/
	length = number_length(number);
	remainder = index % length; /*Modulo*/
	if( remainder == 0 ){
		answer = number % 10;
	}
	else {
		difference = length - remainder;
		d_difference = (double)difference; /*Type casting for pow() function*/
		power = (int)pow(10.0,d_difference);
		quotient = number / power;
		answer = quotient % 10;
	}
	return (answer);
}


