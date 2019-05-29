#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"GeomND.h"

// INPUT FROM CONSOLE
ftype* input_coordinates(ntype N)
{
    if (N<=0)
    {
        printf("Error: N<=0, must be >0 !");
        return 0;
    }
    ftype *rez;
    char* arr;
    rez = (ftype*)malloc(N*sizeof(ftype));
    for (ntype i=0; i<N; i++)
    {
        arr = f_read();
        if (arr[0]=='N' && arr[1]=='O')
        {
            printf("Couldn't convert your thing into ftype.\nTry to enter this coordinate again. ");
            i--;
        }
        else
        {
            rez[i] = atof(arr);
        }
        free(arr);
    }
    return rez;
}

PointND input_point()
{
    PointND THE_POINT;
    printf("N = ");
    char* arr;
    arr = i_read();
    while (arr[0]=='N' || atoi(arr)<=0)
    {
        printf("Enter a natural number! ");
        arr = i_read();
    }
    THE_POINT.N = atoi(arr);
    free(arr);
    printf("Point's coordinates: ");
    THE_POINT.coordinates = input_coordinates(THE_POINT.N);
    return THE_POINT;
}

SegmentND input_segment()
{
    char* arr;
    SegmentND S;
    printf("N = ");
    arr = i_read();
    while (arr[0]=='N' || atoi(arr)<=0)
    {
        printf("Enter a natural number! ");
        arr = i_read();
    }
    S.N = atoi(arr);
    free(arr);
    S.point1.N = S.N;
    S.point2.N = S.N;
    printf("Coordinates of point1 of your segment: ");
    S.point1.coordinates = input_coordinates(S.N);
    printf("Coordinates of point2 of your segment: ");
    S.point2.coordinates = input_coordinates(S.N);
    return S;
}

PyramidND input_pyramid()
{
    char* arr;
    PyramidND PYR;
    printf("N = ");
    arr = i_read();
    while (arr[0]=='N' || atoi(arr)<=0)
    {
        printf("Enter a natural number! ");
        arr = i_read();
    }
    PYR.N = atoi(arr);
    free(arr);
    printf("NUMBER of points = ");
    arr = i_read();
    while (arr[0]=='N' || atoi(arr)<=0)
    {
        printf("Enter a natural number! ");
        arr = i_read();
    }
    PYR.NUM = atoi(arr);
    free(arr);
    PYR.points = (PointND*)malloc((PYR.NUM)*sizeof(PointND));
    PYR.apex.N = PYR.N;
    printf("Coordinates of the pyramid's apex:");
    PYR.apex.coordinates = input_coordinates(PYR.N);
    for (ntype i=0; i<=PYR.NUM; i++)
    {
        PYR.points[i].N = PYR.N;
        printf("coordinates of point[%d] of the pyramid: ", i);
        PYR.points[i].coordinates = input_coordinates(PYR.N);
    }
    return PYR;
}

VectorND input_vector()
{
    char *arr;
    VectorND VECT;
    printf("N = ");
    arr = i_read();
    while (arr[0]=='N' || atoi(arr)<=0)
    {
        printf("Enter a natural number! ");
        arr = i_read();
    }
    VECT.N = atoi(arr);
    free(arr);
    printf("Input coordinates of the vector: ");
    VECT.coordinates = input_coordinates(VECT.N);
    return VECT;
}

LineND input_line()
{
    char* arr;
    LineND LINE;
    printf("N = ");
    arr = i_read();
    while (arr[0]=='N' || atoi(arr)<=0)
    {
        printf("Enter a natural number! ");
        arr = i_read();
    }
    LINE.N = atoi(arr);
    free(arr);
    LINE.point1.N =
    LINE.point2.N = LINE.N;
    LINE.point1.coordinates = input_coordinates(LINE.N);
    printf("Point2 coordinates: ");
    LINE.point2.coordinates = input_coordinates(LINE.N);
    return LINE;
}

PlaneND input_plane()
{
    char* arr;
    PlaneND PLANE;
    printf("N=");
    arr = i_read();
    while (arr[0]=='N' || atoi(arr)<=0)
    {
        printf("Enter a natural number! ");
        arr = i_read();
    }
    PLANE.N = atoi(arr);
    free(arr);
    PLANE.points = (PointND*)malloc(PLANE.N*sizeof(PointND));
    for (ntype i=0; i<PLANE.N; i++)
    {
        PLANE.points[i].N = PLANE.N;
        printf("Coordinates of %i-th point of the plane: ", i);
        PLANE.points[i].coordinates = input_coordinates(PLANE.N);
    }
    return PLANE;
}

AngleND input_angle()
{
    char* arr;
    AngleND angle;
    printf("Angle ND; N = ");
    arr = i_read();
    while (arr[0]=='N' || atoi(arr)<=1)
    {
        printf("Enter a natural number more than one! ");
        arr = i_read();
    }
    angle.N = atoi(arr);
    free(arr);
    printf("\nAngle components: ");
    angle.components = input_coordinates(angle.N-1);
    return angle;
}

// OUTPUT TO CONSOLE
void output_coordinates(PointND point, ntype type, ntype width, ntype precision)
{
    char modes[3][4] = {"f ", "g ", "e "};
    char out[96] = "%", buf[64];
    sprintf(buf, "%d.%d", width, precision);
    strcat(out, buf);
    strcat(out, modes[type]);
    for (ntype i=0; i<point.N; i++)
    {
        printf(out, point.coordinates[i]);
    }
    printf("\n");
}

void output_point(PointND point, ntype type, ntype width, ntype precision)
{
    printf("Point%dD: ", point.N);
    output_coordinates(point, type, width, precision);
}

void output_segment(SegmentND segment, ntype type, ntype width, ntype precision)
{
    printf("Segment%dD:\nPoint1: ", segment.N);
    output_coordinates(segment.point1, type, width, precision);
    printf("\nPoint2: ");
    output_coordinates(segment.point2, type, width, precision);
}

void output_pyramid(PyramidND pyramid, ntype type, ntype width, ntype precision)
{
    printf("Pyramid%dD:\n", pyramid.N);
    printf("apex:");
    output_coordinates(pyramid.apex, type, width, precision);
    printf("number of points: %d", pyramid.NUM);
    for (ntype i=0; i<pyramid.NUM; i++)
    {
        printf("Point[%d]", i+1);
        output_coordinates(pyramid.points[i], type, width, precision);
    }
}

void output_line(LineND line, ntype type, ntype width, ntype precision)
{
    printf("Line%dD:\nPoint1: ", line.N);
    output_coordinates(line.point1, type, width, precision);
    printf("Point2: ");
    output_coordinates(line.point2, type, width, precision);
}

void output_plane(PlaneND plane, ntype type, ntype width, ntype precision)
{
    printf("Plane%dD:\n", plane.N);
    for (ntype i=0; i<plane.N; i++)
    {
        printf("Point%d: ", i+1);
        output_coordinates(plane.points[i], type, width, precision);
    }
}

void output_vector(VectorND vect, ntype type, ntype width, ntype precision)
{
    printf("Vector%dD: ", vect.N);
    output_coordinates(vect_to_point(vect), type, width, precision);
}

void output_angle(AngleND angle, ntype type, ntype width, ntype precision)
{
    printf("Angle%dD: ", angle.N);
    char modes[3][4] = {"f ", "g ", "e "};
    char out[96] = "%", buf[64];
    sprintf(buf, "%d.%d", width, precision);
    strcat(out, buf);
    strcat(out, modes[type]);
    for (ntype i=0; i<angle.N-1; i++)
    {
        printf(out, angle.components[i]);
    }
    printf("\n");
}

// READ FROM BINARY FILE
ntype inputBinaryFile_point(char* file, PointND *p)
{
    FILE *f;
    ntype m=0, N;
    float fl_num;
    f = fopen(file, "rb");
    if (f!=NULL)
    {
        fseek(f, 0, SEEK_SET);
        //printf("f %d", p.N);
        while (m!=F_POINT)
        {
            fread(&m, sizeof(int), 1, f);
            fread(&N, sizeof(int), 1, f);
            if (m==1)
            {

            }
            else if (m==F_LINE)
            {
                for (int i=0; i<2; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PLANE)
            {
                for (int i=0; i<N; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PYRAMID)
            {
                for (int i=0; i<N+1; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_ANGLE)
            {
                for (int i=0; i<N-1; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
        }
        p->N = N;
        p->coordinates = (float*)malloc(p->N*sizeof(float));
        fread(p->coordinates, sizeof(ftype), p->N, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype inputBinaryFile_segment(char* file, SegmentND *s)
{
    ntype status;
    FILE *f;
    ntype m=0, N;
    float fl_num;
    f = fopen(file, "rb");
    if (f!=NULL)
    {
        fseek(f, 0, SEEK_SET);
        while (m!=F_SEGMENT)
        {
            fread(&m, sizeof(int), 1, f);
            fread(&N, sizeof(int), 1, f);
            if (m==1)
            {
                for (int i=0; i<N; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
            else if (m==F_LINE)
            {

            }
            else if (m==F_PLANE)
            {
                for (int i=0; i<N; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PYRAMID)
            {
                for (int i=0; i<N+1; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_ANGLE)
            {
                for (int i=0; i<N-1; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
        }
        s->N = N;
        s->point1.N = N;
        s->point2.N = N;
        s->point1.coordinates = (float*)malloc((s->N)*sizeof(ftype));
        s->point2.coordinates = (float*)malloc((s->N)*sizeof(ftype));
        fread(s->point1.coordinates, sizeof(ftype), s->N, f);
        fread(s->point2.coordinates, sizeof(ftype), s->N, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype inputBinaryFile_pyramid(char* file, PyramidND *pyramid)
{
    ntype status;
    FILE *f;
    ntype m=0, N;
    float fl_num;
    f = fopen(file, "rb");
    if (f!=NULL)
    {
        fseek(f, 0, SEEK_SET);
        while (m!=F_PYRAMID)
        {
            fread(&m, sizeof(int), 1, f);
            fread(&N, sizeof(int), 1, f);
            if (m==1)
            {
                for (int i=0; i<N; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
            else if (m==F_LINE)
            {
                for (int i=0; i<2; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PLANE)
            {
                for (int i=0; i<N; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_ANGLE)
            {
                for (int i=0; i<N-1; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
        }
        pyramid->N = N;
        int num;
        fread(&num, sizeof(int), 1, f);
        pyramid->NUM = num;
        pyramid->points = (PointND*)malloc(num*sizeof(PointND));
        for (int i=0; i<num; i++)
        {
            pyramid->points[i].N = N;
        }
        pyramid->apex.N = N;
        pyramid->apex.coordinates = (float*)malloc((pyramid->N)*sizeof(ftype));
        fread(pyramid->apex.coordinates, sizeof(ftype), pyramid->N, f);
        for (int i=0; i<pyramid->NUM; i++)
        {
            pyramid->points[i].coordinates = (float*)malloc((pyramid->N)*sizeof(ftype));
            fread(pyramid->points[i].coordinates, sizeof(ftype), pyramid->N, f);
        }
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype inputBinaryFile_line(char* file, LineND *line)
{
    ntype status;
    FILE *f;
    ntype m=0, N;
    float fl_num;
    f = fopen(file, "rb");
    if (f!=NULL)
    {
        fseek(f, 0, SEEK_SET);
        while (m!=F_LINE)
        {
            fread(&m, sizeof(int), 1, f);
            fread(&N, sizeof(int), 1, f);
            if (m==1)
            {
                for (int i=0; i<N; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
            else if (m==F_LINE)
            {

            }
            else if (m==F_PLANE)
            {
                for (int i=0; i<N; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PYRAMID)
            {
                for (int i=0; i<N+1; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_ANGLE)
            {
                for (int i=0; i<N-1; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
        }
        line->N = N;
        line->point1.N = N;
        line->point2.N = N;
        line->point1.coordinates = (float*)malloc((line->N)*sizeof(ftype));
        line->point2.coordinates = (float*)malloc((line->N)*sizeof(ftype));
        fread(line->point1.coordinates, sizeof(ftype), line->N, f);
        fread(line->point2.coordinates, sizeof(ftype), line->N, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype inputBinaryFile_plane(char* file, PlaneND *plane)
{
    FILE *f;
    ntype m=0, N;
    float fl_num;
    f = fopen(file, "rb");
    if (f!=NULL)
    {
        fseek(f, 0, SEEK_SET);
        while (m!=F_PLANE)
        {
            fread(&m, sizeof(int), 1, f);
            fread(&N, sizeof(int), 1, f);
            if (m==1)
            {
                for (int i=0; i<N; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
            else if (m==F_LINE)
            {
                for (int i=0; i<2; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PLANE)
            {

            }
            else if (m==F_PYRAMID)
            {
                for (int i=0; i<N+1; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_ANGLE)
            {
                for (int i=0; i<N-1; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
        }
        plane->N = N;
        plane->points = (PointND*)malloc(N*sizeof(PointND));
        for (int i=0; i<N; i++)
        {
            plane->points[i].N = N;
        }
        for (int i=0; i<N; i++)
        {
            plane->points[i].coordinates = (float*)malloc((plane->N)*sizeof(ftype));
            fread(plane->points[i].coordinates, sizeof(ftype), plane->N, f);
        }
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype inputBinaryFile_vector(char* file, VectorND *vect)
{
    FILE *f;
    ntype m=0, N;
    float fl_num;
    f = fopen(file, "rb");
    if (f!=NULL)
    {
        fseek(f, 0, SEEK_SET);
        //printf("f %d", p.N);
        while (m!=F_VECTOR)
        {
            fread(&m, sizeof(int), 1, f);
            fread(&N, sizeof(int), 1, f);
            if (m==1)
            {

            }
            else if (m==F_LINE)
            {
                for (int i=0; i<2; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PLANE)
            {
                for (int i=0; i<N; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PYRAMID)
            {
                for (int i=0; i<N+1; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_ANGLE)
            {
                for (int i=0; i<N-1; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
        }
        vect->N = N;
        vect->coordinates = (float*)malloc(vect->N*sizeof(float));
        fread(vect->coordinates, sizeof(ftype), vect->N, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype inputBinaryFile_angle(char* file, AngleND *angle)
{
    FILE *f;
    ntype m=0, N;
    float fl_num;
    f = fopen(file, "rb");
    if (f!=NULL)
    {
        fseek(f, 0, SEEK_SET);
        //printf("f %d", p.N);
        while (m!=F_ANGLE)
        {
            fread(&m, sizeof(int), 1, f);
            fread(&N, sizeof(int), 1, f);
            if (m==1)
            {
                for (int i=0; i<N; i++)
                {
                    fread(&fl_num, sizeof(float), 1, f);
                }
            }
            else if (m==F_LINE)
            {
                for (int i=0; i<2; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PLANE)
            {
                for (int i=0; i<N; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
            else if (m==F_PYRAMID)
            {
                for (int i=0; i<N+1; i++)
                {
                    for (int j=0; j<N; j++)
                    {
                        fread(&fl_num, sizeof(float), 1, f);
                    }
                }
            }
        }
        angle->N = N;
        angle->components = (float*)malloc((angle->N-1)*sizeof(float));
        fread(angle->components, sizeof(ftype), angle->N-1, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

// WRITE TO BINARY FILE
ntype outputBinaryFile_point(char* file, PointND p)
{
    FILE *f;
    f = fopen(file, "ab");
    if (f!=NULL)
    {
        ntype m = F_POINT;
        fwrite(&m, sizeof(ntype), 1, f);
        fwrite(&p.N, sizeof(int), 1, f);
        fwrite(p.coordinates, sizeof(ftype), p.N, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputBinaryFile_segment(char* file, SegmentND s)
{
    FILE *f;
    ntype m=F_SEGMENT;
    f = fopen(file, "ab");
    if (f!=NULL)
    {
        fwrite(&m, sizeof(int), 1, f);
        fwrite(&s.N, sizeof(int), 1, f);
        fwrite(s.point1.coordinates, sizeof(ftype), s.N, f);
        fwrite(s.point2.coordinates, sizeof(ftype), s.N, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputBinaryFile_pyramid(char* file, PyramidND pyramid)
{
    FILE *f;
    ntype m=F_PYRAMID;
    f = fopen(file, "ab");
    if (f!=NULL)
    {
        fwrite(&m, sizeof(int), 1, f);
        fwrite(&pyramid.N, sizeof(int), 1, f);
        fwrite(&pyramid.NUM, sizeof(int), 1, f);
        fwrite(pyramid.apex.coordinates, sizeof(ftype), pyramid.N, f);
        for (int i=0; i<pyramid.NUM; i++)
        {
            fwrite(pyramid.points[i].coordinates, sizeof(ftype), pyramid.N, f);
        }
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputBinaryFile_line(char* file, LineND line)
{
    FILE *f;
    ntype m=F_LINE;
    f = fopen(file, "ab");
    if (f!=NULL)
    {
        fwrite(&m, sizeof(int), 1, f);
        fwrite(&line.N, sizeof(int), 1, f);
        fwrite(line.point1.coordinates, sizeof(ftype), line.N, f);
        fwrite(line.point2.coordinates, sizeof(ftype), line.N, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputBinaryFile_plane(char* file, PlaneND plane)
{
    FILE *f;
    ntype m=F_PLANE;
    f = fopen(file, "ab");
    if (f!=NULL)
    {
        fwrite(&m, sizeof(int), 1, f);
        fwrite(&plane.N, sizeof(int), 1, f);
        for (int i=0; i<plane.N; i++)
        {
            fwrite(plane.points[i].coordinates, sizeof(ftype), plane.N, f);
        }
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputBinaryFile_vector(char* file, VectorND vect)
{
    FILE *f;
    ntype m=F_VECTOR;
    f = fopen(file, "ab");
    if (f!=NULL)
    {
        fwrite(&m, sizeof(int), 1, f);
        fwrite(&vect.N, sizeof(int), 1, f);
        fwrite(vect.coordinates, sizeof(ftype), vect.N, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputBinaryFile_angle(char* file, AngleND angle)
{
    FILE *f;
    ntype m=F_ANGLE;
    f = fopen(file, "ab");
    if (f!=NULL)
    {
        fwrite(&m, sizeof(int), 1, f);
        fwrite(&angle.N, sizeof(int), 1, f);
        fwrite(angle.components, sizeof(ftype), angle.N-1, f);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

// READ FROM TEXT FILE
ntype inputTextFile_point(char* file, PointND *p)
{
    FILE *f;
    f = fopen(file, "rt");
    if (f!=NULL)
    {
        fscanf(f, "Point%dD", &p->N);
        for (int i=0; i<p->N; i++)
        {
            fscanf(f, "%f ", &p->coordinates[i]);
        }

        fclose(f);
        return 1;
    }
    else {return 0;}
}

ntype inputTextFile_segment(char* file, SegmentND *s)
{
    FILE *f;
    f = fopen(file, "rt");
    if (f!=NULL)
    {
        fscanf(f, "Segment%dD", &s->N);
        for (int i=0; i<s->N; i++)
        {
            fscanf(f, "%f ", &s->point1.coordinates[i]);
        }
        for (int i=0; i<s->N; i++)
        {
            fscanf(f, "%f ", s->point2.coordinates[i]);
        }
        fclose(f);
        return 1;
    }
    else {return 0;}
}

ntype inputTextFile_pyramid(char* file, PyramidND *pyramid)
{
    FILE *f;
    f = fopen(file, "rt");
    if (f!=NULL)
    {
        fscanf(f, "Pyramid%dD", &pyramid->N);
        fscanf(f, " %d ", &pyramid->NUM);
        pyramid->apex.N = pyramid->N;
        for (int i=0; i<pyramid->N; i++)
        {
            fscanf(f, "%f ", &pyramid->apex.coordinates[i]);
        }
        for (int i=0; i<pyramid->NUM; i++)
        {
            pyramid->points[i].N = pyramid->N;
            for (int j=0; j<pyramid->N; j++)
            {
                fscanf(f, "%f ", &pyramid->points[i].coordinates[j]);
            }
        }

        fclose(f);
        return 1;
    }
    else {return 0;}
}

ntype inputTextFile_line(char* file, LineND *line)
{
    FILE *f;
    f = fopen(file, "rt");
    if (f!=NULL)
    {
        fscanf(f, "Line%dD", &line->N);
        for (int i=0; i<line->N; i++)
        {
            fscanf(f, "%f ", &line->point1.coordinates[i]);
        }
        for (int i=0; i<line->N; i++)
        {
            fscanf(f, "%f ", &line->point2.coordinates[i]);
        }
        fclose(f);
        return 1;
    }
    else {return 0;}
}

ntype inputTextFile_plane(char* file, PlaneND *plane)
{
    FILE *f;
    f = fopen(file, "rt");
    if (f!=NULL)
    {
        fscanf(f, "Plane%dD", &plane->N);
        for (int k=0; k<plane->N; k++)
        {
            for (int i=0; i<plane->N; i++)
            {
                fscanf(f, "%f ", &plane->points[k].coordinates[i]);
            }
        }
        fclose(f);
        return 1;
    }
    else {return 0;}
}

ntype inputTextFile_vector(char* file, VectorND *vect)
{
    FILE *f;
    f = fopen(file, "rt");
    if (f!=NULL)
    {
        fscanf(f, "Vector%dD", &vect->N);
        for (int i=0; i<vect->N; i++)
        {
            fscanf(f, "%f ", &vect->coordinates[i]);
        }
        fclose(f);
        return 1;
    }
    else {return 0;}
}

ntype inputTextFile_angle(char* file, AngleND *angle)
{
    FILE *f;
    f = fopen(file, "rt");
    if (f!=NULL)
    {
        fscanf(f, "Angle%dD", &angle->N);
        for (int i=0; i<angle->N-1; i++)
        {
            fscanf(f, "%f ", &angle->components[i]);
        }
        fclose(f);
        return 1;
    }
    else {return 0;}
}

// WRITE TO TEXT FILE
void output_coordinates_to_text_file(FILE* f, PointND point, ntype type, ntype width, ntype precision)
{
    char modes[3][4] = {"f ", "g ", "e "};
    char out[96] = "%", buf[64];
    sprintf(buf, "%d.%d", width, precision);
    strcat(out, buf);
    strcat(out, modes[type]);
    for (ntype i=0; i<point.N; i++)
    {
        fprintf(f, out, point.coordinates[i]);
    }
    fprintf(f, "\n");
}

ntype outputTextFile_point(char* file, PointND p, ntype type, ntype width, ntype precision)
{
    FILE *f;
    f = fopen(file, "at");
    if (f!=NULL)
    {
        fseek(f, 0, SEEK_END);
        printf("!=NULL");
        fprintf(f, "fff");
        printf("ooo");
        fprintf(f, "\nPoint%dD: ", p.N);
        printf("OK");
        output_coordinates_to_text_file(f, p, type, width, precision);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputTextFile_segment(char* file, SegmentND s, ntype type, ntype width, ntype precision)
{
    FILE *f;
    f = fopen(file, "at");
    if (f!=NULL)
    {
        fprintf(f, "\nSegment%dD: ",s.N);
        output_coordinates_to_text_file(f, s.point1, type, width, precision);
        output_coordinates_to_text_file(f, s.point2, type, width, precision);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputTextFile_pyramid(char* file, PyramidND pyramid, ntype type, ntype width, ntype precision)
{
    FILE *f;
    f = fopen(file, "at");
    if (f!=NULL)
    {
        fprintf(f, "\nPyramid%dD: ",pyramid.N);
        fprintf(f, " %d ", pyramid.NUM);
        output_coordinates_to_text_file(f, pyramid.apex, type, width, precision);
        for (int i=0; i<pyramid.NUM; i++)
        {
            output_coordinates_to_text_file(f, pyramid.points[i], type, width, precision);
        }
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputTextFile_line(char* file, LineND line, ntype type, ntype width, ntype precision)
{
    FILE *f;
    f = fopen(file, "at");
    if (f!=NULL)
    {
        fprintf(f, "\nLine%dD: ",line.N);
        output_coordinates_to_text_file(f, line.point1, type, width, precision);
        output_coordinates_to_text_file(f, line.point2, type, width, precision);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputTextFile_plane(char* file, PlaneND plane, ntype type, ntype width, ntype precision)
{
    FILE *f;
    f = fopen(file, "at");
    if (f!=NULL)
    {
        fprintf(f, "\nPlane%dD: ",plane.N);
        for (int i=0; i<plane.N; i++)
        {
            output_coordinates_to_text_file(f, plane.points[i], type, width, precision);
        }
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputTextFile_vector(char* file, VectorND vect, ntype type, ntype width, ntype precision)
{
    FILE *f;
    f = fopen(file, "at");
    if (f!=NULL)
    {
        fprintf(f, "\nVector%dD: ", vect.N);
        output_coordinates_to_text_file(f, vect_to_point(vect), type, width, precision);
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

ntype outputTextFile_angle(char* file, AngleND angle, ntype type, ntype width, ntype precision)
{
    FILE *f;
    f = fopen(file, "at");
    if (f!=NULL)
    {
        fprintf(f, "\nAngle%dD: ", angle.N);
        char modes[3][4] = {"f ", "g ", "e "};
        char out[96] = "%", buf[64];
        sprintf(buf, "%d.%d", width, precision);
        strcat(out, buf);
        strcat(out, modes[type]);
        for (ntype i=0; i<angle.N-1; i++)
        {
            fprintf(f, out, angle.components[i]);
        }
        fprintf(f, "\n");
        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

// VECTOR FUNCTIONS
VectorND add(VectorND v1, VectorND v2)
{
    VectorND v3;
    ntype i=0;
    if (v1.N>=v2.N) {v3.N=v1.N;}
    else {v3.N = v2.N;}
    v3.coordinates = (ftype*)calloc(v3.N, sizeof(ftype));
    if (v1.N>=v2.N)
    {
        for (i=0; i<v2.N; i++){
            v3.coordinates[i] = v1.coordinates[i]+v2.coordinates[i];}
        while (i<v1.N){
            v3.coordinates[i] = v1.coordinates[i]; i++;}
    }
    else
    {
        for (i=0; i<v1.N; i++){
            v3.coordinates[i] = v1.coordinates[i]+v2.coordinates[i];}
        while (i<v2.N){
            v3.coordinates[i] = v2.coordinates[i];}
    }
    return v3;
}

VectorND sub(VectorND v1, VectorND v2)
{
    VectorND v3;
    ntype i=0;
    if (v1.N>=v2.N) {v3.N=v1.N;}
    else {v3.N = v2.N;}
    v3.coordinates = (ftype*)calloc(v3.N, sizeof(ftype));
    if (v1.N>=v2.N)
    {
        for (i=0; i<v2.N; i++){
            v3.coordinates[i] = v1.coordinates[i]-v2.coordinates[i];}
        while (i<v1.N){
            v3.coordinates[i] = v1.coordinates[i]; i++;}
    }
    else
    {
        for (i=0; i<v1.N; i++){
            v3.coordinates[i] = v1.coordinates[i]-v2.coordinates[i];}
        while (i<v2.N){
            v3.coordinates[i] = -v2.coordinates[i];}
    }
    return v3;
}

ftype multS(VectorND v1, VectorND v2)
{
    ftype rez=0;
    ntype i;
    if (v1.N>=v2.N)
    {
        for (i=0; i<v2.N; i++){
            rez += v1.coordinates[i]*v2.coordinates[i];}
    } else {
        for (i=0; i<v1.N; i++){
            rez += v1.coordinates[i]*v2.coordinates[i];}
    }
    return rez;
}

VectorND mult(VectorND *vectors)
{
    VectorND v3;
    ntype n = vectors[0].N;
    v3.N = n;
    ftype** matrix = (ftype**)malloc((n-1)*sizeof(ftype*));
    for (ntype i=0; i<n-1; i++){
        matrix[i]=(ftype*)malloc((n-1)*sizeof(ftype));}
    for (ntype i=0; i<n; i++)
    {
        for (ntype j=0; j<n; j++)
        {
            for (ntype k=0; k<n; k++)
            {
                if (k<i){
                    matrix[j][k]=vectors[j].coordinates[k];}
                else if (k>i){
                    matrix[j][k-1]=vectors[j].coordinates[k];}
            }
        }
        v3.coordinates[i]=determinant(matrix, n-1);
    }
    for (ntype i=0; i<n-1; i++){
        free(matrix[i]);
    }
    free(matrix);
    return v3;
}

// SOME OTHER FUNCTIONS
VectorND normal(PlaneND pl)
{
    VectorND normal;
    normal.N = pl.N;
    ftype ** matrix = (ftype**)malloc((pl.N-1)*sizeof(ftype*));
    for (ntype i=0; i<pl.N-1; i++){
        matrix[i] = (ftype*)malloc((pl.N-1)*sizeof(ftype));}
    for (ntype i=0; i<pl.N-1; i++)
    {
        for (ntype j=0; j<pl.N-1; j++)
        {
            for (ntype k=0; k<pl.N; k++)
            {
                if (k<i){
                    matrix[j][k] = pl.points[i].coordinates[k];}
                else if (k>i){
                    matrix[j][k-1] = pl.points[i].coordinates[k];}
            }
        }
        normal.coordinates[i] = determinant(matrix, pl.N-1);
    }
    for (ntype i=0; i<normal.N; i++) {
        free(matrix[i]);}
    free(matrix);
    return normal;
}

ftype determinant(ftype **matr, ntype n)
{
    ftype rez=1, suma1, suma2, t, mn, elem;
    ntype i, j, k;
    i=0;
    for (i=0; i<n; i++)
    {
        for (ntype ii=i; ii<n; ii++)
        {
            for (ntype jj=i; jj<n; jj++)
            {
                if (matr[ii][jj]!=0)
                {
                    if (ii!=i)
                    {
                        rez*=(-1);
                        for (k=0; k<n; k++)
                        {
                            t = matr[ii][k];
                            matr[ii][k] = matr[i][k];
                            matr[i][k] = t;
                        }
                    }
                    if (jj!=i)
                    {
                        rez*=(-1);
                        for (k=0; k<n; k++)
                        {
                            t = matr[k][jj];
                            matr[k][jj] = matr[k][i];
                            matr[k][i] = t;
                        }
                    }
                    jj=n;
                    ii=n;
                }
            }
        }
        if (matr[i][i]==0)
        {return 0;}
        else if (i<n-1)
        {
            mn = matr[i][i];
            if (mn != 0)
            {
                rez *= mn;
                for (j=i; j<n; j++)
                {matr[i][j] /= mn;}
            }
            for (k=i+1; k<n; k++)
            {
                if (matr[k][i] != 0)
                {
                    elem = matr[k][i];
                    for (j=i; j<n; j++)
                    {matr[k][j] -= matr[i][j]*elem;}
                }
            }
        }
        else
        {
            for (i=0; i<n; i++)
            {rez = rez*matr[i][i];}
            printf("rez %f", rez);
            return rez;
        }
    }
}

// INTERSECT
LineND intersect_planes(PlaneND *planes)
{
    VectorND *normals = (VectorND*)malloc(planes[0].N*sizeof(VectorND));
    for (ntype i=0; i<planes[0].N-1; i++)
    {
        normals[i] = normal(planes[i]);
    }
    VectorND the_vector = mult(normals);

    return vect_to_line(the_vector);
}

PointND intersect_line_plane(LineND l1, PlaneND p1)
{
    PointND point;
    point.N = l1.N;
    point.coordinates = (ftype*)malloc(point.N*sizeof(ftype));
    if (l1.N!=p1.N){printf("ERROR");}
    else
    {
        VectorND n = normal(p1);
        if (multS(n, line_to_vect(l1))==0)
        {
            printf("don't intersect");
            for (ntype i=0; i<point.N; i++){point.coordinates[i]=0;}
        }
        else
        {
            printf("intersect");

        }
        return point;
    }
}

VectorND get_vector(PointND p1, PointND p2)
{
    VectorND vector;
    vector.N = p1.N;
    vector.coordinates = (ftype*)malloc(vector.N*sizeof(ftype));
    for (ntype i=0; i<p1.N; i++)
    {
        vector.coordinates[i] = p1.coordinates[i]-p2.coordinates[i];
    }
    return vector;
}

double get_triangle_square(PointND p1, PointND p2, PointND p3)
{
    double a, b, c;
    a = module(get_vector(p1, p2));
    b = module(get_vector(p1, p2));
    c = module(get_vector(p1, p2));
    double p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

// PYRAMID_ND
ftype osnova_area(PyramidND p)
{
    ftype area;


    return area;
}

ftype volumeND(PyramidND p)
{
    ftype vol, osn, height;
    PointND point=p.points[0];
    osn = osnova_area(p);


    vol = osn*height/p.N;

    return vol;
}

ftype* side_areasND(PyramidND p)
{
    ftype* squares = (ftype*)malloc(p.NUM*sizeof(ftype));
    squares[0] = get_triangle_square(p.apex, p.points[p.NUM-1], p.points[0]);
    for (ntype i=1; i<p.NUM; i++)
    {
        squares[i] = get_triangle_square(p.apex, p.points[i-1], p.points[i]);
    }
    return squares;
}

ftype areaND(PyramidND p)
{
    ftype rez;
    rez = osnova_area(p);
    ftype *ars = side_areasND(p);
    for (ntype i=0; i<p.NUM; i++)
    {
        rez += ars[i];
    }
    return rez;
}

PointND weight_center(PyramidND p)
{
    PointND center;

    return center;
}

// PYRAMID AND PLANE
PointND** get_figures(PyramidND pyram, PlaneND plane)
{
    PointND **figures;

    return figures;
}

ftype* get_squares(PyramidND pyram, PlaneND plane)
{
    ftype* squares;

    return squares;
}

ftype* get_volumes(PyramidND pyram, PlaneND plane)
{
    ftype* volumes;

    return volumes;
}

// TURN POINT, TURN PYRAMID
PointND turn_point(PointND p, AngleND ang)
{
    PointND new_point;
    new_point.N = p.N;
    new_point.components=(ftype*)malloc((new_point.N-1)*sizeof(ftype));
    for (ntype i=0; i<p.N; i++)
    {
        new_point.coordinates[i]=p.coordinates[i];
    }
    for (ntype i=0; i<new_point.N-1; i++)
    {
        ntype x = new_point.coordinates[i];
        ntype y = new_point.coordinates[i+1];
        ntype r = sqrt(x*x+y*y);
        ntype x1 = r*cos(acos(x/r)+ang.components[i]);
        ntype y1 = r*sin(asin(y/r)+ang.components[i]);
        new_point.components[i]=x1;
        new_point.components[i+1]=y1;
    }
    return new_point;
}

PyramidND turn_pyramid(PyramidND p, AngleND ang)
{
    PyramidND new_pyr;
    new_pyr.N = p.N;
    new_pyr.NUM = p.NUM;
    new_pyr.apex = turn_point(p.apex, ang);
    new_pyr.points = (PointND*)malloc(new_pyr.NUM*sizeof(PointND));
    for (int i=0; i<p.NUM; i++)
    {
        new_pyr.points[i] = turn_point(p.points[i], ang);
    }
    return new_pyr;
}

// VECTOR AND FTYPE
VectorND mul(VectorND vect, ftype num)
{
    VectorND v3;
    v3.coordinates = (ftype*)malloc(vect.N*sizeof(ftype));
    v3.N = vect.N;
    for (ntype i=0; i<vect.N; i++){
        v3.coordinates[i] = vect.coordinates[i]*num;}
    return v3;
}

VectorND division(VectorND vect, ftype num)
{
    VectorND v3;
    if (num==0){
        printf("We cannot divide by zero!\n");
        return vect;}
    else{
        v3.coordinates = (ftype*)malloc(vect.N*sizeof(ftype));
        v3.N = vect.N;
        for (ntype i=0; i<vect.N; i++){
            v3.coordinates[i] = vect.coordinates[i]/num;}
        return v3;}
}

// LENGTH OF VECTOR AND SEGMENT
ftype module(VectorND vect)
{
    ftype rez=0;
    for (ntype i=0; i<vect.N; i++){
        rez += vect.coordinates[i]*vect.coordinates[i];}
    rez = sqrt(rez);
    return rez;
}

ftype length(SegmentND segment)
{
    ftype rez=0;
    ftype curr;
    for (ntype i=0; i<segment.N; i++){
        curr = (segment.point1.coordinates[i]-segment.point2.coordinates[i]);
        rez += curr*curr;}
    return sqrt(rez);
}

// UNARY OPERATIONS
VectorND unadd(VectorND* vect1, const VectorND vect2)
{
    if (vect1->N>=vect2.N){
        for (ntype i=0; i<vect2.N; i++){
            vect1->coordinates[i]+=vect2.coordinates[i];}
    }
    else{
        printf("Error: vect1.N<vect2.N");}
    return *vect1;
}

VectorND unsub(VectorND* vect1, const VectorND vect2)
{

    if (vect1->N>=vect2.N){
        for (ntype i=0; i<vect2.N; i++){
            vect1->coordinates[i]-=vect2.coordinates[i];}
    }
    else{
        printf("error: vect1.N<vect2.N");}
    return *vect1;
}

VectorND unmul(VectorND* vect1, const ftype num)
{
    for (ntype i=0; i<vect1->N; i++){
        vect1->coordinates[i]*=num;}
    return *vect1;
}

VectorND undiv(VectorND* vect1, const ftype num)
{
    if (num==0){
        printf("Error: division by zero\n");}
    else{
        for (ntype i=0; i<vect1->N; i++) {vect1->coordinates[i]/=num;}
    }
    return *vect1;
}

// CONVERT VECTOR TO SEGMENT, LINE, POINT, ...
SegmentND vect_to_segm(VectorND vect)
{
    SegmentND segm;
    segm.N = vect.N;
    segm.point1.N = vect.N;
    segm.point2.N = vect.N;
    segm.point1.coordinates = (ftype*)calloc(segm.N, sizeof(ftype));
    segm.point2.coordinates = (ftype*)malloc(segm.N*sizeof(ftype));
    for (ntype i=0; i<segm.N; i++) {
        segm.point2.coordinates[i] = vect.coordinates[i];}
    return segm;
}

VectorND segm_to_vect(SegmentND segm)
{
    VectorND vect;
    vect.N = segm.N;
    vect.coordinates = (ftype*)malloc(vect.N*sizeof(ftype));
    for (ntype i=0; i<vect.N; i++){
        vect.coordinates[i] = segm.point2.coordinates[i]-segm.point1.coordinates[i];}
    return vect;
}

LineND vect_to_line(VectorND vect)
{
    LineND line;
    line.N = vect.N;
    line.point1.N = vect.N;
    line.point2.N = vect.N;
    line.point1.coordinates = (ftype*)calloc(line.N, sizeof(ftype));
    line.point2.coordinates = (ftype*)malloc(line.N*sizeof(ftype));
    for (ntype i=0; i<line.N; i++){
        line.point2.coordinates[i] = vect.coordinates[i];}
    return line;
}

VectorND line_to_vect(LineND line)
{
    VectorND v;
    v.N = line.N;
    v.coordinates = (ftype*)malloc(v.N*sizeof(ftype));
    for (ntype i=0; i<line.N; i++){
        v.coordinates[i] = line.point1.coordinates[i]-line.point2.coordinates[i];}
    return v;
}

LineND segm_to_line(SegmentND segm)
{
    LineND line;
    line.N = segm.N;
    line.point1.N = segm.N;
    line.point2.N = segm.N;
    line.point1.coordinates = (ftype*)malloc(line.N*sizeof(ftype));
    line.point2.coordinates = (ftype*)malloc(line.N*sizeof(ftype));
    for (ntype i=0; i<line.N; i++){
        line.point1.coordinates[i] = segm.point1.coordinates[i];
        line.point2.coordinates[i] = segm.point2.coordinates[i];}
    return line;
}

PointND vect_to_point(VectorND vect)
{
    PointND point;
    point.N = vect.N;
    point.coordinates = (ftype*)malloc(point.N*sizeof(ftype));
    for (ntype i=0; i<point.N; i++){
        point.coordinates[i] = vect.coordinates[i];}
    return point;
}

VectorND point_to_vect(PointND point)
{
    VectorND vect;
    vect.N = point.N;
    vect.coordinates = (ftype*)malloc(vect.N*sizeof(ftype));
    for (ntype i=0; i<vect.N; i++){
        vect.coordinates[i] = point.coordinates[i];}
    return vect;
}

// READ FTYPE AND NTYPE NUMBERS
char* f_read()
{
    char *s;
    s = (char*)malloc(LEN*sizeof(char));
    ntype i=0, l, digits=0;
    short koma=0;
    scanf("%s", s);
    l = strlen(s);
    for (i=0; i<l; i++)
    {
        if (isalpha(s[i]) && s[i]!='e' && s[i] != 'E') {
            memset(s, 0, strlen(s));
            strcat(s, "NO-1");
            return s;}
        else if (isdigit(s[i])) {digits++;}
        else if (s[i]==',') {koma++;}
    }
    if (!digits){
        memset(s, 0, strlen(s));
        strcat(s, "NO-2");
        return s;}
    i=0;
    if (s[0]=='+' || s[0]=='-') {i++;}
    if (!(s[i]=='.' || s[i]==',' || isdigit(s[i]))){
        memset(s, 0, strlen(s));
        strcat(s, "NO-3");
        return s;}
    while (isdigit(s[i]) && i+1<l) {i++;}
    if (s[i]=='.' || s[i]==',')
    {
        i++;
        if (!(isdigit(s[i]) || s[i]=='e' || s[i]=='E' || i==l)){
            memset(s, 0, strlen(s));
            strcat(s, "NO-4");
            return s;}
        while (isdigit(s[i]) && i+1<l) {i++;}
    }
    if (s[i]=='e' || s[i]=='E')
    {
        i++;
        if (s[i]=='+' || s[i]=='-') {i++;}
        if (!isdigit(s[i])){
            memset(s, 0, strlen(s));
            strcat(s, "NO-5");
            return s;}
        while (isdigit(s[i])) {i++;}
    }
    if (i<l-1)
    {
        memset(s, 0, strlen(s));
        strcat(s, "NO-6");
        return s;
    }
    else if (i==l-1)
    {
        if (!(s[i]==';' || s[i]==',' || isdigit(s[i]))){
            memset(s, 0, strlen(s));
            strcat(s, "NO-7");
            return s;}
        else if (s[i]==',' || s[i]==';'){
            s[i]=' ';}
    }
    if (koma)
    {
        for (i=0; i<l; i++){
            if (s[i]==',') {s[i] = '.';}
        }
    }
    return s;
}

char* i_read()
{
    char* s;
    ntype l, i=0;
    s = (char*)malloc(LEN*sizeof(char));
    scanf("%s", s);
    l = strlen(s);
    if (s[0]=='+' || s[0]=='-') {i++;}
    while (i<l)
    {
        if (!isdigit(s[i]))
        {
            memset(s, 0, strlen(s));
            strcat(s, "NO");
            return s;
        }
        i++;
    }
    return s;
}

// GENERATE RANDOM OBJECTS
ftype* generate_coordinates(ntype N)
{
    ftype* rez;
    if (N<=0)
    {
        printf("Error generating numbers: N=0");
        rez = (ftype*)calloc(1, sizeof(ftype));
    }
    else
    {
        rez = (ftype*)malloc(N*sizeof(ftype));
        for (ntype i=0; i<N; i++){
            rez[i] = (ftype)rand()/100;}
    }
    return rez;
}

PointND generate_point(ntype N)
{
    PointND p;
    p.N = N;
    p.coordinates = generate_coordinates(N);
    return p;
}

SegmentND generate_segment(ntype N)
{
    SegmentND segm;
    segm.N = N;
    segm.point1 = generate_point(N);
    segm.point2 = generate_point(N);
    return segm;
}

PyramidND generate_pyramid(ntype N)
{
    PyramidND pyram;
    pyram.N = N;
    pyram.points = (PointND*)malloc((N+1)*sizeof(PointND));
    for (ntype i=0; i<=N; i++){
        pyram.points[i] = generate_point(N);}
    return pyram;
}

VectorND generate_vector(ntype N)
{
    VectorND vect;
    vect.N = N;
    vect.coordinates = generate_coordinates(N);
    return vect;
}

LineND generate_line(ntype N)
{
    LineND line;
    line.N = N;
    line.point1 = generate_point(N);
    line.point2 = generate_point(N);
    return line;
}

PlaneND generate_plane(ntype N)
{
    PlaneND plane;
    plane.N = N;
    plane.points = (PointND*)malloc(N*sizeof(PointND));
    for (ntype i=0; i<N; i++){
        plane.points[i] = generate_point(N);}
    return plane;
}

AngleND generate_angle(ntype N)
{
    AngleND angle;
    angle.N = N;
    if (angle.N-1<=0)
    {
        printf("Error generating angle: N<=1");
        angle.components = (ftype*)calloc(1, sizeof(ftype));
    }
    else
    {
        angle.components = (ftype*)malloc((angle.N-1)*sizeof(ftype));
        for (ntype i=0; i<N; i++){
            angle.components[i] = (ftype)(rand()%1000)/300;}
    }
    return angle;
}

