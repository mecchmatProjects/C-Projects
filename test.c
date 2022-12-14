#include "cunion.h"

int main() {
    FILE *fi = fopen("test.txt", "r");
    FILE *out = fopen("output.txt", "w");

    point a = input_file_point(fi);
    point b = input_file_point(fi);

    money kop = input_file_money(fi);
    money uah_kop = input_file_money(fi);

    my_vector v1 = input_file_vector(fi);
    my_vector v2 = input_file_vector(fi);
    my_vector v3 = input_file_vector(fi);

    point3 a1 = input_file_point3(fi);
    point3 b1 = input_file_point3(fi);

    figure square = input_file_figure(fi);
    figure triangle = input_file_figure(fi);
    figure rectangle = input_file_figure(fi);
    figure trapezium = input_file_figure(fi);
    figure circle = input_file_figure(fi);


    // test 1
    // print_figure(c);
    fprintf(out, "****test 1: finding the length between two points on a plane:\n\n");
    fprintf(out, "The length between points ");
    print_file_point(out, a);
    print_file_point(out, b);
    fprintf(out, "is %g\n", length_cartesian(a, b));

    // test 2

    fprintf(out, "\n****test 2: printing cost:\n\n");
    print_file_money(out, 1, 1, kop);
    fprintf(out, "\nAnd in hryvnia and kopecs: \n");
    print_file_money(out, 1, 2, kop);

    fprintf(out, "\n");
    print_file_money(out, 2, 2, uah_kop);
    fprintf(out, "\nAnd in kopecs: \n");
    print_file_money(out, 2, 1, uah_kop);

    // test 3
    fprintf(out, "\n****test 3: is 3 vectors colinear: ");
    fprintf(out, "\nVectors: (%g, %g), (%g, %g) and (%g, %g) are ", v1.ends.x1-v1.ends.x2, v1.ends.y1-v1.ends.y2,
    v2.ends.x1-v2.ends.x2, v2.ends.y1-v2.ends.y2, v3.ends.x1-v3.ends.x2, v3.ends.y1-v3.ends.y2);

    if (is_colinear_3(v1, v2, v3, 1)) {
        fprintf(out, "colinear\n");
    } else {
        fprintf(out, "not colinear\n");
    }

    // test 4
    fprintf(out, "\n****test 4: finding the length between two points in a space:\n\n");
    fprintf(out, "The length between points ");
    print_file_point3(out, a1);
    print_file_point3(out, b1);
    fprintf(out, "is %g\n", length(a1, b1, 1));

    // test 5
    fprintf(out, "\n****test 5: perimeters and areas of figures:\n\n");
    print_file_figure(out, square, 1);
    fprintf(out, "Perimeter is equal to %g\n", perimeter(square, 1));
    fprintf(out, "Area is equal to %g", area(square, 1));

    fprintf(out, "\n\n");

    print_file_figure(out, triangle, 2);
    fprintf(out, "Perimeter is equal to %g\n", perimeter(triangle, 2));
    fprintf(out, "Area is equal to %g", area(triangle, 2));

    fprintf(out, "\n\n");

    print_file_figure(out, rectangle, 3);
    fprintf(out, "Perimeter is equal to %g\n", perimeter(rectangle, 3));
    fprintf(out, "Area is equal to %g", area(rectangle, 3));

    fprintf(out, "\n\n");

    print_file_figure(out, trapezium, 4);
    fprintf(out, "Perimeter is equal to %g\n", perimeter(trapezium, 4));
    fprintf(out, "Area is equal to %g", area(trapezium, 4));

    fprintf(out, "\n\n");

    print_file_figure(out, circle, 5);
    fprintf(out, "Perimeter is equal to %g\n", perimeter(circle, 5));
    fprintf(out, "Area is equal to %g", area(circle, 5));

    fclose(fi);
    fclose(out);
    return 0;
}