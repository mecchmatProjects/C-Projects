#include "../headers/interpolation_tyshchenko.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Welcome to my Interpolation Project\n");

    printf("Please choose input type: \n"); 
    printf("c/t - console/text file \n");

    character work_type;
    scanf("%c",&work_type);
    IType wrong_input_flag =    work_type == 'c'
                                | work_type == 't';
    while (wrong_input_flag==0) {
        printf("Please choose correct input type: \n");
        printf("c/t - console/text file \n");
        scanf("%c",&work_type);
        wrong_input_flag = work_type == 'c'
                           | work_type == 't';
    }

    struct DVector x,y;
    struct Input_Data inputData = {0, &x, &y};
    struct DVector ans_linear;
    // struct DVector ans_cubic;
    character *filename = (character *) malloc(100 * sizeof(character));

    if        (work_type == 'c') {
        if (!input(&inputData)) { // exit code == 0 => it's ok
            ans_linear = Calculate  (&inputData);
            // ans_cubic  = Interpolate(&inputData);
        } else {
            return 1;
        }
    } else if (work_type == 't') {
        printf("Please write a filename Interpolation_Tyshchenko_C/tests/inp.txt:\n");
        scanf("%s", filename);
        if (!inputTextFile(filename, &inputData)) { // exit code == 0 => it's ok
            ans_linear = Calculate  (&inputData);
            // ans_cubic  = Interpolate(&inputData);
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
        scanf("%c",&work_type);
        wrong_input_flag = work_type == 'c'| work_type == 't'| work_type == 'b';
    }

    if        (work_type == 'c') {
        output(&ans_linear);
        // output(&ans_cubic);
    } else if (work_type == 'b') {
        printf("Please write a filename Interpolation_Tyshchenko_C/tests/out.txt:\n");
        scanf("%s", filename);
        outputBinaryFile(filename, &ans_linear);
        // outputBinaryFile(filename, &ans_cubic);
    } else if (work_type == 't') {
        printf("Please write a filename:\n");
        scanf("%s", filename);
        outputTextFile(filename, &ans_linear);
        // outputTextFile(filename, &ans_cubic);
    }

    printf("Thanks for your attention. \n");

    free(inputData.x->coordinates);
    free(inputData.y->coordinates);

    free(ans_linear.coordinates);
    // free(ans_cubic.coordinates);

    free(filename);

    return 0;
}
//gcc c_project_interpolation/tests/test_interpolation.c c_project_interpolation/src/interpolation.c -o cproject
