#ifndef VECTORLIB_h
#define VECTORLIB_h

/*RGB colors*/
typedef struct Color {
	double red, green, blue; 
} Color;

/*Binary Tree*/
typedef struct Tree {
	int number;
	double x, y;
	struct Tree * left;
	struct Tree * right;
} Tree;

/*Point*/
typedef struct Point2D {
	double x, y;
	int flag; /*The flag represents whether the point is the starting point or the continuation point*/
	struct Point2D *next;
} Point2D;

/*Figure*/
typedef struct Figure {
	double width,
		   height,
		   thickness,
		   resolution,
		   xmin, ymin, /*for bot-left, x and y values*/
		   xmax, ymax; /*for top-right, x and y values*/
	Color c;
	Point2D * point;
	int text_flag; /*The text_flag represents whether there is text in the figure*/
	Tree * root;
	Point2D * lines;
} Figure;

/*Creating Figure Functions*/
Figure * start_figure(double width, double height);
void set_thickness_resolution(Figure * fig, double thickness, double resolution);
Color create_color(double r, double g, double b);
void set_color(Figure * fig, Color c);

Point2D * start_point2d(double x, double y, int flag);
void insert_end(Point2D * point, double x, double y, int flag);

/*Drawing f(x)*/
void draw_fx(Figure * fig, double f(double x), double start_x, double end_x, double step_size);
double f(double x); /*The helper function that is using draw_fx()*/

/*Creating Point2D*/
Point2D * start_point2d(double x, double y, int flag);
void insert_end(Point2D * point, double x, double y, int flag);

/*Drawing Polyline*/
void draw_polyline(Figure * fig, Point2D * poly_line, int n);
Point2D * create_polyline(int n);

/*Drawing Polygon*/
void draw_polygon(Figure * fig, Point2D * poly_line);
Point2D * create_polygon();

/*Drawing Ellipse*/
void draw_ellipse(Figure * fig, Point2D * centre, Point2D * width_height);
Point2D * ellipse_up(double * array);
Point2D * ellipse_down(double * array);

/*Drawing Binary Tree*/
void draw_binary_tree(Figure * fig, Tree * root);
void draw_nodes(Figure * fig, Point2D * centre, Point2D * lines, double radius, double x, double y);
Tree * create_leaf(double x, double y);
Tree * create_tree(double x, double y);
void draw_circle(Figure * fig, Point2D * centre, double radius);
Point2D * circle_up(double * array);
Point2D * circle_down(double * array);

/*Functions for editing and exporting figure*/
void scale_figure(Figure * fig, double scale_x, double scale_y);
void resize_figure(Figure * fig, Point2D *start_roi, Point2D *end_roi);
void append_figures(Figure * fig1, Figure * fig2);
void export_eps(Figure * fig, char * file_name);

#endif