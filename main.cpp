# include "src/mapcart.cpp"
# include "src/map_create.cpp"
# include <iostream>

using namespace std;


int main()
{
	FILE *file_completed;
	char filename[256], file_res[256];
	int row, col, checked;
	int i, flag, colored_pixels, region_p, region_a, rectangles_amount;
	int cur_lines_color, cur_color_lines_amount, current_color, i_col, cur_color_pixels_amount, ellipses_amount;
	int ellipse_predicted[4];
	double line_length, perimeter, area, max_perimeter, max_area, line_max_len, ellipse_max_area;

	size_x = 200, size_y = 200;
	colors_max = 10;

	strcpy(filename, "test_map.dat");
	strcpy(file_res, "test_res.txt");

	create_map(filename, size_x, size_y, colors_max);
	read_color_map(filename);

	colored_pixels = 0;

	for (row = 0; row < size_y; row++)
	{
		for (col = 0; col < size_x; col++)
			if (map[row][col] != 0) colored_pixels++;
	}

	pixel_lst = (PixelList**)calloc(colored_pixels + 1, sizeof(PixelList*));

	if (pixel_lst == nullptr) { printf("ALLOCATION ERROR"); exit(-1); }

	for (i = 0; i < colored_pixels; i++)
	{
		pixel_lst[i] = (PixelList*) calloc(1, sizeof(PixelList));
		if (pixel_lst[i] == nullptr) { printf("ALLOCATION ERROR"); exit(-1); }
	}

	linked_regions = (int*)calloc(colored_pixels + 1, sizeof(int));
	if (linked_regions == nullptr) { printf("ALLOCATION ERROR"); exit(-1); }

	create_pixel_list();
	cout << endl;
	region_size();

	file_completed = fopen(file_res, "wt");
	if (file_completed == NULL)
	{
		cout << "FILE ERROR." << file_res;
		exit(-1);
	}

	for (row = 0; row < size_y; row++)
	{
		for (col = 0; col < size_x; col++)
			fprintf(file_completed, "%i", map[row][col]);
		fprintf(file_completed, "\n");
	}

	line_max_len = 30.0;
	cur_lines_color = 2;
	cur_color_lines_amount = 0;

	max_perimeter = 0.0;
	max_area = 0.0;
	rectangles_amount = 0;
	region_p = -1;
	region_a = -1;

	ellipses_amount = 0;
	ellipse_max_area = 25.0;

	current_color = 1;
	cur_color_pixels_amount = 0;

	for (i = 0; i < regions_amount; i++)
	{
		cout << "\nRegion" << i << endl;
		fprintf(file_completed, "\nRegion %i \n", i);

		checked = 0;
		i_col = pixel_lst[linked_regions[i]]->color;
		if (i_col == current_color) cur_color_pixels_amount += (linked_regions[i + 1] - linked_regions[i]);

		flag = is_line(i, &line_length);

		if (flag > 0){
			checked = 1;
			printf("LINE, length: %.2f\n", line_length);
			fprintf(file_completed, "LINE, length: %.2f\n", line_length);

			if (line_length > line_max_len && i_col == cur_lines_color) cur_color_lines_amount++;

			continue;
		}

		flag = is_rectangle(i, &perimeter, &area, ellipse_predicted);

		if (flag > 0) {
			checked = 2;
			rectangles_amount++;

			if (perimeter > max_perimeter) { max_perimeter = perimeter; region_p = i; }
			if (area > max_area) { max_area = area; region_a = i; }

			printf("RECTANGLE, perimeter: %.2f, area: %.2f\n", perimeter, area);
			printf("x0=%i   y0=%i\n", ellipse_predicted[0], ellipse_predicted[1]);
			printf("x1=%i   y1=%i\n", ellipse_predicted[2], ellipse_predicted[3]);

			fprintf(file_completed, "RECTANGLE, perimeter: %.2f, area: %.2f\n", perimeter, area);
			fprintf(file_completed, "x0=%i   y0=%i\n", ellipse_predicted[0], ellipse_predicted[1]);
			fprintf(file_completed, "x1=%i   y1=%i\n", ellipse_predicted[2], ellipse_predicted[3]);

			continue;
		}

		flag = is_ellipse(i, ellipse_predicted);

		if (flag > 0){
			checked = 3;
			if (M_PI * ellipse_predicted[2] * ellipse_predicted[3] > ellipse_max_area) { ellipses_amount++; }

			cout << "ELLIPSE\n";
			printf("x0=%i, y0=%i\n", ellipse_predicted[0], ellipse_predicted[1]);
			printf("a=%i, b=%i\n", ellipse_predicted[2], ellipse_predicted[3]);

			fprintf(file_completed, "ELLIPSE\n");
			fprintf(file_completed, "x0=%i, y0=%i\n", ellipse_predicted[0], ellipse_predicted[1]);
			fprintf(file_completed, "a=%i, b=%i\n", ellipse_predicted[2], ellipse_predicted[3]);

			continue;
		}

		if (checked == 0){
			printf("NOT RECOGNIZED!\n");
			fprintf(file_completed, "NOT RECOGNIZED!\n");
		}
	}

	cout << "\n*** Regions:" << regions_amount << endl;
	cout << "*** Rectangles: " << rectangles_amount << endl;
	printf("    Rectangle %i max perimeter: %.2f \n", region_p , max_perimeter);
	printf("    Rectangle %i max area: %.2f\n", region_a, max_area);
	printf("*** Lines with length > %.2f of color %i: %i\n", line_max_len, cur_lines_color, cur_color_lines_amount);
	printf("*** Ellipses with area > %.2f: %i\n", ellipse_max_area, ellipses_amount);
	cout << "*** Pixels of color" << current_color << ": " << cur_color_pixels_amount << endl;

	fprintf(file_completed, "\n*** Regions: %i\n", regions_amount);
	fprintf(file_completed, "*** Rectangles: %i\n", rectangles_amount);
	fprintf(file_completed, "    Rectangle %i max perimeter: %.2f \n", region_p , max_perimeter);
	fprintf(file_completed, "    Rectangle %i max area: %.2f\n", region_a, max_area);
	fprintf(file_completed, "*** Lines with length > %.2f of color %i: %i\n", line_max_len, cur_lines_color);
	fprintf(file_completed, "*** Ellipses with area > %.2f: %i\n", ellipse_max_area, ellipses_amount);
	fprintf(file_completed, "*** Pixels of color %i: %i\n", current_color, cur_color_pixels_amount);

	for (i = 0; i < colored_pixels; i++) free(pixel_lst[i]);
	for (int row = 0; row < size_y; row++) free(map[row]);

	free(pixel_lst); free(map); free(linked_regions);

	fclose(file_completed);
}
