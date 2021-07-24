#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "vectorlib.h"

/*-----Creating Figure-----*/

Figure * start_figure(double width, double height){
	Figure * fig = (Figure *)malloc(sizeof(Figure));
	fig->width = width;
	fig->height = height;
	fig->xmin = -width/2;
	fig->ymin = -height/2;
	fig->xmax = width/2;
	fig->ymax = height/2;
	/*something extra*/
	fig->root = NULL;
	fig->lines = NULL;
	fig->point = NULL;
	fig->text_flag = 0;
	return fig;
}

void set_thickness_resolution(Figure * fig, double thickness, double resolution){
	fig->thickness = thickness;
	fig->resolution = resolution;
}

Color create_color(double r, double g, double b){
	Color c;
	c.red = r;
	c.green = g;
	c.blue = b;
	return c;
}

void set_color(Figure * fig, Color c){
	fig->c.red = c.red;
	fig->c.green = c.green;
	fig->c.blue = c.blue;
}

/*-----Creating Point2D-----*/

Point2D * start_point2d(double x, double y, int flag){
	Point2D * point = (Point2D *)malloc(sizeof(Point2D));
	point->x = x;
	point->y = y;
	point->flag = flag;
	point->next = NULL;
	return point;
}

void insert_end(Point2D * point, double x, double y, int flag) {
	Point2D * temp, * newpoint;
	temp = point;
	while (temp->next!=NULL) temp = temp->next;

	newpoint = (Point2D *) malloc(sizeof(Point2D));
	newpoint->x = x;
	newpoint->y = y;
	newpoint->flag = flag;
	newpoint->next = NULL;
	temp->next = newpoint;
}

/*-----Drawing f(x)-----*/

void draw_fx(Figure * fig, double f(double x), double start_x, double end_x, double step_size){
	Point2D * headpoint = start_point2d(start_x, f(start_x), 1);

	for(double i=start_x+step_size; i<=end_x; i+=step_size){
		insert_end(headpoint, i, f(i), 0);
	}

	fig->point = headpoint;
}

double f(double x){
	return x * sin(x) / 2.0;
}

/*-----Drawing Polyline-----*/

void draw_polyline(Figure * fig, Point2D * poly_line, int n){
	Point2D * temp;
	for(int i=0; i<n; i++){
		if(i==0)	temp = start_point2d(poly_line[i].x, poly_line[i].y, 1);
		else	insert_end(temp, poly_line[i].x, poly_line[i].y, 0);	
	}
	fig->point = temp;
}

Point2D * create_polyline(int n){
	Point2D * poly_line;
	for(int i=0; i<n; i++){
		if(i == 0){
			poly_line = (Point2D *) malloc(sizeof(Point2D));
		}
		else{
			poly_line = (Point2D *) realloc(poly_line, sizeof(Point2D)*(i+1));
		}

		if(i%2 == 0){
			poly_line[i].x = 20;
			poly_line[i].y = i*10;
		}
		else{
			poly_line[i].x = -20;
			poly_line[i].y = (i-10)*10;
		}

		poly_line[i].flag = 1;
		poly_line[i].next = NULL;
	}
	return poly_line;
}

/*-----Drawing Polygon-----*/

/*These functions draw an octagon*/

void draw_polygon(Figure * fig, Point2D * poly_line){
	Point2D * temp;
	for(int i=0; i<8; i++){ /*octagon*/
		if(i==0)	temp = start_point2d(poly_line[i].x, poly_line[i].y, 1);
		else	insert_end(temp, poly_line[i].x, poly_line[i].y, 0);	
	}
	insert_end(temp, poly_line[0].x, poly_line[0].y, 0);
	fig->point = temp;
}

Point2D * create_polygon(){ 
	Point2D * poly_line;
	for(int i=0; i<=8; i++){ /*octagon*/
		if(i == 0)	poly_line = (Point2D *) malloc(sizeof(Point2D));
		else	poly_line = (Point2D *) realloc(poly_line, sizeof(Point2D)*(i+1));
	}
	/*points*/
	poly_line[0].x = -50;	poly_line[0].y = 150;	
	poly_line[1].x = 50;	poly_line[1].y = 150;		
	poly_line[2].x = 125;	poly_line[2].y = 50;	
	poly_line[3].x = 125;	poly_line[3].y = -50;	
	poly_line[4].x = 50;	poly_line[4].y = -150;	
	poly_line[5].x = -50;	poly_line[5].y = -150;	
	poly_line[6].x = -125;	poly_line[6].y = -50;
	poly_line[7].x = -125;	poly_line[7].y = 50;	
	poly_line[8].x = -50;	poly_line[8].y = 150;
	return poly_line;
}

/*-----Drawing Ellipse-----*/

/*
centre = (h,k)
width = 2*a
height = 2*b
general formula = ((x-h)²/a²) + ((y-k)²/b²) = 1
*/

void draw_ellipse(Figure * fig, Point2D * centre, Point2D * width_height){	
	Figure * fig2 = (Figure *)malloc(sizeof(Figure));
	double x, y;
	double  * array = (double *)calloc(6, sizeof(double));
	
	*(array) = (width_height->x)/2; //a
	*(array+1) = (width_height->y)/2; //b
	*(array+2) = centre->x; //h
	*(array+3) = centre->y; //k
	*(array+4) = centre->x - (width_height->x)/2; //x
	*(array+5) = centre->y; //y
	
	Point2D * headpoint = ellipse_up(array);
	Point2D * headpoint2 = ellipse_down(array);
	
	fig->point = headpoint;
	fig2->point = headpoint2;
	append_figures(fig, fig2);
}

Point2D * ellipse_up(double * array){
	Point2D * headpoint = start_point2d(*(array+4), *(array+5), 1);
	double  a = *(array),
			b = *(array+1),
			h = *(array+2),
			k = *(array+3),
			x, y;

	for(double i = 0.02; i <= 2*a; i += 0.02){ 
		x = h - a + i;
		y = sqrt( abs((1 - ( pow((x-h),2)/(a*a) ) ) * b * b ) ) + k;
		insert_end(headpoint, x, y, 0);
	}
	x = h + a;
	y = sqrt( abs((1 - ( pow((x-h),2)/(a*a) ) ) * b * b ) ) + k;
	insert_end(headpoint, x, y, 0);
	return headpoint;
}

Point2D * ellipse_down(double * array){
	Point2D * headpoint = start_point2d(*(array+4), *(array+5), 1);
	double  a = *(array),
			b = *(array+1),
			h = *(array+2),
			k = *(array+3),
			x, y;

	for(double i = 0.02; i <= 2*a; i += 0.02){ 
		x = h - a + i;
		y = - sqrt( abs((1 - ( pow((x-h),2)/(a*a) ) ) * b * b ) ) + k;
		insert_end(headpoint, x, y, 0);
	}
	x = h + a;
	y = - sqrt( abs((1 - ( pow((x-h),2)/(a*a) ) ) * b * b ) ) + k;
	insert_end(headpoint, x, y, 0);
	return headpoint;
}

/*-----Drawing Binary Tree-----*/

void draw_binary_tree(Figure * fig, Tree * root){
	double radius = 50.0;
	double x, y;

	fig->text_flag = 1;
	fig->root = root;
	
	Figure * temp = start_figure(900, 700);
	Point2D * centre = start_point2d(0, 200, 1);
	draw_circle(fig, centre, radius);
	
	Point2D * centre2 = start_point2d(-200, 0, 1);//left
	x = -15;
	y = - sqrt( abs( radius*radius - (x-centre->x)*(x-centre->x)) ) + centre->y;
	Point2D * lines = start_point2d(x, y, 1);
	draw_nodes(fig, centre2, lines, radius, x, y);

	Point2D * centre3 = start_point2d(200, 0, 1);//right
	x = 15;
	y = - sqrt( abs( radius*radius - (x-centre->x)*(x-centre->x)) ) + centre->y;
	draw_nodes(fig, centre3, lines, radius, x, y);

	Point2D * centre4 = start_point2d(-100, -200, 1);//left
	x = -185;
	y = - sqrt( abs( radius*radius - (x-centre2->x)*(x-centre2->x)) ) + centre2->y;
	draw_nodes(fig, centre4, lines, radius, x, y);

	Point2D * centre5 = start_point2d(-300, -200, 1);//left
	x = -215;
	y = - sqrt( abs( radius*radius - (x-centre2->x)*(x-centre2->x)) ) + centre2->y;
	draw_nodes(fig, centre5, lines, radius, x, y);

	Point2D * centre6 = start_point2d(300, -200, 1);//right
	x = 215;
	y = - sqrt( abs( radius*radius - (x-centre3->x)*(x-centre3->x)) ) + centre3->y;
	draw_nodes(fig, centre6, lines, radius, x, y);

	fig->lines = lines;
}

void draw_nodes(Figure * fig, Point2D * centre, Point2D * lines, double radius, double x, double y){
	Figure * temp = start_figure(900, 700);
	draw_circle(temp, centre, radius);
	append_figures(fig,temp);
	insert_end(lines, x, y, 1);
	x = centre->x;
	y = radius + centre->y;
	insert_end(lines, x, y, 0);
}

Tree * create_leaf(double x, double y){
	Tree * leaf = (Tree *)malloc(sizeof(Tree));
	leaf->number = rand()%1000;
	leaf->x = x;
	leaf->y = y;
	leaf->left = NULL;
	leaf->right = NULL;
	return leaf;
}

Tree * create_tree(double x, double y){
	srand(time(NULL));
	Tree * root = create_leaf(-15, 195);
	root->left = create_leaf(-215, -5);
	root->right = create_leaf(185, -5);
	root->left->left = create_leaf(-315, -205);
	root->left->right = create_leaf(-115, -205);
	root->right->right = create_leaf(285, -205);
	return root;
}
/*
centre = (h,k)
radius = r
general formula = (x-h)² + (y-k)² = r²
*/
void draw_circle(Figure * fig, Point2D * centre, double radius){
	Figure * fig2 = (Figure *)malloc(sizeof(Figure));
	double x, y;
	double  * array = (double *)calloc(5, sizeof(double));
	*(array) = centre->x; //h
	*(array+1) = centre->y; //k
	*(array+2) = radius;
	*(array+3) = centre->x - radius; //x
	*(array+4) = centre->y; //y
	
	Point2D * headpoint = circle_up(array);
	Point2D * headpoint2 = circle_down(array);
	
	fig->point = headpoint;
	fig2->point = headpoint2;
	append_figures(fig, fig2);
}

Point2D * circle_up(double * array){
	Point2D * headpoint = start_point2d(*(array+3), *(array+4), 1);
	double 	h = *(array),
			k = *(array+1),
			r = *(array+2),
			x = *(array+3),
			y = *(array+4);

	for(double i = 0.02; i<=2*r; i += 0.02){ 
		x = h - r + i;
		y = sqrt( abs( r*r - (x-h)*(x-h)) ) + k;
		insert_end(headpoint, x, y, 0);
	}
	insert_end(headpoint, *(array+3)+2*r, *(array+4), 0);
	return headpoint;
}

Point2D * circle_down(double * array){
	Point2D * headpoint = start_point2d(*(array+3), *(array+4), 1);
	double 	h = *(array),
			k = *(array+1),
			r = *(array+2),
			x = *(array+3),
			y = *(array+4);

	for(double i = 0.02; i <= 2*r; i += 0.02){ 
		x = h - r + i;
		y = - sqrt( abs( r*r - (x-h)*(x-h)) ) + k;
		insert_end(headpoint, x, y, 0);
	}
	insert_end(headpoint, *(array+3)+2*r, *(array+4), 0);
	return headpoint;
}

/*-----Editing Figure-----*/

void scale_figure(Figure * fig, double scale_x, double scale_y){
/*
If scale values > 1, there is upsizing.
If scale values < 1 and > 0, there is downsizing.
*/
	Point2D * temp = fig->point;

	fig->width *= scale_x;
	fig->height *= scale_y;
	fig->xmin *= scale_x;
	fig->ymin*= scale_y;
	fig->xmax *= scale_x;
	fig->ymax *= scale_y;

	while(temp != NULL){
		temp->x *= scale_x;
		temp->y *= scale_y;
		temp = temp->next;
	}
}

void resize_figure(Figure * fig, Point2D * start_roi, Point2D * end_roi){
	fig->xmin = start_roi->x;
	fig->ymin = start_roi->y;
	fig->xmax = end_roi->x;
	fig->ymax = end_roi->y;
	fig->width = (end_roi->x) * 2;
	fig->height = (end_roi->y) * 2;
}

void append_figures(Figure * fig1, Figure * fig2){
	Point2D *temp;
	temp = fig1->point;
	while(temp->next != NULL)	temp = temp->next;
	temp->next = fig2->point;
	temp->next->flag = 1;
}

/*-----Exporting .eps File-----*/

void export_eps(Figure * fig, char * file_name){
	Point2D * temp;
	Point2D * temp2;

	FILE * fp = fopen(file_name, "w");
	if( fp == NULL){ /*the file does not exist*/
		printf("Error.\n");
	}
	else{
		fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
		fprintf(fp, "%%%%BoundingBox: %lf %lf %lf %lf\n", fig->xmin, fig->ymin, fig->xmax, fig->ymax);
		fprintf(fp, "%lf setlinewidth\n", fig->thickness);
		fprintf(fp, "%.1f %.1f %.1f setrgbcolor\n", fig->c.red, fig->c.green, fig->c.blue);
		if(fig->text_flag == 1){

			fprintf(fp, "/Times-Roman findfont\n");
			fprintf(fp, "%lf scalefont setfont\n", 25.0);//değiştir

			fprintf(fp, "%lf %lf moveto\n", fig->root->x, fig->root->y);
			fprintf(fp, "(%d) show\n", fig->root->number);

			fprintf(fp, "%lf %lf moveto\n", fig->root->left->x, fig->root->left->y);
			fprintf(fp, "(%d) show\n", fig->root->left->number);

			fprintf(fp, "%lf %lf moveto\n", fig->root->right->x, fig->root->right->y);
			fprintf(fp, "(%d) show\n", fig->root->right->number);

			fprintf(fp, "%lf %lf moveto\n", fig->root->right->right->x, fig->root->right->right->y);
			fprintf(fp, "(%d) show\n", fig->root->right->right->number);

			fprintf(fp, "%lf %lf moveto\n", fig->root->left->right->x, fig->root->left->right->y);
			fprintf(fp, "(%d) show\n", fig->root->left->right->number);

			fprintf(fp, "%lf %lf moveto\n", fig->root->left->left->x, fig->root->left->left->y);
			fprintf(fp, "(%d) show\n", fig->root->left->left->number);

			temp2 = fig->lines;
			while(temp2 != NULL){
				if(temp2->flag == 1){
					fprintf(fp, "%.5lf %.5lf moveto\n", temp2->x, temp2->y);
				}
				else{
					fprintf(fp, "%.5lf %.5lf lineto\n", temp2->x, temp2->y);
				}
				temp2 = temp2->next;
			}
		}

		temp = fig->point;
		while(temp != NULL){
			if(temp->flag == 1){
				fprintf(fp, "%.5lf %.5lf moveto\n", temp->x, temp->y);
			}
			else{				
				fprintf(fp, "%.5lf %.5lf lineto\n", temp->x, temp->y);
			}
			temp = temp->next;
		}
		fprintf(fp, "stroke\n");
	}
}