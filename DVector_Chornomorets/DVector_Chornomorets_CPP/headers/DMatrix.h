#ifndef CHORNOMORETS_DMATRIX_C
#define CHORNOMORETS_DMATRIX_C


class DMatrix {
private:
    Ntype n;
    Ntype m;
    Dtype *items;

public:

    DMatrix (): n(0),m(0),items((Dtype*)malloc(0)) {}
    DMatrix (Ntype n, Ntype  m, Dtype*items): n(n),m(m), items(items) {}
    DMatrix (Ntype n,Ntype m): n(n), m(m), items((Dtype*)malloc(n*m*sizeof(Dtype))) {
        for (Ntype i=0; i<n*m; i++ ) items[i]=0;}
    DMatrix (DMatrix* v): n(v->n), m(v->m),
        items((Dtype*)malloc(v->n*v->m*sizeof(Dtype))) {
        for (Ntype i=0; i<n*m; i++ ) items[i]=v->items[i];}

    friend void DMatrix_destroy(DMatrix x);
    friend DMatrix generate_DMatrix(Ntype n);
    DMatrix operator+(DMatrix y);
    DMatrix operator-(DMatrix y);
    DMatrix operator*(DMatrix y);
    DMatrix operator*(Dtype y);
    friend DMatrix operator*(Dtype y,DMatrix x);
    DMatrix operator*(DVector y);
    friend DMatrix operator*(DVector y,DMatrix x);
    friend Dtype det(DMatrix x);
    friend DMatrix inverse(DMatrix x);
    Itype operator+=(DMatrix y);
    Itype operator-=(DMatrix y);
    Itype operator*=(Dtype y);
    friend Itype inputs_DMatrix(DMatrix* x, char* str);
    friend Itype inputTextFile_DMatrix (char* file,DMatrix* x);
    friend void output_DMatrix(DMatrix x, int type,int width, int precision);
    friend Ntype input_DMatrix(DMatrix* x);
    friend Itype outputTextFile_DMatrix(char* file,DMatrix x, int type,int width, int precision);
    friend Itype outputBinaryFile_DMatrix (char* file, DMatrix x);
    friend Itype inputBinaryFile_DMatrix (char* file, DMatrix* x);
    void swap_rows(Ntype n1, Ntype n2);
    void swap_columns(Ntype m1, Ntype m2);
    Ntype operator==(DMatrix y);
    Ntype operator!=(DMatrix y);
};

#endif
