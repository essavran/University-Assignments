#include <stdio.h> /*printf,scanf definitions*/
/*Functions are defined to be called in the main and other functions*/
int length (int a); /*to find length of any number*/
int compare_length (int a, int b); /*to compare lengths of two numbers*/
int is_binary (int a, int b); /*to check if the integers are binary or not*/
int power_10 (int a); /*to calculate 10^a*/
int andop (int a, int b); /*to implement logical AND operation on two integers*/

void main(){
	int a, b, /*inputs - two integers*/
		length, /*value to be returned from the compare_length function*/
		binary; /*value to be returned from the is_binary function*/
	printf("First integer:\n"); /*Get the first integer*/
	scanf("%d",&a);
	printf("Second integer:\n"); /*Get the second integer*/
	scanf("%d",&b);
	length = compare_length(a,b); /*The function is called*/
	binary = is_binary(a,b); /*The function is called*/
	do{ /*If lengths are not same or integers are not binary, do these*/
		if( (length==0) && (binary==1) ){ /*The lengths are not same but integers are binary*/
			printf("Integers should have the same length, please enter 2 new integers.\n");
			printf("First integer:\n");
			scanf("%d",&a);
			printf("Second integer:\n");
			scanf("%d",&b);
			length = compare_length(a,b);
			binary = is_binary(a,b);
		}
		else if( (length==1) && (binary==0) ){ /*The lengths are same but integers are not binary*/
			printf("Integers should be binary, please enter 2 new integers.\n");
			printf("First integer:\n");
			scanf("%d",&a);
			printf("Second integer:\n");
			scanf("%d",&b);
			length = compare_length(a,b);
			binary = is_binary(a,b);
		}
		else if( (length==0) && (binary==0) ){ /*The lengths are not same and integers are not binary*/
			printf("Integers should have the same length, please enter 2 new integers.\n");
			printf("Integers should be binary, please enter 2 new integers.\n");
			printf("First integer:\n");
			scanf("%d",&a);
			printf("Second integer:\n");
			scanf("%d",&b);
			length = compare_length(a,b);
			binary = is_binary(a,b);
		}
	} while( (length != 1) || (binary != 1) );
	printf("%d AND %d = %d\n",a,b,andop(a,b));/*Called the andop function and printed the answer*/
}

int length(int a){
	int length_a=1;
	while(a>=10){
		a /= 10;
		length_a++;
	}
return (length_a);/*to return the length*/
}

int compare_length(int a, int b){
	int length_a,/*to find length of the first integer*/
		length_b,/*to find length of the second integer*/
		turning;/*to determine the value which is turned*/
	length_a = length(a);/*length of the first integer*/
	length_b = length(b);/*length of the second integer*/

	if(length_a == length_b){/*The lengths are same*/
		turning = 1;/*Function returns 1*/
	}
	else{/*The lengths are not same*/
		turning = 0;/*Function returns 0*/
	}
return(turning);
}

int is_binary (int a, int b){
	int length_a,/*to find (length-1) of the first integer*/
		count_a=-1,/*to check the loop*/
		check_a=1,/*to check if "a" is binary or not*/
		length_b,/*to find (length-1) of the second integer*/
		count_b=-1,/*to check the loop*/
		check_b=1,/*to check if "b" is binary or not*/
		turning;/*to determine the value which is turned*/

	length_a = length(a)-1;
	length_b = length(b)-1;

	while(length_a != count_a){
		if( ((a%10)>=2)	|| ((a%10)<0) ){ /*Remainder is not 1 or 0*/
			check_a = 0; /*"a" is not binary*/
			count_a = length_a; /*to finish the loop*/
		}
		else{ /*Remainder is 1 or 0*/
			count_a++; /*to check the loop*/
			a /= 10; /*"a" is an integer of (a/10)*/
		}
	}

	while(length_b != count_b){
		if( ((b%10)>=2) || ((b%10)<0) ){ /*Remainder is not 1 or 0*/
			check_b = 0; /*"b" is not binary*/
			count_b = length_b; /*to finish the loop*/
		}
		else{ /*Remainder is 1 or 0*/
			count_b++; /*to check the loop*/
			a /= 10; /*"b" is an integer of (b/10)*/
		}
	}
	if( (check_a != 0) && (check_b != 0) ){/*"a" and "b" are binary numbers*/
		turning = 1;/*the function returns 1*/
	}
	else{ /*"a" or "b" are not binary numbers*/
		turning = 0;/*the function returns 0*/
	}
return (turning);
}

int power_10 (int a){/*to calculate 10^a*/
	int count = 0,
		answer = 1;
	while(count != a){
		answer *= 10;
		count++;
	}
return(answer);
}

int andop (int a, int b){
	int	length_a,/*to find length of "a"*/
		power_a,
		answer_a,
		quotient_a,
		length_b,/*to find length of "b"*/
		power_b, 
		answer_b,
		quotient_b,
		answer,
		check;
	length_a = length(a);/*Finds length of "a"*/
	length_b = length(b);/*Finds length of "b"*/
	answer = power_10(length_a-1);/*Because of lengths of "a" and "b", only length of "a" is used*/
	/*Controls the digits individually 
	by starting from the left and skipping the first digit
	(Because the first digit is always assumed to be 1).
	This is done for both numbers.*/
	while(length_a != 1){
		check=2;
		/*For "a"*/
		power_a = power_10(length_a-check);
		quotient_a = a / power_a;
		answer_a = quotient_a % 10;
		/*For "b"*/
		power_b = power_10(length_b-check);
		quotient_b = b / power_b;
		answer_b = quotient_b % 10;
		/*1 AND 1 = 1 but in other cases, the answer is always 0.*/
		if( (answer_a==1) && (answer_b==1) ){/*1 AND 1*/
			answer += power_a;
		}
		else{/*other cases*/
			answer = answer;
		}
	length_a--;
	length_b--;
	check++;
	}
	return (answer);
}