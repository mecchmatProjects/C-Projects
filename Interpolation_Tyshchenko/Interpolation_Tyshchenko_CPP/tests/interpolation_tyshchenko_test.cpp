

#include<iostream>
#include "../headers/interpolation_tyshchenko.h"
//g++ c++_project_interpolation/tests/test_interpolation.cpp c++_project_interpolation/src/interpolation.cpp -o test
int main(){
    printf("Welcome to my Interpolation Project\n");

    printf("Please choose input type: \n"); 
    printf("c/t - console/text file \n");

    character work_type;
    scanf(" %c",&work_type);
    IType wrong_input_flag = work_type == 'c' | work_type == 't';
    while (wrong_input_flag==0) {
        printf("Please choose correct input type: \n");
        printf("c/t - console/text file \n");
        scanf(" %c",&work_type);
        wrong_input_flag = work_type == 'c' | work_type == 't';
    }


    Project interpolation;

    character *filename = (character *) malloc(100 * sizeof(character));

    if(work_type == 'c') {
        if (!interpolation.input()) { // exit code == 0 => it's ok
            interpolation.ans_linear = interpolation.Calculate  ();
//            interpolation.ans_cubic  = Interpolate(&inputData);
        } else {
            return 1;
        }
    } else if (work_type == 't') {
        printf("Please write a filename Interpolation_Tyshchenko_CPP/tests/inp.txt:\n");
        scanf(" %s", filename);
        if (!interpolation.inputTextFile(filename)) { // exit code == 0 => it's ok
            interpolation.ans_linear = interpolation.Calculate();
//            interpolation.ans_cubic  = interpolation.Interpolate(&inputData);
        } else {
            return 1;
        }
    }

    printf("Please choose output type: \n");
    printf("c/t/b - console/binary file/text file \n");
    scanf(" %c",&work_type);
    wrong_input_flag = work_type == 'c' || work_type == 't' || work_type == 'b';
    while (wrong_input_flag == 0) {
        printf("Please choose correct output type: \n");
        printf("c/b/t - console/binary file/text file \n");
        scanf(" %c",&work_type);
        wrong_input_flag = work_type == 'c' | work_type == 't' | work_type == 'b';
    }

    if(work_type == 'c') {
        interpolation.output(&interpolation.ans_linear);
//        interpolation.output(&interpolation.ans_cubic);
    } else if(work_type == 'b') {
        printf("Please write a filename Interpolation_Tyshchenko_CPP/tests/out.txt:\n");
        scanf("%s", filename);
        interpolation.outputBinaryFile(filename, &interpolation.ans_linear);
//        interpolation.outputBinaryFile(filename, &interpolation.ans_cubic);
    } else if(work_type == 't') {
        printf("Please write a filename:\n");
        scanf("%s", filename);
        interpolation.outputTextFile(filename, &interpolation.ans_linear);
//        interpolation.outputTextFile(filename, &interpolation.ans_cubic);
    }

    printf("Thanks for your attention. \n");

    free(interpolation.inputData.x->coordinates);
    free(interpolation.inputData.y->coordinates);

    free(interpolation.ans_linear.coordinates);
//    free(interpolation.ans_cubic.coordinates);

    free(filename);

    return 0;
}
//gcc Interpolation_Tyshchenko_C/tests/interpolation_tyshchenko_test.c Interpolation_Tyshchenko_C/src/interpolation_tyshchenko.c -o cproject && g++ Interpolation_Tyshchenko_CPP/tests/interpolation_tyshchenko_test.cpp Interpolation_Tyshchenko_CPP/src/interpolation_tyshchenko.cpp -o cppproject