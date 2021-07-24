#include <stdio.h> /*printf,scanf definitions*/

int main(){

	double amount; /*input - amount*/
	int select, /*input - selection*/
		select2, /*input - another selection*/
		i = 1; /*counter to check the value to be returned*/

	printf("***** Welcome to ABC Exchange Office *****\n");
	printf("Enter your amount\n");
	scanf("%lf",&amount); /*Get the amount*/

	printf("\nPlease select your currency\n");
	printf("1. Turkish Lira\n");
	printf("2. Euro\n");
	printf("3. Dollar\n");
	scanf("%d",&select);

	switch(select){ /*Type of currency*/
	    case 1:
            printf("You have %lf Turkish Liras\n",amount);
            break;

        case 2:
            printf("You have %lf Euro\n",amount);
            break;

        case 3:
            printf("You have %lf Dollars\n",amount);
            break;

	    default:
            printf("\nYour selection is invalid!\n");
            i--; /*now, i != 1*/
            break;
    }    
    /*There is an if statement to check the value to be returned*/
    if(i == 1){
	    printf("Choose which currency you want to convert\n");
	    scanf("%d",&select2);

		/*1 Euro = 6.69 Turkish Liras
		1 Dollar = 6.14 Turkish Liras
		and
		1 Euro = 1.09 Dollars*/

	    switch(select2){ /*Convert between currencies*/
		    case 1:
				switch(select){
		    		case 1:
		    			printf("\nYou have %lf Turkish Liras\n",amount);
		    			break;
		    		case 2:
		    			printf("\nYou have %lf Turkish Liras\n",(amount*6.69));
		    			break;
		    		case 3:
		               printf("\nYou have %lf Turkish Liras\n",(amount*6.14));
		               break;
		        }
				break;

	        case 2:
				switch(select){
		    		case 1:
		    			printf("\nYou have %lf Euro\n",(amount/6.69));
		    			break;
		    		case 2:
		    			printf("\nYou have %lf Euro\n",amount);
		    			break;
		    		case 3:
		               printf("\nYou have %lf Euro\n",(amount/1.09));
		               break;
		    	}
		    	break;

	        case 3:
				switch(select){
		    		case 1:
		    			printf("\nYou have %lf Dollars\n",(amount/6.14));
		    			break;
		    		case 2:
		    			printf("\nYou have %lf Dollars\n",(amount*1.09));
		    			break;
		    		case 3:
		               printf("\nYou have %lf Dollars\n",amount);
		               break;
		    	}
		    	break;

	        default:
	            printf("\nYour selection is invalid!\n");
	            i--; /*i == 0*/
	            break;
	    }
	}
	else{
	i = 0;
	}
return (i);
}