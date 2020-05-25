#pragma once
#ifndef MAPCART_H
#define MAPCART_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <direct.h>


struct PixelList
{
	int x, y;
	int color;
};

void read_color_map(char * );

void create_pixel_list(void);
void region_size(void);
void add_pixel(int, int, int, int);
void check_pixel(int, int, int, int);
double distance_between_pixels(int, int, int, int);

int  is_line(int, double *);
int  is_rectangle(int, double *, double *, int *);
int  is_ellipse(int, int *);


#endif
