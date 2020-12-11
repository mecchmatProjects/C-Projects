#ifndef CHORNOMORETS_DVECTOR_C
#define CHORNOMORETS_DVECTOR_C

class DVector {

private:
    Ntype n;
    Dtype *items;

public:

    DVector (): n(0),items((Dtype*)malloc(0)) {}
    DVector (Ntype n,Dtype*items): n(n), items(items) {}
    DVector (Ntype n): n(n), items((Dtype*)malloc(n*sizeof(Dtype))) {
        for (Ntype i=0; i<n; i++ ) items[i]=0;}
    DVector (DVector* v): n(v->n),
        items((Dtype*)malloc(v->n*sizeof(Dtype))) {
        for (Ntype i=0; i<n; i++ ) items[i]=v->items[i];}

    friend void DVector_destroy(DVector x);
    friend DVector generate_DVector(Ntype n);
    DVector operator+(DVector y);
    DVector operator-(DVector y);
    Dtype operator*(DVector y);
    DVector operator*(Dtype y);
    friend DVector operator*(Dtype y,DVector x);
    DVector operator/(Dtype y);
    friend Dtype abs(DVector x);
    Itype operator+=(DVector y);
    Itype operator-=(DVector y);
    Itype operator*=(Dtype y);
    friend Itype inputs_DVector(DVector* x, char* str);
    friend Itype inputTextFile_DVector (char* file,DVector* x);
    friend void output_DVector(DVector x, int type,int width, int precision);
    friend Ntype input_DVector(DVector* x);
    friend Itype outputTextFile_DVector(char* file,DVector x, int type,int width, int precision);
    friend Itype outputBinaryFile_DVector (char* file, DVector x);
    friend Itype inputBinaryFile_DVector (char* file, DVector* x);
    Ntype operator==(DVector y);
    Ntype operator!=(DVector y);
    Itype get_n(){return n;}
    Dtype get_item(Ntype nmb){return items[nmb];}
};

#endif
