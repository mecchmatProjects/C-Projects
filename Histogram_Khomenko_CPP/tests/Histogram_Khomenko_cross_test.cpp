//#include "../src/Histogram.cpp"
#include "../headers/another_funcs.h"
#include "../headers/input_funcs.h"
#include "../headers/Histogram.h"

using namespace std;

Histrogram H;

IType Histogram_properties_cross_test()
{
    printf("your Histogram:\n");
    H.output_Histogram(0, 4, 3);
    printf("\nnumber of elements in Histogram: %d\n\n", H.num());
    printf("input column's index of Histogram from 0 to %d:\n", H.M - 1);
    NType column_idx = atoi(input_str());
    printf("frequency of column with index %d: %d\n\n", column_idx, H.numHist(column_idx));
    printf("mean value of all numbers in Histogram: %.3f\n\n", H.mean());
    printf("root mean square value of all numbers in Histogram: %.3f\n\n", H.dispersion());
    printf("median of all numbers in Histogram: %.3f\n\n", H.median());
    printf("mean deviation of all numbers in Histogram: %.3f\n\n", H.dev());
    printf("standard deviation of all numbers in Histogram: %.3f\n\n", H.dev_squared());
    printf("central empirical moment of order 3 of all numbers in Histogram: %.3f\n\n", H.centr_empiric_moment3());
    printf("central empirical moment of order 4 of all numbers in Histogram: %.3f\n\n", H.centr_empiric_moment4());
    printf("asymmetry coefficient of all numbers in Histogram: %.3f\n\n", H.asymmetry());
    printf("access coefficient of all numbers in Histogram: %.3f\n\n", H.access());
    printf("variance coefficient of all numbers in Histogram: %.3f\n\n", H.variance());
    return 0;
}

IType Histrogram_cross_test()
{
    FILE* fc = fopen("../../Histogram_Khomenko_C/tests/Histogram_compare_cross_test.txt", "r");
    FILE* fcpp = fopen("Histogram_compare_cross_test.txt", "r");
    if (!fc){
        cout << "file '../../Histogram_Khomenko_C/tests/Histogram_compare_cross_test.txt' is not exist" << endl;
        fclose(fc);
        return -1;
    }
    if (!fcpp){
        cout << "file 'Histogram_compare_cross_test.txt' is not exist" << endl;
        fclose(fcpp);
        return -1;
    }
    char* buffer_c = (char*)malloc(0);
    char* buffer_cpp = (char*)malloc(0);
    char* funcs_name  = (char*)malloc(0);
    NType buffer_c_len = 0, buffer_cpp_len = 0, funcs_name_len = 0;
    char c_c, c_cpp;
    //bool is_difference = false;
    while (true)
    {
        c_c = fgetc(fc);
        c_cpp = fgetc(fcpp);
        if (feof(fc) || feof(fcpp)){
            //printf("end_symb='%c'", c_cpp);
            break;
        }
        buffer_c_len++;
        buffer_c = (char*)realloc(buffer_c, buffer_c_len * sizeof(char));
        buffer_c[buffer_c_len - 1] = c_c;


        buffer_cpp_len++;
        buffer_cpp = (char*)realloc(buffer_cpp, buffer_cpp_len * sizeof(char));
        buffer_cpp[buffer_cpp_len - 1] = c_cpp;

        //printf("'%c' - '%c'\n", buffer_c[buffer_c_len - 1], buffer_cpp[buffer_cpp_len - 1]);
        //printf("input point, c_c='%c', c_cpp='%c'\n", c_c, c_cpp);

        if ((c_c == '#') || (c_cpp == '#')){
            //printf("if point, c_c='%c', c_cpp='%c'\n", c_c, c_cpp);
            if (c_c != '#'){
                //is_difference = true;
                while (true){
                    c_c = fgetc(fc);
                    if (c_c == '#' || feof(fc)){
                        break;
                    }
                }
            }
            else if (c_cpp != '#'){
                //is_difference = true;
                while (true){
                    c_cpp = fgetc(fcpp);
                    if (c_cpp == '#' || feof(fcpp)){
                        break;
                    }
                }
            }
            //printf("first point elems: '%c' - '%c'\n", c_c, c_cpp);
            buffer_c_len++;
            buffer_c = (char*)realloc(buffer_c, buffer_c_len * sizeof(char));
            buffer_c[buffer_c_len - 1] = '\0';

            
            buffer_cpp_len++;
            buffer_cpp = (char*)realloc(buffer_cpp, buffer_cpp_len * sizeof(char));
            buffer_cpp[buffer_cpp_len - 1] = '\0';

            

            while(true){
                c_c = fgetc(fc);
                c_cpp = fgetc(fcpp);
                //printf("pre second symbs: '%c' - '%c'\n", c_c, c_cpp);
                if (c_c == '\n'){
                    funcs_name_len++;
                    funcs_name = (char*)realloc(funcs_name, sizeof(char) * funcs_name_len);
                    funcs_name[funcs_name_len - 1] = '\0';    
                    break;
                }
                funcs_name_len++;
                funcs_name = (char*)realloc(funcs_name, sizeof(char) * funcs_name_len);
                funcs_name[funcs_name_len - 1] = c_c;
            }

            //printf("second point elems: '%c' - '%c'\n", c_c, c_cpp);
            cout << endl;
            if (equal_strs(buffer_c, buffer_cpp)){// && !is_difference
                cout << funcs_name << " functions have same results in C and Cpp projects, result = \n"<< buffer_c << endl;
            }
            else{
                //is_difference = false;
                cout << funcs_name << " functions don't have same results in C and Cpp projects" << endl;
                printf("end point s1-'%s'\ns2-'%s'\n", buffer_c, buffer_cpp);
            }
            funcs_name_len = 0;
            funcs_name = (char*)realloc(funcs_name, 0);

            buffer_c = (char*)realloc(buffer_c, 0);
            buffer_c_len = 0;
            buffer_cpp = (char*)realloc(buffer_cpp, 0);
            buffer_cpp_len = 0;

        }
    }
    fclose(fc);
    fclose(fcpp);
    free(buffer_c);
    free(buffer_cpp);
    free(funcs_name);
    return 0;
}

int main()
{
    cout << "CPP/C_Histogram cross_tests" << endl;
    Histrogram_cross_test();
    cout << "\ninput anything to exit...";
    getc(stdin);
    /*FILE* fc = fopen("../../Histogram_Khomenko_C/tests/Histogram_compare_cross_test.txt", "r");
    FILE* fcpp = fopen("Histogram_compare_cross_test.txt", "r");
    while (true){
        if (feof(fcpp) || feof(fc))
            break;
        printf("char - '%c', '%c'\n", fgetc(fcpp), fgetc(fc));
    }
    fclose(fcpp);
    fclose(fc);*/
    return 0;
}