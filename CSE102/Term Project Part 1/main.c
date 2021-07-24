#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "vectorlib.h"

void main(){
	printf("\nPlease wait...\nFiles are exporting...\n");

	/* fig1 shows that draw_fx() */
	/* f(x) = x * sin(x) / 2.0 */
	Figure * fig1 = start_figure(400, 400);
	set_thickness_resolution(fig1, 0.1, 1.5);
	set_color(fig1, create_color(1.0, 0.0, 1.0));
	draw_fx(fig1, f, -80, 80, 0.02);
	export_eps(fig1, "fig1.eps");

	/* fig2 shows that draw_polyline() */
	Figure * fig2 = start_figure(200, 200);
	set_thickness_resolution(fig2, 0.1, 0.8);
	set_color(fig2, create_color(0.0, 0.0, 1.0));
	Point2D * poly_line1 = create_polyline(7);
	draw_polyline(fig2, poly_line1, 7);
	export_eps(fig2, "fig2.eps");

	/* fig3 shows that draw_polygon() */
	Figure * fig3 = start_figure(500, 500);
	set_thickness_resolution(fig3, 0.1, 0.5);
	set_color(fig3, create_color(1.0, 0.7, 0.0));
	Point2D * poly_line2 = create_polygon();
	draw_polygon(fig3, poly_line2);
	export_eps(fig3, "fig3.eps");

	/* fig4 and fig5 show that draw_ellipse() */
	Figure * fig4 = start_figure(500, 500);
	set_thickness_resolution(fig4, 1, 0.8);
	set_color(fig4, create_color(0.0, 1.0, 1.0));
	Point2D * centre1 = start_point2d(0, 0, 1);
	Point2D * width_height1 = start_point2d(200, 100, 1);
	draw_ellipse(fig4, centre1, width_height1);
	export_eps(fig4, "fig4.eps");

	Figure * fig5 = start_figure(500, 500);
	set_thickness_resolution(fig5, 1, 0.8);
	set_color(fig5, create_color(0.0, 1.0, 1.0));
	Point2D * centre2 = start_point2d(0, 0, 1);
	Point2D * width_height2 = start_point2d(100, 200, 1);
	draw_ellipse(fig5, centre2, width_height2);
	export_eps(fig5, "fig5.eps");

	/* fig6 shows that draw_binary_tree() */
	Figure * fig6 = start_figure(1000, 1000);//tree içn
	set_thickness_resolution(fig6, 1, 0.8);
	set_color(fig6, create_color(0.0, 0.5, 0.0));
	Tree * root = create_tree(450, 350);
	draw_binary_tree(fig6, root);
	export_eps(fig6, "fig6.eps");

	/* fig7 shows that scale_figure() */
	Figure * fig7 = fig1;
	scale_figure(fig7, 5, 5);
	export_eps(fig7, "fig7.eps");

	/* fig8 shows that resize_figure() */
	Figure * fig8 = fig3;
	Point2D * start_roi = start_point2d(0, -250, 1);
	Point2D * end_roi = start_point2d(250, 250, 1);
	resize_figure(fig8, start_roi, end_roi);	
	export_eps(fig8, "fig8.eps");

	/* fig9 shows that append_figures() */
	Figure * fig9 = fig4;
	append_figures(fig9, fig5);
	export_eps(fig9, "fig9.eps");
}