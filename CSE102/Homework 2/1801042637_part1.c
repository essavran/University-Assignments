/* In this code, I used "math.h" library. 
So, when you compile the code, please add "-lm".
Try this commands:

$ gcc -c 1801042637_part1.c
$ gcc 1801042637_part1.o -o 1801042637_part1 -lm
$ ./1801042637_part1

Thank you. */

#include <stdio.h> /*printf,scanf definitions*/
#include <math.h> /*sqrt() function*/

/*Functions are defined to be called in the main function*/
int draw_triangle(int side1, int side2, int side3);
void type_triangle(int side1, int side2, int side3);
int perimeter_triangle(int side1, int side2, int side3);
double area_triangle(int side1, int side2, int side3, int perimeter);

void main(){
	
	int side1, side2, side3, /*input - sides of triangle*/
		determination, /*value which is turned from function*/
		perimeter; /*value which is turned from function*/

	/*Get the sides of triangle*/
	printf("The length of first side:\n");
	scanf("%d",&side1);
	printf("The length of second side:\n");
	scanf("%d",&side2);
	printf("The length of third side:\n");
	scanf("%d",&side3);
	/*Function is called to determine whether the triangle can be drawn*/
	determination = draw_triangle(side1, side2, side3);
	/*There is an if statement 
	because of to determine what to program do by the value from the function*/
	if(determination == 0){
		printf("\nAccording to the triangle inequality theorem, this triangle cannot be drawn.\n");
	}
	else if(determination == 1){
		printf("\nAccording to the triangle inequality theorem, this triangle can be drawn.\n");
		/*Function is called to determine whether the type of triangle*/
		type_triangle(side1, side2, side3);
		/*Function is called to calculate the perimeter of triangle*/
		perimeter = perimeter_triangle(side1, side2, side3);
		/*Print the perimeter*/
		printf("The perimeter of the triangle: %d\n",perimeter);
		/*Function is called to calculate the area of triangle and print it*/
		printf("The area of the triangle: %lf\n", area_triangle(side1, side2, side3, perimeter));
	}
}

int draw_triangle(int side1, int side2, int side3){
	
	/*"The Triangle Inequality Theorem states that 
	the sum of any 2 sides of a triangle must be 
	greater than the measure of the third side."*/

	int turning; /*to determine the value which is turned*/

	if(	( ( (side1 + side2) > side3 ) && ( (side2 + side3) > side1 ) ) 
			&& 
		( ( (side2 + side3) > side1 ) && ( (side1 + side3) > side2 ) ) ){

		turning = 1;
	}
	else {
		turning = 0;
	}
	return turning;
}

void type_triangle(int side1, int side2, int side3){ 
	/*To determine whether the type of triangle*/
	if( (side1 == side2)
		&&
		(side2 == side3) ){
		printf("\nIt is an Equilateral Triangle.\n");
	}
	else if(
		((side1 == side2) && (side1 != side3))
		||
		((side1 == side3) && (side1 != side2))
		||
		((side2 == side3) && (side1 != side2))
		){
		printf("\nIt is an Isosceles Triangle.\n");
	}
	else{
		printf("\nIt is a Scalene Triangle.\n");
	}
}

int perimeter_triangle(int side1, int side2, int side3){
	/*To calculate the perimeter of triangle*/
	return (side1 + side2 + side3);
}

double area_triangle(int side1, int side2, int side3, int perimeter){
	/* Area = (p*(p-a)*(p-b)*(p-c))^1/2
	p=(perimeter)/2 */
	double half_perimeter, /*p*/
		   square, /*To value which write into the square root function*/
		   area; /*To return the value*/

	half_perimeter = ((double)perimeter) / 2.0; 
	square = half_perimeter * (half_perimeter - side1) * (half_perimeter - side2) * (half_perimeter - side3);
	area = sqrt(square);
	return area;
}
