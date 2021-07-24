/* In this code, "math.h" library is used. 
So, when you compile the code, please add "-lm".
Try this commands:

$ gcc -c 1801042637.c
$ gcc 1801042637.o -o 1801042637 -lm
$ ./1801042637

Thank you. */
#include <stdio.h> /*standart input output library*/
#include <string.h> /*strlen(), strcpy(), strcmp() functions*/
#include <stdlib.h> /*abs() functions*/
#include <math.h> /*pow(), sqrt(), acos() functions and M_PI */

#define STRING_SIZE 10
#define ARRAY_SIZE 100
#define LINES_SIZE 100
#define COMPONENT_SIZE 20 
#define ROW 500
#define COLUMN 200
#define NUMBER_COUNT 10
/*Functions and structures are defined to be called in the main and other functions*/
typedef struct {
	double x,
		   y;
	char name_point[STRING_SIZE];
} point;

typedef struct {
	point points_line[LINES_SIZE];
	char name_line[STRING_SIZE];
} line;

typedef struct {
	point points_poly[COMPONENT_SIZE];
	line lines_poly[COMPONENT_SIZE];
	char name_polygon[STRING_SIZE];
} polygon;

void read_input(char* file_path, char input[ROW][COLUMN]);/*to read all the information from the file*/
void read_data(char input[ROW][COLUMN], int count_array[NUMBER_COUNT], int flag, point *points, line *lines, polygon *polygons);/*to read all the data from the file*/
void read_actions(char input[ROW][COLUMN], int count_array[NUMBER_COUNT], int flag, point *points, line *lines, polygon *polygons);/*to read all the action from the file*/
char type_object(char input[ROW][COLUMN], int flag);/*to determine type of objects*/
double distance_points(char temp2[STRING_SIZE], char temp3[STRING_SIZE], int count_array[NUMBER_COUNT], point *points);/*to find distance between two points*/
double distance_lines(char temp2[STRING_SIZE], char temp3[STRING_SIZE], int count_array[NUMBER_COUNT], point *points, line *lines);/*to finds distance between a line and a point*/
double angle(char temp2[STRING_SIZE], char temp3[STRING_SIZE], int count_array[NUMBER_COUNT], point *points, line *lines);/*to find angle between two lines*/
double area(char temp2[STRING_SIZE], int count_array[NUMBER_COUNT], point *points, polygon *polygons);/*to find are of polygon*/
double length_line(char temp2[STRING_SIZE], int count_array[NUMBER_COUNT], line *lines);/*to find length of line*/
double length_polygon (char temp2[STRING_SIZE], int count_array[NUMBER_COUNT], point *points, polygon *polygons);/*to find length of polygon*/

void main(){
	
	char input[ROW][COLUMN] = {'\0'};/*all the inputs is in this array*/

	point points[ARRAY_SIZE];
	line lines[ARRAY_SIZE];
	polygon polygons[ARRAY_SIZE];

	int count_array[NUMBER_COUNT];/*to keep some counters*/

	read_input("commands.txt", input);

	for(int i=0; input[i][0] != '\0'; i++){		
		if( strcmp(input[i], "data") == 0 ){ /*there is "data"*/
			read_data(input, count_array, i+1, points, lines, polygons);
		}
		
		if( strcmp(input[i],"actions") == 0 ){ /*there is "actions"*/
			read_actions(input, count_array, i+1, points, lines, polygons);
		}	
	}
}

void read_input(char* file_path, char input[ROW][COLUMN]){

	int inp,/*To check EOF*/ 
	row = 0,
	column = 0;
	char c; /*to keep characters of the comment line temporarily*/

	FILE *fp = fopen(file_path,"r");
	
	if( fp == NULL){ /*the file does not exist*/
		printf("Error.\n");
	}
	else{
		inp = fscanf(fp, "%c", &input[row][column]);	
		do{
			if( input[row][column] == '/' ){
				column++;			
				fscanf(fp, "%c", &input[row][column]);

				if( input[row][column] == '/' ){ /*there is a comment line*/

					input[row][column] = '\0';
					input[row][column-1] = '\0';

					column-=2;
					fscanf(fp, "%c", &c);

					while(c != '\n' ){
							
						fscanf(fp, "%c", &c);
					} /*end of the comment line*/
					input[row][column] = c;
				}
			}
			
			if( input[row][column] == '\n' ){/*there is a new line*/
				input[row][column] = '\0';
				row++;
				column = 0;
				inp = fscanf(fp, "%c", &input[row][column]);
			}

			column++;			
			inp = fscanf(fp, "%c", &input[row][column]);

		}while( inp != EOF );
			
		fclose(fp);	
	
		for(int i=0; i<=row; i++){ /*remove \r and SPACE from the array */
			sscanf(input[i],"%[^\r]",input[i]);
			int j=(int)strlen(input[i])-1;

			while( (int)input[i][j] == 32 ){
				input[i][j] = '\0';
				j--;
			}
		}
	}
}

void read_data(char input[ROW][COLUMN], int count_array[NUMBER_COUNT], int flag, point *points, line *lines, polygon *polygons){

	int count=0,
		count_point=0,
		count_line=0,
		count_poly=0,
		count_poly_line=0,
		count_poly_point=0;
	char temp[20]={'\0'};
	
	sscanf(input[flag], "%d", &count);

	for(int i=0; i<count; i++){
		switch( type_object(input, flag+i+1) ){

			case 'P':/*there is a point*/
				sscanf(input[flag+i+1], "%lf %lf %s", &points[count_point].x, &points[count_point].y, points[count_point].name_point );
				count_point++;
				break;
			case 'L':/*there is a line*/
				sscanf(input[flag+i+1], "%s %s %s", lines[count_line].points_line[0].name_point, lines[count_line].points_line[1].name_point, lines[count_line].name_line );
				count_line++;
				break;
			case 'l': /*there is a polygon(lines)*/
				sscanf(input[flag+i+1], "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", 
					polygons[count_poly].lines_poly[0].name_line, polygons[count_poly].lines_poly[1].name_line,
					polygons[count_poly].lines_poly[2].name_line, polygons[count_poly].lines_poly[3].name_line, 
					polygons[count_poly].lines_poly[4].name_line, polygons[count_poly].lines_poly[5].name_line, 
					polygons[count_poly].lines_poly[6].name_line, polygons[count_poly].lines_poly[7].name_line, 
					polygons[count_poly].lines_poly[8].name_line, polygons[count_poly].lines_poly[9].name_line, 
					polygons[count_poly].lines_poly[10].name_line, polygons[count_poly].lines_poly[11].name_line, 
					polygons[count_poly].lines_poly[12].name_line, polygons[count_poly].lines_poly[13].name_line, 
					polygons[count_poly].lines_poly[14].name_line, polygons[count_poly].lines_poly[15].name_line, 
					polygons[count_poly].lines_poly[16].name_line, polygons[count_poly].lines_poly[17].name_line, 
					polygons[count_poly].lines_poly[18].name_line, polygons[count_poly].lines_poly[19].name_line,
					polygons[count_poly].name_polygon);
	
				if( ((strlen(input[flag+i+1])+1)/4) < 21 ){
					strcpy(temp, polygons[count_poly].lines_poly[((strlen(input[flag+i+1])+1)/4)-1].name_line);
					strcpy(polygons[count_poly].lines_poly[((strlen(input[flag+i+1])+1)/4)-1].name_line, "\0");
					strcpy(polygons[count_poly].name_polygon, temp );
				}

				count_poly++;
				count_poly_line++;
				break;
			case 'p': /*there is a polygon(points)*/
				sscanf(input[flag+i+1], "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", 
					polygons[count_poly].points_poly[0].name_point, polygons[count_poly].points_poly[1].name_point,
					polygons[count_poly].points_poly[2].name_point, polygons[count_poly].points_poly[3].name_point, 
					polygons[count_poly].points_poly[4].name_point, polygons[count_poly].points_poly[5].name_point, 
					polygons[count_poly].points_poly[6].name_point, polygons[count_poly].points_poly[7].name_point, 
					polygons[count_poly].points_poly[8].name_point, polygons[count_poly].points_poly[9].name_point, 
					polygons[count_poly].points_poly[10].name_point, polygons[count_poly].points_poly[11].name_point, 
					polygons[count_poly].points_poly[12].name_point, polygons[count_poly].points_poly[13].name_point, 
					polygons[count_poly].points_poly[14].name_point, polygons[count_poly].points_poly[15].name_point, 
					polygons[count_poly].points_poly[16].name_point, polygons[count_poly].points_poly[17].name_point, 
					polygons[count_poly].points_poly[18].name_point, polygons[count_poly].points_poly[19].name_point,
					polygons[count_poly].name_polygon);
				
				if( ((strlen(input[flag+i+1]))/3) < 21 ){
					strcpy(temp, polygons[count_poly].points_poly[((strlen(input[flag+i+1]))/3)-1].name_point);
					strcpy(polygons[count_poly].points_poly[((strlen(input[flag+i+1]))/3)-1].name_point, "\0");
					strcpy(polygons[count_poly].name_polygon, temp );
				}

				count_poly++;
				count_poly_point++;
				break;
			case 'E': /*something is wrong. for example, there is empty line*/
				break;
		}
	}

	for(int count=0; count<count_line; count++){/*to fill elements of lines[]*/
		for(int i=0; i<2; i++){
			for(int j=0; j<count_point; j++){
				if( strcmp(lines[count].points_line[i].name_point, points[j].name_point) == 0 ){
					lines[count].points_line[i].x = points[j].x;
					lines[count].points_line[i].y = points[j].y;	
				}
			}
		}
	}
	for(int count=0; count<count_poly; count++){/*to fill elements of polygons[].lines_poly[]*/
		for(int i=0; i<20; i++){
			for(int j=0; j<count_line; j++){
				for(int k=0; k<1; k++){
					if( strcmp(lines[j].name_line, polygons[count].lines_poly[i].name_line) == 0 ){
						strcpy(polygons[count].lines_poly[i].points_line[0].name_point, lines[j].points_line[0].name_point);
						strcpy(polygons[count].lines_poly[i].points_line[1].name_point, lines[j].points_line[1].name_point);
						polygons[count].lines_poly[i].points_line[j].x = lines[j].points_line[k].x;
						polygons[count].lines_poly[i].points_line[j].y = lines[j].points_line[k].y;	
					}
				}
			}
		}
	}
	for(int count=0; count<count_poly; count++){/*to fill elements of polygons[].lines_poly[]*/
		for(int i=0; i<20; i++){
			for(int j=0; j<count_point; j++){
				for(int k=0; k<1; k++){
					if( strcmp(points[j].name_point, polygons[count].points_poly[i].name_point) == 0 ){
						polygons[count].points_poly[i].x = points[j].x;
						polygons[count].points_poly[i].y = points[j].y;	
					}
				}
			}
		}
	}
	/*counters are kept to use in other functions*/
	count_array[0] = count_point;
	count_array[1] = count_line;
	count_array[2] = count_poly;
	count_array[3] = count_poly_line;
	count_array[4] = count_poly_point;
}

void read_actions(char input[ROW][COLUMN], int count_array[NUMBER_COUNT], int flag, point *points, line *lines, polygon *polygons){

	char file_path[20] = {'\0'};
	char temp[STRING_SIZE] = {'\0'};
	int count=0,
		inp;
	char temp2[STRING_SIZE], temp3[STRING_SIZE];

	sscanf(input[flag], "%s", file_path);/*a file name indicating where the results of the actions will be output*/
	sscanf(input[flag+1], "%d", &count);
	
	FILE *fp = fopen(file_path,"w");	
	
	if( fp == NULL ){ /*the file could not be opened*/
		printf("Error.\n");
	}
	else{
		for(int i=0; i<count; i++){

			sscanf(input[flag+2+i], "%s", temp);

			if( strcmp( temp, "Distance" ) == 0 ){
				sscanf(input[flag+2+i], "%s %s %s", temp, temp2, temp3);
				switch( type_object(input, flag+2+i) ){
					case 'P':
						fprintf(fp, "%s(%s,%s) = %.1lf\n", temp, temp2, temp3, distance_points(temp2,temp3,count_array,points));
						break;
					case 'L':
						fprintf(fp, "%s(%s,%s) = %.1lf\n", temp, temp2, temp3, distance_lines(temp2,temp3,count_array,points,lines));
						break;
					default:
						break;
				}
			}

			if( strcmp( temp, "Angle" ) == 0 ){
				sscanf(input[flag+2+i], "%s %s %s", temp, temp2, temp3);
				fprintf(fp, "%s(%s,%s) = %.1lf\n", temp, temp2, temp3, angle(temp2, temp3, count_array, points, lines));
			} 
			
			if( strcmp( temp, "Length" ) == 0 ){
				sscanf(input[flag+2+i], "%s %s", temp, temp2);
				switch( type_object(input, flag+2+i) ){
					case 'L':
						fprintf(fp, "%s(%s) = %.1lf\n", temp, temp2, length_line(temp2, count_array, lines));
						break;	
					default:
						fprintf(fp, "%s(%s) = %.1lf\n", temp, temp2, length_polygon(temp2, count_array, points, polygons));
						break;
				}
			} 

			if( strcmp( temp, "Area" ) == 0 ){
				sscanf(input[flag+2+i], "%s %s", temp, temp2);
				fprintf(fp, "%s(%s) = %.1lf\n", temp, temp2, area(temp2, count_array, points, polygons));
			} 
		}
	}
	fclose(fp);
}


char type_object(char input[ROW][COLUMN], int flag){

	char c;
	int counter_p=0,
		counter_l=0,
		counter_pg=0;

	for(int i=0; input[flag][i] != '\0'; i++){
		if( input[flag][i] == 'P'){
			counter_p++;
		}
		if( input[flag][i] == 'L'){
			counter_l++;
		}
		if( input[flag][i] == 'P' && input[flag][i+1] == 'G'){
			counter_pg++;
		}
	}

	if( counter_pg != 0 ){ /*there is a polygon line*/
		if(counter_l > 0){ /*there is a polygon(with lines) line*/
			return 'l';
		}
		else if(counter_p > 0){/*there is a polygon(with points) line*/
			return 'p';
		}
		else{
			return 'E';
		}
	}
	else if( counter_l != 0 ){/*there is a line line*/
		return 'L';
	}
	else if( counter_p != 0){/*there is a point line*/
		return 'P';
	}
	else{
		return 'E';
	}
}

double distance_points(char temp2[STRING_SIZE], char temp3[STRING_SIZE], int count_array[NUMBER_COUNT], point *points){

	int count_point_1=0,
		count_point_2=0;
	double x[count_array[0]],y[count_array[0]]; 

	for(int i=0; i<count_array[0]; i++){
		if( strcmp(temp2,points[i].name_point) == 0 ){
			x[i] = points[i].x;
			y[i] = points[i].y;
			count_point_1 = i;
		}
		if( strcmp(temp3,points[i].name_point) == 0 ){
			x[i] = points[i].x;
			y[i] = points[i].y;
			count_point_2 = i;
		}
	}
	return sqrt( pow((x[count_point_2] - x[count_point_1]),2) + pow((y[count_point_2] - y[count_point_1]),2) );		
}

double distance_lines(char temp2[STRING_SIZE], char temp3[STRING_SIZE], int count_array[NUMBER_COUNT], point *points, line *lines){

	double x0[count_array[0]], y0[count_array[0]], x1[count_array[1]], x2[count_array[1]], y1[count_array[1]], y2[count_array[1]], length1, length2;
	double answer=0.0;
	int count2=0,
		count1=0,
		count0=0;

	for(int i=0; i<count_array[0]; i++){
		if( strcmp(temp2,points[i].name_point) == 0 ){
			x0[i] = points[i].x;
			y0[i] = points[i].y;
			count0 = i;
		}
	}
	for(int i=0; i<count_array[1]; i++){
		if( strcmp(temp3, lines[i].name_line ) == 0 ){
			x1[i] = lines[i].points_line[0].x;
			y1[i] = lines[i].points_line[0].y;
			x2[i] = lines[i].points_line[1].x;
			y2[i] = lines[i].points_line[1].y;
			count1=i;
		}
	}
	answer = (double)abs( ( (y2[count1]-y1[count1])*x0[count0] ) - ( (x2[count1]-x1[count1])*y0[count0] ) + ( x2[count1]*y1[count1] ) - ( y2[count1]*x1[count1] ) );
	return answer/ sqrt( pow( y2[count1]-y1[count1], 2) + pow( x2[count1]-x1[count1], 2) );
}

	
double angle(char temp2[STRING_SIZE], char temp3[STRING_SIZE], int count_array[NUMBER_COUNT], point *points, line *lines){

	double x[count_array[1]], y[count_array[1]], x1[count_array[1]], x2[count_array[1]], y1[count_array[1]], y2[count_array[1]], length1, length2;
	double answer;
	int count2=0,
		count3=0,
		count=0;
	
	for(int i=0; i<count_array[1]; i++){
		if( strcmp(temp2, lines[i].name_line ) == 0 ){
			count2=i;
			count++;
		}
		if( strcmp(temp3, lines[i].name_line ) == 0 ){
			count3=i;
			count++;
		}
		if(count == 2){
			x1[count2] = lines[count2].points_line[0].x;
			y1[count2] = lines[count2].points_line[0].y;
			x2[count2] = lines[count2].points_line[1].x;
			y2[count2] = lines[count2].points_line[1].y;
			x[count2] = x2[count2] - x1[count2];
			y[count2] = y2[count2] - y1[count2];

			x1[count3] = lines[count3].points_line[0].x;
			y1[count3] = lines[count3].points_line[0].y;
			x2[count3] = lines[count3].points_line[1].x;
			y2[count3] = lines[count3].points_line[1].y;
			x[count3] = x2[count3] - x1[count3];
			y[count3] = y2[count3] - y1[count3];

			length1 = length_line(temp2,count_array,lines);
			length2 = length_line(temp3,count_array,lines);
			answer = ((x[count3] * x[count2]) + (y[count3] * y[count2])) / (length1 * length2);
			answer = acos(answer) * 180 / M_PI;
			if(answer == 180){
				answer = 0;
			}
			return answer;
		}
	}
}

double length_line(char temp2[STRING_SIZE], int count_array[NUMBER_COUNT], line *lines){
	
	int count=0,
		count_polypoint=0,
		count_polyline=0;
	double x1[count_array[0]],y1[count_array[0]]; 
	double x2[count_array[0]],y2[count_array[0]];
	double length_object = 0.0;

	for(int i=0; i<count_array[1]; i++){
		if( strcmp(temp2, lines[i].name_line ) == 0 ){
			x1[i] = lines[i].points_line[0].x;
			y1[i] = lines[i].points_line[0].y;
			x2[i] = lines[i].points_line[1].x;
			y2[i] = lines[i].points_line[1].y;
			count=i;
		}	
	}
	return sqrt( pow((x2[count] - x1[count]),2) + pow((y2[count] - y1[count]),2) );
}

double length_polygon (char temp2[STRING_SIZE], int count_array[NUMBER_COUNT], point *points, polygon *polygons){
	
	int count=0,
		count_polypoint=0,
		count_polyline=0;
	double x1[count_array[0]],y1[count_array[0]]; 
	double x2[count_array[0]],y2[count_array[0]];
	double length_object = 0.0;

	for(int i=0; i<count_array[2]; i++){
		if( strcmp(temp2, polygons[i].name_polygon) == 0 ){
			if( polygons[i].points_poly[0].name_point[0] == 'P' ){
				for(int j=0; j<20; j++){
					if( polygons[i].points_poly[j].name_point[0] == 'P' ){
						count_polypoint++;
					}
				}
				for(int j=0; j<count_polypoint-1; j++){ 
					length_object += distance_points(polygons[i].points_poly[j].name_point,polygons[i].points_poly[j+1].name_point, count_array, points);
				}
				length_object += distance_points(polygons[i].points_poly[count_polypoint-1].name_point,polygons[i].points_poly[0].name_point, count_array, points);
				return length_object;
			}
			else if( polygons[i].lines_poly[0].name_line[0] == 'L' ){
				for(int j=0; j<20; j++){
					if( polygons[i].lines_poly[j].name_line[0] == 'L' ){
						count_polyline++;
					}
				}
				for(int j=0; j<count_polyline; j++){
					length_object += distance_points(polygons[i].lines_poly[j].points_line[0].name_point, polygons[i].lines_poly[j].points_line[1].name_point, count_array, points);
				}
				return length_object;
			}
		}
	}
}

double area(char temp2[STRING_SIZE], int count_array[NUMBER_COUNT], point *points, polygon *polygons){
	
	int count=0,
		count_polypoint=0,
		count_polyline=0;
	double x1[count_array[0]],y1[count_array[0]]; 
	double x2[count_array[0]],y2[count_array[0]];
	int arr_points[25] = {-1};
	double area_object = 0.0;

	for(int i=0; i<count_array[2]; i++){
		if( strcmp(temp2, polygons[i].name_polygon ) == 0 ){
			if( polygons[i].points_poly[0].name_point[0] == 'P' ){
				for(int j=0; j<20; j++){
					if( polygons[i].points_poly[j].name_point[0] == 'P' ){
						count_polypoint++;
					}
				}
				for(int j=0; j<count_polypoint-1; j++){
					area_object += (polygons[i].points_poly[j].x * polygons[i].points_poly[j+1].y)-(polygons[i].points_poly[j].y * polygons[i].points_poly[j+1].x);
				}
				area_object += (polygons[i].points_poly[count_polypoint-1].x * polygons[i].points_poly[0].y)-(polygons[i].points_poly[count_polypoint-1].y * polygons[i].points_poly[0].x);
				return (double)abs(area_object)/2.0;
			}

			else if( polygons[i].lines_poly[0].name_line[0] == 'L' ){
				for(int j=0; j<20; j++){
					if( polygons[i].lines_poly[j].name_line[0] == 'L' ){
						count_polyline++;
					}
				}
				for(int j=0; j<20; j++){
					for(int m=0; m<2; m++){
						for(int k=0; k<count_array[0]; k++){
							if( strcmp(polygons[i].lines_poly[j].points_line[m].name_point, points[k].name_point) == 0 ){
								if(arr_points[k-1] != k){
									arr_points[k] = k;
								}
							}
						}
					} 
				}
				for(int j=0; j<count_polyline-1; j++){
					area_object += (points[j].x *  points[j+1].y)-( points[j].y *  points[j+1].x);
				}
				area_object += (points[count_polyline-1].x *  points[0].y)-( points[count_polyline-1].y *  points[0].x);
				return (double)abs(area_object)/2.0;
			}
		}	
	}
}