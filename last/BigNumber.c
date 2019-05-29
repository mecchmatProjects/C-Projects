#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
/* File  BigNumber.c
Realization of BugNumber
Done by Zelenko Petro & Goryslavets Dmytro Statistics 2 curs
Email:  zelenko.peter369@gmail.com & d.goryslavets@ukr.net
Date 26.05.2019 */

const int nmax = 50;
typedef struct
{
    unsigned int* num; // pointer on array of coefficient
    int len;          // length of array
    short sign;      // sign of number(can be: +1, -1)
}Tlong;


char *substring(const char *string, int position, int length) // make a cut of string from position with length length
{
   char *pointer = (char*)malloc(length+1);
   int c;
   for (c = 0; c < length; c++)
   {
      *(pointer+c) = *(string+position);
      string++;
   }
   *(pointer+c) = '\0';
   return pointer;
}


Tlong add_abs(Tlong *a, Tlong *b) // addition of numbers by modulus(bitwise, in the columns)
{
    Tlong res;
    res.len=a->len;
    res.sign=a->sign;
    res.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) res.num[i] = (unsigned int)0;
    unsigned int p=0;//to the next digit in number
    if(a->len<b->len)
        res.len = b->len;
    for(int i=nmax-1;i>=nmax-res.len-1;i--)//addition is done bitwise
    {
        long long s = (long long)a->num[i] + (long long)b->num[i] + p; // the first two positions are added in the broader type
        res.num[i] = (unsigned int)(s%((long long)((unsigned int)(-1))+1));// and then broken down by necessary discharges
        p = (unsigned int)(s/((long long)((unsigned int)(-1))+1));
    }
    if (res.num[nmax-res.len-1]>0)//correction length
    {
        res.len++;
    }
    return res;
}

Tlong sub_abs(Tlong *a,Tlong *b) // subtraction of numbers by modulus (in a column, from a larger one less)
{
    Tlong res;
    res.len=a->len;
    res.sign=a->sign;
    res.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) res.num[i] = (unsigned int)0;
    int z=0;//transfer
    for(int i=nmax-1;i>=nmax-a->len;i--)//bitwise
    {
        long long r = (long long)a->num[i]-(long long)b->num[i]-z; // similar to adding
        if(r<0)
        {
            r+=(long long)((long long)((unsigned int)(-1))+1);
            z=1;
        }
        else
        {
            z=0;
        }
        res.num[i] = (unsigned int)r;
    }
    while(res.len>1 && res.num[nmax-res.len]==0)//correction length
    {
        res.len--;
    }
    return res;
}

int comp_abs(Tlong* a, Tlong* b)// comparison of two numbers by module
{
    if (a->len>b->len)//first in length
    {
        return 1;
    }
    else
    {
        if(a->len<b->len)
        {
            return -1;
        }
        else
        {
            int i=nmax-a->len;//then one by one
            while(i<nmax && a->num[i]==b->num[i])
            {
                i++;
            }
            if(a->num[i]>b->num[i])
            {
                return 1;
            }
            else
            {
                if(a->num[i]<b->num[i])
                {
                    return -1;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}
int compare(Tlong *a,Tlong *b)//comparison of two numbers taking into account the sign
{
    if(a->sign==b->sign)
    {
        if(a->sign==-1)
        {
            return -comp_abs(a,b);
        }
        else
        {
            return comp_abs(a,b);
        }
    }
    else
    {
        if(a->sign==-1)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
}

Tlong add(Tlong *a, Tlong *b)//addition with a sign
{
    /*Depending on the character of the numbers, this may be both an addition and a subtraction*/
    Tlong res;
    if(a->sign==b->sign)
    {
        res=add_abs(a,b);
        res.sign=a->sign;
    }
    else
    {
        int s=comp_abs(a,b);
        if(s>0)
        {
            res=sub_abs(a,b);
            res.sign=a->sign;
        }
        else
        {

            if(s<0)
            {
                res=sub_abs(b,a);
                res.sign=b->sign;
            }
            else
            {
                res.len=1;
                res.sign=1;
                res.num = (unsigned int *)malloc(nmax*32);
                for(int i=0;i<nmax;i++) res.num[i] = (unsigned int)0;
            }
        }
    }
    return res;
}

Tlong sub(Tlong *a, Tlong *b)//pictures based on the sign
{
    b->sign= b->sign *(-1);
    Tlong res=add(a,b);//subtraction - addition with the opposite sign
    b->sign= b->sign *(-1);
    return res;
}

Tlong convert(long long a) // conversion of a "short" number into a long one
{
    Tlong res;
    res.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) res.num[i] = (unsigned int)0;
    if(a>=0) res.sign = 1;
    else {res.sign=-1; a = -a;}
    res.len = 1;// the whole number can take up to 2 bits(in array)
    res.num[nmax-1] = (unsigned int)(a%((long long)((unsigned int)(-1))+1));
    res.num[nmax-2] = (unsigned int)(a/((long long)((unsigned int)(-1))+1));
    if(res.num[nmax-2]!=0) res.len=2;
    return res;
}

void setlen(Tlong *res)//correction of the length of the number (if the length is incorrect then it changes with the correct one)
{
    int i=0;
    while(i<nmax && res->num[i]==0) i++;
    if(i<nmax) res->len=nmax-i;
    else res->len=1;
}

Tlong mul(Tlong *a, Tlong *b)//multiplication of two numbers
{
    Tlong nol = convert(0);
    if(compare(&nol,a) == 0 || compare(&nol,b) == 0) return nol;
    free(nol.num);
    Tlong res;
    res.sign=a->sign*b->sign;
    res.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) res.num[i] = (unsigned int)0;
    unsigned int r=0;//transfer
    for(int j=nmax-1;j>=nmax-b->len;j--)//multiplying in the column
    {
        for(int i=nmax-1;i>=nmax-a->len;i--)
        {
            unsigned long long multi=(unsigned long long)r+(unsigned long long)a->num[i]*(unsigned long long)b->num[j];
            res.num[i+j-nmax+1] += (unsigned int)(multi % ((unsigned long long)((unsigned int)(-1))+1));
            r = (unsigned int)(multi/((unsigned long long)((unsigned int)(-1))+1));
        }
        res.num[nmax-a->len + j - nmax] = r;//after multiplying each discharge for the whole number a must take into account and reset the transfer
        r=0;
    }
    setlen(&res);//checking and correcting the length of the resulting number
    return res;
}

void shift(Tlong *a, int k)//shift the number left (right - k - negative) to k positions
{
    if(k>=0)//if k a positive number the number is shifted to the left and the places that are freed become 0
    {
        a->len+=k;
        for(int i=nmax-a->len;i<nmax-k;i++) a->num[i]=a->num[i+k];
        for(int i=nmax-k;i<nmax;i++) a->num[i]=0;
    }
    else
    {
        for(int i=nmax+k-1;i>=nmax-a->len;i--) a->num[i-k]=a->num[i];
        for(int i=nmax-a->len;i<nmax-a->len-k;i++) a->num[i]=0;
    }
    while(a->len>1 && a->num[nmax-a->len]==0) a->len--;
}

Tlong add_scal(Tlong *a, long long b)//adding short to a long number
{
    Tlong c = convert(b);
    return add(a, &c);
}
Tlong sub_scal(Tlong *a, long long b)//subtraction from a short long number
{
    Tlong c = convert(b);
    return sub(a, &c);
}
Tlong mul_scal(Tlong *a, long long b)// multiplying for a short one
{
    Tlong c = convert(b);
    return mul(a, &c);
}

int compare_scal(Tlong *a, long long b) //comparison of long and short numbers
{
    Tlong c = convert(b);
    int res = compare(a,&c);
    free(c.num);
    return res;
}
Tlong divT(Tlong *a, Tlong *b)//dividing two numbers all the way
{
    if(compare_scal(b,0)==0) {printf("division by zero"); exit(1);}
    if(compare_scal(a,0)==0) return convert(0);
    if(comp_abs(a,b)<0) return convert(0);
    if(comp_abs(a,b)==0) return convert((int)a->sign*b->sign);
    Tlong quot,rest;
    short as = a->sign, bs=b->sign;
    a->sign=1;
    b->sign=1;
    quot.sign=1;
    quot.len = 1;
    quot.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) quot.num[i] = (unsigned int)0;
    rest.sign=1;
    rest.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) rest.num[i] = (unsigned int)0;
    if(a->len<b->len) rest.len=a->len;
    else rest.len=b->len;
    for(int i=0;i<rest.len;i++) rest.num[nmax-rest.len+i]=a->num[nmax-a->len+i];
    for(int p=nmax-a->len+b->len-1;p<nmax;p++)//is realized by dividing into a column with a binary search of factors
    {
        unsigned long long l=0, r = (unsigned long long)2*((unsigned int)-1);
        while (l < r - 1)
        {
            unsigned long long m = (l + r) / 2;
            Tlong res = mul_scal(b, m);
            Tlong riz = sub(&rest, &res);
            int comp = compare_scal(&riz, 0);
            if(comp == 0)
            {
                l = m;
                r = m;
                break;
            }
            if (comp>0) l = m;
            else r = m;
            free(res.num);
            free(riz.num);
        }
        Tlong res = mul_scal(b, l);
        Tlong riz = sub_abs(&rest, &res);
        Tlong c = sub(&riz, b);
        if(l == r-1 && compare_scal(&c, 0)>0)
        {
            l++;
            riz = c;
        }
        free(res.num);
        free(rest.num);
        rest.num = riz.num;
        rest.len = riz.len;
        setlen(&rest);
        shift(&quot,1);
        quot.num[nmax-1]=l;
        shift(&rest,1);
        rest.num[nmax-1]=a->num[p+1];
    }
    free(rest.num);
    a->sign=as;
    b->sign=bs;
    quot.sign = as*bs;
    return quot;
}

Tlong modT(Tlong *a, Tlong *b)// the remainder of the division of two large numbers
{
    if(compare_scal(b,0)==0) {printf("division by zero"); exit(1);}
    if(compare_scal(a,0)==0) return convert(0);
    if(comp_abs(a,b)<0)//the procedure itself is identical to the whole-round division procedure
    {
        Tlong res;
        res.len = a->len;
        res.sign = a->sign;
        res.num = a->num;
        return res;
    }
    if(comp_abs(a,b)==0) return convert(0);
    Tlong quot,rest;
    short as = a->sign, bs=b->sign;
    a->sign=1;
    b->sign=1;
    quot.sign=1;
    quot.len = 1;
    quot.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) quot.num[i] = (unsigned int)0;
    rest.sign=1;
    rest.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) rest.num[i] = (unsigned int)0;
    if(a->len<b->len) rest.len=a->len;
    else rest.len=b->len;
    for(int i=0;i<rest.len;i++) rest.num[nmax-rest.len+i]=a->num[nmax-a->len+i];
    for(int p=nmax-a->len+b->len-1;p<nmax;p++)
    {
        unsigned long long l=0, r = (unsigned long long)2*((unsigned int)-1);
        while (l +1 < r)
        {
            unsigned long long m = (l + r) / 2;
            Tlong res = mul_scal(b, m);
            Tlong riz = sub(&rest, &res);
            int comp = compare_scal(&riz, 0);
            if(comp == 0)
            {
                l = m;
                r = m;
                break;
            }
            if (comp>0) l = m;
            else r = m;
            free(res.num);
            free(riz.num);
        }
        Tlong res = mul_scal(b, l);
        Tlong riz = sub_abs(&rest, &res);
        Tlong c = sub(&riz, b);
        if(l == r-1 && compare_scal(&c, 0)>0)
        {
            l++;
            riz = c;
        }
        free(res.num);
        free(rest.num);
        rest.num = riz.num;
        rest.len = riz.len;
        setlen(&rest);
        shift(&quot,1);
        quot.num[nmax-1]=l;
        shift(&rest,1);
        rest.num[nmax-1]=a->num[p+1];
    }
    free(quot.num);
    a->sign=as;
    b->sign=bs;
    quot.sign = as*bs;
    shift(&rest,-1);
    return rest;
}
Tlong divT_scal(Tlong *a, long long b)//dividing long on short
{
    Tlong c = convert(b);
    Tlong res = divT(a, &c);
    free(c.num);
    return res;
}
Tlong divscal_T(long long b, Tlong *a)//dividing a short on a long whole
{
    Tlong c = convert(b);
    Tlong res = divT(&c, a);
    free(c.num);
    return res;
}
Tlong modT_scal(Tlong *a, long long b)//the remainder of the division is long to short
{
    Tlong c = convert(b);
    Tlong res = modT(a, &c);
    free(c.num);
    return res;
}
Tlong modscal_T(long long b, Tlong *a)//the remainder of dividing short by long
{
    Tlong c = convert(b);
    Tlong res = modT(&c, a);
    free(c.num);
    return res;
}

Tlong copyT(Tlong *a)//copying long
{
    Tlong res;
    res.len = a->len;
    res.sign = a->sign;
    res.num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) res.num[i] = a->num[i];
    return res;
}
Tlong NSD(Tlong *a, Tlong *b)//search for the largest common divider
{
    if(a->sign == -1 || a->sign == -1) return convert(0);
    Tlong A = copyT(a), B = copyT(b);
    while(compare_scal(&A, 0) > 0 && compare_scal(&B, 0) > 0)//the search is done using the Euclidean algorithm
    {
        if(compare(&A,&B)>0)
        {
            Tlong m = modT(&A,&B);
            free(A.num);
            A.len = m.len;
            A.num = m.num;
        }
        else
        {
            Tlong m = modT(&B,&A);
            free(B.num);
            B.len = m.len;
            B.num = m.num;
        }
    }
    return add(&A,&B);
}
Tlong NSK(Tlong *a, Tlong *b)//search for the smallest common multiple
{
    Tlong res1 = mul(a,b), nsd = NSD(a,b);//by the formula a * b / nsd (a, b)
    Tlong res2 = divT(&res1, &nsd);
    free(res1.num);
    free(nsd.num);
    return res2;
}
int input_from_str(Tlong *x, const char *str, int systema_chislennya)//entering a number from a string
{
    x->len=0;
    x->num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) (*x).num[i] = (unsigned int)0;
    int shift=0;
    if(str[0]=='-' || str[0]=='+')
    {
        if(str[0]=='-') x->sign = -1;
        if(str[0]=='+') x->sign = 1;
        shift=1;
    }
    else x->sign=1;
    int r=shift;
    switch (systema_chislennya)
    {
    case 2:
        {
            for(int i=shift;i<strlen(str);i++)
            {
                if(str[i] < '0' || str[i] > '1')
                break;
                else r++;
            }
            x->len = (r-shift)/32;
            for(int i=1; i<=x->len;i++)
            {
                char* roz = substring(str, r - i*32, 32), *end;
                x->num[nmax - i] = (unsigned int)strtoul(roz, &end, 2);
                free(roz);
            }
            if(r%32 != 0)
            {
                x->len++;
                char* roz = substring(str, shift, (r-shift)%32), *end;
                x->num[nmax - x->len] = (unsigned int)strtoul(roz, &end, 2);
                free(roz);
            }
            break;
        }
    case 16:
        {
            for(int i=shift;i<strlen(str);i++)
            {
                if((str[i] >= '0' && str[i] <= '9') || (toupper(str[i]) <= 'F' && toupper(str[i]) >= 'A'))
                r++;
                else break;
            }

            x->len = (r-shift)/8;
            for(int i=1; i<=x->len;i++)
            {
                char* roz = substring(str, r - i*8, 8), *end;
                x->num[nmax - i] = (unsigned int)strtoul(roz, &end, 16);
                free(roz);
            }
            if((r-shift)%8 != 0)
            {
                x->len++;
                char* roz = substring(str, shift, (r-shift)%8), *end;
                x->num[nmax - x->len] = (unsigned int)strtoul(roz, &end, 16);
                free(roz);
            }
            break;
        }
    case 10:
        {
            for(int i=shift;i<strlen(str);i++)
            {
                if(str[i] < '0' || str[i] > '9')
                break;
                else r++;
            }
            Tlong res = convert(0);
            Tlong osn = convert(1);
            for(int i=r-1;i>=shift;i--)
            {
                if(str[i]!='0')
                {
                    Tlong m = mul_scal(&osn, str[i] - '0');
                    Tlong dod = add(&res, &m);
                    free(m.num);
                    free(res.num);
                    res.num=dod.num;
                    res.len = dod.len;
                }
                Tlong no = mul_scal(&osn, 10);
                free(osn.num);
                osn.len = no.len;
                osn.num = no.num;
            }
            free(x->num);
            free(osn.num);
            x->len = res.len;
            x->num = res.num;
        }
    }
    return r;
}

int append(Tlong *x, unsigned int a)//add a new junior level with the displacement of the whole number
{
    shift(x,1);
    x->num[nmax-1] = a;
    return 1;
}

int update(Tlong *x, int k, unsigned int a)//replacement of the value of the k-th category
{
    x->num[nmax - k] = a;
    return 1;
}

int input_from_console(Tlong *x, int systema_chislennya)//entering a number from the console in the number system bitwise
{
    int len = 0;// the number should be entered in the format 123 123 123.
    x->len = 1;// the point at the end is obligatory
    x->num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) (*x).num[i] = (unsigned int)0;
    char s[1000], *end;
    scanf("%s", s);
    if(s[0]=='-' || s[0]=='+')
    {
        char* roz = substring(s, 1, strlen(s));
        append(x, (unsigned int)strtoul(roz, &end, systema_chislennya));
        if(s[0]=='-') x->sign = -1;
        if(s[0]=='+') x->sign = 1;
        free(roz);
    }
    else
    {
        append(x, (unsigned int)strtoul(s, &end, systema_chislennya));
        x->sign=1;
    }
    len++;
    if(s[strlen(s)-1] == '.') return len;
    while(s[strlen(s)-1] != '.')
    {
        scanf("%s", s);
        append(x,(unsigned int)strtoul(s, &end, systema_chislennya));
        len++;
    }
    return len;
}

int inputTextFile(char* file, Tlong *x, int systema_chislennya)//enter a number from the file file in the system with one long number
{
    FILE *f = fopen(file,"r");
    fseek(f,0, SEEK_END);
    int s = ftell(f);
    fseek(f,0, SEEK_SET);
    char*st = (char*)malloc(ftell(f));
    fread(st,s,1,f);
    st[s/sizeof(char)]= '\0';
    int k=input_from_str(x,st,systema_chislennya);
    free(st);
    fclose(f);
    return k;
}
int input_console_oneline(Tlong *x, int systema_chislennya)//entering a large number in the console in a single-line system, for example: 12348298428374982348729874834
{
    char s[1000];
    fgets(s,1000,stdin);
    return input_from_str(x, &s, systema_chislennya);
}

int inputBinaryFile(char* file, Tlong* x)//read from a binary file in this way as write
{
    FILE *f = fopen(file,"rb");
    fseek(f,0, SEEK_END);
    x->num = (unsigned int *)malloc(nmax*32);
    for(int i=0;i<nmax;i++) (*x).num[i] = (unsigned int)0;
    int s = (ftell(f) - sizeof(short))/sizeof(unsigned int);
    fseek(f,0, SEEK_SET);
    fread(&(x->sign), sizeof(short), 1, f);
    x->len = s;
    for(int i=nmax-x->len;i<=nmax;i++) fread(&x->num[i], sizeof(unsigned int), 1, f);
    fclose(f);
    return 1;
}
int outputBinaryFile(char* file, Tlong* x)//output in a binary file in this way: first, a short digit(sign) of the number and then all the digits
{
    FILE *f = fopen(file,"wb");
    fseek(f,0, SEEK_SET);
    fwrite(&x->sign, sizeof(short), 1, f);
    for(int i=nmax-x->len;i<nmax;i++) fwrite(&x->num[i], sizeof(unsigned int), 1, f);
    fclose(f);
    return 1;
}

int outputTextFile(char* file, Tlong *a, int width, int heigh)//output to a text file bitwise with the ability to select the width and height of the table
{
    int x,y;// for these parameters correspond to width and heigh, if one of them (or both) 0 then the program automatically selects the size
    if(width == 0 && heigh == 0)
    {
        x = a->len;
        y = 1;
    }
    if(width != 0 && heigh == 0)
    {
        x = width;
        y = a->len/width;
        if(a->len%width!=0) y++;
    }
    if(width == 0 && heigh != 0)
    {
        x = a->len/heigh;
        y = heigh;
        if(a->len%heigh!=0) x++;
    }
    if(width != 0 && heigh != 0)
    {
        x = width;
        y = heigh;
    }
    FILE *f = fopen(file,"w");
    fseek(f,0, SEEK_SET);
    int k=0;
    if(a->sign == -1) fprintf(f,"%c",'-');
    for(int i=0;i<y && k<a->len;i++)
    {
        for(int j=0;j<x && k<a->len;j++) {fprintf(f,"%010u ", a->num[nmax - a->len + k]);k++;}
        fprintf(f,"\n");
    }
    fclose(f);
    return 1;
}

int outputConsole(Tlong *a, int width, int heigh)// output number in the console to adjust the size of the table, the regulation is not different from working with the file
{
    int x,y;
    if(width == 0 && heigh == 0)
    {
        x = a->len;
        y = 1;
    }
    if(width != 0 && heigh == 0)
    {
        x = width;
        y = a->len/width;
        if(a->len%width!=0) y++;
    }
    if(width == 0 && heigh != 0)
    {
        x = a->len/heigh;
        y = heigh;
        if(a->len%heigh!=0) x++;
    }
    if(width != 0 && heigh != 0)
    {
        x = width;
        y = heigh;
    }
    int k=0;
    if(a->sign == -1) printf("%c",'-');
    for(int i=0;i<y && k<a->len;i++)
    {
        for(int j=0;j<x && k<a->len;j++) {printf("%010u ", a->num[nmax - a->len + k]);k++;}
        printf("\n");
    }
    return 1;
}

int destroy(Tlong *x)//release of memory
{
    free(x->num);
}
