#include "../headers/common.h"
#include "../headers/Point3D.h"
#include "../headers/Angle3D.h"
#include "../headers/Edge3D.h"
#include "../headers/Figure3D.h"
#include "../headers/Progections3D.h"

#include <stdio.h>
#include <stdlib.h>

IType test(Point3D* pointA, Point3D* pointB, Figure3D* fig, ChType* output, IType writeTo){
    /** Test cases for project.
     *
     * Results are printed out in console and output file.
     *
     */
    if (writeTo==1){
        FILE* filePtr = freopen(output,"w",stdout);
        if (filePtr == NULL){
            return SIGFNF;
        }
    }

    printf("Point 1 coordinate system transformations:\n");
    //fprintf(filePtr,"Point 1 coordinate system transformations:\n");
    change_system(pointA, CARTESIAN);
    printf(" %s\n", _repr_Point(pointA));
    //fprintf(filePtr," %s\n", _repr_Point(point_A));
    change_system(pointA, CYLINDRICAL);
    printf(" %s\n", _repr_Point(pointA));
    //fprintf(filePtr," %s\n", _repr_Point(point_A));
    change_system(pointA, SPHERICAL);
    printf(" %s\n", _repr_Point(pointA));
    //fprintf(filePtr," %s\n", _repr_Point(point_A));
    change_system(pointA, CARTESIAN);
    printf("\n---------------------------------\n"
           "Point 2 coordinate system transformations:\n");
    change_system(pointB, CARTESIAN);
    printf(" %s\n", _repr_Point(pointB));
    change_system(pointB, CYLINDRICAL);
    printf(" %s\n", _repr_Point(pointB));
    change_system(pointB, SPHERICAL);
    printf(" %s\n", _repr_Point(pointB));
    change_system(pointB, CARTESIAN);

    printf("\n---------------------------------\n"
           "Sum of Point1 and Point2:\n");
    printf(" %s\n", _repr_Point(pointAdd(pointA, pointB)));
    Edge3D *vector = make_Edge(pointA, pointB);

    printf("\n---------------------------------\n"
           "Figure rotation around vector(Point1,Point2):\n");

    printf("\n0 degrees absolute rotation:\n%s\n", _repr_Figure(fig));
    Angle3D* angle = make_Angle3D(10, DEGREE);
    rotate_Figure(fig, angle, vector);
    printf("\n---------------------------------"
           "\n10 degrees absolute rotation:\n%s\n", _repr_Figure(fig));
    angle = make_Angle3D(35, DEGREE);
    rotate_Figure(fig, angle, vector);
    printf("\n---------------------------------"
           "\n45 degrees absolute rotation:\n%s\n", _repr_Figure(fig));
    angle = make_Angle3D(45, DEGREE);
    rotate_Figure(fig, angle, vector);
    printf("\n---------------------------------"
           "\n90 degrees absolute rotation:\n%s\n", _repr_Figure(fig));

    angle = make_Angle3D(90, DEGREE);
    rotate_Figure(fig, angle, vector);

    printf("\n---------------------------------"
           "\n180 degrees absolute rotation:\n%s\n", _repr_Figure(fig));

    angle = make_Angle3D(180, DEGREE);
    rotate_Figure(fig, angle, vector);

    printf("\n---------------------------------"
           "\n360 degrees absolute rotation:\n%s\n", _repr_Figure(fig));
    printf("\n---------------------------------\n"
           "Projection figure onto a plane with normal vector (point_A,point_B), plane passes through point_A");
    printf("\n %s", _repr_Figure(project_Figure(fig, vector)));

    free_Figure(fig);
    free_Edge(vector);
    free(angle);
    free(pointA);
    free(pointB);
    return 0;
}

IType Point_from_file(FILE *filePtr, Point3D *newPoint){
    /** Reads point from file stream.
     *
     * Point should be represented as:
     * Point {first coordinate} {second coordinate} {third coordinate} {coordinate system}
     * Example:
     *  Point 1 1 0 CARTESIAN
     *
     */
    DType x;
    DType y;
    DType z;
    ChType* type = malloc(sizeof(ChType)*50);
    ChType* sys = malloc(sizeof(ChType)*50);

    if(fscanf(filePtr,"%s %lf %lf %lf %s",type, &x, &y, &z, sys) == 5 && strcmp(type,"Point") == 0){
        if (strcmp(sys,"CARTESIAN")==0) {
            *newPoint = *make_Point(x, y, z, CARTESIAN);
        } else if (strcmp(sys,"CYLINDRICAL")==0) {
            *newPoint = *make_Point(x, y, z, CYLINDRICAL);
        } else if (strcmp(sys,"SPHERICAL")==0) {
            *newPoint = *make_Point(x, y, z, SPHERICAL);
        } else {
            free(sys);
            return SIGIOR;}
        free(sys);

    } else {
        free(sys);
        return SIGIOR;}
    return 0;
}

DType Point_from_console(Point3D *newPoint){
    /** Reads point from console.
     *
     * Point should be represented as:
     * Point {first coordinate} {second coordinate} {third coordinate} {coordinate system}
     * Example:
     *  Point 1 1 0 CARTESIAN
     *
     */
    DType x;
    DType y;
    DType z;
    ChType* type = malloc(sizeof(ChType)*20);
    ChType* sys = malloc(sizeof(ChType)*20);

    if(scanf("%s %lf %lf %lf %s",type, &x, &y, &z, sys) == 5 && strcmp(type,"Point") == 0){
        if (strcmp(sys,"CARTESIAN")==0) {
            *newPoint = *make_Point(x, y, z, CARTESIAN);
        } else if (strcmp(sys,"CYLINDRICAL")==0) {
            *newPoint = *make_Point(x, y, z, CYLINDRICAL);
        } else if (strcmp(sys,"SPHERICAL")==0) {
            *newPoint = *make_Point(x, y, z, SPHERICAL);
        } else { return SIGIOR;}

    } else {return SIGIOR;}

    return 0;
}

IType read_from_file(ChType *filename, ChType *output, IType writeTo){
    /** Reads test data from txt file.
     *
     * If writeTo == 1 writes data to output.txt
     *
     * In first two lines should be two points representation, then should be two IType values "p", "e":
     * first represent number of points in figure, second -- number of edges.
     * In following p+2*e lines should be:
     *  1) p points of figure
     *  2) 2*e points each pair represents an edge of figure.
     * Returns SIGFNF if file doesn't exists and SIGIOR if there was an input error.
     * Runs test function in other case.
     */
    FILE* filePtr = fopen(filename,"r");
    if (filePtr == NULL){
        return SIGFNF;
    } else {


        Point3D* pointA = make_Point(0, 0, 0, CARTESIAN);
        if (Point_from_file(filePtr, pointA)!=0) {
            return SIGIOR;
        }

        Point3D* pointB = make_Point(0, 0, 0, CARTESIAN);
        if (Point_from_file(filePtr, pointB)!=0) {
            return SIGIOR;
        }

        IType pointsNum;
        IType edgesNum;

        if (fscanf(filePtr, "%i %i", &pointsNum, &edgesNum)!=2){return SIGIOR;}
        Point3DArray* pArray = make_PointArray(pointsNum);
        Edge3DArray* eArray = make_EdgeArray(edgesNum);

        for (int i=0; i<pointsNum;i++){
            Point3D* newPoint = make_Point(0, 0, 0, 1);
            if (Point_from_file(filePtr, newPoint)!=0){return SIGIOR;}
            change_system(newPoint, CARTESIAN);
            pArray->data[i] = newPoint;
        }

        for (int i=0; i<edgesNum;i++){
            Point3D* newPointA = make_Point(0, 0, 0, 1);
            Point3D* newPointB = make_Point(0, 0, 0, 1);
            if (Point_from_file(filePtr, newPointA)!=0 || Point_from_file(filePtr, newPointB)!=0 ){return SIGIOR;}
            change_system(newPointA, CARTESIAN);
            change_system(newPointB, CARTESIAN);
            eArray->data[i] = make_Edge(newPointA, newPointB);
        }

        Figure3D* newFig = make_Figure(eArray, pArray);
        test(pointA, pointB, newFig, output, writeTo);

    }
    fclose(filePtr);
    return 0;
}

IType read_from_console(ChType *output, IType writeTo) {
    /** Reads test data from console.
     *
     * If writeTo == writes to output.txt
     *
     * In first two lines should be two points representation, then should be two IType values "p", "e":
     * first represent number of points in figure, second -- number of edges.
     * In following p+2*e lines should be:
     *  1) p points of figure
     *  2) 2*e points each pair represents an edge of figure.
     * Returns SIGFNF if file doesn't exists and SIGIOR if there was an input error.
     * Runs test function in other case.
     */



    Point3D *pointA = make_Point(0, 0, 0, CARTESIAN);
    if (Point_from_console(pointA) != 0) {
        return SIGIOR;
    }

    Point3D *pointB = make_Point(0, 0, 0, CARTESIAN);
    if (Point_from_console(pointB) != 0) {
        return SIGIOR;
    }

    IType pointsNum;
    IType edgesNum;

    if (scanf("%i %i", &pointsNum, &edgesNum) != 2) { return SIGIOR; }
    Point3DArray *pArray = make_PointArray(pointsNum);
    Edge3DArray *eArray = make_EdgeArray(edgesNum);

    for (int i = 0; i < pointsNum; i++) {
        Point3D *newPoint = make_Point(0, 0, 0, 1);
        if (Point_from_console(newPoint) != 0) { return SIGIOR; }
        change_system(newPoint, CARTESIAN);
        pArray->data[i] = newPoint;
    }

    for (int i = 0; i < edgesNum; i++) {
        Point3D *newPointA = make_Point(0, 0, 0, 1);
        Point3D *newPointB = make_Point(0, 0, 0, 1);
        if (Point_from_console(newPointA) != 0 || Point_from_console(newPointB) != 0) { return SIGIOR; }
        change_system(newPointA, CARTESIAN);
        change_system(newPointB, CARTESIAN);
        eArray->data[i] = make_Edge(newPointA, newPointB);
    }

    Figure3D *newFig = make_Figure(eArray, pArray);
    test(pointA, pointB, newFig, output, writeTo);

    return 0;
}


int main() {
    /**
     * In first two lines should be two points representation, then should be two IType values "p", "e":
     * first represent number of points in figure, second -- number of edges.
     * In following p+2*e lines should be:
     *  1) p points of figure
     *  2) 2*e points each pair represents an edge of figure.
     *
     */
    IType writeTo;
    printf("Select output type:\n0-to console, 1-to file\n");
    while (scanf("%i", &writeTo) != 1 || writeTo < 0 || writeTo > 1) {
        printf("Wrong input\nSelect output type:\n0-to console, 1-to file\n");
    }

    printf("Select input type:\n1-from file, 2-from console\n");
    IType status;
    while (scanf("%i", &status) != 1 || status < 1 || status > 2) {
        printf("Wrong input\nSelect input type:\n1-from file, 2-from console\n");
    }
    if (status == 1) {
        printf("Reading from 'Quaternion_test.txt'.\nWriting to 'Quaternion_test_output.txt'.");

        IType fileStatus = read_from_file("../tests/Quaternion_test.txt", "../tests/Quaternion_test_output.txt",
                                          writeTo);
        if (fileStatus == SIGFNF) {
            printf("File doesnt exists!\n");
            return 0;
        } else if (fileStatus == SIGIOR) {
            printf("File reading error!\n");
            return 0;
        } else {
            return 0;
        }
    } else if (status == 2) {
        if (read_from_console("../tests/Quaternion_test_output.txt", writeTo) != 0) {
            printf("Wrong input");
            return 0;
        }
    } else { printf("\nUNEXPECTED ERROR\n"); }

    return 0;
}