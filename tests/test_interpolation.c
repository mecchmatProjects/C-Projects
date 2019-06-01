//
// Created by olga on 10.05.19.
//
// Olga Moskanova
// statistics, 2 year
//
// olyushkam@gmail.com
// https://github.com/gamble27
//
// this project can also be found here:
// https://github.com/gamble27/c_interpolation
//

#include "interpolation.h"
#include <stdio.h>
#include <malloc.h>

int main(){
    printf("Welcome to my Interpolation Project\n");

//======================= INPUT TYPE =========================

    printf("Please choose input type: \n");
    printf("c/t - console/text file \n");

    character work_type;
    scanf("%c",&work_type);
    integer wrong_input_flag =    work_type == 'c'
                                | work_type == 't';
    while (wrong_input_flag==0) {
        printf("Please choose correct input type: \n");
        printf("c/t - console/text file \n");
        scanf("%c",&work_type);
        wrong_input_flag = work_type == 'c'
                           | work_type == 't';
    }

//============= INPUT FUNCTIONS + CALCULATE CALL =============

    struct DVector x,y;
    struct Input_Data inputData = {0, &x, &y};
    struct DVector ans_linear;
//    struct DVector ans_cubic;
    character *filename = (character *) malloc(100 * sizeof(character));

    if        (work_type == 'c') {
        if (!input(&inputData)) { // exit code == 0 => it's ok
            ans_linear = Calculate  (&inputData);
//            ans_cubic  = Interpolate(&inputData);
        } else {
            return 1;
        }
    } else if (work_type == 't') {
        printf("Please write a filename:\n");
        scanf("%s", filename);
        if (!inputTextFile(filename, &inputData)) { // exit code == 0 => it's ok
            ans_linear = Calculate  (&inputData);
//            ans_cubic  = Interpolate(&inputData);
        } else {
            return 1;
        }
    }

//===================== OUTPUT TYPE ======================

    printf("Please choose output type: \n");
    printf("c/t/b - console/binary file/text file \n");

    scanf("%c",&work_type);
    wrong_input_flag = work_type == 'c'
                       | work_type == 't'
                       | work_type == 'b';
    //fixme twice printf
    while (wrong_input_flag==0) {
        printf("Please choose correct output type: \n");
        printf("c/b/t - console/binary file/text file \n");
        scanf("%c",&work_type);
        wrong_input_flag = work_type == 'c'
                           | work_type == 't'
                           | work_type == 'b';
    }

//===================== OUTPUT FUNCTIONS CALL ======================

    if        (work_type == 'c') {
        output(&ans_linear);
//        output(&ans_cubic);
    } else if (work_type == 'b') {
        printf("Please write a filename:\n");
        scanf("%s", filename);
        outputBinaryFile(filename, &ans_linear);
//        outputBinaryFile(filename, &ans_cubic);
    } else if (work_type == 't') {
        printf("Please write a filename:\n");
        scanf("%s", filename);
        outputTextFile(filename, &ans_linear);
//        outputTextFile(filename, &ans_cubic);
    }

    printf("Thanks for your attention. \n (c) Olga Moskanova, #0 coder (or no)");

    free(inputData.x->coordinates);
    free(inputData.y->coordinates);

    free(ans_linear.coordinates);
//    free(ans_cubic.coordinates);

    free(filename);

    return 0;
}