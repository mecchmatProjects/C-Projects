
void DMatrix_destroy(DMatrix x)
{
    free(x.items);
}
// generating matrix
DMatrix generate_DMatrix(Ntype n, Ntype m)
{
    DMatrix x;
    x.n=n;
    x.m=m;
    x.items=malloc(n*m*sizeof(Dtype));
    for (Ntype i=0; i<n*m; i++)
        x.items[i]=(0.5- (double) rand()/RAND_MAX);
    //Generates every item as double in range from -50 to 50
    return x;
}
//standard operations:
DMatrix add_DMatrix(DMatrix x, DMatrix y)
{
    DMatrix z;
    z.n=x.n;
    z.m=x.m;
    z.items = (Dtype*) malloc(z.n*z.n*sizeof(Dtype));
    for (Ntype i=0;i<x.n*x.m;i++)
        z.items[i]=x.items[i]+y.items[i];
    return z;
}
DMatrix sub_DMatrix(DMatrix x, DMatrix y)
{
    DMatrix z;
    z.n=x.n;
    z.m=x.m;
    z.items = (Dtype*) malloc(z.n*z.m*sizeof(Dtype));
    for (Ntype i=0;i<x.n*x.m;i++)
        z.items[i]=x.items[i]-y.items[i];
    return z;
}
DMatrix mmul_DMatrix(DMatrix x, DMatrix y)
{
    DMatrix z;
    Dtype d;
    z.n=x.n;
    z.m=y.m;
    z.items = (Dtype*) malloc(z.n*z.m*sizeof(Dtype));
    for (Ntype i=0;i<z.n;i++) for (Ntype j=0;j<z.m;j++)
    {
        d=0;
        for (Ntype r=0;r<x.m;r++)
            d+=x.items[i*x.m+r]*y.items[r*y.m+j];
        z.items[i*z.m+j]=d;
    }
    return z;
}
//product of matrix and float
DMatrix dmul_DMatrix(DMatrix x, Dtype y)
{
    DMatrix z;
    z.n=x.n;
    z.m=x.m;
    z.items = (Dtype*) malloc(z.n*z.m*sizeof(Dtype));
    for (Ntype i=0;i<x.n*x.m;i++)
        z.items[i]=x.items[i]*y;
    return z;
}
DMatrix mulv_DMatrix(DMatrix x, DVector y)
{
    DMatrix yy,z;
    yy.n=y.n;
    yy.m=1;
    yy.items = y.items;
    z=mmul_DMatrix( x, yy);
    return z;
}
DMatrix vmul_DMatrix(DVector y,DMatrix x)
{
    DMatrix yy,z;
    yy.n=1;
    yy.m=y.n;
    yy.items = y.items;
    z=mmul_DMatrix( yy,x);
    return z;
}
Dtype det_DMatrix(DMatrix x)
{
    Dtype det=0;
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
    det+=pow(-1,0)*x.items[0]*det_DMatrix(y);

    for (Ntype i=1;i<x.n;i++)
    {
        for (Ntype j=0;j<y.m;j++)
            y.items[(i-1)*y.m+j]=x.items[(i-1)*x.m+(j+1)];
        det+=pow(-1,i)*x.items[i*x.m]*det_DMatrix(y);
   }
    free(y.items);
    return det;
}
DMatrix inverse_DMatrix(DMatrix x)
{
    DMatrix y,z;
    y.n=x.n;
    y.m=x.m;
    y.items=(Dtype*) malloc(y.n*y.m*sizeof(Dtype));
    z.n=x.n-1;
    z.m=x.m-1;
    z.items=(Dtype*) malloc(z.n*z.m*sizeof(Dtype));
    Dtype det1=1/det_DMatrix(x);
    for (Ntype i=0;i<y.n;i++) for (Ntype j=0;j<y.m;j++)
    {
        for (Ntype ii=0;ii<z.n;ii++)
            for (Ntype jj=0;jj<z.m;jj++)
            z.items[ii*z.m+jj]=
            x.items[(ii+(ii>=i))*x.m+jj+(jj>=j)];

        y.items[j*y.m+i]=pow(-1,i+j)*det_DMatrix(z)*det1;
    }
    free(z.items);
    return y;

}
//standart unary operations
Itype unadd_DMatrix(DMatrix* x, DMatrix y)
{
    for (Ntype i=0;i<x->n*x->m;i++)
        x->items[i]+=y.items[i];
    return 0;
}
Itype unsub_DMatrix(DMatrix* x, DMatrix y)
{
    for (Ntype i=0;i<x->n*x->m;i++)
        x->items[i]-=y.items[i];
    return 0;
}
Itype undmul_DMatrix(DMatrix* x, Dtype y)
{
    for (Ntype i=0;i<x->n*x->m;i++)
        x->items[i]*=y;
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
    /*char str1[20]="0";
    Ntype cnt=0;

    int cur_smb=0;
    int cur_sz=0;
    while (!(str[cur_smb]==' ' || str[cur_smb]=='\0'))
    {   str1[cur_sz]=str[cur_smb]; cur_sz++; cur_smb++;}
    while (str[cur_smb]==' ')
    {   str1[cur_sz]=str[cur_smb]; cur_sz++; cur_smb++;}
    str1[cur_sz]='\0';

    sscanf(str1,"%u",&(x->n));

    cur_sz=0;
    while (!(str[cur_smb]==' ' || str[cur_smb]=='\0'))
    {   str1[cur_sz]=str[cur_smb]; cur_sz++; cur_smb++;}
    while (str[cur_smb]==' ')
    {   str1[cur_sz]=str[cur_smb]; cur_sz++; cur_smb++;}
    str1[cur_sz]='\0';

    sscanf(str1,"%u",&(x->m));

    x->items=(Dtype*) malloc(x->n*x->m*sizeof(Dtype));

    for (Ntype i=0;i<x->n;i++)
    {
        cur_sz=0;
        while (!(str[cur_smb]==' ' || str[cur_smb]=='\0'))
        {   str1[cur_sz]=str[cur_smb]; cur_sz++; cur_smb++;}
        while (str[cur_smb]==' ')
        {   str1[cur_sz]=str[cur_smb]; cur_sz++; cur_smb++;}
        str1[cur_sz]='\0';
        cnt+=sscanf(str1,"%lf",&(x->items[i]));
    }
    return cnt;
    */
    FILE* fout = fopen("temp.txt", "w");
    if (!fout) return -1;
    fprintf(fout,"%s",str);
    fclose(fout);
    Ntype cnt=inputTextFile_DMatrix("temp.txt",x);
    return cnt;
}

//printing matrix with printf
//type=1 means scientific format, else type means standard format
void output_DMatrix(DMatrix x, int type,int width, int precision)
{
    printf("%u %u \n",x.n,x.m);
    char techstring[6]="%";
    techstring[1]='0'+width;
    techstring[2]='.';
    techstring[3]='0'+precision;
    if (type==1) techstring[4]='e';
    else techstring[4]='f';
    //now techstring looks like "%1.2f" if width=1, precision=2
    for (Ntype i=0; i<x.n; i++)
    {
        for (Ntype j=0; j<x.m-1; j++)
        {
            printf(techstring,x.items[i*x.m+j]);
            printf(" ");
        }
        printf(techstring,x.items[(i+1)*x.m-1]);
        printf("\n");
    }
}

//printing matrix to text file (same as with printf)
Itype outputTextFile_DMatrix(char* file,DMatrix x, int type,int width, int precision)
{
    FILE* fout = fopen(file, "w");
    if (!fout) return -1;
    fprintf(fout,"%u %u \n",x.n,x.m);
    char techstring[6]="%";
    techstring[1]='0'+width;
    techstring[2]='.';
    techstring[3]='0'+precision;
    if (type==1) techstring[4]='e';
    else techstring[4]='f';
    //now techstring looks like "%1.2f" if width=1, precision=2
    for (Ntype i=0; i<x.n; i++)
    {
        for (Ntype j=0; j<x.m-1; j++)
        {
            fprintf(fout,techstring,x.items[i*x.m+j]);
            fprintf(fout," ");
        }
        fprintf(fout,techstring,x.items[(i+1)*x.m-1]);
        fprintf(fout,"\n");
    }
    fclose(fout);
    return 0;
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
void swap_rows_DMatrix(DMatrix*x,Ntype n1, Ntype n2)
{
    n1--;
    n2--;
    Dtype temp;
    for (int j=0;j<x->m;j++)
    {
        temp=x->items[n1*(x->m)+j];
        x->items[n1*(x->m)+j]=x->items[n2*(x->m)+j];
        x->items[n2*(x->m)+j]=temp;
    }
}

void swap_columns_DMatrix(DMatrix*x,Ntype m1, Ntype m2)
{
    m1--;
    m2--;
    Dtype temp;
    for (int i=0;i<x->n;i++)
    {
        temp=x->items[i*(x->m)+m1];
        x->items[i*(x->m)+m1]=x->items[i*(x->m)+m2];
        x->items[i*(x->m)+m2]=temp;
    }
}

/*int main()
{
    //srand(time(NULL));
    DMatrix a,b,c;
    Dtype d;
    /*a=generate_DMatrix(3,2);
    //b=generate_DMatrix(2,4);
    c=mul_DMatrix(a,b);
    output_DMatrix(a,0,3,2);
    output_DMatrix(b,0,3,2);

    DMatrix m=generate_DMatrix(3,3);
    output_DMatrix(m,0,3,5);
    printf("%lf\n",det_DMatrix(m));
    DMatrix m1=inverse_DMatrix(m);
    output_DMatrix(m1,0,3,5);
}*/
