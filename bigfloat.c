#include "bigfloat.h"

BigFloat *create(char *str) {
    int i;
    BigFloat *res;
    res = malloc(sizeof(BigFloat));
    res->decimal = 1;
    for (i = 0; i < PRECISION; i++) {
    res->digits[i] = 0;
    }
    res->negative = 0;
    parse(res, str);
    return res;
}

void freeBigFloat(BigFloat *b) {
  free(b);
}

void make_array(FILE* file, char* array, int size) {
   // read entire file into array
   fread(array, 1, size, file);
}

void read_from_file(char* res){
    FILE* file = fopen("Bigfloat_read_file.txt", "r");
    if (file == NULL) { printf("Error!"); }
    fseek(file, 0, SEEK_END);
    int fs = ftell(file);
    fseek(file, 0, SEEK_SET);
    char array[fs];
    make_array(file, array, fs);
    fclose(file);
    for(int i = 0; i < fs; i++) {
      res[i] = array[i];
  }
}

void write_to_file(BigFloat *b){
    FILE* file = fopen("Bigfloat_write_file.txt", "w");
    if (file == NULL) { printf("Error!"); }
    else{
        int i;
        if (b->negative) {
        fprintf(file,"-");
        }
        for (i = 0; i < PRECISION; i++) {
        if (i == b->decimal) {
          fprintf(file,".");
               }
        fprintf(file, "%d", b->digits[i]);
           }
        printf("\n");
    }
    fclose(file);
}

void parse(BigFloat *b, char *str) {
    int i = 0;
    int index = 0;
    if (str[0] == '-') {
    b->negative = 1;
    i = 1;
    } else {
    b->negative = 0;
    }
    for (; i < strlen(str) && index < PRECISION; i++) {
    if (str[i] == '.') {
      b->decimal = (b->negative) ? i - 1 : i;
    } else {
      b->digits[index++] = str[i] - '0';
    }
  }
}

void make_negative(BigFloat *b) {
    int i;
    if (b->negative == 0) {
     b->negative = 1;
  }
}

void print(BigFloat *b) {
    int i;
    if (b->negative) {
    printf("-");
    }
    for (i = 0; i < PRECISION; i++) {
    if (i == b->decimal) {
      printf(".");
    }
    printf("%d", b->digits[i]);
    }
    printf("\n");
}

lli to_int(BigFloat *b) {
    int i = 0;
    int n = 0;
    char res[30];
    for (i = 0; i < b->decimal; i++) {
    res[i] = b->digits[i];
    n++;
    }
    lli s;
    s = 0;
    lli f, pow1;
    if ( n<20 ){   //no more than 19 numbers before "."
    for (f = n - 1, pow1 = 1; f >= 0; --f, pow1*=10) {
        s += res[f] * pow1;
    }
    return s;
    }
    else{printf("ERROR: Too Big number to solve quadratic equation!!!\n");
      return 0;
  }
}

lli quadratic_equation(BigFloat *a1, BigFloat *b1, BigFloat *c1){
    lli a,b,c;
    lli d,root1,root2;

    a = to_int(a1);
    b = to_int(b1);
    c = to_int(c1);

    d = b * b - 4 * a * c;
    printf("A: %lld\n B: %lld\n C: %lld\n",a,b,c);

    if (d < 0){
        printf("Roots are complex number.\n");

        printf("Roots of quadratic equation are: ");
        printf("%.lld%+.3Lfi", -b/(2*a), sqrtl(-d) / (2*a));
        printf(", %.lld%+.3Lfi", -b/(2*a), -sqrtl(-d) / (2*a));

        return 0;
    }
    else if(d==0){
    printf("Both roots are equal.\n");

    root1 = -b /(2* a);
    printf("Root of quadratic equation is: %lld ",root1);

    return 0;
    }
    else{
    printf("Roots are real numbers.\n");

    root1 = ( -b + sqrt(d)) / (2* a);
    root2 = ( -b - sqrt(d)) / (2* a);
    printf("Roots of quadratic equation are: %lld , %lld",root1,root2);
    }
    return 0;
}

void solve_y(BigFloat *a, BigFloat *b, BigFloat *c){
    BigFloat *res1, *res2;

    res1 = create("0.0");
    res2 = create("0.0");

    standardizeDecimal(a, b);
    standardizeDecimal(a, c);
    if (equals(a, res1)) { // res1 == 0 so check if a == 0
    printf("Value of Y cannot be predicted!!!\n");
  } else {
      add(b,c,res1);
      divide(res1,a,res2);
        make_negative(res2);
      print(res2);
  }
}

void add(BigFloat *a, BigFloat *b, BigFloat *res) {
    int i, result;
    int carry = 0;
    standardizeDecimal(a, b);
    clear(res);
    res->decimal = a->decimal;
    for (i = PRECISION - 1; i >= 0; i--) {
    result = carry;
    /*    result += (a->negative) ? -1 * a->digits[i] : a->digits[i];
    result += (b->negative) ? -1 * b->digits[i] : b->digits[i]; */

    result += a->digits[i] + b->digits[i];
    carry = result / 10;
    res->digits[i] = result % 10;
    }
    if (carry != 0) {
    shiftDownBy(res->digits, PRECISION, 1);
    res->decimal++;
    res->digits[0] = carry;
    }
    trailingZeros(a);
    trailingZeros(b);
    trailingZeros(res);
}
void subtract(BigFloat *a, BigFloat *b, BigFloat *res) {
    int i, result;
    int carry = 0;
    BigFloat *top, *bottom;
    standardizeDecimal(a, b);
    clear(res);
    res->decimal = a->decimal;
    if (compare(a,b) >= 0) {
    top = a;
    bottom = b;
    } else {
    top = b;
    bottom = a;
    res->negative = 1;
    }
    for (i = PRECISION - 1; i >= 0; i--) {
     result = carry + top->digits[i];
     if (result < bottom->digits[i]) {
       carry = -1;
       res->digits[i] = result + 10 - bottom->digits[i];
     } else {
       carry = 0;
       res->digits[i] = result - bottom->digits[i];
     }
    }
    trailingZeros(a);
    trailingZeros(b);
    trailingZeros(res);
}
void multiply(BigFloat *a, BigFloat *b, BigFloat *res) {
    int i;
    int carry = 0;
    BigFloat *line = create("0.0");
    BigFloat *temp = create("0.0");
    clear(res);
    res->decimal = PRECISION;
    line->decimal = PRECISION;
    zerosFirst(a);
    zerosFirst(b);
    for (i = PRECISION - 1; i >= 0; i--) {
    multiplyLine(a, line, b->digits[i]);
    shiftUpBy(line->digits, PRECISION, PRECISION - i);
    add(res, line, temp);
    line->decimal = PRECISION;
    zerosFirst(temp);
    memcpy(res, temp, sizeof(BigFloat));
    }
    res->decimal -= PRECISION - a->decimal + PRECISION - b->decimal + 1;
    trailingZeros(a);
    trailingZeros(b);
    trailingZeros(res);
    freeBigFloat(line);
    line = NULL;
    res->negative = ((a->negative || b->negative) && !(a->negative && b->negative)) ? 1 : 0;
}
void divide(BigFloat *a, BigFloat *b, BigFloat *res) {
    int i, counter;
    int carry = 0;
    int index = 0;
    clear(res);
    res->decimal = b->decimal;
    if (equals(b, res)) { // res == 0 so check if b == 0
        printf("ERROR: cannot divide by 0\n");
    } else {
        BigFloat *current = create("0.0");
        BigFloat *temp = create("0.0");
        current->decimal = 0;
        res->decimal = a->decimal;
        for (i = 0; i < PRECISION; i++) {
            counter = 0;
            current->digits[index++] = a->digits[i];
            current->decimal++;
            trailingZeros(current);
            while (compare(current, b) >= 0) {
                subtract(current, b, temp);
                memcpy(current, temp, sizeof(BigFloat));
                counter++;
            }
            res->digits[i] = counter;
        }
        freeBigFloat(temp);
        freeBigFloat(current);
        trailingZeros(res);
    }
}

void multiplyLine(BigFloat *a, BigFloat *line, int mult) {
    int i, result;
    int carry = 0;
    for (i = PRECISION - 1; i >= 0; i--) {
    result = carry;
    result += a->digits[i] * mult;
    carry = result / 10;
    line->digits[i] = result % 10;
  }
}

char equals(BigFloat *a, BigFloat *b) {
    int i;
    if (a == b) {
    return 1;
  } else {
    if (a->decimal == b->decimal && a->negative == b->negative) {
      for (i = 0; i < PRECISION; i++) {
        if (a->digits[i] != b->digits[i]) {
          return 0;
        }
      }
      return 1;
    }
    else {return 0;}
  }
}
char compare(BigFloat *a, BigFloat *b) {
    int i;
    if (a == b) {
    return 0;
    }
    else {
    if (a->decimal != b->decimal) {
      return (char) a->decimal - b->decimal;
    }
    else {
      for (i = 0; i < PRECISION; i++) {
        if (a->digits[i] != b->digits[i]) {
          return (char) a->digits[i] - b->digits[i];
        }
      }
      return 0;
    }
  }
}

void zerosFirst(BigFloat *a) {
    int i, start;
    for (i = PRECISION - 1; i >= 0 && !a->digits[i]; i--);
    start = i;
    shiftDownBy(a->digits, PRECISION, PRECISION - start - 1);
    a->decimal += PRECISION - start - 1;
}
void trailingZeros(BigFloat *a) {
    int i, start;
    for (i = 0; i < PRECISION && !a->digits[i]; i++);
    if (a->decimal - i < 1) {
    i = a->decimal - 1;
    }
    start = i;
    shiftUpBy(a->digits, PRECISION, start);
    a->decimal -= start;
}

void standardizeDecimal(BigFloat *a, BigFloat *b) {
  if (b->decimal > a->decimal) {
    shiftDownBy(a->digits, PRECISION, b->decimal - a->decimal);
    a->decimal = b->decimal;
  } else if (b->decimal < a->decimal) {
    shiftDownBy(b->digits, PRECISION, a->decimal - b->decimal);
    b->decimal = a->decimal;
  }
}

void shiftDownBy(char *ar, int length, int shift) {
    int i;
  for (i = length - 1; i >= 0; i--) {
    if (i - shift >= 0) {
      ar[i] = ar[i - shift];
    } else {
      ar[i] = 0;
    }
  }
}
void shiftUpBy(char *ar, int length, int shift) {
    int i;
  for (i = 0; i < length; i++) {
    if (i + shift < length) {
      ar[i] = ar[i + shift];
    } else {
      ar[i] = 0;
    }
  }
}

void clear(BigFloat *a) {
    int i;
  if (a != NULL) {
    for (i = 0; i < PRECISION; i++) {
      a->digits[i] = 0;
    }
  }
}