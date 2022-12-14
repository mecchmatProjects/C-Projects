/* @file cunion.h
*
*  @brief Structures and function prototypes for the half year project
*   
*  Completing date: 13.12.2022
*
*  @author Pisnya Maria  
*  @bug no known bugs
*
*/



#ifndef CUNION_H
#define CUNION_H

#include <math.h>
#include <stdio.h>
#define pi 3.1415926
#define N 20

// 1) universal type for setting point in the Cartesian and Polar coordinates on the plate

typedef union {
    struct {
        double x; 
        double y;
        } Cart;
    struct {double r, fi;} Polar; 
    } point;

// 2) universal money type for setting cost in kopecs only and hryvnia and kopecs

typedef union {
    struct {int kopecs;} kopec;
    struct {int uah; int kopecs;} UAH;
    } money;

// 3) universal type for setting vector as start and finish point and ar start point and vector to the finish one 

typedef union {
    struct {double x1, y1, x2, y2;} ends;
    struct { double x, y, x_v, y_v;} point_and_vector;
    } my_vector;

// 4) universal type for setting point in 3 dimentional space in 1) cartesian, 2) spherical or 3) cylindrical coordinates 

typedef union {
    struct {double x, y, z;} cart;
    struct {double r, fi, psi;} spherical;
    } point3;

// 5 universal type for setting figures as circle, square, triangle, rectangle and trapezium

typedef union {
    struct {double r;} circle;
    struct {double a;} square;
    struct {double a, b, c;} triangle;
    struct {double a, b;} rectangle;
    struct {double a, b, base1, base2, height;} trapezium;
    } figure;


// functions ..


//.. for the first type point

point input_point();                         // allows user to input point set in both cartesian and polar coordinates according to the choise

void print_point(point A, char a);           // prints the points cartesian coordinates no matter how it is set

double length_cartesian(point A, point B);   // returns the length of the line between points setted in cartesian coordinates

double length_polar(point A, point B);       // returns the length of the line between points setted in polar coordinates

//.. for the second type money 

money input_money();                         // allows user to input money in 1) kopecs only or 2) in hryvnia and kopecs 
void print_money(money cost);                // prints cost in 1) kopecs only or 2) in hryvnia and kopecs 

//.. for the third type vector

                                                                      // allows user to input vector as 
my_vector input_vector();                                             // 1) start and finish point coordinates 
                                                                      // 2) start point coordinates and vector to another point 

my_vector create_vector(double x1, double y1, double x2, double y2);  // allows user to create vector by existing data and not input it

void print_vector(my_vector v);                                       // prints vector as start and finish point coordinates no matter how it is setted 

int is_colinear_2(my_vector m, my_vector n, int type);                // allows to check if 2 vectors on a plane setted by 1) two points or 2) point and vector each

int is_colinear_3(my_vector m, my_vector n, my_vector k, int type);   // same to the previous function but for 3 vectors on a plane 


//.. for the firth type point3 (point in 3 dimentional space)

point3 input_point3();               // allows to input point 

void print_point3(point3 a);         // prints point in cartesian coordinates 

double length(point3 A, point3 B, int type);   // length of line, type 1) cartesian coordinates and 2) spherical

//.. for the fifth type figure (on plane)

figure input_figure();          // allows to input a figure

void print_figure(figure f);    // prints the description of the figure 

double area(figure A, int type);          // allows to find an area, type is 1) square 2) triangle 3) rectangle 4) trapezium 5) circle

double perimeter(figure A, int type);     // allows to find a perimeter, type is 1) square 2) triangle 3) rectangle 4) trapezium 5) circle


//functions for input from and output to file 

point input_file_point(FILE *fi);        

money input_file_money(FILE *fi);

my_vector input_file_vector(FILE *fi);

point3 input_file_point3(FILE *fi);

figure input_file_figure(FILE *fi);

void print_file_point(FILE *fi, point a);

void print_file_money(FILE *fi, int type_inp, int type_out, money a);  // type_inp: 1) input cost is in kopecs 
                                                                       //           2) input cost is in hryvnia and kopecs

                                                                       // type_out: 1) output cost is in kopecs 
                                                                       //           2) output cost is in hryvnia and kopecs
void print_file_vector(FILE *fi, my_vector a);

void print_file_point3(FILE *fi, point3 a);

void print_file_figure(FILE *fi, figure f, int type);                  // type  1) square 
                                                                       //       2) triangle 
                                                                       //       3) rectangle 
                                                                       //       4) trapezium
                                                                       //       5) circle 


#endif