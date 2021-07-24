#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "vectorlib.h"
#include <string.h>

#define LINES_DEFAULTS 9

typedef struct Grid {
	double  r, g, b,
			thickness,
			tile_size;
	int show_grid; /* 1 or 0 */
} Grid;

typedef struct Pattern {
	double  r, g, b,
			thickness,
			angle,
			offset;
} Pattern;

typedef struct Canvas {
	double  r, g, b,
			width,
			height;

} Canvas;

typedef struct Type {
	int archetype; /* 4 or 6 */
	char * file_name;
} Type; 

void read_defaults(Grid * grid_default, Pattern * pattern_default, Canvas * canvas_default);
void read_commands(Grid * grid_default, Pattern * pattern_default, Canvas * canvas_default);
void draw_command(Grid * grid, Pattern * pattern, Canvas * canvas, Type * type);

int main(){
	Grid * grid_default = (Grid *)malloc(sizeof(Grid));
	Pattern * pattern_default = (Pattern *)malloc(sizeof(Pattern)); 
	Canvas * canvas_default = (Canvas *)malloc(sizeof(Canvas));
	printf("\n---------------------------------------\n");
	read_defaults(grid_default, pattern_default, canvas_default);
	read_commands(grid_default, pattern_default, canvas_default);

	printf("\nIt's done. Goodbye!\n---------------------------------------\n\n");
	return 0;
}

void read_defaults(Grid * grid_default, Pattern * pattern_default, Canvas * canvas_default){
	char c;
	char ** data;
	int index = 0,
		newline_counter = 0;
	FILE * fp = fopen("defaults.txt", "r");

	while( newline_counter <= LINES_DEFAULTS ){ 
		fscanf(fp, "%c", &c);
		if( c == '/' ){	
			fscanf(fp, "%c", &c);
			if(c == '/'){
				while( c != '\n' ){
					fscanf(fp, "%c", &c);
				}
			}
		}
		if(c == '\n'){
				fscanf(fp, "%c", &c);
				data[newline_counter] = (char *)realloc(data[newline_counter], sizeof(char)*(index+1));
				data[newline_counter][index] = '\0';
				newline_counter++;
				index = 0;
		}

		if( newline_counter == 0 && index == 0)		data = (char **)malloc(sizeof(char *));
		else if( newline_counter != 0 && index == 0 )	data = (char **)realloc(data, sizeof(char *) * (newline_counter + 1));
		
		if( index == 0) 	data[newline_counter] = (char *)malloc(sizeof(char));
		else 	data[newline_counter] = (char *)realloc(data[newline_counter], sizeof(char)*(index+1));
		data[newline_counter][index] = c;
		index++;
	}

	char * string = (char *)malloc(sizeof(char *));
	char * p1, * p2;
	for(int i=0; i<newline_counter-1; i++){
		p1 = p2 = NULL;
		index = 0;
		*string = data[i][index];
		index++;
		while( data[i][index] != ':' ){
			string = (char *)realloc(string, sizeof(char)*(index+1));
			string[index] = data[i][index];
			index++;
		}
		string = (char *)realloc(string, sizeof(char)*(index+1));
		*(string + index) = '\0';
		
		if( !strcmp( "grid_color", string ) ){
			p1 = strtok(data[i], "(");
			*(p1 + index) = '\0';
			grid_default->r = strtod(strtok(NULL, ","), NULL) / 255.0;
			grid_default->g = strtod(strtok(NULL, ","), NULL) / 255.0;
			grid_default->b = strtod(strtok(NULL, ")"), NULL) / 255.0;
		}
		
		else if( !strcmp( "foreground_color", string ) ){
			p1 = strtok(data[i], "(");
			*(p1 + index) = '\0';
			pattern_default->r = strtod(strtok(NULL, ","), NULL) / 255.0;
			pattern_default->g = strtod(strtok(NULL, ","), NULL) / 255.0;
			pattern_default->b = strtod(strtok(NULL, ")"), NULL) / 255.0;
		}

		else if( !strcmp( "background_color", string ) ){
			p1 = strtok(data[i], "(");
			*(p1 + index) = '\0';
			canvas_default->r = strtod(strtok(NULL, ","), NULL) / 255.0;
			canvas_default->g = strtod(strtok(NULL, ","), NULL) / 255.0;
			canvas_default->b = strtod(strtok(NULL, ")"), NULL) / 255.0;
		}

		else if( !strcmp( "pattern_thickness", string ) ){
			p1 = strtok(data[i], ":");
			pattern_default->thickness = strtod(strtok(NULL, " \t"), NULL);
		}

		else if( !strcmp( "grid_thickness", string ) ){
			p1 = strtok(data[i], ":");
			*(p1 + index) = '\0';
			grid_default->thickness = strtod(strtok(NULL, " \t"), NULL);
		}

		else if( !strcmp( "tile_size", string ) ){
			p1 = strtok(data[i], ":");
			grid_default->tile_size = strtod(strtok(NULL, " \t"), NULL);
		}

		else if( !strcmp( "canvas_size", string ) ){
			p1 = strtok(data[i], "(");
			*(p1 + index) = '\0';
			canvas_default->width = strtod(strtok(NULL, ","), NULL);
			canvas_default->height = strtod(strtok(NULL, ")"), NULL);
		}

		else if( !strcmp( "show_grid", string ) ){
			p1 = strtok(data[i], ":");
			p2 = strtok(NULL, " \t");
			if( !strcmp( "False", p2 ) ) 	grid_default->show_grid = 0;
			else if( !strcmp( "True", p2 ) ) 	grid_default->show_grid = 1;
		}

		else if( !strcmp( "angle_offset", string ) ){
			p1 = strtok(data[i], "(");
			*(p1 + index) = '\0';
			pattern_default->angle = strtod(strtok(NULL, ","), NULL);
			pattern_default->offset = strtod(strtok(NULL, ")"), NULL);
		}
	}
	fclose(fp);
}

void read_commands(Grid * grid_default, Pattern * pattern_default, Canvas * canvas_default){
	char c;
	char ** data;
	int index = 0,
		newline_counter = 0;
	FILE * fp = fopen("commands.txt", "r");

	while( fscanf(fp, "%c", &c) != EOF ){ 	
		if( c == '/' ){
			fscanf(fp, "%c", &c);
			if(c == '/'){
				while( c != '\n' ){
					fscanf(fp, "%c", &c);
				}
			}
		}
		if(c == '\n'){
				fscanf(fp, "%c", &c);
				data[newline_counter] = (char *)realloc(data[newline_counter], sizeof(char)*(index+1));
				data[newline_counter][index] = '\0';
				newline_counter++;
				index = 0;
		}
		if( newline_counter == 0 && index == 0)		data = (char **)malloc(sizeof(char *));
		else if( newline_counter != 0 && index == 0 )	data = (char **)realloc(data, sizeof(char *) * (newline_counter + 1));
		
		if( index == 0) 	data[newline_counter] = (char *)malloc(sizeof(char));
		else 	data[newline_counter] = (char *)realloc(data[newline_counter], sizeof(char)*(index+1));
		data[newline_counter][index] = c;
		index++;
	}

	Grid * grid = (Grid *)malloc(sizeof(Grid));
	Pattern * pattern = (Pattern *)malloc(sizeof(Pattern)); 
	Canvas * canvas = (Canvas *)malloc(sizeof(Canvas));
	Type * temp3 = (Type *)malloc(sizeof(Type));

	char * string = (char *)malloc(sizeof(char *));
	char * p1, * p2;
	int flag = 0;

	for(int i=0; i<newline_counter; i++){
		flag = 0;
		index = 0;
		while( index <= strlen(data[i]) ){ //valid or invalid lines
				int count = 1;
				*string = data[i][index];
				index++;
			while( data[i][index] != ':' ){
				string = (char *)realloc(string, sizeof(char)*(index+1));
				string[count] = data[i][index];
				index++;			
				count++;
			}
			while( (data[i][index] > 'z' || data[i][index] < 'a') || data[i][index-1] != ',' && index <= strlen(data[i])){ 
				index++;				
			}
		string = (char *)realloc(string, sizeof(char)*(index+1));
		*(string + count) = '\0';
		if( !strcmp( "archetype", string) ) flag++;
		else if( !strcmp( "file_name", string ) ) flag++;
		}

		if( flag == 0 ) 	printf("!!! ERROR. No '%s' and '%s' at line %d.\n", "archetype", "file_name", i+1);
		else if( flag == 1 ) 	printf("!!! ERROR. No '%s' or '%s' at line %d.\n", "archetype", "file_name", i+1);
		else if( flag > 2 ) 		printf("!!! ERROR. Too many argument at line %d.\n", i+1);
		else{
			flag = 0;
			index = 0;
		int g_color = 0, p_color = 0, c_color = 0,
			g_thick = 0, p_thick = 0, t_size = 0,
			c_size = 0, s_grid = 0, a_offset = 0;
			while( index <= strlen(data[i]) ){ 
					int count = 1;
					*string = data[i][index];
					index++;
				while( data[i][index] != ':' ){
					string = (char *)realloc(string, sizeof(char)*(index+1));
					string[count] = data[i][index];
					index++;			
					count++;
				}
			string = (char *)realloc(string, sizeof(char)*(index+1));
			*(string + count) = '\0';
			char * temp;
			int temp_count = 0;
			if( !strcmp( "grid_color", string ) ){
				g_color = 1;
				index += 2;
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				grid->r = strtod(temp, NULL) / 255.0;

				temp_count = 0;
				index++;
				free(temp);
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				grid->g = strtod(temp, NULL) / 255.0;

				temp_count = 0;
				index++;
				free(temp);				
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				grid->b = strtod(temp, NULL) / 255.0;
				temp_count = 0;
				index++;
				free(temp);
			}
			
			else if( !strcmp( "foreground_color", string ) ){
				p_color = 1;
				index += 2;
				temp_count = 0;				
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				pattern->r = strtod(temp, NULL) / 255.0;

				temp_count = 0;
				index++;
				free(temp);
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				pattern->g = strtod(temp, NULL) / 255.0;

				temp_count = 0;
				index++;
				free(temp);				
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				pattern->b = strtod(temp, NULL) / 255.0;

				temp_count = 0;
				index++;
				free(temp);	
			}
				
			else if( !strcmp( "background_color", string ) ){
				c_color = 1;
				index += 2;
				
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				canvas->r = strtod(temp, NULL) / 255.0;

				temp_count = 0;
				index++;
				free(temp);
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				canvas->g = strtod(temp, NULL) / 255.0;

				temp_count = 0;
				index++;
				free(temp);				
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				canvas->b = strtod(temp, NULL) / 255.0;
				temp_count = 0;
				index++;
				free(temp);	
			}
			
			else if( !strcmp( "pattern_thickness", string ) ){
				p_thick = 1;
				index++;
				temp_count = 0;				
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				pattern->thickness = strtod(temp, NULL);

				free(temp);
				index++;
			}

			else if( !strcmp( "grid_thickness", string ) ){
				g_thick = 1;
				index++;
				temp_count = 0;	
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				grid->thickness = strtod(temp, NULL);
				free(temp);
				index++;
			}

			else if( !strcmp( "tile_size", string ) ){
				temp_count = 0;				
				t_size = 1;
				index++;
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				grid->tile_size = strtod(temp, NULL);
				free(temp);
				index++;
			}

			else if( !strcmp( "canvas_size", string ) ){
				c_size = 1;
				index += 2;
				temp_count = 0;
		
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				canvas->width = strtod(temp, NULL);
				temp_count = 0;
				index++;
				free(temp);
				while( data[i][index] != ')' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';

				canvas->height = strtod(temp, NULL);

				temp_count = 0;
				index++;
				index++;
				free(temp);
			}

			else if( !strcmp( "show_grid", string ) ){
				s_grid = 1;
				index++;
				temp_count = 0;
				
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				if( !strcmp( "False", temp ) ) 	grid->show_grid = 0;
				else if( !strcmp( "True", temp ) ) 	grid->show_grid = 1;
				free(temp);
				index++;
			}

			else if( !strcmp( "angle_offset", string ) ){
				a_offset = 1;
				index += 2;
				temp_count = 0;

				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				pattern->angle = strtod(temp, NULL);
				temp_count = 0;
				index++;
				free(temp);
				while( data[i][index] != ')' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				pattern->offset = strtod(temp, NULL);
				temp_count = 0;
				index++;
				index++;
				free(temp);
			}

			else if( !strcmp( "archetype", string ) ){
				index++;
				temp_count = 0;
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0){
					if(temp_count == 0)		temp = (char *)malloc(sizeof(char));
					else	temp = (char *)realloc(temp, sizeof(char) * (temp_count+1));
					*(temp + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp+temp_count) = '\0';
				if( !strcmp( "Hexagon", temp ) ) 	temp3->archetype = 6;
				else if( !strcmp( "Square", temp ) ) 	temp3->archetype = 4;
				free(temp);
				index++;
			}

			else if( !strcmp( "file_name", string ) ){
				index++;
				temp_count = 0;
				while( data[i][index] != ',' && data[i][index] != '\n' && data[i][index] != 0 && data[i][index] != ' '){
					if(temp_count == 0)		temp3->file_name = (char *)malloc(sizeof(char));
					
					else	temp3->file_name = (char *)realloc(temp3->file_name, sizeof(char) * (temp_count+1));

					*(temp3->file_name + temp_count) = data[i][index];
					temp_count++;
					index++;
				}
				*(temp3->file_name+temp_count) = '\0';

				index++;
			}
			}

			if( g_color != 1 ){
				grid->r = grid_default->r; grid->g = grid_default->g; grid->b = grid_default->b;
			}		
			if( p_color != 1 ){
				pattern->r = pattern_default->r; pattern->g = pattern_default->g; pattern->b = pattern_default->b;
			}		
			if( c_color != 1 ){
				canvas->r = canvas_default->r; canvas->g = canvas_default->g; canvas->b = canvas_default->b;
			}		
			if( g_thick != 1 )		grid->thickness = grid_default->thickness;
			if( p_thick != 1 )		pattern->thickness = pattern_default->thickness;
			if( t_size != 1 )		grid->tile_size = grid_default->tile_size;
			if( c_size != 1 ){
				canvas->width = canvas_default->width; canvas->height = canvas_default->height;
			}		
			if( s_grid != 1 )		grid->show_grid = grid_default->show_grid;
			if( a_offset != 1 ){
				pattern->angle = pattern_default->angle; pattern->offset = pattern_default->offset;
			}		
			draw_command(grid, pattern, canvas, temp3);
		}
	}
}

void draw_command(Grid * grid, Pattern * pattern, Canvas * canvas, Type * type){
	printf("-> '%s' is prepared...\n", type->file_name);
	/* Grid */
	Figure * fig1 = start_figure(canvas->width, canvas->height); //grid
	Color c1 = create_color(grid->r, grid->g, grid->b);
	set_color(fig1, c1);
	set_thickness_resolution(fig1, grid->thickness, 0.8);
	Point2D * poly_line1 = create_polygon(type->archetype, canvas->width, canvas->height, grid->tile_size, 0.0, 0.0);
	draw_polygon(fig1, poly_line1, (3*type->archetype) * ((canvas->width/grid->tile_size) * (canvas->height/grid->tile_size) + 1), type->archetype);	
	fig1->show = grid->show_grid;
	/* Pattern */
	Figure * fig2 = start_figure(canvas->width, canvas->height); //pattern
	Color c2 = create_color(pattern->r, pattern->g, pattern->b);
	set_color(fig2, c2);
	set_thickness_resolution(fig2, pattern->thickness, 0.8);
	Point2D * poly_line2 = create_polygon(type->archetype, canvas->width, canvas->height, grid->tile_size , pattern->angle, pattern->offset);
	draw_polygon(fig2, poly_line2, (3*type->archetype) * ((canvas->width/grid->tile_size) * (canvas->height/grid->tile_size) + 1), type->archetype);
	/* Canvas */
	Figure * fig3 = start_figure(canvas->width, canvas->height); //canvas
	Color c3 = create_color(canvas->r, canvas->g, canvas->b);
	set_color(fig3, c3);
	set_thickness_resolution(fig3, 0.0, 0.8);	
	Point2D * poly_line3 = create_polygon(1, canvas->width, canvas->height, 0.0, 0.0, 0.0);
	draw_polygon(fig3, poly_line3, 0, 1);
	/* Export */
	export_eps(fig1, fig2, fig3, type->file_name);
	printf("-> '%s' is ready.\n", type->file_name);
}