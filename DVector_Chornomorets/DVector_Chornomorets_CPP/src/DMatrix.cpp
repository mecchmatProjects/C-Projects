
void DMatrix_destroy(DMatrix x)
{
    free(x.items);
}
// generating matrix
DMatrix generate_DMatrix(Ntype n, Ntype m)
{
    Dtype* rez_items=(Dtype*)malloc(n*m*sizeof(Dtype));
    for (Ntype i=0; i<n*m; i++)
        rez_items[i]=(0.5- (double) rand()/RAND_MAX);
    //Generates every item as double in range from -50 to 50
    return DMatrix(n,m,rez_items);
}
//standard operations:
DMatrix DMatrix::operator+(DMatrix y)
{
    Dtype* rez_items = (Dtype*) malloc(n*m*sizeof(Dtype));
    for (Ntype i=0;i<n*m;i++)
        rez_items[i]=items[i]+y.items[i];
    return DMatrix(n,m,rez_items);
}

DMatrix DMatrix::operator-(DMatrix y)
{
    Dtype* rez_items = (Dtype*) malloc(n*m*sizeof(Dtype));
    for (Ntype i=0;i<n*m;i++)
        rez_items[i]=items[i]-y.items[i];
    return DMatrix(n,m,rez_items);
}

DMatrix DMatrix::operator*(DMatrix y)
{
    DMatrix z;
    Dtype d;
    z.n=n;
    z.m=y.m;
    z.items = (Dtype*) malloc(z.n*z.m*sizeof(Dtype));
    for (Ntype i=0;i<z.n;i++) for (Ntype j=0;j<z.m;j++)
    {
        d=0;
        for (Ntype r=0;r<m;r++)
            d+=items[i*m+r]*y.items[r*y.m+j];
        z.items[i*z.m+j]=d;
    }
    return z;
}
//product of matrix and float
DMatrix DMatrix::operator*(Dtype y)
{
    DMatrix z;
    z.n=n;
    z.m=m;
    z.items = (Dtype*) malloc(z.n*z.m*sizeof(Dtype));
    for (Ntype i=0;i<n*m;i++)
        z.items[i]=items[i]*y;
    return z;
}

DMatrix operator*(Dtype y,DMatrix x)
{
    return x*y;
}

DMatrix DMatrix::operator*(DVector y)
{
    DMatrix z;
    Dtype* itms=(Dtype*)malloc(y.get_n()*sizeof(Dtype));
    for (Ntype i=0;i<y.get_n();i++) itms[i]=y.get_item(i);
    return ((*this)*DMatrix(y.get_n(),1,itms));
}
DMatrix operator*(DVector y,DMatrix x)
{
     DMatrix z;
    Dtype* itms=(Dtype*)malloc(y.get_n()*sizeof(Dtype));
    for (Ntype i=0;i<y.get_n();i++) itms[i]=y.get_item(i);
    return (DMatrix(1,y.get_n(),itms)*x);
}
Dtype det(DMatrix x)
{
    Dtype dett=0;
    if (x.n==0) return 1;
    if (x.n==1) return x.items[0];
    DMatrix y;
    y.n=x.n-1;
    y.m=x.m-1;
    y.items = (Dtype*) malloc(y.n*y.m*sizeof(Dtype));
    for (Ntype i=0;i<y.n;i++)
        for (Ntype j=0;j<y.m;j++)
        {
            y.items[i*y.m+j]=x.items[(i+1)*x.m+(j+1)];
        }
    dett+=pow(-1,0)*x.items[0]*det(y);

    for (Ntype i=1;i<x.n;i++)
    {
        for (Ntype j=0;j<y.m;j++)
            y.items[(i-1)*y.m+j]=x.items[(i-1)*x.m+(j+1)];
        dett+=pow(-1,i)*x.items[i*x.m]*det(y);
   }
    free(y.items);
    return dett;
}
DMatrix inverse(DMatrix x)
{
    DMatrix y,z;
    y.n=x.n;
    y.m=x.m;
    y.items=(Dtype*) malloc(y.n*y.m*sizeof(Dtype));
    z.n=x.n-1;
    z.m=x.m-1;
    z.items=(Dtype*) malloc(z.n*z.m*sizeof(Dtype));
    Dtype det1=1/det(x);
    for (Ntype i=0;i<y.n;i++) for (Ntype j=0;j<y.m;j++)
    {
        for (Ntype ii=0;ii<z.n;ii++)
            for (Ntype jj=0;jj<z.m;jj++)
            z.items[ii*z.m+jj]=
            x.items[(ii+(ii>=i))*x.m+jj+(jj>=j)];

        y.items[j*y.m+i]=pow(-1,i+j)*det(z)*det1;
    }
    free(z.items);
    return y;

}
//standart unary operations
Itype DMatrix::operator+=( DMatrix y)
{
    for (Ntype i=0;i<n*m;i++)
        items[i]+=y.items[i];
    return 0;
}
Itype DMatrix::operator-=(DMatrix y)
{
    for (Ntype i=0;i<n*m;i++)
        items[i]-=y.items[i];
    return 0;
}
Itype DMatrix::operator*=( Dtype y)
{
    for (Ntype i=0;i<n*m;i++)
        items[i]*=y;
    return 0;
}
//inputing matrix with scanf
Ntype input_DMatrix(DMatrix* x)
{
    Ntype cnt=0;
    printf("Entering a DMatrix. Enter dimension (n and m): ");
    //inputing a dimension
    scanf("%ui",&(x->n));
    scanf("%ui",&(x->m));
    x->items=(Dtype*) malloc(x->n*x->m*sizeof(Dtype));
    printf("Now enter %i koefficients (going by rows): ",x->n*x->m);
    //inputing koefficients
    for (Ntype i=0;i<x->n*x->m;i++)
    {
        cnt+=scanf("%lf",&(x->items[i]));
    }
    return cnt;
}

//inputing matrix from text file (dimensions, then coefficients)
Itype inputTextFile_DMatrix (char* file,DMatrix* x)
{
    FILE* finp = fopen(file, "r");
    if (!finp) return -1;
    Ntype cnt=0;
    fscanf(finp,"%ui",&(x->n));
    fscanf(finp,"%ui",&(x->m));
    x->items=(Dtype*) malloc(x->n*x->m*sizeof(Dtype));
    //inputing koefficients
    for (Ntype i=0;i<x->n*x->m;i++)
    {
        cnt+=fscanf(finp,"%lf",&(x->items[i]));
    }
    fclose(finp);
    return cnt;
}

//inputing matrix from string (dimensions, then coefficients)
Itype inputs_DMatrix(DMatrix* x, char* str)
{
    FILE* fout = fopen("temp.txt", "w");
    if (!fout) return -1;
    fprintf(fout,"%s",str);
    fclose(fout);
    Ntype cnt=inputTextFile_DMatrix("temp.txt",x);
    return cnt;
}

//printing matrix
//type=1 means scientific format, else type means standard format
void output_DMatrix(DMatrix x, int type=0,int width=3, int precision=2)
{
    cout<<x.n<<" "<<x.m<<endl;
    cout.precision(precision);
    cout.width(width);
    if (type==1) cout<<scientific;
    for (Ntype i=0; i<x.n; i++)
    {
        for (Ntype j=0; j<x.m; j++)
        {
            cout<<x.items[i*x.m+j]<<" ";
        }
        cout<<endl;
    }
    if (type==1) cout<<fixed;
}

//printing matrix to text file (same as with printf)
Itype outputTextFile_DMatrix(char* file,DMatrix x, int type=0,int width=3, int precision=2)
{
    ofstream fout;
    fout.open(file);
    if (!fout.is_open()) return -1;
    fout<<x.n<<" "<<x.m<<endl;
    fout.precision(precision);
    fout.width(width);
    if (type==1) fout<<scientific;
    for (Ntype i=0; i<x.n; i++)
    {
        for (Ntype j=0; j<x.m; j++)
        {
            fout<<x.items[i*x.m+j]<<" ";
        }
        fout<<endl;
    }
    fout<<defaultfloat;
}

//saving dimensions and coefficients to binary file
Itype outputBinaryFile_DMatrix (char* file, DMatrix x)
{
    FILE* fout = fopen(file, "wb");
    if (!fout) return -1;
    Itype cnt =fwrite(&x.n, sizeof(Ntype),1,fout)*
            fwrite(&x.m, sizeof(Ntype),1,fout);
    cnt *=fwrite(x.items, sizeof (Dtype), x.n*x.m, fout);
    fclose(fout);
    return cnt;
}

//inputing vector from  binary file
Itype inputBinaryFile_DMatrix (char* file,DMatrix * x)
{
    FILE* finp = fopen(file, "rb");
    if (!finp) return -1;
    Itype cnt=fread(&(x->n), sizeof(Ntype), 1, finp)*
            fread(&(x->m), sizeof(Ntype), 1, finp);
    x->items = (Dtype*) malloc(x->n * x->m * sizeof (Dtype));
    cnt*=fread(x->items, sizeof(Dtype), x->n*x->m, finp);
    fclose(finp);
    return cnt;
}

//swap rows with numbers n1 and n2 (starting from 1)
void DMatrix::swap_rows(Ntype n1, Ntype n2)
{
    n1--;
    n2--;
    Dtype temp;
    for (int j=0;j<m;j++)
    {
        temp=items[n1*(m)+j];
        items[n1*(m)+j]=items[n2*(m)+j];
        items[n2*(m)+j]=temp;
    }
}

void DMatrix::swap_columns(Ntype m1, Ntype m2)
{
    m1--;
    m2--;
    Dtype temp;
    for (int i=0;i<n;i++)
    {
        temp=items[i*(m)+m1];
        items[i*(m)+m1]=items[i*(m)+m2];
        items[i*(m)+m2]=temp;
    }
}

Ntype DMatrix::operator==(DMatrix y)
{
    if (n!=y.n || m!=y.m) return 0;
    for (int i=0; i<n*m; i++)
        if (abs(items[i]-y.items[i])>pow(10,-6))
            return 0;
    return 1;
}

Ntype DMatrix::operator!=(DMatrix y)
{
    return (!(*this==y));
}
