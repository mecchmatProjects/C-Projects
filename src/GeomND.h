#ifndef HEADER_P
#define HEADER_P 1

#define LEN 200

#define SCIENTIFIC 2
#define SHORTEST 1
#define FLOAT 0

#define F_POINT 1
#define F_VECTOR 1
#define F_LINE 2
#define F_SEGMENT 2
#define F_PLANE 3
#define F_PYRAMID 4

typedef unsigned int ntype;
typedef float ftype;

typedef struct{
    ntype N;
    ftype *coordinates;
}PointND;

typedef struct{
    int N;
    PointND point1, point2;
}SegmentND;

typedef struct{
    ntype N;
    ntype NUM;
    PointND apex;
    PointND *points;
}PyramidND;

typedef struct{
    ntype N;
    ftype* coordinates;
}VectorND;

typedef struct{
    int N;
    PointND point1, point2;
}LineND;

typedef struct{
    ntype N;
    PointND *points;
}PlaneND;


extern ftype* input_coordinates(ntype N);

//input from console functions
extern PointND input_point();
extern SegmentND input_segment();
extern PyramidND input_pyramid();
extern VectorND input_vector();
extern LineND input_line();
extern PlaneND input_plane();
//output to console functions
extern void output_point(PointND point, ntype type, ntype width, ntype precision);
extern void output_segment(SegmentND segment, ntype type, ntype width, ntype precision);
extern void output_pyramid(PyramidND point, ntype type, ntype width, ntype precision);
extern void output_line(LineND line, ntype type, ntype width, ntype precision);
extern void output_plane(PlaneND plane, ntype type, ntype width, ntype precision);
extern void output_vector(VectorND vect, ntype type, ntype width, ntype precision);

//read from binary file functions
extern ntype inputBinaryFile_point(char* file, PointND *p);
extern ntype inputBinaryFile_segment(char* file, SegmentND *s);
extern ntype inputBinaryFile_pyramid(char* file, PyramidND *pyramid);
extern ntype inputBinaryFile_line(char* file, LineND *line);
extern ntype inputBinaryFile_plane(char* file, PlaneND *plane);
extern ntype inputBinaryFile_vector(char* file, VectorND *vect);

//write to binary file functions
extern ntype outputBinaryFile_point(char* file, PointND p);
extern ntype outputBinaryFile_segment(char* file, SegmentND s);
extern ntype outputBinaryFile_pyramid(char* file, PyramidND pyramid);
extern ntype outputBinaryFile_line(char* file, LineND line);
extern ntype outputBinaryFile_plane(char* file, PlaneND plane);
extern ntype outputBinaryFile_vector(char* file, VectorND vect);

//functions with vectors
extern VectorND add(VectorND v1, VectorND v2);
extern VectorND sub(VectorND v1, VectorND v2);
extern ftype multS(VectorND v1, VectorND v2);
extern VectorND mult(VectorND *vectors);

//other helpful functions
extern VectorND normal(PlaneND pl);
extern double get_triangle_square(PointND p1, PointND p2, PointND p3);

//functions intersect
extern LineND intersect_planes(PlaneND *planes);

//functions with PyramidND
extern ftype* side_squaresND(PyramidND p);

//functions with vector and ftype
extern VectorND mul(VectorND vect, ftype num);
extern VectorND division(VectorND vect, ftype num);

//length of vector and length of segment
extern ftype module(VectorND vect);
extern ftype length(SegmentND segment);

//unary operations
extern VectorND unadd(VectorND* vect1, VectorND vect2);
extern VectorND unsub(VectorND* vect1, VectorND vect2);
extern VectorND unmul(VectorND* vect1, ftype num);
extern VectorND undiv(VectorND* vect1, ftype num);

//functions to convert vector to segment and segment to vector
extern SegmentND vect_to_segm(VectorND vect);
extern VectorND segm_to_vect(SegmentND segm);
extern LineND vect_to_line(VectorND vect);
extern LineND segm_to_line(SegmentND segm);
extern PointND vect_to_point(VectorND vect);
extern VectorND point_to_vect(PointND point);
extern VectorND line_to_vect(LineND line);

//functions to read ftype and ntype numbers
extern char* f_read();
extern char* i_read();

//functions which generate random objects
extern PointND generate_point(ntype N);
extern SegmentND generate_segment(ntype N);
extern PyramidND generate_pyramid(ntype N);
extern VectorND generate_vector(ntype N);
extern LineND generate_line(ntype N);
extern PlaneND generate_plane(ntype N);

#endif