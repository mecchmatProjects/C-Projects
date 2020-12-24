#include "../headers/input_funcs.h"


/*
читає з консолі рядок довільної довжини(до знаку  '\n') та повертає його
*/
char* input_str()
{
    NType str_len = 0;
    char* str = (char*)malloc(0);
    //printf("input:\n");
    char c = getc(stdin);
    while (1){
            if (c != '\n')
                break;
            c = getc(stdin);
    }
    while(c != '\n'){
        (str_len)++;
        str = (char*)realloc(str, sizeof(char) * (str_len));
        str[(str_len) - 1] = c;

        c = getc(stdin);
    }
    (str_len)++;
    str = (char*)realloc(str, sizeof(char) * (str_len));
    str[(str_len) - 1] = '\0';
    //printf("%s\n", str);
    return str;
}

IType equal_strs(char str1[], char str2[])
{
    for (int i = 0; ; i++){
        //printf("%c - %c\n", str1[i], str2[i]);
        if (str1[i] != str2[i]){
            return 0;
        }
        if (str1[i] == '\0' || str2[i] == '\0')
            break;
    }
    return 1;
}

/*
якщо мається на увазі ввід не с файлу(с консолі) filename = "not_file", 
в іншому випадку  filename рівний назві файлу в купі з розширенням файлу (".txt", ".dat")
*/
DType* input_float_number(IType* n, char filename[])
{
    IType filename_len = strlen(filename);
    DType* numbers = (DType*)malloc(sizeof(DType) * 0);
    //printf("fghjk");
    IType numbers_len = 0;

    if (equal_strs(filename, "not_file") || strstr(filename, ".txt") != NULL){
        FILE* f;
        char c, c_start = '#', c_sep1, c_sep2, c_end;
        if (equal_strs(filename, "not_file")){
            c_sep1 = ',', c_end = '\n';
            while ((c_start = getc(stdin)) == '\n') { }
        }
        else{
            //printf("prepare file\n");
            c_sep1 = ' ', c_sep2 = '\n', c_end = EOF;
            f = fopen(filename, "r");
            if (!f){
                printf("coudn't open file '%s'", filename);
                return numbers;
            }
            //printf("endofprepare file\n");
        }
        
        char* strin = (char*)malloc(sizeof(char) * 0);
        IType strin_len = 0; 
        //printf("\n-%c-%c-%c-\n", c_sep1, c_sep2, c_end);
        
        while(1)
        {
            if (equal_strs(filename, "not_file")){
                if (c_start == '#'){
                    c = getc(stdin);
                }
                else
                {
                    c = c_start;
                    c_start = '#';
                }
            }
            else
                c = getc(f);
            if (c == c_end || c == c_sep1 || c == c_sep2){
                if (strin_len != 0){
                    strin_len++;
                    strin = (char*)realloc(strin, sizeof(char) * strin_len);
                    strin[strin_len - 1] = '\0';

                    numbers_len++;
                    numbers = (DType*)realloc(numbers, sizeof(DType) * numbers_len);
                    numbers[numbers_len - 1] = atof(strin);
                    //printf("\n%f, strin: %s", numbers[numbers_len - 1], strin);
                    strin_len = 0;
                }
                if (c == c_end){
                    //printf("3fghjklkmnb vghjkm \n");
                    break;
                }
                continue;
            } 
            strin_len++;
            strin = (char*)realloc(strin, sizeof(char) * strin_len);
            strin[strin_len - 1] = c;
        }
        //printf("\nin_input numb[0]: %f", numbers[0]);
        if (!equal_strs(filename, "not_file"))
            fclose(f);
        *n = numbers_len;
        return numbers;
    }
    else if (strstr(filename, ".dat") != NULL){
        FILE* f = fopen(filename, "rb");
        DType number;
        while (1)
        {
            fread(&number, sizeof(DType), 1, f);
            if (feof(f))
                break;
            numbers_len++;
            numbers = (DType*)realloc(numbers, sizeof(DType) * numbers_len);
            numbers[numbers_len - 1] = number;
            //printf("\nnumber: %f", numbers[numbers_len - 1]);
        }
        fclose(f);
        *n = numbers_len;
        return numbers;
    }
    return 0;
}