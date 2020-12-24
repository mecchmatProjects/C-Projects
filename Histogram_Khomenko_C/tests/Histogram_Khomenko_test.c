//#include "../src/Histogram.c"
//#include "../src/input_funcs.c"
#include "../headers/common.h"
#include "../headers/input_funcs.h"
#include "../headers/other_funcs.h"
#include "../headers/His_col.h"
#include "../headers/Histogram.h"

Histrogram H;

IType ioput_test()
{
    char* skip_c;
    printf("if you want to input Histogram from standart file(Histogram_input_test.txt) and skip other tests input '+' \notherwise input anything:\n");
    skip_c = input_str();
    if (skip_c[0] == '+'){
        inputTextFile_Historgam("Histogram_input_test.txt", &H, "new_Histogram");
        return 0;
    }
    printf("let's input our first Histogram using Console:\n");
    input_Histogram(&H, "new_Histogram");
    char check_symb = '+';
    IType style_idx, width, precision;
    while (check_symb == '+'){
        printf("choose type of numbers output for Histogram output: \ninput '1' to choose output numbers in scientific style;\ninput '0' to choose output numbers in basic double style\n");
        scanf("%d", &style_idx);
        printf("input minimal width of each number:\n");
        scanf("%d", &width);
        printf("input precision of each number:\n");
        scanf("%d", &precision);
        printf("Histogram that you inputed:\n");
        output_Histogram(H, style_idx, width, precision);
        printf("\nif you want to output your Histogram using another parameters input '+'\nif you want to go further input '-':\n");
        check_symb = getc(stdin);
        while (1){
            if (check_symb == '+' || check_symb == '-')
                break;
            check_symb = getc(stdin);
        }
    }
    printf("let's input our Histogram using '.txt' file \n(for example here is file with Histogram - 'Histogram_input_test.txt')\n");
    printf("input name of file that consists Histogram:\n");
    char* filename = input_str();
    IType out_token = inputTextFile_Historgam(filename, &H, "used_Histogram");
    while(out_token == -1){
        printf("\nyou input file that is not exist, input name of file again:\n");
        filename = input_str();
        out_token = inputTextFile_Historgam(filename, &H, "used_Histogram");
    }
    printf("Histogram that you inputed using '%s' file:\n", filename);
    output_Histogram(H, 0, 6 ,3);
    printf("\nlet's output Histogram using '.txt' file\ninput name of file that will be output_file for our Histogram:\n");
    filename = input_str();
    check_symb = '+';
    while (check_symb == '+'){
        printf("choose type of numbers output for Histogram output: \ninput '1' to choose output numbers in scientific style;\ninput '0' to choose output numbers in basic double style\n");
        scanf("%d", &style_idx);
        printf("input minimal width of each number:\n");
        scanf("%d", &width);
        printf("input precision of each number:\n");
        scanf("%d", &precision);
        printf("Histogram was inputed in file %s\n", filename);
        outputTextFile_Histogram(filename, H, style_idx, width, precision, "w");
        printf("\nif you want to output your Histogram using another parameters input '+'\nif you want to go further input '-':\n");
        check_symb = getc(stdin);
        while (1){
            if (check_symb == '+' || check_symb == '-')
                break;
            check_symb = getc(stdin);
        }
    }
    return 0;
}

IType ioput_test1()
{
    printf("input output functions tests\n");
    printf("\n");
    printf("function 'inputTextFile_Historgam' using 'Histogram_input_test.txt' file\n");
    printf("\n");
    FILE* f = fopen("Histogram_input_test.txt", "r");
    printf("file content will be like this 'start'contnet'end':\n");
    printf("start\n");
    char c;
    while (1)
    {
        //printf("point\n");
        c = getc(f);
        if (c == EOF)
            break;
        printf("%c", c);
    }
    fclose(f);
    printf("\nend\n");
    inputTextFile_Historgam("Histogram_input_test.txt", &H, "new_Histogram");
    printf("\n");
    printf("function 'output_Histogram'");
    printf("\n");
    output_Histogram(H, 0, 5, 2);
    printf("\n");
    printf("function 'outputTextFile_Histogram' in file 'Histogram_compare_cross_test.txt'\n");
    outputTextFile_Histogram("Histogram_compare_cross_test.txt", H, 0, 5, 2, "w");
    printf("\n");
    printf("file content will be like this 'start'contnet'end':\n");
    f = fopen("Histogram_compare_cross_test.txt", "r");
    printf("start\n");
    while (1)
    {
        //printf("point\n");
        c = getc(f);
        if (c == EOF)
            break;
        printf("%c", c);
    }
    fclose(f);
    //write cross_test file
    printf("\nend\n");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#inputTextFile_Historgam, outputTextFile_Histogram\n",f);
    fclose(f);
    //
}

IType Histogram_numbers_input_test()
{
    char* skip_c;
    printf("if you want to skip adding numbers to Histogram input '+' \notherwise(want to add numbers to Histogram) input anything:\n");
    skip_c = input_str();
    if (skip_c[0] == '+'){
        return 0;
    }

    IType source_type, values_input_type;
    char* manage_str;
    while(1){
        printf("your Histogram:");
        output_Histogram(H, 0, 4, 3);
        /*
        0 - Console
        1 - Text file
        2 - Binary file
        */
        printf("\nif you want to add numbers to Histogram using Console input '0'\nif you want to add numbers to Histogram using '.txt' file input '1'\nif you want to add numbers to Histogram using '.dat' file input '2':\n");
        manage_str = input_str();
        source_type = manage_str[0] - '0';
        /*
        0 - without changing Histogram
        1 - with changing Histogram
        */
        printf("if you want to add numbers in Histogram without changing of this Histogram input '0'\nif you want to add numbers in Histogram with changing Histogram(intervals of Histogram) input '1':\n");
        manage_str = input_str();
        values_input_type = manage_str[0] - '0';
        printf("values_input_type:%d\n", values_input_type);
        char mode[11];
        char* filename;
        //printf("hi\n");
        if (source_type == 0){
            filename = (char*)malloc(sizeof(char) * 9);
            strcpy(filename, "not_file");
            printf("filename: %s\n", filename);
        }
        else if (source_type == 1){
            printf("you choose add numbers from text file, input name of file(for example: 'Histogram_numbers_test.txt') :\n");
            manage_str = input_str();
            filename = (char*)malloc(sizeof(char) * strlen(manage_str));
            strcpy(filename, manage_str);
            FILE* f = fopen(filename, "r");
            while (!f){
                printf("file that you inputed is not exist, input another file name:\n");
                manage_str = input_str();
                strcpy(filename, manage_str);
                fclose(f);
                f = fopen(filename, "r");
            }
            fclose(f);
        }
        else if (source_type == 2){
            printf("you choose add numbers from binary file, input name of file(for example: 'Histogram_numbers_test.dat', \nthat consists of {-1.4, -4.6, -0.7, 2.400, 1.5670, 2.456, -4.546, 1.87, 9.400, -2.350}) :\n");
            manage_str = input_str();
            filename = (char*)malloc(sizeof(char) * strlen(manage_str));
            strcpy(filename, manage_str);
            FILE* f = fopen(filename, "rb");
            while (!f){
                printf("file that you inputed is not exist, input another file name:\n");
                manage_str = input_str();
                strcpy(filename, manage_str);
                fclose(f);
                f = fopen(filename, "rb");
            }
            fclose(f);
        }

        if (values_input_type == 0){
            strcpy(mode, "not_change");
        }
        else if (values_input_type == 1){
            //printf("hi\n");
            strcpy(mode, "change");
            //printf("hi\n");
        }
        printf("'%s', '%s'\n", filename, mode);
        NType n = input_numbers_in_Histogram(&H, filename, mode);
        //printf("n=%d\n", n);
        printf("your Histogram:");
        output_Histogram(H, 0, 6, 3);
        printf("\nif you want to add some another values in your Histogram input '+'\nif you want to go furhter input '-':\n");
        manage_str = input_str();
        
        //free(filename);
        if (manage_str[0] == '-'){
            free(manage_str);
            free(filename);
            break;
        }
        //free(manage_str);
    }


}

IType Histogram_numbers_input_test1()
{
    FILE* f;
    printf("'addNumber', 'addbatch' functions tests\n");
    printf("your Histogram\n");
    output_Histogram(H, 0, 5, 2);
    printf("\n");
    printf("function 'addNumber'\n");
    printf("\n");
    printf("add number '0.6' to Histogram that belong Histogram range [0, 5]\n");
    addNumber(0.6, &H, "not_change");
    printf("your Histogram\n");
    output_Histogram(H, 0, 5, 2);

    //write cross_test file
    outputTextFile_Histogram("Histogram_compare_cross_test.txt", H, 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addNumber mode 'not_change'\n",f);
    fclose(f);
    //

    printf("\n");
    printf("add number '-2.6' (without changing Histogram) to Histogram, number is not belong Histogram range [0, 5]\n");
    addNumber(-2.6, &H, "not_change");
    printf("your Histogram\n");
    output_Histogram(H, 0, 5, 2);

    //write cross_test file
    outputTextFile_Histogram("Histogram_compare_cross_test.txt", H, 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addNumber mode 'not_change'\n",f);
    fclose(f);
    //

    printf("\n");
    printf("add number '-2.6' (with changing Histogram) to Histogram, number is not belong Histogram range [0, 5]\n");
    addNumber(-2.6, &H, "change");
    printf("your Histogram\n");
    output_Histogram(H, 0, 5, 2);

    //write cross_test file
    outputTextFile_Histogram("Histogram_compare_cross_test.txt", H, 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addNumber mode 'change'\n",f);
    fclose(f);
    //

    printf("\n");
    printf("addbatch (numbers) {-2.7, 3.4, -1.4} (without changing Histogram) to Histogram, Histogram range [-2.6, 5]\n");
    DType numbers[] = {-2.7, 3.4, -1.4};
    addbatch(numbers, 3, &H, "not_change");
    printf("your Histogram\n");
    output_Histogram(H, 0, 5, 2);

    //write cross_test file
    outputTextFile_Histogram("Histogram_compare_cross_test.txt", H, 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addbatch mode 'not_change'\n",f);
    fclose(f);
    //

    printf("\n");
    printf("addbatch (numbers) {-2.5, -1.4, -0.45, 2.5} (with changing Histogram) to Histogram, Histogram range [-2.6, 5]\n");
    DType numbers1[] = {-2.5, -1.4, -0.45, 2.5};
    addbatch(numbers1, 4, &H, "change");
    printf("your Histogram\n");
    output_Histogram(H, 0, 5, 2);

    //write cross_test file
    outputTextFile_Histogram("Histogram_compare_cross_test.txt", H, 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addbatch mode 'change'\n",f);
    fclose(f);
    //
}

IType Histogram_properties_test()
{   
    FILE* f = fopen("Histogram_compare_cross_test.txt", "at");;
    IType res_type1;
    DType res_type2;
    char res_str[30];
    inputTextFile_Historgam("Histogram_input_test.txt", &H, "used_Histogram");
    printf("\nProperties of this Histogram:\n");
    output_Histogram(H, 0, 5, 2);
    
    res_type1 = num(&H);
    //write cross_test file
    sprintf(res_str, "\n%d\n#num\n", res_type1);
    fputs(res_str, f);
    //
    printf("\nnumber of elements in Histogram: %d\n\n", res_type1);
    
    NType column_idx = 3;
    res_type1 = numHist(&H, column_idx);
    //write cross_test file
    sprintf(res_str, "\n%d\n#numHist\n", res_type1);
    fputs(res_str, f);
    //
    printf("frequency of column with index %d: %d\n\n", column_idx, res_type1);

    res_type2 = mean(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#mean\n", res_type2);
    fputs(res_str, f);
    //
    printf("mean value of all numbers in Histogram: %.3f\n\n", res_type2);

    res_type2 = dispersion(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#dispersion\n", res_type2);
    fputs(res_str, f);
    //
    printf("root mean square value(dispersion) of all numbers in Histogram: %.3f\n\n", res_type2);

    res_type2 = median(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#median\n", res_type2);
    fputs(res_str, f);
    //
    printf("median of all numbers in Histogram: %.3f\n\n", res_type2);

    res_type2 = dev(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#dev\n", res_type2);
    fputs(res_str, f);
    //
    printf("mean deviation of all numbers in Histogram: %.3f\n\n", dev(&H));
    
    res_type2 = dev_squared(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#dev_squared\n", res_type2);
    fputs(res_str, f);
    //
    printf("standard deviation of all numbers in Histogram: %.3f\n\n", dev_squared(&H));
    
    res_type2 = centr_empiric_moment3(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#centr_empiric_moment3\n", res_type2);
    fputs(res_str, f);
    //
    printf("central empirical moment of order 3 of all numbers in Histogram: %.3f\n\n", centr_empiric_moment3(&H));
    
    res_type2 = centr_empiric_moment4(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#centr_empiric_moment4\n", res_type2);
    fputs(res_str, f);
    //
    printf("central empirical moment of order 4 of all numbers in Histogram: %.3f\n\n", centr_empiric_moment4(&H));
    
    res_type2 = asymmetry(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#asymmetry\n", res_type2);
    fputs(res_str, f);
    //
    printf("asymmetry coefficient of all numbers in Histogram: %.3f\n\n", asymmetry(&H));
    
    res_type2 = access(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#access\n", res_type2);
    fputs(res_str, f);
    //
    printf("access coefficient of all numbers in Histogram: %.3f\n\n", access(&H));
    
    res_type2 = variance(&H);
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#variance\n", res_type2);
    fputs(res_str, f);
    //
    printf("variance coefficient of all numbers in Histogram: %.3f\n\n", variance(&H));

    res_type1 = fash(&H);
    //write cross_test file
    sprintf(res_str, "\n%d\n#fashion\n", res_type1);
    fputs(res_str, f);
    //
    fclose(f);
    printf("fashion of Histogram is column with index %d\n\n", fash(&H));
}

IType main()
{
    printf("\nC_Histogram tests\n");
    //ioput_test();
    //Histogram_numbers_input_test();
    ioput_test1();
    Histogram_numbers_input_test1();
    Histogram_properties_test();
    printf("\nInput anything to exit...");
    getc(stdin);
    /*
    DType numbers[] = {-1.4, -4.6, -0.7, 2.400, 1.5670, 2.456, -4.546, 1.87, 9.400, -2.350};
    FILE* f = fopen("Histogram_numbers_test.dat", "w");
    IType n = fwrite(numbers, sizeof(DType), 10, f);
    printf("%d written\n", n);
    fclose(f);
    IType h;
    DType* numbers1 = (DType*)malloc(0);
    numbers1 = input_float_number(&h, "Histogram_numbers_test.dat");
    printf("\n%d\n", h);
    for (int i = 0; i < h; i++)
        printf("%f\n", numbers1[i]);
    */
    
    
    return 0;
}