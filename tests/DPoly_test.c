#include "DPoly.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <ctype.h>

/*constant value for tests*/
#define N 10

int dpoly_zero_test(void){
    dpoly poly;
    dpoly_zero(&poly,N);
    if(poly.size!=N){
        dpoly_destroy(&poly);
        return 1;
    }
    for(int i=0;i<N;++i){
        if(poly.coefficients[i]!=0.){
            dpoly_destroy(&poly);
            return 1;
        }
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_generate_test(void){
    dpoly poly;
    dpoly_generate(&poly,N);
    if(poly.size==N){
        dpoly_destroy(&poly);
        return 0;
    }
    dpoly_destroy(&poly);
    return 1;
}

int dpoly_destroy_test(void){
    dpoly poly;
    dpoly_zero(&poly,N);
    dpoly_destroy(&poly);
    if(poly.size==0&&poly.coefficients==NULL){
        return 0;
    }
    return 1;
}

int dpoly_copy_test(void){
    dpoly poly;
    dpoly_zero(&poly,N);
    for(int i=0;i<N;++i){
        poly.coefficients[i]=i;
    }
    dpoly poly_c;
    dpoly_copy(&poly,&poly_c);
    dpoly_destroy(&poly);
    if(poly_c.size!=N){
        dpoly_destroy(&poly_c);
        return 1;
    }
    int res=0;
    for(int i=0;i<N;++i){
        if(poly_c.coefficients[i]!=i){
           res=1;
        }
    }
    dpoly_destroy(&poly_c);
    return res;
}

int dpoly_sinput_test_1(void){
    char str[]="2*x - 2.5 x +1.4e2*x^3 + 3";
    dpoly poly;
    if(dpoly_sinput(&poly, str)!=4){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.size!=4){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=3.||poly.coefficients[1]!=-0.5||
        poly.coefficients[2]!=0.||poly.coefficients[3]!=140.){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_sinput_test_2(void){
    char str[]="5*x^2+ x+ y*x+ #@& +2";
    dpoly poly;
    if(dpoly_sinput(&poly, str)!=2){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.size!=3){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0||poly.coefficients[1]!=1||
        poly.coefficients[2]!=5){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_sinput_test_3(void){
    char str[]="";
    dpoly poly;
    if(dpoly_sinput(&poly, str)!=0){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.size!=1){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}



int dpoly_finput_test_1(void){
    FILE* f = fopen("test.txt", "w");
    fprintf(f, "2*x - 2.5 x +1.4e2*x^3 + 3\n");
    fclose(f);
    f = fopen("test.txt", "r");

    dpoly poly;
    if(dpoly_finput(&poly, f)!=4){
        dpoly_destroy(&poly);
        fclose(f);
        return 1;
    }
    fclose(f);

    if(poly.size!=4){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=3.||poly.coefficients[1]!=-0.5||
        poly.coefficients[2]!=0.||poly.coefficients[3]!=140.){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_finput_test_2(void){
    FILE *f = fopen("test.txt", "w");
    fprintf(f, "5*x^2+ x+ y*x+ #@& +2\n");
    fclose(f);
    f = fopen("test.txt", "r");

    dpoly poly;
    if(dpoly_finput(&poly, f)!=2){
        dpoly_destroy(&poly);
        fclose(f);
        return 1;
    }
    fclose(f);

    if(poly.size!=3){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0||poly.coefficients[1]!=1||
        poly.coefficients[2]!=5){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_finput_test_3(void){
    FILE* f = fopen("test.txt", "w");
    fclose(f);
    f = fopen("test.txt", "r");

    dpoly poly;
    int r = dpoly_finput(&poly, f);
    if(r!=0){
        dpoly_destroy(&poly);
        fclose(f);
        return 1;
    }
    fclose(f);



    if(poly.size!=1){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_sread_text_test_1(void){
    char str[]="3 -0.5 0 1.4e2";
    dpoly poly;
    if(dpoly_sread_text(&poly, str)!=4){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.size!=4){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=3.||poly.coefficients[1]!=-0.5||
        poly.coefficients[2]!=0.||poly.coefficients[3]!=140.){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_sread_text_test_2(void){
    char str[]="0 1 5 #@& 2";
    dpoly poly;
    if(dpoly_sread_text(&poly, str)!=3){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.size!=3){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0||poly.coefficients[1]!=1||
        poly.coefficients[2]!=5){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_sread_text_test_3(void){
    char str[]="";
    dpoly poly;
    if(dpoly_sread_text(&poly, str)!=0){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.size!=1){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_fread_text_test_1(void){
    FILE* f = fopen("test.txt", "w");
    fprintf(f, "3 -0.5 0 1.4e2\n");
    fclose(f);
    f = fopen("test.txt", "r");

    dpoly poly;
    if(dpoly_fread_text(&poly, f)!=4){
        dpoly_destroy(&poly);
        fclose(f);
        return 1;
    }
    fclose(f);

    if(poly.size!=4){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=3.||poly.coefficients[1]!=-0.5||
        poly.coefficients[2]!=0.||poly.coefficients[3]!=140.){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_fread_text_test_2(void){
    FILE *f = fopen("test.txt", "w");
    fprintf(f, "0 1 5 #@& 2\n");
    fclose(f);
    f = fopen("test.txt", "r");

    dpoly poly;
    if(dpoly_fread_text(&poly, f)!=3){
        dpoly_destroy(&poly);
        fclose(f);
        return 1;
    }
    fclose(f);

    if(poly.size!=3){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0||poly.coefficients[1]!=1||
        poly.coefficients[2]!=5){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_fread_text_test_3(void){
    FILE* f = fopen("test.txt", "w");
    fclose(f);
    f = fopen("test.txt", "r");

    dpoly poly;
    if(dpoly_fread_text(&poly, f)!=0){
        dpoly_destroy(&poly);
        fclose(f);
        return 1;
    }
    fclose(f);

    if(poly.size!=1){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_fread_binary_test_1(void){
    FILE* f = fopen("test.dat", "wb");
    int k=4;
    fwrite(&k, sizeof k, 1, f);
    dtype c[]={3,-0.5,0,1.4e2};
    fwrite(&c, sizeof(dtype), 4, f);
    fclose(f);
    f = fopen("test.dat", "rb");

    dpoly poly;
    if(dpoly_fread_binary(&poly, f)!=4){
        dpoly_destroy(&poly);
        fclose(f);
        return 1;
    }
    fclose(f);

    if(poly.size!=4){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=3.||poly.coefficients[1]!=-0.5||
        poly.coefficients[2]!=0.||poly.coefficients[3]!=140.){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_fread_binary_test_2(void){
    FILE* f = fopen("test.dat", "wb");
    int k=1;
    fwrite(&k, sizeof k, 1, f);
    dtype c[]={0};
    fwrite(&c, sizeof(dtype), 1, f);
    fclose(f);
    f = fopen("test.dat", "rb");

    dpoly poly;
    if(dpoly_fread_binary(&poly, f)!=1){
        dpoly_destroy(&poly);
        return 1;
    }
    fclose(f);

    if(poly.size!=1){
        dpoly_destroy(&poly);
        return 1;
    }
    if(poly.coefficients[0]!=0){
        dpoly_destroy(&poly);
        return 1;
    }
    dpoly_destroy(&poly);
    return 0;
}

int dpoly_sprint_test(void){
    dpoly poly;
    char str[]="2 6 1 -0.4 5";
    dpoly_sread_text(&poly,str);

    char* p=dpoly_sprint(&poly);
   /* printf("%s/n",p);*/
    int res=(strcmp(p,"2 + 6 x + x^2 - 0.4 x^3 + 5 x^4")!=0);
    dpoly_destroy(&poly);
    free(p);
    return res;
}

int dpoly_fprint_test(void){
    dpoly poly;
    char str[]="2 6 1 -0.4 5";
    dpoly_sread_text(&poly,str);

    FILE* f = fopen("test.txt", "w");

    dpoly_fprint(&poly, f);
    fclose(f);
    f = fopen("test.txt", "r");
    char buff[64];
    fgets(buff, 64 , f);
   /* printf("%s/n",buff);*/
    fclose(f);
    dpoly_destroy(&poly);
    return (strcmp(buff,"2 + 6 x + x^2 - 0.4 x^3 + 5 x^4\n")!=0);
}

int dpoly_swrite_text_test(void){
    dpoly poly;
    char str[]="2 6 1 -0.4 5";
    dpoly_sread_text(&poly,str);

    char* p=dpoly_swrite_text(&poly);

    int res=(strcmp(p,"2 6 1 -0.4 5")!=0);
    dpoly_destroy(&poly);
    free(p);
    return res;
}

int dpoly_fwrite_text_test(void){
    dpoly poly;
    char str[]="2 6 1 -0.4 5";
    dpoly_sread_text(&poly,str);

    FILE* f = fopen("test.txt", "w");

    dpoly_fwrite_text(&poly, f);
    fclose(f);
    f = fopen("test.txt", "r");
    char buff[255];
    fgets(buff, 255 , f);

    fclose(f);
    int res=(strcmp(buff,"2 6 1 -0.4 5\n")!=0);
    dpoly_destroy(&poly);
    return res;
}


int dpoly_fwrite_binary_test(void){
    dpoly poly;
    char str[]="2 6 1 -0.4 5";
    dpoly_sread_text(&poly,str);

    FILE* f = fopen("test.dat", "wt");

    dpoly_fwrite_binary(&poly, f);
    fclose(f);
    f = fopen("test.dat", "rb");
    int res = 1;

    int sz;
    fread(&sz, sizeof sz, 1, f);
    res = res && (sz == 5);
    dtype cf[5];
    dtype cfc[5] = {2, 6, 1, -0.4, 5};
    fread(cf, sizeof(dtype), 5, f);
    fclose(f);

    res = res && (memcmp(cf, cfc, sizeof(dtype) * 5) == 0);
    dpoly_destroy(&poly);
    return !res;
}


int dpoly_value_at_test(void){
    dpoly poly;
    char str[]="2 6 -0.5 3";
    dpoly_sread_text(&poly,str);

    int res = dpoly_value_at(&poly, -2.) != -36.;
    dpoly_destroy(&poly);
    return res;
}

int dpoly_add_assign_test(void){
    dpoly poly1, poly2;
    dpoly_sread_text(&poly1, "2 6 -0.5 3");
    dpoly_sread_text(&poly2, "1 -4");

    dpoly_add_assign(&poly1, &poly2);

    char* val = dpoly_swrite_text(&poly1);
    int res = strcmp(val, "3 2 -0.5 3") != 0;
    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    free(val);

    return res;
}


int dpoly_add_test(void){
    dpoly poly1, poly2, poly3;
    dpoly_sread_text(&poly1, "2 6 -0.5 3");
    dpoly_sread_text(&poly2, "1 -4 5");

    dpoly_add(&poly1, &poly2, &poly3);

    char* val = dpoly_swrite_text(&poly3);
    int res = strcmp(val, "3 2 4.5 3") != 0;
    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    free(val);

    return res;
}

int dpoly_mul_assign_test(void){
    dpoly poly1, poly2;
    dpoly_sinput(&poly1, "2 + 3x - 0.5 x^2 + 4 x^3");
    dpoly_sinput(&poly2, "1 - 4x + 2 x^2 - 3.5 x^3");

    dpoly_mul_assign(&poly1, &poly2);

    char* val = dpoly_sprint(&poly1);
    int res = strcmp(val, "2 - 5 x - 8.5 x^2 + 5 x^3 - 27.5 x^4 + 9.75 x^5 - 14 x^6") != 0;
    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    free(val);

    return res;
}

int dpoly_mul_test(void){
    dpoly poly1, poly2, poly3;

    dpoly_sinput(&poly1, "2 + 0.5 x + 9 x^2 - 15 x^3 + 0.1 x^4");
    dpoly_sinput(&poly2, "22 + 0.2 x - 31 x^2 - x^3 - 3 x^4");

    dpoly_mul(&poly1, &poly2, &poly3);

    char* val = dpoly_sprint(&poly3);
    int res = strcmp(val, "44 + 11.4 x + 136.1 x^2 - 345.7 x^3 - 286.3 x^4 + 454.52 x^5 - 15.1 x^6 + 44.9 x^7 - 0.3 x^8") != 0;
    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    free(val);

    return res;
}

int dpoly_div_test(void){
    dpoly poly1, poly2, poly3;

    dpoly_sinput(&poly1, "3.6 x^6 + 167.79 x^5 - 18.5 x^4 - 20.41 x^3 + 200 x^2 - 11 x - 14");
    dpoly_sinput(&poly2, "-17 + x + 0.7 x^2 - 12 x^3");

    dpoly_div(&poly1, &poly2, &poly3);

    char* val = dpoly_sprint(&poly3);
    int res = strcmp(val, "1 + 0.7 x - 14 x^2 - 0.3 x^3") != 0;
    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    free(val);

    return res;
}

int dpoly_mod_test(void){
    dpoly poly1, poly2, poly3;

    dpoly_sinput(&poly1, "3.6 x^6 + 167.79 x^5 - 18.5 x^4 - 20.41 x^3 + 200 x^2 - 11 x - 14");
    dpoly_sinput(&poly2, "-17 + x + 0.7 x^2 - 12 x^3");

    dpoly_mod(&poly1, &poly2, &poly3);

    char* val = dpoly_sprint(&poly3);
    int res = strcmp(val, "3 - 0.1 x - 39.4 x^2") != 0;
    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    free(val);

    return res;
}

int dpoly_div_assign_test(void){
    dpoly poly1, poly2;
    dpoly_sinput(&poly1, "3.6 x^6 + 167.79 x^5 - 18.5 x^4 - 20.41 x^3 + 200 x^2 - 11 x - 14");
    dpoly_sinput(&poly2, "-17 + x + 0.7 x^2 - 12 x^3");

    dpoly_div_assign(&poly1, &poly2);

    char* val = dpoly_sprint(&poly1);
    int res = strcmp(val, "1 + 0.7 x - 14 x^2 - 0.3 x^3") != 0;
    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    free(val);

    return res;
}

int dpoly_mod_assign_test(void){
    dpoly poly1, poly2;
    dpoly_sinput(&poly1, "3.6 x^6 + 167.79 x^5 - 18.5 x^4 - 20.41 x^3 + 200 x^2 - 11 x - 14");
    dpoly_sinput(&poly2, "-17 + x + 0.7 x^2 - 12 x^3");

    dpoly_mod_assign(&poly1, &poly2);

    char* val = dpoly_sprint(&poly1);
    int res = strcmp(val, "3 - 0.1 x - 39.4 x^2") != 0;
    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    free(val);

    return res;
}

int dpoly_divmod_test(void){
    dpoly poly1, poly2, poly3, poly4;
    dpoly_sinput(&poly1, "3.6 x^6 + 167.79 x^5 - 18.5 x^4 - 20.41 x^3 + 200 x^2 - 11 x - 14");
    dpoly_sinput(&poly2, "-17 + x + 0.7 x^2 - 12 x^3");

    dpoly_divmod(&poly1, &poly2, &poly3, &poly4);

    char* val = dpoly_sprint(&poly3);
    int res = strcmp(val, "1 + 0.7 x - 14 x^2 - 0.3 x^3") != 0;
    free(val);

    val = dpoly_sprint(&poly4);
    res = res || strcmp(val, "3 - 0.1 x - 39.4 x^2") != 0;
    free(val);

    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    dpoly_destroy(&poly4);
    return res;
}

int dpoly_modulo_add_test(void){
    dpoly poly1, poly2, poly3, poly4;
    dpoly_sinput(&poly1, "2 + 3x - 0.5 x^2 + 4 x^3");
    dpoly_sinput(&poly2, "1 - 4x + 2 x^2 - 3.5 x^3");
    dpoly_sinput(&poly3, "1 + x + x^2");

    dpoly_modulo_add(&poly1, &poly2, &poly3, &poly4);

    char* val = dpoly_sprint(&poly4);
    int res = strcmp(val, "2 - 2.5 x") != 0;
    free(val);

    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    dpoly_destroy(&poly4);
    return res;
}

int dpoly_modulo_add_assign_test(void){
    dpoly poly1, poly2, poly3;
    dpoly_sinput(&poly1, "2 + 3x - 0.5 x^2 + 4 x^3");
    dpoly_sinput(&poly2, "1 - 4x + 2 x^2 - 3.5 x^3");
    dpoly_sinput(&poly3, "1 + x + x^2");

    dpoly_modulo_add_assign(&poly1, &poly2, &poly3);

    char* val = dpoly_sprint(&poly1);
    int res = strcmp(val, "2 - 2.5 x") != 0;
    free(val);

    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    return res;
}

int dpoly_modulo_mul_test(void){
    dpoly poly1, poly2, poly3, poly4;
    dpoly_sinput(&poly1, "2 + 3x - 0.5 x^2 + 4 x^3");
    dpoly_sinput(&poly2, "1 - 4x + 2 x^2 - 3.5 x^3");
    dpoly_sinput(&poly3, "1 + x + x^2");

    dpoly_modulo_mul(&poly1, &poly2, &poly3, &poly4);

    char* val = dpoly_sprint(&poly4);
    int res = strcmp(val, "-8.25 - 33.75 x") != 0;
    free(val);

    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    dpoly_destroy(&poly4);
    return res;
}

int dpoly_modulo_mul_assign_test(void){
    dpoly poly1, poly2, poly3;
    dpoly_sinput(&poly1, "2 + 3x - 0.5 x^2 + 4 x^3");
    dpoly_sinput(&poly2, "1 - 4x + 2 x^2 - 3.5 x^3");
    dpoly_sinput(&poly3, "1 + x + x^2");

    dpoly_modulo_mul_assign(&poly1, &poly2, &poly3);

    char* val = dpoly_sprint(&poly1);
    int res = strcmp(val, "-8.25 - 33.75 x") != 0;
    free(val);

    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);
    return res;
}


int dpoly_derivative_test(void){
    dpoly poly1, poly2;
    dpoly_sinput(&poly1, "2 + 3 x - 0.5 x^2 + 4 x^3");

    dpoly_derivative(&poly1, &poly2);

    char* val = dpoly_sprint(&poly2);
    int res = strcmp(val, "3 - x + 12 x^2") != 0;
    free(val);

    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    return res;
}

int dpoly_derivative_at_test(void){
    dpoly poly1;
    dpoly_sinput(&poly1, "2 + 3 x - 0.5 x^2 + 4 x^3");

    dtype val = dpoly_derivative_at(&poly1, -3);

    dpoly_destroy(&poly1);
    return val != 114.;
}


int dpoly_indefinite_integral_test(void){
    dpoly poly1, poly2;
    dpoly_sinput(&poly1, "1 + 3 x - 1.5 x^2 + 4 x^3");

    dpoly_indefinite_integral(&poly1, &poly2);

    char* val = dpoly_sprint(&poly2);
    int res = strcmp(val, "x + 1.5 x^2 - 0.5 x^3 + x^4") != 0;
    free(val);

    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    return res;
}

int dpoly_definite_integral_test(void){
    dpoly poly1;
    dpoly_sinput(&poly1, "1 + 3 x - 1.5 x^2 + 4 x^3");

    dtype val = dpoly_definite_integral(&poly1, -3, 4);

    dpoly_destroy(&poly1);
    return val != 147.;
}

int do_test(int(*f)(void),const char* descr){
    int res=(*f)();
    printf("%-40s", descr);
    if(res==0) printf("%s \n", "passed");
    else printf("%s \n", "failed");
    return res;
}

void input_flush(void) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int state=0;
    state+=do_test(&dpoly_zero_test,        "test 1 -- zero_test : ");
    state+=do_test(&dpoly_generate_test,    "test 2 -- generate_test : ");
    state+=do_test(&dpoly_destroy_test,     "test 3 -- destroy_test : ");
    state+=do_test(&dpoly_copy_test,        "test 4 -- copy_test : ");

    state+=do_test(&dpoly_sinput_test_1,    "test 5 -- sinput_test_1 : ");
    state+=do_test(&dpoly_sinput_test_2,    "test 6 -- sinput_test_2 : ");
    state+=do_test(&dpoly_sinput_test_3,    "test 7 -- sinput_test_3 : ");

    state+=do_test(&dpoly_finput_test_1,    "test 8 -- finput_test_1 : ");
    state+=do_test(&dpoly_finput_test_2,    "test 9 -- finput_test_2 : ");
    state+=do_test(&dpoly_finput_test_3,    "test 10 -- finput_test_3 : ");

    state+=do_test(&dpoly_sread_text_test_1,    "test 11 -- sread_text_test_1 : ");
    state+=do_test(&dpoly_sread_text_test_2,    "test 12 -- sread_text_test_2 : ");
    state+=do_test(&dpoly_sread_text_test_3,    "test 13 -- sread_text_test_3 : ");

    state+=do_test(&dpoly_fread_text_test_1,    "test 14 -- fread_text_test_1 : ");
    state+=do_test(&dpoly_fread_text_test_2,    "test 15 -- fread_text_test_2 : ");
    state+=do_test(&dpoly_fread_text_test_3,    "test 16 -- fread_text_test_3 : ");

    state+=do_test(&dpoly_fread_binary_test_1,  "test 17 -- fread_binary_test_1 : ");
    state+=do_test(&dpoly_fread_binary_test_2,  "test 18 -- fread_binary_test_2 : ");

    state+=do_test(&dpoly_sprint_test,          "test 19 -- sprint_test : ");
    state+=do_test(&dpoly_fprint_test,          "test 20 -- fprint_test : ");
    state+=do_test(&dpoly_swrite_text_test,     "test 21 -- swrite_text_test : ");

    state+=do_test(&dpoly_fwrite_text_test,     "test 22 -- fwrite_text_test : ");

    state+=do_test(&dpoly_fwrite_binary_test,   "test 23 -- fwrite_binary_test : ");

    state+=do_test(&dpoly_value_at_test,        "test 24 -- value_at_test : ");

    state+=do_test(&dpoly_add_assign_test,      "test 25 -- add_assign_test : ");
    state+=do_test(&dpoly_add_test,             "test 26 -- add_test : ");

    state+=do_test(&dpoly_mul_assign_test,      "test 27 -- mul_assign_test : ");
    state+=do_test(&dpoly_mul_test,             "test 28 -- mul_test : ");

    state+=do_test(&dpoly_div_test,             "test 29 -- div_test : ");
    state+=do_test(&dpoly_mod_test,             "test 30 -- mod_test : ");

    state+=do_test(&dpoly_div_assign_test,      "test 31 -- div_assign_test : ");
    state+=do_test(&dpoly_mod_assign_test,      "test 32 -- mod_assign_test : ");
    state+=do_test(&dpoly_divmod_test,          "test 33 -- divmod_test : ");

    state+=do_test(&dpoly_modulo_add_test,          "test 34 -- modulo_add_test : ");
    state+=do_test(&dpoly_modulo_add_assign_test,   "test 35 -- modulo_add_assign_test : ");
    state+=do_test(&dpoly_modulo_mul_test,          "test 36 -- modulo_mul_test : ");
    state+=do_test(&dpoly_modulo_mul_assign_test,   "test 37 -- modulo_mul_assign_test : ");

    state+=do_test(&dpoly_derivative_test,          "test 38 -- derivative_test : ");
    state+=do_test(&dpoly_derivative_at_test,       "test 39 -- derivative_at_test : ");

    state+=do_test(&dpoly_indefinite_integral_test,     "test 40 -- indefinite_integral_test : ");
    state+=do_test(&dpoly_definite_integral_test,       "test 41 -- definite_integral_test : ");

    if(state==0) printf("%s \n", "All tests passed.");
    else printf("%d tests failed. \n",state );

    int method = 0;

    do {
        printf("Select the input method for the demonstration: 1 - terminal, 2 - file\n");
        scanf("%d", &method);
        input_flush();
    } while(method != 1 && method != 2);

    dpoly poly1, poly2, poly3;
    dtype x0, x1;

    if (method == 1) {
        int cnt = 1;
        do {
            printf("Enter the first polynomial (A)\n");
            dpoly_input(&poly1);
            printf("The polynomial read is:\n");
            dpoly_print(&poly1);
            printf("Enter 0 to confirm, 1 to retry entering the polynomial:\n");
            scanf("%d", &cnt);
            input_flush();
            if (cnt) {
                dpoly_destroy(&poly1);
            }
        } while (cnt);
        cnt = 1;
        do {
            printf("Enter the second polynomial (B)\n");
            dpoly_input(&poly2);
            printf("The polynomial read is:\n");
            dpoly_print(&poly2);
            printf("Enter 0 to confirm, 1 to retry entering the polynomial:\n");
            scanf("%d", &cnt);
            input_flush();
            if (cnt) {
                dpoly_destroy(&poly2);
            }
        } while (cnt);

        cnt = 1;
        do {
            printf("Enter the modulus polynomial (M)\n");
            dpoly_input(&poly3);
            printf("The polynomial read is:\n");
            dpoly_print(&poly3);
            printf("Enter 0 to confirm, 1 to retry entering the polynomial:\n");
            scanf("%d", &cnt);
            input_flush();
            if (cnt) {
                dpoly_destroy(&poly3);
            }
        } while (cnt);

        printf("Enter two points (xo x1)\n");
        scanf("%lf%lf", &x0, &x1);
        input_flush();
    } else {
        char fname[255];
        FILE* f = 0;

        do {
            printf("Enter the filename with three polynomials (A, B, M)\n");
            printf("and two points (x0, x1)\n");

            fgets(fname, 255, stdin);

            int n = strlen(fname) - 1;
            while (n >= 0 && isspace(fname[n])) {
                fname[n] = 0;
                --n;
            }

            f = fopen(fname, "r");
            if (!f) {
                printf("Could not open the file\n");
            }
        } while (!f);

        dpoly_finput(&poly1, f);
        dpoly_finput(&poly2, f);
        dpoly_finput(&poly3, f);
        fscanf(f, "%lf%lf", &x0, &x1);
        fclose(f);
    }

    char fname[255];
    FILE* f = 0;

    do {
        printf("Enter the filename for the output\n");

        fgets(fname, 255, stdin);

        int n = strlen(fname) - 1;
        while (n >= 0 && isspace(fname[n])) {
            fname[n] = 0;
            --n;
        }

        f = fopen(fname, "w");
        if (!f) {
            printf("Could not open the file\n");
        }
    } while (!f);

    printf("A(x0) = %f\n", dpoly_value_at(&poly1, x0));
    fprintf(f, "A(x0) = %f\n", dpoly_value_at(&poly1, x0));

    dpoly poly_res;
    dpoly_add(&poly1, &poly2, &poly_res);
    printf("A + B = ");
    dpoly_print(&poly_res);
    fprintf(f, "A + B = ");
    dpoly_fprint(&poly_res, f);
    dpoly_destroy(&poly_res);

    dpoly_mul(&poly1, &poly2, &poly_res);
    printf("A * B = ");
    dpoly_print(&poly_res);
    fprintf(f, "A * B = ");
    dpoly_fprint(&poly_res, f);
    dpoly_destroy(&poly_res);

    dpoly poly_mod;
    dpoly_divmod(&poly1, &poly2, &poly_res, &poly_mod);
    printf("A / B = ");
    dpoly_print(&poly_res);
    fprintf(f, "A / B = ");
    dpoly_fprint(&poly_res, f);
    dpoly_destroy(&poly_res);

    printf("A %% B = ");
    dpoly_print(&poly_mod);
    fprintf(f, "A %% B = ");
    dpoly_fprint(&poly_mod, f);
    dpoly_destroy(&poly_mod);

    dpoly_modulo_add(&poly1, &poly2, &poly3, &poly_res);
    printf("(A + B) %% M = ");
    dpoly_print(&poly_res);
    fprintf(f, "(A + B) %% M = ");
    dpoly_fprint(&poly_res, f);
    dpoly_destroy(&poly_res);

    dpoly_modulo_mul(&poly1, &poly2, &poly3, &poly_res);
    printf("(A * B) %% M = ");
    dpoly_print(&poly_res);
    fprintf(f, "(A * B) %% M = ");
    dpoly_fprint(&poly_res, f);
    dpoly_destroy(&poly_res);

    dpoly_derivative(&poly1, &poly_res);
    printf("A' = ");
    dpoly_print(&poly_res);
    fprintf(f, "A' = ");
    dpoly_fprint(&poly_res, f);
    dpoly_destroy(&poly_res);

    printf("A'(x0) = %f\n", dpoly_derivative_at(&poly1, x0));
    fprintf(f, "A'(x0) = %f\n", dpoly_derivative_at(&poly1, x0));

    dpoly_indefinite_integral(&poly1, &poly_res);
    printf("\\int A dx= ");
    dpoly_print(&poly_res);
    fprintf(f, "\\int A dx = ");
    dpoly_fprint(&poly_res, f);
    dpoly_destroy(&poly_res);

    printf("\\int_x0^x1 A dx = %f\n", dpoly_definite_integral(&poly1, x0, x1));
    fprintf(f, "\\int_x0^x1 A dx = %f\n", dpoly_definite_integral(&poly1, x0, x1));

    fclose(f);

    dpoly_destroy(&poly1);
    dpoly_destroy(&poly2);
    dpoly_destroy(&poly3);

    return 0;
}
