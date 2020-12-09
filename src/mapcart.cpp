#include "../headers/mapcart.h"
#include <cstring>

PixelList ** pixel_lst;

int size_x, size_y, colors_max;
int pixel_lst_counter;
int **map;
int *linked_regions;
int regions_amount;

void create_pixel_list()
{
	int row, col;
	int color, num;

	num = 0;
	pixel_lst_counter = 0;


	regions_amount = 0;
	linked_regions[regions_amount] = pixel_lst_counter;
	for (row = 0; row < size_y; row++)
	{
	    for (col = 0; col < size_x; col++)
		{
			if (map[row][col] != 0)
			{
				color = map[row][col];
				num = pixel_lst_counter;

				add_pixel(color, num, row, col);

				pixel_lst_counter++;
				regions_amount ++;
				linked_regions[regions_amount] = pixel_lst_counter;
			}
		}
	}

	for (num = 0; num < linked_regions[regions_amount]; num++)
	{
		row = pixel_lst[num]->y;
		col = pixel_lst[num]->x;
		map[row][col] = pixel_lst[num]->color;
	}
}

void add_pixel(int color, int num, int row, int col)
{

	map[row][col] = 0;

	pixel_lst[pixel_lst_counter]->x = col;
	pixel_lst[pixel_lst_counter]->y = row;
	pixel_lst[pixel_lst_counter]->color = color;

	check_pixel(color, num, row, col);
}

void check_pixel (int color, int num, int row, int col)
{
	int rb, cb, re, ce;
	int i, j;

	cb = pixel_lst[num]->x;
	rb = pixel_lst[num]->y;

	ce = pixel_lst[num]->x;
	re = pixel_lst[num]->y;

	if (cb > 0) cb--;
	if (rb > 0) rb--;

	if (ce < size_x - 1) ce++;
	if (re < size_y - 1) re++;


	for (i = rb; i <= re; i++)
	{
		for (j = cb; j <= ce; j++)
		{
			if (map[i][j] == color)
			{
				pixel_lst_counter++;
				num= pixel_lst_counter;
				add_pixel(color, num, i, j);
			}
		}
	}
}

void region_size()
{
	int i, j, k, region_max, color_max;
	int *region_colors_lst;

	region_colors_lst = (int*) calloc (colors_max + 1, sizeof(int));
	memset(region_colors_lst, 0, colors_max * sizeof(int));

	region_max = 0;
	color_max = 0;

	for (i = 1; i <= regions_amount; i++)
	{
		k = linked_regions[i] - linked_regions[i - 1];
		j = linked_regions[i - 1];

		region_colors_lst[pixel_lst[j]->color] += k;

		if (k > region_max)
		{
			region_max = k;
			color_max = pixel_lst[j]->color;
		}
	}

	for (i = 1; i <= colors_max; i++)
	{
		if (region_colors_lst[i] > 0)
			printf("--- %i px, color: %i\n", region_colors_lst[i], i );
	}

	printf("* * * MAX REGION: %i px, color: %i * * *\n", region_max, color_max);

	free(region_colors_lst);
}

double distance_between_pixels(int x1, int y1, int x2, int y2)
{
	int dx, dy;
	double d;

	dx = x1 - x2;
	dy = y1 - y2;
	d = sqrt((double)(dx*dx + dy*dy));
	return d;
}

int is_line(int rnum, double *line_length)
{
	char si;
	int i, n, k;
	int x0,x1, y0,y1, d1, d2;
	int kmin, kmax, xmin, xmax, ymin, ymax, in, ik;

	double a, b;


	n = linked_regions[rnum];
	k = linked_regions[rnum + 1];

	if ( k - n  < 2)
	{
		*line_length = 0.0;
		return -1;
	}

	xmin = size_x;
	xmax = 0;
	for (i = n; i < k; i++)
	{
		x1 = pixel_lst[i]->x;
		if (x1 > xmax) { xmax = x1; ik = i;	}
		if (x1 < xmin) { xmin = x1; in = i;	}
	}

	ymin = size_y;
	ymax = 0;

	if (pixel_lst[ik]->y >= pixel_lst[in]->y)
	{
		kmax = xmax;
		kmin = xmin;
	}
	else
	{
		kmin = xmax;
		kmax = xmin;
	}
	for (i = n; i < k; i++)
	{
		x1 = pixel_lst[i]->x;
		y1 = pixel_lst[i]->y;
		if (x1 == kmax && y1 > ymax) { ymax = y1; ik = i; }
		if (x1 == kmin && y1 < ymin) { ymin = y1; in = i; }
	}

	x0 = pixel_lst[in]->x;
	y0 = pixel_lst[in]->y;
	x1 = pixel_lst[ik]->x;
	y1 = pixel_lst[ik]->y;

	d1 = y1 - y0;
	d2 = x1 - x0;

	*line_length = distance_between_pixels(x0, y0, x1, y1);

	if (d2 == 0)
	{
		x0 = pixel_lst[n]->x;
		for (i = n+1; i < k; i++)
		{
			x1 = pixel_lst[i]->x;

			if (x0 != x1 )
			{
				*line_length = 0.0;
				return -2;
			}
		}

		printf("x = %i\n",x0);
		return 1;
	}

	if (d1 == 0)
	{
		y0 = pixel_lst[n]->y;
		for (i = n+1; i < k; i++)
		{
			y1 = pixel_lst[i]->y;

			if ( y0 != y1 )
			{
				*line_length = 0.0;
				return -3;
			}

		}

		printf("y = %i\n", y0);
		return 1;
	}

	a = (double) d1 / (double) d2;
	b = (double) y1 - a * (double) x1;

	for (i = n; i < k; i++)
	{
		y1 = pixel_lst[i]->y;
		x1 = pixel_lst[i]->x;

		d1 = abs((int)(y1 - round(x1*a + b)));

		if (d1 > 1)
		{
			*line_length = 0.0;
			return -4;
		}
	}

	if (b <= 0.0) si = ' ';
	else          si = '+';

	printf("line equation: y = %.2fx",a);

	if ( b!= 0) printf("%c%.2f", si, b);
	printf("\n");

	return 1;

}

int is_rectangle(int region_num, double *perimeter, double *area, int *x_and_y_array){
	int i, n, k;
	int x1, y1, d1, d2;
	int kmin, kmax, xmin, xmax, ymin, ymax, in, ik;


	n = linked_regions[region_num];
	k = linked_regions[region_num + 1];

	if (k - n < 4) {
		*perimeter = 0.0;
		*area = 0.0;
		return -1;
	}

	xmin = size_x;
	xmax = 0;
	ymin = size_y;
	ymax = 0;

	for (i = n; i < k; i++) {
		x1 = pixel_lst[i]->x;
		if (x1 > xmax) { xmax = x1; ik = i; }
		if (x1 < xmin) { xmin = x1; in = i; }
	}

	for (i = n; i < k; i++) {
		x1 = pixel_lst[i]->x;
		y1 = pixel_lst[i]->y;
		if (x1 == xmax && y1 > ymax) { ymax = y1; ik = i; }
		if (x1 == xmin && y1 < ymin) { ymin = y1; in = i; }
	}

	kmax = 0;
	for (i = n; i < k; i++) {
		x1 = pixel_lst[i]->x;
		y1 = pixel_lst[i]->y;

		if (x1 == xmin && y1 == ymin) kmax++;
		if (x1 == xmax && y1 == ymax) kmax++;
		if (x1 == xmax && y1 == ymin) kmax++;
		if (x1 == xmin && y1 == ymax) kmax++;
	}

	if ( kmax != 4 ) {
		*perimeter = 0.0;
		*area = 0.0;
		return -2;
	}

	d1 = ymax - ymin+1;
	d2 = xmax - xmin+1;

	*perimeter = (d1 + d2) * 2;
	*area = d1 * d2;

	if ((int)*area != k - n )
	{
		*perimeter = 0.0;
		*area = 0.0;
		return -3;
	}

	x_and_y_array[0] = xmin;
	x_and_y_array[1] = ymin;
	x_and_y_array[2] = xmax;
	x_and_y_array[3] = ymax;

	return 1;
}

int is_ellipse(int region_num, int *ellipse){
	int i, m, n, k;
	int x0, x1, y0, y1;
	int min_x, max_x, min_y, max_y;

	int p[6];

	double distance_1, distance_2;
	double a, b, some_angle;

	n = linked_regions[region_num];
	k = linked_regions[region_num + 1];

	if (k - n < 4)	return -1;

	max_x = 0;
	max_y = 0;
	min_x = size_x;
	min_y = size_y;

	for (i = n; i < k; i++) {
		x1 = pixel_lst[i]->x;
		y1 = pixel_lst[i]->y;

		if (x1 > max_x) { max_x = x1; p[0] = i; }
		if (x1 < min_x) { min_x = x1; p[1] = i; }
		if (y1 > max_y) { max_y = y1; p[2] = i; }
		if (y1 < min_y) { min_y = y1; p[3] = i; }
	}

	x0 = (max_x + min_x) / 2;
	y0 = (max_y + min_y) / 2;

	for (i = n; i < k; i++) if (pixel_lst[i]->x == x0 && pixel_lst[i]->y == y0) break;
	if (i == k) return -2;

	a = max_x - x0;
	b = max_y - y0;

	ellipse[0] = (int) x0;
	ellipse[1] = (int) y0;
	ellipse[2] = (int) a;
	ellipse[3] = (int) b;

	m = 0;

	for (i = n; i < k; i++)
	{
		x1 = pixel_lst[i]->x;
		y1 = pixel_lst[i]->y;

		if (x1 == x0 )
		{
			if (abs(y1 - y0) <= b)
			{
			    m++;
			    continue;
			}
			else
            {
			    break;
            }
		}

		if (y1 == y0)
		{
			if (abs(x1 - x0) <= a)
			{
			    m++;
			    continue;
			}
			else break;
		}

		some_angle = atan((double) (y1 - y0) / (double) (x1 - x0));

		max_x = x0 + round(a * cos(some_angle));
		max_y = y0 + round(b * sin(some_angle) );

		distance_1 = distance_between_pixels(x0, y0, x1, y1);
		distance_2 = distance_between_pixels(x0, y0, max_x, max_y);

		if (distance_2 + 1.0 > distance_1 ) m++;
		else break;
	}

	if (m == k - n)
    {
	    return 1;
    }
	else{
        return -3;
    }
}


void read_color_map(char * filename)
{
	size_t sr;
	FILE *fr;
	int row;

	fr = fopen(filename, "rb");

	if (fr == NULL)
	{
		printf("read_color_map - Unable to open file %s", filename);
		exit(-1);
	}

	fread(&size_x, sizeof(int), 1, fr);
	fread(&size_y, sizeof(int), 1, fr);
	fread(&colors_max, sizeof(int), 1, fr);

	map = (int**)calloc(size_y, sizeof(int*));

	if (map == nullptr)
	{
		printf("create_map - map can't be allocated.\n");
		exit(-1);
	}

	for (row = 0; row < size_y; row++)
	{
		map[row] = (int*) calloc(size_y, sizeof(int));

		if (map[row] == nullptr)
		{
			printf("create_map - map %i can't be allocated.\n", row);
			exit(-1);
		}
	}

	for (row = 0; row < size_y; row++)
	{
		sr = fread(map[row], sizeof(int), size_x, fr);

		if (sr < size_x)
		{
			printf("Error reading: %s row=%i\n", filename, row);
			exit(-1);
		}
	}

	fclose(fr);
}
