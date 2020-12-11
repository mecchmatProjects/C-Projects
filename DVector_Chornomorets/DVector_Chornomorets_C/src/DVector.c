
void DVector_destroy(DVector x)
{
    free(x.items);
}
// generating vector
DVector generate_DVector(Ntype n)
{
    DVector dv;
    dv.n=n;
    dv.items=malloc(n*sizeof(Dtype));
    for (Ntype i=0; i<n; i++)
        dv.items[i]=100*(0.5- (double) rand()/RAND_MAX);
    //Generates every item as double in range from -50 to 50
    return dv;
}

//standard operations:
DVector add_DVector(DVector x, DVector y)
{
    DVector dv;
    dv.n=x.n;
    dv.items = (Dtype*) malloc(dv.n*sizeof(Dtype));
    for (Ntype i=0;i<x.n;i++)
        dv.items[i]=x.items[i]+y.items[i];
    return dv;
}


DVector sub_DVector(DVector x, DVector y)
{
    DVector dv;
    dv.n=x.n;
    dv.items = (Dtype*) malloc(dv.n*sizeof(Dtype));
    for (Ntype i=0;i<y.n;i++)
        dv.items[i]=x.items[i]-y.items[i];
    return dv;
}

//scalar product of 2 vectors
Dtype vmul_DVector(DVector x, DVector y)
{
    Dtype d=0;
    for (Ntype i=0;i<x.n;i++)
        d+=x.items[i]*y.items[i];
    return d;
}

//product of vector and float
DVector dmul_DVector(DVector x, Dtype y)
{
    DVector dv;
    dv.n=x.n;
    dv.items = (Dtype*) malloc(dv.n*sizeof(Dtype));
    for (Ntype i=0;i<x.n;i++)
        dv.items[i]=x.items[i]*y;
    return dv;
}

//product of vector and float, inverted to given float
DVector div_DVector(DVector x, Dtype y)
{
    DVector dv;
    dv.n=x.n;
    dv.items = (Dtype*) malloc(dv.n*sizeof(Dtype));
    if (dv.items)
    for (Ntype i=0;i<x.n;i++)
        dv.items[i]=x.items[i]/y;
    return dv;
}

//absolute value of a vector
Dtype abs_DVector(DVector x)
{
    Dtype d=0;
    for (Ntype i=0;i<x.n;i++)
        d+=pow(x.items[i],2);
    d=sqrt(d);
    return d;
}

//standart unary operations
Itype unadd_DVector(DVector* x, DVector y)
{
    for (Ntype i=0;i<x->n;i++)
        x->items[i]+=y.items[i];
    return 0;
}

Itype unsub_DVector(DVector* x, DVector y)
{
    for (Ntype i=0;i<x->n;i++)
        x->items[i]-=y.items[i];
    return 0;
}


Itype undmul_DVector(DVector* x, Dtype y)
{
    for (Ntype i=0;i<x->n;i++)
        x->items[i]*=y;
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
void output_DVector(DVector x, int type,int width, int precision)
{
    printf("%i ",x.n);
    char techstring[20]="%";
    techstring[1]='0'+width;
    techstring[2]='.';
    techstring[3]='0'+precision;
    if (type==1) techstring[4]='e';
    else techstring[4]='f';
    //now techstring looks like "%1.2f" if width=1, precision=2
    for (Ntype i=0; i<x.n; i++)
        {
            printf(techstring,x.items[i]);
            printf(" ");
        }
    printf("\n");
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
    /*char str1[20]="0";
    Ntype cnt=0;
    sscanf(str,"%u",&(x->n));
    x->items=(Dtype*) malloc(x->n*sizeof(Dtype));
    int cur_smb=1;
    int cur_sz;
    while (!(str[cur_smb]==' ' || str[cur_smb]=='\0'))
        cur_smb+=1;
    while (str[cur_smb]==' ') cur_smb+=1;
    for (Ntype i=0;i<x->n;i++)
    {
        cur_sz=0;
        while (!(str[cur_smb]==' ' || str[cur_smb]=='\0'))
        {   str1[cur_sz]=str[cur_smb]; cur_sz++; cur_smb++;}
        while (str[cur_smb]==' ')
        {   str1[cur_sz]=str[cur_smb]; cur_sz++; cur_smb++;}
        str1[cur_sz]='\0';
        cnt+=sscanf(str1,"%lf",&(x->items[i]));
    }*/
    Ntype cnt=inputTextFile_DVector("temp.txt",x);
    return cnt;
}

Itype outputTextFile_DVector(char* file,DVector x, int type,int width, int precision)
{
    FILE* fout = fopen(file, "w");
    if (!fout) return -1;
    fprintf(fout ,"%i ",x.n);
    char techstring[20]="%";
    techstring[1]='0'+width;
    techstring[2]='.';
    techstring[3]='0'+precision;
    if (type==1) techstring[4]='e';
    else techstring[4]='f';
    //now techstring looks like "%1.2f" if width=1, precision=2
    for (Ntype i=0; i<x.n; i++)
        {
            fprintf(fout ,techstring,x.items[i]);
            fprintf(fout ," ");
        };
    fprintf(fout ,"\n");
    fclose(fout);
    return 0;
}

/*
//inputing vector from any normal string
Ntype inputs1_DVector(DVector* x, char* str)
{
    Ntype d_started=0, i=0, after_point=0;
    //d_started is boolean detecting if new number reading has started
    //i is current index
    //after_point is 0 if there has been no point yet in current number
    //otherwise after_point if number of chars read after point+1
    Dtype curr=0,  cur_sgn=1;
    //curr is current number in process of reading (without a sign)
    //cur_sgn is 1 if there was no - on start of current number and -1 otherwise
    x->n=0;
    x->items=(Dtype*) malloc(0);
    while(1)
    {
        //printf("%c\n",str[i]);
        if (str[i]=='-')
        {
            if (d_started) break;
            cur_sgn=-1;
            //sign is changed to -1
        }
        if (str[i]=='.')
        {
            d_started=1;
            //the number is now started, if it wasn't
            after_point=1;
            //the next digit will be 1st after point
        }
        if ('0'<=str[i] && str[i]<='9')
        {
            d_started=1;
            //the number is now started, if it wasn't
            if (after_point>0)
            {
                curr+=(str[i]-'0')/pow(10,after_point);
                //because it is (after_point)-th digit after point
                //(str[i]-'0') gets integer from char digit
                after_point++;
                //one more digit after point has been read
            }
            else
            {
                curr=curr*10+(str[i]-'0');
                //because there is no point in number now
            }
        }
        else if (!(str[i]=='.'||str[i]=='-')) //if current char is not a digit or - or .
        {
            if (d_started>0)
            {
                //ending reading a number if it was started
                d_started=0; //boolean to 0
                //adding read number to list of items and increasing vector dimension
                x->n+=1;
                x->items=(Dtype*) realloc(x->items,x->n*sizeof(Dtype));
                x->items[x->n-1]=curr*cur_sgn;
                curr=0; //to default
                cur_sgn=1; //to default
                after_point=0; //to default
            }
        }
        //printf("%f %f %i %i \n",cur_sgn,curr,after_point,d_started);
        if (str[i]=='\0') break; //end of string (number has been ended already)
        i++;
    }
    return i;
}
//inputing vector from text file like from string
Ntype inputTextFile1_DVector (char* file,DVector* x)
{
    FILE* finp = fopen(file, "r");
    if (!finp) return -1;
    fseek (finp, 0, SEEK_END);
    Ntype fl_sz = ftell (finp);//getting size of file
    fseek (finp, 0, SEEK_SET);
    char* str = (char*)  malloc((fl_sz+1)*sizeof(char));
    //inputing all file to string
    for (int i=0;i<fl_sz;i++)
    {
        str[i]=fgetc(finp);
        // printf("%i",str[i]=='\0');
    }
    //adding '\0' to stop inputs_DVector
    str[fl_sz]='\0';
    //inputing vector from string
    Ntype cnt=inputs_DVector(x, str);
    fclose(finp);
    return cnt;
}
//printing vector with printf
void output1_DVector(DVector x, int type,int width, int precision)
{
    printf("(");
    char techstring[20]="%";
    techstring[1]='0'+width;
    techstring[2]='.';
    techstring[3]='0'+precision;
    techstring[4]='f';
    //now techstring looks like "%1.2f" if width=1, precision=2
    for (Ntype i=0; i<x.n-1; i++)
        {
            printf(techstring,x.items[i]);
            printf(", ");
        }
    printf(techstring,x.items[x.n-1]);
    printf(")\n");
}
//printing vector to text file (same as with printf)
Ntype outputTextFile1_DVector(char* file,DVector x, int type,int width, int precision)
{
    FILE* fout = fopen(file, "w");
    if (!fout) return -1;
    fprintf(fout,"(");
    char techstring[20]="%";
    techstring[1]='0'+width;
    techstring[2]='.';
    techstring[3]='0'+precision;
    techstring[4]='f';
    //now techstring looks like "%1.2f" if width=1, precision=2
    for (Ntype i=0; i<x.n-1; i++)
        {
            fprintf(fout,techstring,x.items[i]);
            fprintf(fout,", ");
        }
    fprintf(fout,techstring,x.items[x.n-1]);
    fprintf(fout,")\n");
    fclose(fout);
    return 0;
}
*/
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


/*int main()
{
    srand(time(NULL));
    DVector v,u,w;
    Dtype d;
    v=generate_DVector(4);
    //char* terr=malloc(6*sizeof(char));
    //terr="23 54.3 -3 76";
    //u=generate_DVector(4);
    //outputTextFile_DVector("inp2.txt",v,0,3,2);
    output_DVector(v,0,3,2);
    outputBinaryFile_DVector("v1.dvect",v);
    d=inputTextFile_DVector("inp2.txt",&v);
    inputBinaryFile_DVector("v1.dvect",&u);
    output_DVector(v,0,3,2);
    output_DVector(u,0,3,2);
    w=add_DVector(v,u);
    output_DVector(w,0,3,2);
    w=sub_DVector(v,u);
    output_DVector(w,0,3,2);
    d=mmul_DVector(v,u);
    printf("%f\n",d);
    w=mul_DVector(v,2);
    output_DVector(w,0,3,2);
    w=div_DVector(v,2);
    output_DVector(w,0,3,2);
    d=abs_DVector(v);
    printf("%f\n",d);
    return 0;
}
*/
