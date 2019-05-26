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
    changeSys(pointA, CARTESIAN);
    printf(" %s\n", reprPoint(pointA));
    changeSys(pointA, CYLINDRICAL);
    printf(" %s\n", reprPoint(pointA));
    changeSys(pointA, SPHERICAL);
    printf(" %s\n", reprPoint(pointA));
    changeSys(pointA, CARTESIAN);
    printf("\n---------------------------------\n"
           "Point 2 coordinate system transformations:\n");
    changeSys(pointB, CARTESIAN);
    printf(" %s\n", reprPoint(pointB));
    changeSys(pointB, CYLINDRICAL);
    printf(" %s\n", reprPoint(pointB));
    changeSys(pointB, SPHERICAL);
    printf(" %s\n", reprPoint(pointB));
    changeSys(pointB, CARTESIAN);

    printf("\n---------------------------------\n"
           "Sum of Point1 and Point2:\n");
    printf(" %s\n", reprPoint(pointAdd(pointA, pointB)));
    Edge3D *vector = makeEdge(pointA, pointB);

    printf("\n---------------------------------\n"
           "Figure rotation around vector(Point1,Point2):\n");

    printf("\n0 degrees absolute rotation:\n%s\n", reprFigure(fig));
    Angle3D* angle = makeAngle3D(10, DEGREE);
    rotateFigure(fig, angle, vector);
    printf("\n---------------------------------"
           "\n10 degrees absolute rotation:\n%s\n", reprFigure(fig));
    angle = makeAngle3D(35, DEGREE);
    rotateFigure(fig, angle, vector);
    printf("\n---------------------------------"
           "\n45 degrees absolute rotation:\n%s\n", reprFigure(fig));
    angle = makeAngle3D(45, DEGREE);
    rotateFigure(fig, angle, vector);
    printf("\n---------------------------------"
           "\n90 degrees absolute rotation:\n%s\n", reprFigure(fig));

    angle = makeAngle3D(90, DEGREE);
    rotateFigure(fig, angle, vector);

    printf("\n---------------------------------"
           "\n180 degrees absolute rotation:\n%s\n", reprFigure(fig));

    angle = makeAngle3D(180, DEGREE);
    rotateFigure(fig, angle, vector);

    printf("\n---------------------------------"
           "\n360 degrees absolute rotation:\n%s\n", reprFigure(fig));
    printf("\n---------------------------------\n"
           "Projection figure onto a plane with normal vector (pointA,pointB), plane passes through pointA");
    printf("\n %s", reprFigure(projectFigure(fig, vector)));

    freeFigure(fig);
    freeEdge(vector);
    free(angle);
    free(pointA);
    free(pointB);
    return 0;
}

IType fileReadPoint(FILE *filePtr, Point3D *newPoint){
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
        free(type);
        if (strcmp(sys,"CARTESIAN")==0) {
            *newPoint = *makePoint(x, y, z, CARTESIAN);
        } else if (strcmp(sys,"CYLINDRICAL")==0) {
            *newPoint = *makePoint(x, y, z, CYLINDRICAL);
        } else if (strcmp(sys,"SPHERICAL")==0) {
            *newPoint = *makePoint(x, y, z, SPHERICAL);
        } else {
            free(sys);
            return SIGIOR;}
        free(sys);
    } else {
        free(sys);
        return SIGIOR;}

    return 0;
}

DType consoleReadPoint(Point3D *newPoint){
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
            *newPoint = *makePoint(x, y, z, CARTESIAN);
        } else if (strcmp(sys,"CYLINDRICAL")==0) {
            *newPoint = *makePoint(x, y, z, CYLINDRICAL);
        } else if (strcmp(sys,"SPHERICAL")==0) {
            *newPoint = *makePoint(x, y, z, SPHERICAL);
        } else { return SIGIOR;}

    } else {return SIGIOR;}

    return 0;
}

IType readFromFile(ChType* filename, ChType* output, IType writeTo){
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


       Point3D* pointA = makePoint(0,0,0,CARTESIAN);
       if (fileReadPoint(filePtr, pointA)!=0) {
           return SIGIOR;
       }

       Point3D* pointB = makePoint(0,0,0,CARTESIAN);
       if (fileReadPoint(filePtr, pointB)!=0) {
           return SIGIOR;
       }

       IType pointsNum;
       IType edgesNum;

       if (fscanf(filePtr, "%i %i", &pointsNum, &edgesNum)!=2){return SIGIOR;}
       Point3DArray* pArray = initPointArray(pointsNum);
       Edge3DArray* eArray = initEdgeArray(edgesNum);

       for (int i=0; i<pointsNum;i++){
           Point3D* newPoint = makePoint(0,0,0,1);
           if (fileReadPoint(filePtr, newPoint)!=0){return SIGIOR;}
           changeSys(newPoint,CARTESIAN);
           pArray->data[i] = newPoint;
       }

       for (int i=0; i<edgesNum;i++){
           Point3D* newPointA = makePoint(0,0,0,1);
           Point3D* newPointB = makePoint(0,0,0,1);
           if (fileReadPoint(filePtr, newPointA)!=0 || fileReadPoint(filePtr, newPointB)!=0 ){return SIGIOR;}
           changeSys(newPointA,CARTESIAN);
           changeSys(newPointB,CARTESIAN);
           eArray->data[i] = makeEdge(newPointA, newPointB);
       }

       Figure3D* newFig = makeFigure(eArray, pArray);
       test(pointA, pointB, newFig, output, writeTo);

   }
   fclose(filePtr);
   return 0;
}

IType readFromConsole(ChType* output, IType writeTo) {
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



    Point3D *pointA = makePoint(0, 0, 0, CARTESIAN);
    if (consoleReadPoint(pointA) != 0) {
        return SIGIOR;
    }

    Point3D *pointB = makePoint(0, 0, 0, CARTESIAN);
    if (consoleReadPoint(pointB) != 0) {
        return SIGIOR;
    }

    IType pointsNum;
    IType edgesNum;

    if (scanf("%i %i", &pointsNum, &edgesNum) != 2) { return SIGIOR; }
    Point3DArray *pArray = initPointArray(pointsNum);
    Edge3DArray *eArray = initEdgeArray(edgesNum);

    for (int i = 0; i < pointsNum; i++) {
        Point3D *newPoint = makePoint(0, 0, 0, 1);
        if (consoleReadPoint(newPoint) != 0) { return SIGIOR; }
        changeSys(newPoint, CARTESIAN);
        pArray->data[i] = newPoint;
    }

    for (int i = 0; i < edgesNum; i++) {
        Point3D *newPointA = makePoint(0, 0, 0, 1);
        Point3D *newPointB = makePoint(0, 0, 0, 1);
        if (consoleReadPoint(newPointA) != 0 || consoleReadPoint(newPointB) != 0) { return SIGIOR; }
        changeSys(newPointA, CARTESIAN);
        changeSys(newPointB, CARTESIAN);
        eArray->data[i] = makeEdge(newPointA, newPointB);
    }

    Figure3D *newFig = makeFigure(eArray, pArray);
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
    while (scanf("%i",&writeTo)!=1 || writeTo<0 || writeTo>1){
        printf("Wrong input\nSelect output type:\n0-to console, 1-to file\n");
    }

    printf("Select input type:\n1-from file, 2-from console\n");
    IType status;
    while (scanf("%i",&status)!=1 || status<1 || status>2){
        printf("Wrong input\nSelect input type:\n1-from file, 2-from console\n");
    }
    if (status==1){
        printf("Reading from 'Quaternion_test.txt'.\nWriting to 'Quaternion_test_output.txt'.");

        IType fileStatus = readFromFile("../tests/Quaternion_test.txt", "../tests/Quaternion_test_output.txt",writeTo);
        if (fileStatus== SIGFNF){
            printf("File doesnt exists!\n");
            return 0;
        } else if (fileStatus == SIGIOR) {
            printf("File reading error!\n");
            return 0;
        } else {
            return 0;
        }
    } else if (status==2){
        if (readFromConsole("../tests/Quaternion_test_output.txt",writeTo)!=0){
            printf("Wrong input");
            return 0;
        }
    } else{printf("\nUNEXPECTED ERROR\n");}

    return 0;
}