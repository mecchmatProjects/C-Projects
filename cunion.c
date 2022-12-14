#include "cunion.h"

// *************point*************

point input_point() {
    point A;
    printf("Enter x and y coordinates one after another like 'x y' or 'r fi' if you prefer polar coordinates: ");
    scanf("%lf %lf", &A.Cart.x, &A.Cart.y);

    return A;
}

void print_point(point A, char a) {
    if (a == 'c' || a == 'C') {
        printf("Your point is: (%.3lf, %.3lf) \n", A.Cart.x, A.Cart.y);
    } else if (a == 'p' || a == 'P') {
        printf("Your point is: (%.3lf, %.3lf) \n", sin(A.Polar.fi)*A.Polar.r, cos(A.Polar.fi)*A.Polar.r);
    } else {
        printf("Incorrect coordinates format!\n");
    }
}

double length_cartesian(point A, point B) {return sqrt(pow((A.Cart.x - B.Cart.x), 2) + pow((A.Cart.y - B.Cart.y), 2));}

double length_polar(point A, point B) {return sqrt(pow(A.Polar.r, 2) + pow(B.Polar.r, 2) - 2*A.Polar.r*B.Polar.r*cos(fabs(A.Polar.fi-B.Polar.fi)));}


// *************money*************

money input_money() {
    printf("Do you want to enter cost in kopecks only or in hryvnas and kopecs? (1/2) ");
    int answer;
    money cost;

    scanf("%d", &answer);

    if (answer == 1) {
        printf("Enter cost: ");
        scanf("%d", &cost.kopec.kopecs);
    } else if (answer == 2) {
        printf("Enter cost in hryvnia and kopeks one after another: ");
        scanf("%d %d", &cost.UAH.uah, &cost.UAH.kopecs);
    } else {
        printf("Incorrect answer, result may be wrong!\n");
    }
    return cost;
}

void print_money(money cost) {
    int answer1, answer2;

    printf("Do you want to print cost in kopeks only or in hryvnia and kopecs? (1/2) ");
    scanf("%d", &answer1);

    printf("Is ypur cost is in kopeks only or in hryvnia and kopecs? (1/2) ");
    scanf("%d", &answer2);

    if (answer1 == 1) {
        if (answer2 == 1) {
            printf("The cost is %d kopecs.\n", cost.kopec.kopecs);
        } else if (answer2 == 2) {
            printf("The cost is %d kopecs.\n", cost.UAH.uah*100 + cost.UAH.kopecs);
        } else {
            printf("Inсorrect input, result may be wrong!\n");
        }

    } else if (answer1 == 2) {
        if (answer2 == 1) {
            printf("The cost is %d hryvnia and %d kopecs.\n", cost.kopec.kopecs/100, cost.kopec.kopecs%100);
        } else if (answer2 == 2) {
            printf("The cost is %d hryvnia and %d kopecs.\n", cost.UAH.uah, cost.UAH.kopecs);
        } else {
            printf("Inсorrect input, result may be wrong!\n");
        }

    } else {
        printf("Incorrect input, result may be wrong!\n");
    }
}

// *************vector*************

my_vector input_vector() {

    my_vector vector; 
    printf("Enter points coordanates as 'x1 y1, x2 y2' or coordinates of first point and of vector to the second one as well: ");
    scanf("%lf %lf, %lf %lf", &vector.ends.x1, &vector.ends.y1, &vector.ends.x2, &vector.ends.y2);

    return vector;
}

my_vector create_vector(double x1, double y1, double x2, double y2) {
    my_vector vector;

    vector.ends.x1 = x1;
    vector.ends.y1 = y1;
    vector.ends.x2 = x2;
    vector.ends.y2 = y2;

    return vector;
}

void print_vector(my_vector v) {
    int type; 

    printf("Is your vector seted as two points or point and vector? (1/2) ");
    scanf("%d", &type);

    if (type == 1) {
        printf("Your vector starts in point (%.2lf, %.2lf) and ends in point (%.2lf, %.2lf)\n", 
        v.ends.x1, v.ends.y1, v.ends.x2, v.ends.y2);
    } else {
        printf("Your vector starts in point (%.2lf, %.2lf, %.2lf) and ends in point (%.2lf, %.2lf, %.2lf)\n", 
        v.point_and_vector.x, v.point_and_vector.y, 
        v.point_and_vector.x + v.point_and_vector.x_v, v.point_and_vector.y + v.point_and_vector.y_v);
    }
}

int is_colinear_2(my_vector m, my_vector n, int type) {
    double koef1, koef2, koef3;
    double x1, y1, x2, y2, x3, y3;
    if (type == 1) { // in means both vectors seted as two points
        x1 = m.ends.x2 - m.ends.x1;
        y1 = m.ends.y2 - m.ends.y1;

        x2 = n.ends.x2 - n.ends.x1;
        y2 = n.ends.y2 - n.ends.y1;

    } else if (type == 2) {
        x1 = m.point_and_vector.x_v;
        y1 = m.point_and_vector.y_v;

        x2 = n.point_and_vector.x_v;
        y2 = n.point_and_vector.y_v;
    }

    if (x1 == y1 && x2 == y2) {
        return 1;
    } else if ((x1 == 0 && y2 == 0 ) || (x2 == 0 && y1 == 0)) {
        return 0;
    } else if ((x1 == 0 && x2 == 0) || (y1 == 0 && y2 == 0)) {
        return 1;
    } else if (x1 == 0 || y1 == 0 || x2 == 0 || y2 == 0) {
        return 0;
    } else {
        if (x1/x2 == y1/y2) {
            return 1;
        } else {
            return 0;
        }
    }
}

int is_colinear_3(my_vector m, my_vector n, my_vector k, int type) {
    if (is_colinear_2(m, n, type) == 1) {
        if (is_colinear_2(n, k, type) == 1) {
            return 1;
            } else {return 0;}
        } else {return 0;}
}

// *************point3*************

point3 input_point3() {
    point3 a;

    printf("Input your point coordinates in Cartesian (x y z) or Spherical coordinates (r fi psi)\n\n");
    scanf("%lf %lf %lf", &a.cart.x, &a.cart.y, &a.cart.z);
    return a;
}

void print_point3(point3 a) {
    int answer;
    printf("Is your point is in 1) Cartesian or 2) Spherical coordinates? \n(1/2)? ");
    scanf("%d", &answer);

    if (answer == 1) {
        printf("\n(%.2lf, %.2lf, %.2lf)\n", a.cart.x, a.cart.y, a.cart.z);
    } else if (answer == 2) {
        double x = a.spherical.r*cos(a.spherical.fi)*cos(a.spherical.psi);
        double y = a.spherical.r*sin(a.spherical.fi)*cos(a.spherical.psi);
        double z = a.spherical.r*sin(a.spherical.psi);
        printf("\n(%.2lf, %.2lf, %.2lf)\n", x, y, z);
    } else {
        printf("Incorrect input!\n\n");
    }

}

double length(point3 A, point3 B, int type) {

    if (type == 1) {
        return sqrt(pow((A.cart.x-B.cart.x), 2) + pow((A.cart.y-B.cart.y), 2) + pow((A.cart.z-B.cart.z), 2));
    } else if (type == 2) {
        double x, y, z;
        x = A.spherical.r*cos(A.spherical.fi)*cos(A.spherical.psi) - B.spherical.r*cos(B.spherical.fi)*cos(B.spherical.psi);
        y = A.spherical.r*sin(A.spherical.fi)*cos(A.spherical.psi) - B.spherical.r*sin(B.spherical.fi)*cos(B.spherical.psi);
        z = A.spherical.r*sin(A.spherical.psi) - B.spherical.r*sin(B.spherical.psi);
        return sqrt(x*x + y*y + z*z);
    } else {
        printf("Incorrect input!\n");
    }
}

// *************figure*************

double area(figure A, int type) {
    if (type == 1) {
        // printf("Area is equal to %g\n", A.square.a*A.square.a);
        return A.square.a*A.square.a;

    } else if (type == 2) {
        double p = (A.triangle.a + A.triangle.b + A.triangle.c)/2;
        // printf("Area is equal to %g\n", sqrt(p*(p-A.triangle.a)*(p-A.triangle.b)*(p-A.triangle.c)));
        return sqrt(p*(p-A.triangle.a)*(p-A.triangle.b)*(p-A.triangle.c));

    } else if (type == 3) {
        // printf("Area is equal to %g\n", A.rectangle.a*A.rectangle.b);
        return A.rectangle.a*A.rectangle.b;

    } else if (type == 4) {
        // printf("Area is equal to %g\n", ((A.trapezium.base1+A.trapezium.base2)/2)*A.trapezium.height);
        return ((A.trapezium.base1+A.trapezium.base2)/2)*A.trapezium.height;

    } else if (type == 5) {
        // printf("Area is equal to %g\n", pi*A.circle.r*A.circle.r);
        return pi*A.circle.r*A.circle.r;

    }
}

double perimeter(figure A, int type) {
    if (type == 1) {
        // printf("Perimeter is equal to %g\n", A.square.a*4);
        return A.square.a*4;

    } else if (type == 2) {
        // printf("Perimeter is equal to %g\n", A.triangle.a + A.triangle.b + A.triangle.c);
        return A.triangle.a + A.triangle.b + A.triangle.c;

    } else if (type == 3) {
        // printf("Perimeter is equal to %g\n", (A.rectangle.a+A.rectangle.b)*2);
        return (A.rectangle.a+A.rectangle.b)*2;

    } else if (type == 4) {
        // printf("Perimeter is equal to %g\n", A.trapezium.base1+A.trapezium.base2+A.trapezium.a + A.trapezium.b);
        return A.trapezium.base1+A.trapezium.base2+A.trapezium.a+A.trapezium.b;

    } else if (type == 5) {
        // printf("Perimeter is equal to %g\n", 2*pi*A.circle.r);
        return 2*pi*A.circle.r;

    } 
}

figure input_figure() {
    int answer; 
    figure f;

    printf("Is your figure: \n  1) square\n  2) triangle\n  3) rectangle\n  4) trapezium\n  5) circle\n? ");
    scanf("%d", &answer);

    if (answer == 1) {
        printf("a = ");
        scanf("%lf", &f.square.a);

    } else if (answer == 2) {
        printf("a = ");
        scanf("%lf", &f.triangle.a);

        printf("b = ");
        scanf("%lf", &f.triangle.b);

        printf("c = ");
        scanf("%lf", &f.triangle.c);

    } else if (answer == 3) {
        printf("a = ");
        scanf("%lf", &f.rectangle.a);

        printf("b = ");
        scanf("%lf", &f.rectangle.b);

    } else if (answer == 4) {
        printf("a = ");
        scanf("%lf", &f.trapezium.a);

        printf("b = ");
        scanf("%lf", &f.trapezium.b);

        printf("base 1 = ");
        scanf("%lf", &f.trapezium.base1);

        printf("base 2 = ");
        scanf("%lf", &f.trapezium.base2);

        printf("heigth = ");
        scanf("%lf", &f.trapezium.height);

    } else if (answer == 5) {
        printf("r = ");
        scanf("%lf", &f.circle.r);

    } else {
        printf("Incorrect input!\n");
    }

    return f;
}

void print_figure(figure f) {
    int answer;

    printf("Is your figure: \n  1) square\n  2) triangle\n  3) rectangle\n  4) trapezium\n  5) circle\n? ");
    scanf("%d", &answer);

    if (answer == 1) {
        printf("Your figure is a square with side of length %g\n", f.square.a);

    } else if (answer == 2) {
        printf("Your figure is a triangle with sides of length %g, %g and %g\n", f.triangle.a, f.triangle.b, f.triangle.c);
        
    } else if (answer == 3) {
        printf("Your figure is a rectangle with sides of length %g and %g\n", f.rectangle.a, f.rectangle.b);
    
    } else if (answer == 4) {
        printf("Your figure is a trapezium with sides of length %g, %g (sides), %g and %g (bases)\n", f.trapezium.a, f.trapezium.b, f.trapezium.base1, f.trapezium.base2);

    } else if (answer == 5) {
        printf("Your figure is a circle with radius of length %g\n", f.circle.r);

    } else {
        printf("Incorrect input!\n");
    }
}


// file input output 

point input_file_point(FILE *fi) {
    point a;
    fscanf(fi, "(%lf, %lf) \n", &a.Cart.x, &a.Cart.y);
    return a;
}

money input_file_money(FILE *fi) {
    money a;
    fscanf(fi, "%d, %d\n", &a.UAH.uah, &a.UAH.kopecs);
    return a;
}

my_vector input_file_vector(FILE *fi) {
    my_vector a;
    fscanf(fi, "(%lf, %lf), (%lf, %lf)\n", &a.ends.x1, &a.ends.y1, &a.ends.x2, &a.ends.y2);
    return a;
}

point3 input_file_point3(FILE *fi) {
    point3 a;
    fscanf(fi, "(%lf, %lf, %lf)\n", &a.cart.x, &a.cart.y, &a.cart.z);
    return a;
}

figure input_file_figure(FILE *fi) {
    figure f;
    fscanf(fi, "%lf, %lf, %lf, %lf, %lf\n", &f.trapezium.a, &f.trapezium.b, &f.trapezium.base1, &f.trapezium.base2, &f.trapezium.height);
    return f;
}



void print_file_point(FILE *fi, point a) {
    fprintf(fi, "(%g, %g) ", a.Cart.x, a.Cart.y);
}

void print_file_money(FILE *fi, int type_inp, int type_out, money a) {
    if (type_out == 1) {
        if (type_inp == 1) {
            fprintf(fi, "Your value is %d kopecs.\n", a.kopec.kopecs);
        } else {
            fprintf(fi, "Your value is %d kopecs.\n", a.UAH.kopecs+a.UAH.uah*100);
        }
    } else {
        if (type_inp == 1) {
            fprintf(fi, "Your value is %d hryvnia and %d kopecs.\n", a.kopec.kopecs/100, a.kopec.kopecs%100);
        } else {
            fprintf(fi, "Your value is %d hryvnia and %d kopecs.\n", a.UAH.uah, a.UAH.kopecs);
        }
    }
}

void print_file_vector(FILE *fi, my_vector a) {
    fprintf(fi, "(%lf, %lf), (%lf, %lf)\n", a.ends.x1, a.ends.y1, a.ends.x2, a.ends.y2);
}

void print_file_point3(FILE *fi, point3 a) {
    fprintf(fi, "(%g, %g, %g) ", a.cart.x, a.cart.y, a.cart.z);
}

void print_file_figure(FILE *fi, figure f, int type) {

    if (type == 1) {
        fprintf(fi, "Your figure is a square with side of length %g\n", f.square.a);

    } else if (type == 2) {
        fprintf(fi, "Your figure is a triangle with sides of length %g, %g and %g\n", f.triangle.a, f.triangle.b, f.triangle.c);
        
    } else if (type == 3) {
        fprintf(fi, "Your figure is a rectangle with sides of length %g and %g\n", f.rectangle.a, f.rectangle.b);
    
    } else if (type == 4) {
        fprintf(fi, "Your figure is a trapezium with sides of length %g, %g (sides), %g and %g (bases)\n", f.trapezium.a, f.trapezium.b, f.trapezium.base1, f.trapezium.base2);

    } else if (type == 5) {
        fprintf(fi, "Your figure is a circle with radius of length %g\n", f.circle.r);
    }
}
