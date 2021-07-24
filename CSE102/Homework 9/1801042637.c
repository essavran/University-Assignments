#include <stdio.h>/*Standart input output library*/
#include <string.h>/*strlen() functions*/
#include <stdlib.h>/*srand() and rand() functions*/
#include <time.h>/*time(NULL) function*/

/*Functions and structs are defined to be used in the main and other functions*/

struct Hospital {
	char* name;
	char citiesServed[3];
};

struct card {
	const char *face;
	const char *suit;
};

int numPathsHome(int street, int avenue);/*To return the number of paths Cin Ali could take back to the origin from the specified starting position*/
int canOfferCovidCoverage(char _cities[6], char _locations[4][4], int _numHospitals, struct Hospital results[4]);/*To return whether or not it is possible to provide coverage to all cities using the limited number of hospitals*/
void findDesk(struct card desk, const char suits[4][10], const char faces[13][10]);/*To print the elements of the mixed deck randomly*/
int checkServed(char _cities[6], char letterArray[6], char letter); /*To check if the city has been found before*/

int location_row = 0,
	check = 0,
	row = 0,
	count = 0;

void main(){

	int choice, /*Input - User's choice*/
		street, /*Input - Street*/
		avenue, /*Input - Avenue*/
		_numHospitals; /*Input - Maximum number of hospitals that can be constructed*/


	char _locations[4][4] = { {'A', 'B', 'C', '\0'}, {'A', 'C', 'D', '\0'}, {'B', 'F','\0'}, {'C', 'E', 'F', '\0'} },
		 _cities[6] = { 'A', 'B', 'C', 'D', 'E', 'F'};

	const char suits[4][10] = { "Hearts", "Diamonds", "Clubs", "Spades" },
			   faces[13][10] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

	struct Hospital results[4];
	struct card desk;
	
	srand(time(NULL));

	do{
		printf("\n\nPlease chose one of the parts to continue:\n");
		printf("\n1) Execute Part 1\n2) Execute Part 2\n3) Execute Part 3\n4) Exit\n");
		scanf("%d", &choice);
		switch(choice){
			case 1:

				printf("\nEnter the street number: ");
				scanf("%d", &street);
				printf("street: %d\n", street);
				printf("Enter the avenue number: ");
				scanf("%d", &avenue);
				printf("avenue: %d\n", avenue);

				while(street > 5 || avenue > 5 || street < 1 || avenue < 1){ /*Invalid values*/
					printf("\nInvalid values.\n");
					printf("\nEnter the street number: ");
					scanf("%d", &street);
					printf("street: %d\n", street);
					printf("Enter the avenue number: ");
					scanf("%d", &avenue);
					printf("avenue: %d\n", avenue);
				}

				if(street == 1 && avenue == 1){
					printf("\nYou are at home.");
				}
				else{
					printf("\nNumber of optimal paths to take back home: %d", numPathsHome(street,avenue));
				}
				break;

			case 2:
				
				printf("\nEnter the maximum number of hospitals that can be constructed: ");
				scanf("%d", &_numHospitals);

				while( _numHospitals > 4 || _numHospitals < 1){
					printf("\nPlease enter a valid value(Between 1 and 4): ");
					scanf("%d", &_numHospitals);
				}

				count=0;
				location_row=0;	

				if( canOfferCovidCoverage(_cities, _locations, _numHospitals, results) ){
			
					printf("\nYes, you can offer health care to all!\n\n");
					
					for(int i = 0; i<_numHospitals; i++){
						printf("Hospital - %d\n",i );
						for(int m=0; m<3; m++){
							printf("%c",results[i].citiesServed[m] );
						}
						printf("\n");
					}

				}

				else{
					printf("\nNo, some cities are not covered.\n");
				}
				break;

			case 3:

				findDesk(desk, suits, faces);
				break;

			case 4:

				printf("\nGOODBYE!\n");
				break;

			default:

				printf("\nPlease enter a valid value.\n"); 
				break;

		}
	}while(choice != 4);
}

int numPathsHome(int street, int avenue){
	
	/*
	For example:

		1) street = 5 and avenue = 5
		
			1   1   1   1  1
			5   4   3   2  1
			15  10  6   3  1
			35  20  10  4  1
			70  35  15  5  1
			
			The answer is 70.

		2) street = 3 and avenue = 4

			1   1   1   1
			4   3   2   1
			10  6   3   1

			The answer is 10.
	*/

	if (street == 1 || avenue == 1) {
		return 1;
	}

    return (numPathsHome(street-1, avenue) + numPathsHome(street, avenue-1));

}

int canOfferCovidCoverage(char _cities[6], char _locations[4][4], int _numHospitals, struct Hospital results[4]){

	char letterArray[7] = {'\0'},
		 letter;
	int flag;
	
	row = 0;
	check = 0; 
	count++;	

	while( (check < _numHospitals) && (location_row < 4) ){
		
		for(int i=0; _locations[location_row][i] != '\0'; i++){

			for(int j=0; j<6; j++){

				if( _cities[j] == _locations[location_row][i] ){
					letter = _cities[j];

					if( checkServed(_cities,letterArray,letter) ){
						letterArray[row] = letter;
						row++;
					}
				}
			}
		}
		location_row++;
		check++;
	}
	
	flag = count-1;

	if( check == _numHospitals ){

		if( strlen(letterArray) == 6 ){	/*All cities found*/

			for(int i=0; i<_numHospitals; i++){

				for(int m=0; m<3; m++){
					results[i].citiesServed[m]=_locations[flag][m];
				}
				flag++;
			}	
			return 1;
		}

		else {

			if(_numHospitals == 2){
				location_row--;
			}
			else if(_numHospitals == 3){
				location_row-=2;
			}

			return (canOfferCovidCoverage(_cities,_locations,_numHospitals,results));
		}
	}

	else{
		return 0;
	}	
}

int checkServed(char _cities[6], char letterArray[6], char letter){
	
	int counter = 0;

	for(int i=0; i<6; i++){
		if( letterArray[i] != letter){
			counter++;
		}
	}
/*Returns 1 if the city did not find before, 0 if it found*/
	if(counter == 6){
		return 1;
	}
	else{
		return 0;
	}
}

void findDesk(struct card desk, const char suits[4][10], const char faces[13][10]){

	int random[4][13] = {0}, /*To keep 52 different numbers*/
		count=0,/*To check 52*/
		random_suit, /*To keep random numbers*/
		random_face; /*To keep random numbers*/

	srand(time(NULL));

	while( count != 52 ){

		random_suit = rand()%4;
		random_face = rand()%13;

		while( random[random_suit][random_face] == 1 ){ /*There is same value*/
			random_suit = rand()%4;
			random_face = rand()%13;
		}
		
		random[random_suit][random_face] = 1;

		count++;
		desk.suit = suits[ random_suit ];
		desk.face = faces[ random_face ];

		
		printf("%7s of %s\t", desk.face, desk.suit);

		if( count%2 == 0){
			printf("\n");
		}
	}

}

	
