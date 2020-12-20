//#include "../src/Histogram.cpp"
#include "../headers/another_funcs.h"
#include "../headers/input_funcs.h"
#include "../headers/Histogram.h"

using namespace std;

Histrogram H;

IType ioput_test()
{
    char* skip_c;
    printf("if you want to input Histogram from standart file(Histogram_input_test.txt) and skip other tests input '+' \notherwise input anything:\n");
    skip_c = input_str();
    if (skip_c[0] == '+'){
        H.inputTextFile_Historgam("Histogram_input_test.txt", "new_Histogram");
        return 0;
    }
    printf("let's input our first Histogram using Console:\n");
    H.input_Histogram("new_Histogram");
    char check_symb = '+';
    IType style_idx, width, precision;
    while (check_symb == '+'){
        printf("choose type of numbers output for Histogram output: \ninput '1' to choose output numbers in scientific style;\ninput '0' to choose output numbers in basic double style\n");
        //scanf("%d", &style_idx);
        cin >> style_idx;
        printf("input minimal width of each number:\n");
        //scanf("%d", &width);
        cin >> width;
        printf("input precision of each number:\n");
        //scanf("%d", &precision);
        cin >> precision;
        printf("Histogram that you inputed:\n");
        H.output_Histogram(style_idx, width, precision);
        printf("\nif you want to output your Histogram using another parameters input '+'\nif you want to go further input '-':\n");
        //check_symb = getc(stdin);
        cin >> check_symb;
        while (1){
            if (check_symb == '+' || check_symb == '-')
                break;
            //check_symb = getc(stdin);
            cin >> check_symb;
        }
    }
    printf("let's input our Histogram using '.txt' file \n(for example here is file with Histogram - 'Histogram_input_test.txt')\n");
    printf("input name of file that consists Histogram:\n");
    char* filename = input_str();
    IType out_token = H.inputTextFile_Historgam(filename, "used_Histogram");
    while(out_token == -1){
        printf("\nyou input file that is not exist, input name of file again:\n");
        filename = input_str();
        out_token = H.inputTextFile_Historgam(filename, "used_Histogram");
    }
    printf("Histogram that you inputed using '%s' file:\n", filename);
    H.output_Histogram(0, 6 ,3);
    printf("\nlet's output Histogram using '.txt' file\ninput name of file that will be output_file for our Histogram:\n");
    filename = input_str();
    check_symb = '+';
    while (check_symb == '+'){
        printf("choose type of numbers output for Histogram output: \ninput '1' to choose output numbers in scientific style;\ninput '0' to choose output numbers in basic double style\n");
        //scanf("%d", &style_idx);
        cin >> style_idx;
        printf("input minimal width of each number:\n");
        //scanf("%d", &width);
        cin >> width;
        printf("input precision of each number:\n");
        //scanf("%d", &precision);
        cin >> precision;
        printf("Histogram was inputed in file %s\n", filename);
        H.outputTextFile_Histogram(filename, style_idx, width, precision, "w");
        printf("\nif you want to output your Histogram using another parameters input '+'\nif you want to go further input '-':\n");
        //check_symb = getc(stdin);
        cin >> check_symb;
        while (1){
            if (check_symb == '+' || check_symb == '-')
                break;
            //check_symb = getc(stdin);
            cin >> check_symb;
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
    H.inputTextFile_Historgam("Histogram_input_test.txt", "new_Histogram");
    printf("\n");
    printf("function 'output_Histogram'");
    printf("\n");
    H.output_Histogram(0, 5, 2);
    printf("\n");
    printf("function 'outputTextFile_Histogram' in file 'Histogram_compare_cross_test.txt'\n");
    H.outputTextFile_Histogram("Histogram_compare_cross_test.txt", 0, 5, 2, "w");
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
    return 0;
}

IType Histogram_numbers_input_test()
{
    char* skip_c;
    cout << "if you want to skip adding numbers to Histogram input '+' \notherwise(want to add numbers to Histogram) input anything:\n";
    skip_c = input_str();
    if (skip_c[0] == '+'){
        return 0;
    }

    IType source_type, values_input_type;
    char* manage_str;
    while(1){
        cout << "your Histogram:";
        H.output_Histogram(0, 5, 3);
        /*
        0 - Console
        1 - Text file
        2 - Binary file
        */
        cout << "\nif you want to add numbers to Histogram using Console input '0'\nif you want to add numbers to Histogram using '.txt' file input '1'\nif you want to add numbers to Histogram using '.dat' file input '2':\n";
        manage_str = input_str();
        source_type = manage_str[0] - '0';
        /*
        0 - without changing Histogram
        1 - with changing Histogram
        */
        printf("if you want to add numbers in Histogram without changing of this Histogram input '0'\nif you want to add numbers in Histogram with changing Histogram(intervals of Histogram) input '1':\n");
        manage_str = input_str();
        values_input_type = manage_str[0] - '0';
        //printf("values_input_type:%d\n", values_input_type);
        char mode[11];
        char* filename;
        //printf("hi\n");
        if (source_type == 0){
            filename = (char*)malloc(sizeof(char) * 9);
            strcpy(filename, "not_file");
            //printf("filename: %s\n", filename);
        }
        else if (source_type == 1){
            cout << "you choose add numbers from text file, input name of file(for example: 'Histogram_numbers_test.txt') :\n";
            manage_str = input_str();
            filename = (char*)malloc(sizeof(char) * strlen(manage_str));
            strcpy(filename, manage_str);
            FILE* f = fopen(filename, "r");
            while (!f){
                cout << "file that you inputed is not exist, input another file name:\n";
                manage_str = input_str();
                strcpy(filename, manage_str);
                fclose(f);
                f = fopen(filename, "r");
            }
            fclose(f);
        }
        else if (source_type == 2){
            cout << "you choose add numbers from binary file, input name of file(for example: 'Histogram_numbers_test.dat', \nthat consists of {-1.4, -4.6, -0.7, 2.400, 1.5670, 2.456, -4.546, 1.87, 9.400, -2.350}) :\n";
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
            strcpy(mode, "change");
            //printf("hi\n");
        }
        //printf("'%s', '%s'\n", filename, mode);
        NType n = H.input_numbers_in_Histogram(filename, mode);
        //printf("n=%d\n", n);
        cout << "your Histogram:";
        H.output_Histogram(0, 6, 3);
        cout << "\nif you want to add some another values in your Histogram input '+'\nif you want to go furhter input '-':\n";
        manage_str = input_str();
        
        //free(filename);
        if (manage_str[0] == '-'){
            free(manage_str);
            free(filename);
            break;
        }
        //free(manage_str);
    }
    return 0;
}

IType Histogram_numbers_input_test1()
{
    FILE* f;
    printf("'addNumber', 'addbatch' functions tests\n");
    printf("your Histogram\n");
    H.output_Histogram(0, 5, 2);
    printf("\n");
    printf("function 'addNumber'\n");
    printf("\n");
    printf("add number '0.6' to Histogram that belong Histogram range [0, 5]\n");
    H.addNumber(0.6, "not_change");
    printf("your Histogram\n");
    H.output_Histogram(0, 5, 2);

    //write cross_test file
    H.outputTextFile_Histogram("Histogram_compare_cross_test.txt", 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addNumber mode 'not_change'\n",f);
    fclose(f);
    //

    printf("\n");
    printf("add number '-2.6' (without changing Histogram) to Histogram, number is not belong Histogram range [0, 5]\n");
    H.addNumber(-2.6, "not_change");
    printf("your Histogram\n");
    H.output_Histogram(0, 5, 2);

    //write cross_test file
    H.outputTextFile_Histogram("Histogram_compare_cross_test.txt", 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addNumber mode 'not_change'\n",f);
    fclose(f);
    //

    printf("\n");
    printf("add number '-2.6' (with changing Histogram) to Histogram, number is not belong Histogram range [0, 5]\n");
    H.addNumber(-2.6, "change");
    printf("your Histogram\n");
    H.output_Histogram(0, 5, 2);

    //write cross_test file
    H.outputTextFile_Histogram("Histogram_compare_cross_test.txt", 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addNumber mode 'change'\n",f);
    fclose(f);
    //

    printf("\n");
    printf("addbatch (numbers) {-2.7, 3.4, -1.4} (without changing Histogram) to Histogram, Histogram range [-2.6, 5]\n");
    DType numbers[] = {-2.7, 3.4, -1.4};
    H.addbatch(numbers, 3, "not_change");
    printf("your Histogram\n");
    H.output_Histogram(0, 5, 2);

    //write cross_test file
    H.outputTextFile_Histogram("Histogram_compare_cross_test.txt", 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addbatch mode 'not_change'\n",f);
    fclose(f);
    //

    printf("\n");
    printf("addbatch (numbers) {-2.5, -1.4, -0.45, 2.5} (with changing Histogram) to Histogram, Histogram range [-2.6, 5]\n");
    DType numbers1[] = {-2.5, -1.4, -0.45, 2.5};
    H.addbatch(numbers1, 4, "change");
    printf("your Histogram\n");
    H.output_Histogram(0, 5, 2);

    //write cross_test file
    H.outputTextFile_Histogram("Histogram_compare_cross_test.txt", 0, 5, 2, "at");
    f = fopen("Histogram_compare_cross_test.txt", "at");
    fputs("\n#addbatch mode 'change'\n",f);
    fclose(f);
    //
    return 0;
}

IType Histogram_properties_test()
{
    FILE* f = fopen("Histogram_compare_cross_test.txt", "at");;
    IType res_type1;
    DType res_type2;
    char res_str[30];
    H.inputTextFile_Historgam("Histogram_input_test.txt", "used_Histogram");
    printf("\nProperties of this Histogram:\n");
    H.output_Histogram(0, 5, 2);
    
    res_type1 = H.num();
    //write cross_test file
    sprintf(res_str, "\n%d\n#num\n", res_type1);
    fputs(res_str, f);
    //
    printf("\nnumber of elements in Histogram: %d\n\n", res_type1);
    
    NType column_idx = 3;
    res_type1 = H.numHist(column_idx);
    //write cross_test file
    sprintf(res_str, "\n%d\n#numHist\n", res_type1);
    fputs(res_str, f);
    //
    printf("frequency of column with index %d: %d\n\n", column_idx, res_type1);

    res_type2 = H.mean();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#mean\n", res_type2);
    fputs(res_str, f);
    //
    printf("mean value of all numbers in Histogram: %.3f\n\n", res_type2);

    res_type2 = H.dispersion();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#dispersion\n", res_type2);
    fputs(res_str, f);
    //
    printf("root mean square value of all numbers in Histogram: %.3f\n\n", res_type2);

    res_type2 = H.median();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#median\n", res_type2);
    fputs(res_str, f);
    //
    printf("median of all numbers in Histogram: %.3f\n\n", res_type2);

    res_type2 = H.dev();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#dev\n", res_type2);
    fputs(res_str, f);
    //
    printf("mean deviation of all numbers in Histogram: %.3f\n\n", H.dev());
    
    res_type2 = H.dev_squared();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#dev_squared\n", res_type2);
    fputs(res_str, f);
    //
    printf("standard deviation of all numbers in Histogram: %.3f\n\n", H.dev_squared());
    
    res_type2 = H.centr_empiric_moment3();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#centr_empiric_moment3\n", res_type2);
    fputs(res_str, f);
    //
    printf("central empirical moment of order 3 of all numbers in Histogram: %.3f\n\n", H.centr_empiric_moment3());
    
    res_type2 = H.centr_empiric_moment4();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#centr_empiric_moment4\n", res_type2);
    fputs(res_str, f);
    //
    printf("central empirical moment of order 4 of all numbers in Histogram: %.3f\n\n", H.centr_empiric_moment4());
    
    res_type2 = H.asymmetry();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#asymmetry\n", res_type2);
    fputs(res_str, f);
    //
    printf("asymmetry coefficient of all numbers in Histogram: %.3f\n\n", H.asymmetry());
    
    res_type2 = H.access();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#access\n", res_type2);
    fputs(res_str, f);
    //
    printf("access coefficient of all numbers in Histogram: %.3f\n\n", H.access());
    
    res_type2 = H.variance();
    //write cross_test file
    sprintf(res_str, "\n%.4f\n#variance\n", res_type2);
    fputs(res_str, f);
    //
    printf("variance coefficient of all numbers in Histogram: %.3f\n\n", H.variance());

    res_type1 = H.fash();
    //write cross_test file
    sprintf(res_str, "\n%d\n#fashion\n", res_type1);
    fputs(res_str, f);
    //
    printf("fashion of Histogram is column with index %d\n\n", H.fash());

    fclose(f);

    return 0;
}

IType main()
{
    cout << "\nCPP_Histogram tests\n" << endl;
    //ioput_test();
    //Histogram_numbers_input_test();
    ioput_test1();
    Histogram_numbers_input_test1();
    Histogram_properties_test();
    cout << "\ninput anything to exit...";
    getc(stdin);
    // "Histogram_numbers_test.dat" file consists {-1.4, -4.6, -0.7, 2.400, 1.5670, 2.456, -4.546, 1.87, 9.400, -2.350}

    /*
    DType numbers[] = {-1.4, -4.6, -0.7, 2.400, 1.5670, 2.456, -4.546, 1.87, 9.400, -2.350};
    FILE* f = fopen("Histogram_Khomenko_test.dat", "w");
    IType n = fwrite(numbers, sizeof(DType), 10, f);
    printf("%d written\n", n);
    fclose(f);
    IType h;
    DType* numbers1 = (DType*)malloc(0);
    numbers1 = input_float_number(&h, "Histogram_Khomenko_test.dat");
    printf("\n%d\n", h);
    for (int i = 0; i < h; i++)
        printf("%f\n", numbers1[i]);*/
    
    
    
    return 0;
}