/*In this code, I used "math.h" library. 
So, when you compile the code, please add "-lm".
Try this commands:

$ gcc -c 1801042637.c
$ gcc 1801042637.o -o 1801042637 -lm
$ ./1801042637

Thank you. */

#include <stdio.h> /*printf,scanf definitions*/
#include <math.h>  /*sqrt() and fabs() functions*/
#include <stdlib.h> /*abs() function*/

/*Functions are defined to be called in the main function*/

void find_root(); /*part1*/
void find_newtonian_root(); /*part2*/
int find_multiple_closest(int a, int b); /*part3*/


int main(){

	int a, /*input and output - for part3, first integer */
		b, /*input and output - for part3, second integer*/
		c; /*output - for part3, multiple closest number*/

	find_root(); /*part2*/
	find_newtonian_root(); /*part3*/
	
	/*This part of the main function is for part 3. 
	Firstly, get the first and second integers*/

	printf("Enter the first integer:\n");
	scanf("%d",&a);
	printf("Enter the first integer:\n");
	scanf("%d",&b);

	c = find_multiple_closest(a,b); /*The function is called*/

	/*There is an if statement because the answer that return from the function may be the same as the first integer. 
	Because the output will be different, cases are evaluated separately.*/

	if(a==c){ /*The value that return from the function is same as the first integer*/
		printf("Closest number to %d that is multiple of %d is itself.\n",a,b);
	}
	else{ /*The value that return from the function is not same as the first integer*/
		printf("Closest number to %d that is multiple of %d is %d.\n",a,b,c);
	}

	return 0;
}


void find_root(){ 

	int first, /*input and output - first coefficient*/
		second, /*input and output - second coefficient*/
		third; /*input and output - third coefficient*/
		
	double delta, /*output - delta. because of sqrt() function, there is double type*/
		   root_first, root_second; /*output - real roots*/

	/*Read three integers from the user for coefficient*/

	printf("Please Enter the first coefficient:\n");
	scanf("%d", &first);
	printf("Please Enter the second coefficient:\n");
	scanf("%d", &second);
	printf("Please Enter the third coefficient:\n");
	scanf("%d", &third);

	delta = (second * second)-(4 * first * third);

	/*If the delta is greater than and equal to zero, there are real roots.
	If the delta is less than zero, there is not a real root.
	The purpose of this if statement is to control these situations*/

	if(delta >= 0.0){ /*There are real roots*/

		/*Calculating roots*/

		root_first = (-second + sqrt(delta)) /( 2 * first);
		root_second = (-second - sqrt(delta)) /( 2 * first);
		
		/*Print real roots.
		There is an if statement, because of correct output of the signs of coefficients*/

		if(second < 0 && third < 0){
			printf("Your equation %dx^2 %dx %d have real roots {%.1lf,%.1lf}.\n", first, second, third, root_first, root_second);
		}
		else if(second < 0 && third >= 0){
			printf("Your equation %dx^2 %dx + %d have real roots {%.1lf,%.1lf}.\n", first, second, third, root_first, root_second);
		}
		else if(second >= 0 && third < 0){
			printf("Your equation %dx^2 + %dx %d have real roots {%.1lf,%.1lf}.\n", first, second, third, root_first, root_second);
		}
		else{
			printf("Your equation %dx^2 + %dx + %d have real roots {%.1lf,%.1lf}.\n", first, second, third, root_first, root_second);
		}	
	}
	else{ /*There is not a real root*/

		/*Print that there is no real root.
		There is an if statement, because of correct output of the signs of coefficients*/

		if(second < 0 && third < 0){
			printf("Your equation %dx^2 %dx %d does not have any real roots.\n", first, second, third);
		}
		else if(second < 0 && third >= 0){
			printf("Your equation %dx^2 %dx + %d does not have any real roots.\n", first, second, third);
		}
		else if(second >= 0 && third < 0){
			printf("Your equation %dx^2 + %dx %d does not have any real roots.\n", first, second, third);
		}
		else{
			printf("Your equation %dx^2 + %dx + %d does not have any real roots.\n", first, second, third);
		}
	}
}


void find_newtonian_root(){

	/* Newton's Algorithm is that x(n+1) = x(n) - ( f(x) / f'(x) ) */

	int cof1,cof2,cof3; /*input and output - first, second and third coefficients*/
	double initial, /*input and output - initial guess*/
		   delta, /*to calculate delta*/
		   root1, root2, /*to calculate roots*/
		   root_close=0, /*to find the root close to the estimate*/
		   function, /*f(x)*/
		   der_func, /*derivative of f(x)*/
		   difference; /*difference between the actual root and the estimated root*/

	/*Read three integers from the user for coefficients and an initial*/

	printf("Please Enter the first coefficient:\n");
	scanf("%d",&cof1);
	printf("Please Enter the second coefficient:\n");
	scanf("%d",&cof2);
	printf("Please Enter the third coefficient:\n");
	scanf("%d",&cof3);
	printf("Please Enter the initial:\n");
	scanf("%lf",&initial);
	
	delta = (cof2 * cof2) - (4 * cof1 * cof3); /*Calculate delta for find roots*/

	/*calculate roots*/

	root1 = (-cof2 + sqrt(delta)) / (2 * cof1);
	root2 = (-cof2 - sqrt(delta)) / (2 * cof1);

	/*There is an if statement, because of correct output of the signs of coefficients*/

	if(cof2 < 0 && cof3 < 0){
		printf("Your equation %dx^2 %dx %d and iterations are\n", cof1, cof2, cof3);
	}
	else if(cof2 < 0 && cof3 >= 0){
		printf("Your equation %dx^2 %dx + %d and iterations are\n", cof1, cof2, cof3);
	}
	else if(cof2 >= 0 && cof3 < 0){
		printf("Your equation %dx^2 + %dx %d and iterations are\n", cof1, cof2, cof3);
	}
	else{
		printf("Your equation %dx^2 + %dx + %d and iterations are\n", cof1, cof2, cof3);
	}	

	/*There is an if statement to find which root is close to the initial guess*/

	if(fabs(root1-initial) > fabs(root2-initial)){
		root_close = root2;
	}
	else{
		root_close = root1;
	}

	/*Now, The Newton's Algorithm is here*/

	printf("Step \t x \t\t f(x) \t\t Difference\n");

	/*Step 1*/

	function = (cof1 * initial * initial) + (cof2 * initial) + cof3; /*Put the initial guess in the function*/
	der_func = (2 * cof1* initial) + cof2; /*Find derivative function and put the initial guess in the derivative function*/
	initial = initial - (function / der_func); /*Change the initial guess with the estimated root*/
	difference = initial - root_close; /*Find difference between the actual root and the estimated root*/
	function = (cof1 * initial * initial) + (cof2 * initial) + cof3; /*Put the new initial guess in the function*/
	
	printf("x1 \t %.4lf \t %.4lf \t %.4lf	\n",initial,function,difference); /*Print number of step, value of x, value of function, and difference*/

	/*Step 2 is same as Step 1*/

	der_func = (2 * cof1* initial) + cof2;	
	initial = initial - (function / der_func);
	difference = initial - root_close; 
	function = (cof1 * initial * initial) + (cof2 * initial) + cof3;
	
	printf("x2 \t %.4lf \t %.4lf \t %.4lf	\n",initial,function,difference);
	
	/*Step 3  is same as Step 1*/

	der_func = (2 * cof1* initial) + cof2;	
	initial = initial - (function / der_func);
	difference = initial - root_close; 
	function = (cof1 * initial * initial) + (cof2 * initial) + cof3;
	
	printf("x3 \t %.4lf \t %.4lf \t %.4lf	\n",initial,function,difference);
	
	/*Step 4 is same as Step 1*/

	der_func = (2 * cof1* initial) + cof2;	
	initial = initial - (function / der_func);
	difference = initial - root_close; 
	function = (cof1 * initial * initial) + (cof2 * initial) + cof3;
	
	printf("x4 \t %.4lf \t %.4lf \t %.4lf	\n",initial,function,difference);
	
	/*Step 5 is same as Step 1*/

	der_func = (2 * cof1* initial) + cof2;	
	initial = initial - (function / der_func);
	difference = initial - root_close; 
	function = (cof1 * initial * initial) + (cof2 * initial) + cof3;
	
	printf("x5 \t %.4lf \t %.4lf \t %.4lf	\n",initial,function,difference);	
}


int find_multiple_closest(int a, int b){

	int division, /*to find division of a by b*/
		division_up, /*to find next multiple*/
		close = 0; /*to find closest value*/

	division = a / b; /*Find the answer of (a/b) as an integer*/
	division_up = division + 1; /*Add 1 to the answer you find as an integer*/

	if(a%b==0){ 
	/*If there is no remain when (a/b),
	return a*/
		return a;
	}
	else{
	/*If there is a remain when (a/b),
	multiply division and b and multiply division_up and b.
	Then, subtract these values from a and get the absolute value.*/
		if(abs(a-(division*b)) >= abs((division_up*b)-a)){
			/*The closest value will be (division_up*b)*/
			close = division_up * b;
		}
		else{
			/*The closest value will be (division*b)*/
			close = division * b;
		}
	return close;
	}
}