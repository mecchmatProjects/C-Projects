
void DVector_destroy(DVector x)
{
    free(x.items);
}

// generating vector
DVector generate_DVector(Ntype n)
{
    Dtype* rez_items=(Dtype*)malloc(n*sizeof(Dtype));
    for (Ntype i=0; i<n; i++)
        rez_items[i]=100*(0.5- (double) rand()/RAND_MAX);
    return DVector(n,rez_items);
}

//standard operations:
DVector DVector::operator+(DVector y)
{
    Dtype* rez_items = (Dtype*) malloc(n*sizeof(Dtype));
    for (Ntype i=0;i<n;i++)
        rez_items[i]=items[i]+y.items[i];
    return DVector(n,rez_items);
}


DVector DVector::operator-(DVector y)
{
    Dtype* rez_items = (Dtype*) malloc(n*sizeof(Dtype));
    for (Ntype i=0;i<n;i++)
        rez_items[i]=items[i]-y.items[i];
    return DVector(n,rez_items);
}

//scalar product of 2 vectors
Dtype DVector::operator*(DVector y)
{
    Dtype d=0;
    for (Ntype i=0;i<n;i++)
        d+=items[i]*y.items[i];
    return d;
}

//product of vector and float
DVector DVector::operator*(Dtype y)
{
    Dtype* rez_items = (Dtype*) malloc(n*sizeof(Dtype));
    for (Ntype i=0;i<n;i++)
         rez_items[i]=items[i]*y;
    return DVector(n,rez_items);
}

DVector operator*(Dtype y,DVector x)
{
    Dtype* rez_items = (Dtype*) malloc(x.n*sizeof(Dtype));
    for (Ntype i=0;i<x.n;i++)
         rez_items[i]=x.items[i]*y;
    return DVector(x.n,rez_items);
}


//product of vector and float, inverted to given float
DVector DVector::operator/(Dtype y)
{
    Dtype* rez_items = (Dtype*) malloc(n*sizeof(Dtype));
    for (Ntype i=0;i<n;i++)
         rez_items[i]=items[i]/y;
    return DVector(n,rez_items);
}

//absolute value of a vector
Dtype abs(DVector x)
{
    Dtype d=0;
    for (Ntype i=0;i<x.n;i++)
        d+=pow(x.items[i],2);
    d=sqrt(d);
    return d;
}

//standart unary operations
Itype DVector::operator+=(DVector y)
{
    for (Ntype i=0;i<n;i++)
        items[i]+=y.items[i];
    return 0;
}

Itype DVector::operator-=(DVector y)
{
    for (Ntype i=0;i<n;i++)
        items[i]-=y.items[i];
    return 0;
}


Itype DVector::operator*=(Dtype y)
{
    for (Ntype i=0;i<n;i++)
        items[i]*=y;
    return 0;
}

//inputing vector with scanf
Ntype input_DVector(DVector* x)
{
    Ntype cnt=0;
    printf("Entering a DVector. Enter dimension: ");
    //inputing a dimension
    scanf("%u",&(x->n));
    x->items=(Dtype*) malloc(x->n*sizeof(Dtype));
    printf("Now enter %i koefficients: ",x->n);
    //inputing koefficients
    for (Ntype i=0;i<x->n;i++)
    {
        cnt+=scanf("%lf",&(x->items[i]));
    }
    return cnt;
}

//type=1 means scientific format, else type means standard format
void output_DVector(DVector x, int type=0,int width=3, int precision=2)
{
    cout<<x.n<<" ";
    cout.precision(precision);
    cout.width(width);
    if (type==1) cout<<scientific;
    for (Ntype i=0; i<x.n; i++)
        {
            cout<<x.items[i]<<" ";
        }
    cout<<"\n";
    cout<<defaultfloat;
}

Itype inputTextFile_DVector (char* file,DVector* x)
{
    FILE* finp = fopen(file, "r");
    if (!finp) return -1;
    Ntype cnt=0;
    fscanf(finp,"%u",&(x->n));
    x->items=(Dtype*) malloc(x->n*sizeof(Dtype));
    for (Ntype i=0;i<x->n;i++)
    {
        cnt+=fscanf(finp,"%lf",&(x->items[i]));
    }
    fclose(finp);
    return cnt;
}

//inputing vector from string (dimension, then coefficients)
Itype inputs_DVector(DVector* x, char* str)
{
    FILE* fout = fopen("temp.txt", "w");
    if (!fout) return -1;
    fprintf(fout,"%s",str);
    fclose(fout);
    Ntype cnt=inputTextFile_DVector("temp.txt",x);
    return cnt;
}

Itype outputTextFile_DVector(char* file,DVector x, int type,int width, int precision)
{
    ofstream fout;
    fout.open(file);
    if (!fout.is_open()) return -1;
    fout<<x.n<<" ";
    fout.precision(precision);
    fout.width(width);
    if (type==1) fout<<scientific;
    for (Ntype i=0; i<x.n; i++)
        {
            fout<<x.items[i]<<" ";
        }
    fout<<"\n";
    fout<<defaultfloat;
    fout.close();
    return 0;
}
//saving dimension and coefficients to binary file
Itype outputBinaryFile_DVector (char* file, DVector x)
{
    FILE* fout = fopen(file, "wb");
    if (!fout) return -1;
    Itype cnt =fwrite(&x.n, sizeof(Ntype),1,fout);
    cnt *=fwrite(x.items, sizeof (Dtype), x.n, fout);
    fclose(fout);
    return cnt;
}

//inputing vector from  binary file
Itype inputBinaryFile_DVector (char* file, DVector* x)
{
    FILE* finp = fopen(file, "rb");
    if (!finp) return -1;
    Itype cnt=fread(&(x->n), sizeof(Ntype), 1, finp);
    x->items = (Dtype*) malloc(x->n * sizeof (Dtype));
    cnt*=fread(x->items, sizeof(Dtype), x->n, finp);
    fclose(finp);
    return cnt;
}

Ntype DVector::operator==(DVector y)
{
    if (n!=y.n) return 0;
    for (int i=0; i<y.n; i++)
        if (abs(items[i]-y.items[i])>pow(10,-6))
            return 0;
    return 1;
}

Ntype DVector::operator!=(DVector y)
{
    return (!(*this==y));
}
