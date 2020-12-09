void draw_line(int **, int, int, int, int, int, int, int);
void draw_rectangle(int **, int, int, int, int, int, int, int);
void draw_ellipse(int **, int, int, int, int, int, int, int);


void create_map(char *filename, int size_x, int size_y, int colors_max)
{
	FILE *file_map;
	int row, col;
	int **map;

	file_map = fopen( filename, "wb");
	if (file_map == NULL ){ printf( "FILE ERROR", filename); exit(-1); }

	map = (int**) calloc(size_y, sizeof(int*));
	if (map == nullptr) { printf ("ALLOCATION ERROR\n") ; exit(-1); }

	for (row = 0; row < size_y; row++){
		map[row] = (int*)calloc(size_y, sizeof(int));
		if (map[row] == nullptr){ printf( "ALLOCATION ERROR\n"); exit(-1);}
		memset(map[row], 0, size_x * sizeof(int));
	}

	draw_line(map, size_x, size_y, 10, 10, 70, 20, 1);
	draw_line(map, size_x, size_y, 120, 110, 140, 60, 2);
	draw_line(map, size_x, size_y, 150, 130, 190, 190, 3);

	draw_rectangle(map, size_x, size_y, 90, 30, 110, 80, 4);
	draw_rectangle(map, size_x, size_y, 160, 60, 190, 100, 5);
	draw_rectangle(map, size_x, size_y, 10, 110, 70, 190, 6);

	draw_ellipse(map, size_x, size_y, 30, 40, 10, 10, 7);
	draw_ellipse(map, size_x, size_y, 160, 30, 30, 20, 8);
	draw_ellipse(map, size_x, size_y, 100, 155, 5, 35, 9);

	fwrite(&size_x, sizeof(int), 1, file_map);
	fwrite(&size_y, sizeof(int), 1, file_map);
	fwrite(&colors_max, sizeof(int), 1, file_map);

	for (row = 0; row < size_y; row++) {
		fwrite(map[row], sizeof(int), size_x, file_map);

		for (col = 0; col < size_x; col++) printf("%i", map[row][col]);
		printf("\n");
	}

	for (row = 0; row < size_y; row++) { free(map[row]); }
	free(map);
	fclose(file_map);
}

void draw_line(int **map, int size_x, int size_y, int x0, int y0, int x1, int y1, int color) {
	int row, col, d1, d2, dm;
	int max_x, min_x, max_y, min_y;
	double a, b , s , f, del;

	if ((x0 >= size_x || x1 >= size_x || x0 < 0 || x1 < 0) || (y0 >= size_y || y1 >= size_y || y0 < 0 || y1 < 0)){
		printf("BAD PARAMETER(S)!\n");
		return;
	}

	d1 = y1 - y0;
	d2 = x1 - x0;
	dm = abs(d1);

	if (abs(d2) > abs(d1)) dm = abs(d2);

	if (d1 > 0) 
  {
		max_y = y1;
		min_y = y0;
	}
	else 
  {
		max_y = y0;
		min_y = y1;
	}

	if (d2 > 0) {
		max_x = x1;
		min_x = x0;
	} else {
		max_x = x0;
		min_x = x1;
	}

	if (d2 == 0.0) {
		col = x0;
		for (row = min_y; row <= max_y; row++) map[row][col] = color;
	} else {
		if (d1 == 0) {
			row = y0;
			for (col = min_x; col <=max_x; col++) map[row][col] = color;
		} else {
			a = (double)d1 / (double)d2;
			b = (double)y1 - a * (double)x1;

			s = (double)min_x;
			f = (double)max_x;
			del = 1.0 / dm;

			while (s < f) {
				row = round(a*s + b);
				col = round(s);

				map[row][col] = color;
				s += del;
			}
		}
	}
}

void draw_rectangle(int **map, int size_x, int size_y, int x0, int y0, int x1, int y1, int color){
	int row;
	int d1, max_y, min_y;

	if ((x0 >= size_x || x1 >= size_x || x0 < 0 || x1 < 0) || (y0 >= size_y || y1 >= size_y || y0 < 0 || y1 < 0)) {
		printf(("BAD PARAMETER(S)!\n"));
	}

	d1 = y1 - y0;

	if (d1 > 0) {
		max_y = y1;
		min_y = y0;
	} else {
		max_y = y0;
		min_y = y1;
	}

	for (row = min_y; row <= max_y; row++) draw_line(map, size_x, size_y, x0, row, x1, row, color);
}

void draw_ellipse(int **map, int size_x, int size_y, int x0, int y0, int a, int b, int color){
	int  x1, y1, m;
	double d, some_angle;

	if ((x0 + a >= size_x || x0 - a < 0 || a < 0) || (y0 + b >= size_y || y0 - b < 0 || b < 0)){
		printf( ("BAD PARAMETER(S)!\n"));
	}

	m = a;
	if (m < b) m = b;

	d = M_PI / (double)(12 * m);

	some_angle = 0.0;

	while (some_angle <= M_PI * 2.0) {
		x1 = (double) a * cos(some_angle);
		y1 = (double) b * sin(some_angle);

		x1 += x0;
		y1 += y0;

		some_angle += d;

		map[y1][x1] = color;
		draw_line(map, size_x, size_y, x0, y0, x1, y1, color);
	}
}
