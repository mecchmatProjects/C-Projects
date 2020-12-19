#include "../headers/another_funcs.h"
#include "../headers/input_funcs.h"
#include "../headers/Histogram.h"

#define Max_elems_in_column 1024

IType equal_strs(const char str1[], const char str2[])
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
читає з консолі рядок довільної довжини(до знаку  '\n') та повертає його
*/
char* input_str(){
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

/*
якщо мається на увазі ввід не с файлу(с консолі) filename = "not_file", 
в іншому випадку  filename рівний назві файлу в купі з розширенням файлу (".txt", ".dat")
*/
DType* input_float_number(IType* n, const char filename[])
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

/*
видаляє елемент з динамічного массиву, змінюючи його розмір, який передається як параметр, 
та змінюючи кількість пам'яті, яка була виділина на массив, 
та повертає цей елемент
*/
DType exclude_from_mass(DType* mass, NType* n, IType idx)
{
    DType excluded_element = mass[idx];
    
    for (int i = idx; i < *n - 1; i++){
        mass[i] = mass[i + 1];
    }
    *n -= 1;
    mass = (DType*)realloc(mass, sizeof(DType) * (*n));
    //printf("n=%d, %d dfghjk\n", *n, n);
    return excluded_element;
}

void Histrogram::setM(NType m){
    M = m;
}

/*
mode = 'change' || 'not_change'
*/
void Histrogram::setMin(DType m, const char mode[]){
    min_hist = m;
    if (equal_strs(mode, "change")){
        update_Histogram("not_first_start");
    }
}

/*
mode = 'change' || 'not_change'
*/
void Histrogram::setMax(DType m, const char mode[]){
    max_hist = m;
    if (equal_strs(mode, "change")){
        update_Histogram("not_first_start");
    }
}

/*
присвоює динамічним массивам(всередині Гістограми) певний вказівник та робить ці динамічні массиви спроможними до зміни пам'яті (realloc)
*/
void Histrogram::prepare_Histogram(){
    frequency = (NType*)malloc(sizeof(NType) * 0);
    cols = (His_col*)malloc(sizeof(His_col) * 0);
}

/* 
mode = "first_start" || "not_first_start" || "rewrite_borders"
*/
void Histrogram::update_Histogram(const char mode[]){
    if (equal_strs(mode, "first_start")){
        prepare_Histogram();
        frequency = (NType*)realloc(frequency, sizeof(NType) * M);
        cols = (His_col*)realloc(cols, sizeof(His_col) * M);

        update_Histogram("rewrite_borders");
        //printf("M: %d\ninterval: %f\n", H->M, interval_len);
        for(int i = 0; i < M; i++){
            frequency[i] = 0;
            cols[i].elems = (DType*)malloc(sizeof(DType) * 0);
            cols[i].N = 0;
            //printf("l_bord: %f\nr_bord: %f\n\n", H->cols[i].left_bord, H->cols[i].right_bord);
        }
    }
    else if (equal_strs(mode, "rewrite_borders")){
        cols[0].left_bord = min_hist;
        DType interval_len = (max_hist - min_hist) / (DType)M;
        for(int i = 0; i < M; i++){
            if (i < M - 1){
                cols[i].right_bord = min_hist + interval_len * (i + 1);

                cols[i + 1].left_bord = cols[i].right_bord;
            }
            else{
                cols[i].right_bord = max_hist;
            }
        }
    }
    else if (equal_strs(mode, "not_first_start")){
        DType* numbers = (DType*)malloc(sizeof(DType) * 0);
        IType n = 0, start_idx;
        for (int i = 0; i < M; i++){
            start_idx = n;
            n += cols[i].N;
            numbers = (DType*)realloc(numbers, sizeof(DType) * n);
            for (int j = start_idx; j < n; j++){
                numbers[j] = cols[i].elems[j - start_idx];
            }
            cols[i].N = 0;
            frequency[i] = 0;
            cols[i].elems = (DType*)realloc(cols[i].elems, sizeof(DType) * 0);
        }
        //printf("\nn=%d ,dfghjk\n", n);
        update_Histogram("rewrite_borders");
        //printf("dfghjk\n");
        if (n != 0)
            addbatch(numbers, n, "not_change");
    }
}

/*
якщо number не входить у iнтервал [min_hist, max_hist]:
 1) та mode = 'change' number змінює інтервал [min_hist, max_hist] та додається до певного стовпця;
 2) та mode = 'not_change' number не запусується в Histogram;
якщо number входить у інтервал [min_hist, max_hist]: 
 1) тa mode = 'not_change' number додається то певного стовпця;
 2) та mode = 'change' те ж саме що і mode = 'not_change';
*/
void Histrogram::addNumber(DType number, const char mode[])
{
    if (equal_strs(mode, "not_change")){
        if (number >= min_hist && number <= max_hist){
            //printf("\nin add_number_ number: %f\n", number);
            int state = 0;
            for (int i = 0; i < M; i++){
                state = number >= cols[i].left_bord && number < cols[i].right_bord;
                if (state || i == M - 1 && number == cols[i].right_bord){
                    cols[i].N++;
                    cols[i].elems = (DType*)realloc(cols[i].elems, sizeof(DType) * cols[i].N);
                    cols[i].elems[cols[i].N - 1] = number;
                    frequency[i]++;
                    break;
                }
            }
        }
    }
    else if (equal_strs(mode, "change")){
        if (number > max_hist){
            max_hist = number;
            update_Histogram("not_first_start");
            addNumber(number, "not_change");
        }
        else if (number < min_hist){
            min_hist = number;
            update_Histogram("not_first_start");
            addNumber(number, "not_change");
        }
        
    }
}

/*
number is in data
якщо number не входить у iнтервал [min_hist, max_hist]:
 1) та mode = 'change' number змінює інтервал [min_hist, max_hist] та додається до певного стовпця;
 2) та mode = 'not_change' number не запусується в Histogram;
якщо number входить у інтервал [min_hist, max_hist]: 
 1) тa mode = 'not_change' number додається то певного стовпця;
 2) та mode = 'change' те ж саме що і mode = 'not_change';
*/
void Histrogram::addbatch(DType data[], size_t dataSize, const char mode[]){
    int min_idx = -1, max_idx = -1;
    DType min_el = data[0], max_el = data[0];
    //printf("dfcvgbhnjklmjuhyfgxcvbhjnb,cvn bhjkmkljb m\n");
    if (equal_strs(mode, "change")){
        //printf("change mode ghjkvbnmoiuhjijhbgfvcvbghnjmk");
        for (int i = 0; i < dataSize; i++){
            if (data[i] >= max_el){
                max_el = data[i];
                max_idx = i;
            }
            if (data[i] <= min_el){
                min_el = data[i];
                min_idx = i;
            }
        }
        if (min_el < min_hist)
            addNumber(data[min_idx], "change");
        else if (min_el > min_hist){
            setMin(min_el, "change");
            addNumber(min_el, "not_change");
        }
        else if (min_el == min_hist){
            addNumber(min_el, "not_change");
        }

        if (max_el > max_hist)
            addNumber(data[max_idx], "change");
        else if (max_el < max_hist){
            setMax(max_el, "change");
            addNumber(max_el, "not_change");
        }
        else if (max_el == max_hist){
            addNumber(max_el, "not_change");
        }
    }

    for (int i = 0; i < dataSize; i++){
        if (equal_strs(mode, "not_change")){
            addNumber(data[i], mode);
            //printf("not_change_adding number %f\n", data[i]);
        }
        else if (equal_strs(mode, "change")){
            if (i != min_idx && i != max_idx)
                addNumber(data[i], "not_change");
        }
    }

}

/*
mode = "new_Histogram" || "used_Historgam"
*/
void Histrogram::prepare_clean_Histogram(IType col_number, DType min_hist, DType max_hist, const char mode[])
{
    if (equal_strs(mode, "new_Histogram")){
        setM(col_number);
        setMin(min_hist, "not_change");
        setMax(max_hist, "not_change");
        //printf("Histogram: M=%d, max_hist=%f, min_hist=%f\n", H->M, H->max_hist, H->min_hist);
        update_Histogram("first_start");
    }
    else if (equal_strs(mode, "used_Histogram")){
        frequency = (NType*)realloc(frequency, sizeof(NType) * col_number);
        cols = (His_col*)realloc(cols, sizeof(His_col) * col_number);
        //printf("123\n");
        for (int i = 0; i < col_number; i++){
            //printf(":i=%d\n", i);
            frequency[i] = 0;
            cols[i].N = 0;
            if (i >= M)
                cols[i].elems = (DType*)malloc(sizeof(DType) * 0);
            else
                cols[i].elems = (DType*)realloc(cols[i].elems, sizeof(DType) * 0);

            //printf("end_iterarion\n");
        }
        setM(col_number);
        setMin(min_hist, "not_change");
        setMax(max_hist, "not_change");
        update_Histogram("rewrite_borders");
    }
}

/*
якщо мається на увазі ввід не с файлу(с консолі) filename = "not_file", 
в іншому випадку  filename рівний назві файлу в купі з розширенням файлу (".txt", ".dat")
mode = "change" || "not_change"
*/
IType Histrogram::input_numbers_in_Histogram(const char filename[], const char mode[])
{
    DType* numbers;
    IType n, inputed_n = 0;
    for (int i = 0; i < M; i++){
        inputed_n += frequency[i];
        //printf("freq[%d]=%d\n", i, H->frequency[i]);
    }
    //printf("\n1_inputed_n=%d\n", inputed_n);
    if (equal_strs(filename, "not_file")){
        printf("\nyou choose input from console, write numbers like '2.3,4.5,-3.6,0.024E002,1.4,-1.3' in one string and click 'Enter' to end input\n");
        numbers = input_float_number(&n, filename);
        //printf("nghdfxdx");
    }
    else if (strstr(filename, ".txt") != NULL){
        printf("\nyou choose input from '%s' file, numbers in file have to look like '0.024E002' or '2.3' and have to be splited by spaces or '\\n'(new row signs)\nplease prepare you file and click 'Enter'\n", filename);
        getc(stdin);
        numbers = input_float_number(&n, filename);
    }
    else if (strstr(filename, ".dat") != NULL){
        printf("\nyou choose input from '%s' file, file have to contain massive of DType(double) numbers \nplease prepare you file and click 'Enter'\n", filename);
        getc(stdin);
        numbers = input_float_number(&n, filename);
    }
    //printf("\nn=%d \n", n);
    if (n == 1)
        addNumber(numbers[0], mode);
    else if(n > 1){
        
        addbatch(numbers, n, mode);
        //printf("hi girls\n");
    }
    else
    {
        printf("\nyou don't write any DType number\n");
    }
    for (int i = 0; i < M; i++){
        //printf("freq[%d]=%d\n", i,H->frequency[i]);
        inputed_n -= frequency[i];
    }
    inputed_n = abs(inputed_n);
    return inputed_n;
}


/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType Histrogram::input_Histogram(const char mode[])
{
    IType col_number, numbers_len = 0, inputed_amount;
    DType min_hist_this, max_hist_this;
    
    printf("please input 3 values: \nnumber of columns(natural number), \nmin value(double number) in Histogram, \nmax value(double number) in Histogram using one button 'Enter' to split these values:\n");
    scanf("%d %lf %lf", &col_number, &min_hist_this, &max_hist_this);
    //printf("%d %f %f", col_number, min_hist_this, max_hist_this);
    prepare_clean_Histogram(col_number, min_hist_this, max_hist_this, mode);
    printf("input all numbers that your Histogram consists in it's columns\n");
    
    inputed_amount = input_numbers_in_Histogram("not_file", "not_change");
    return inputed_amount;
}

/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType Histrogram::inputTextFile_Historgam(const char* file, const char mode[])
{
    FILE* f = fopen(file, "r");
    if (!f){
        printf("coudn't open file '%s'", file);
        return -1;
    }
    char c, c_end = (char)EOF;
    char c_seps[] = "[, ]:\n";
    char* strin = (char*)malloc(sizeof(char) * 0);
    IType strin_len = 0, col_token_idx = 0, col_number = 0, numbers_len = 0;
    DType number, min_hist_this, max_hist_this;
    DType* numbers = (DType*)malloc(sizeof(DType) * 0);
    while(1)
    {
        c = getc(f);
        if (strchr(c_seps, c) != NULL || c == c_end){
            if (strin_len != 0){
                strin_len++;
                strin = (char*)realloc(strin, sizeof(char) * strin_len);
                strin[strin_len - 1] = '\0';
                
                number = atof(strin);
                
                //printf("\nstrin='%s',strin_len=%d\n", strin, strin_len);
                
                strin_len = 0;
                if (col_token_idx == 0 && col_number == 0){
                    min_hist_this = number;
                    max_hist_this = number;
                }
                else if (col_token_idx >= 2){
                    numbers_len++;
                    numbers = (DType*)realloc(numbers, sizeof(DType) * numbers_len);
                    numbers[numbers_len - 1] = number;
                    //printf("\n%f, strin: %s, col_token_idx=%d", numbers[numbers_len - 1], strin, col_token_idx);
                }
                if (col_token_idx > 0 || col_number != 0){
                    if (number > max_hist_this)
                        max_hist_this = number;
                    else if(number < min_hist_this)
                        min_hist_this = number;
                }
                col_token_idx++;
            }
            
            if (c == '\n' || c == c_end){
                //printf("hi\n");
                if (col_token_idx != 0){
                    //printf("Hi\n");
                    col_token_idx = 0;
                    col_number++;
                }
                if (c == c_end)
                    break;
            }
            if (strin_len == 0)
                continue;
        }
        strin_len++;
        strin = (char*)realloc(strin, sizeof(char) * strin_len);
        strin[strin_len - 1] = c;
    }
    /*printf("numbers_len=%d, min_hist_this=%f, max_hist=%f, col_number=%d, col_token_idx=%d\n", numbers_len, min_hist_this, max_hist, col_number, col_token_idx);
    printf("His,min_hist=%f, max_hist=%f, M=%d\n", H->min_hist, H->max_hist, H->M);
    for (int i = 0; i < numbers_len; i++)
        printf("numb:%f \n", numbers[i]);
    printf("startprepare\n");*/
    prepare_clean_Histogram(col_number, min_hist_this, max_hist_this, mode);
    /*printf("His,min_hist=%f, max_hist=%f, M=%d\n", H->min_hist, H->max_hist, H->M);
    printf("endprepare, =%d\n", H->M);*/

    addbatch(numbers, numbers_len, "not_change");
    //printf("smth else?\n");
    return 0;

}

/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType Histrogram::inputBinaryFile_Histogram(const char* file, const char mode[])
{
    FILE* f = fopen(file, "rb");
    if (!f){
        printf("coudn't open file '%s'", file);
        return -1;
    }
    Histrogram H_buff;
    H_buff.cols = NULL;
    H_buff.frequency = NULL;
    printf("n=%d\n", fread(&H_buff, sizeof(H_buff), 1, f));

    printf("M=%d, min_hist=%f\n", H_buff.M, H_buff.min_hist);
    prepare_clean_Histogram(H_buff.M, H_buff.min_hist, H_buff.max_hist, mode);
    cols = H_buff.cols;
    frequency = H_buff.frequency;
    
    fread(frequency, sizeof(DType), M, f);
    printf("2fghjk\n");
    fread(cols, sizeof(His_col), M, f);
    printf("2fghjk\n");
    for (int i = 0; i < M; i++){
        fread(cols[i].elems, sizeof(DType), cols[i].N, f);
    }
    printf("2fghjk\n");
    return 0;

}

/*
type = 0 : output numebr in basic double style
type = 1 : output number in scientific style
*/
void Histrogram::output_Histogram(IType type, IType width, IType precision)
{
    char str_type[1];
    if (type == 0)
        str_type[0] = 'f';
    else if (type == 1)
        str_type[0] = 'e';

    char format_str[8];//14
    sprintf(format_str, "%s%d.%d%c ; ", "%", width, precision, str_type[0]);//"numb: %s%d.%d%c ; "
    //printf("\nfghjkl;");
    //printf("\ncool_str: %s", format_str);
    for (int i = 0; i < M; i++){
        printf("\ncolumn_%d[%6.3f, %6.3f]: ", i, cols[i].left_bord, cols[i].right_bord);
        for (int j = 0; j < cols[i].N; j++){
            printf(format_str, cols[i].elems[j]);
            //printf("*");
        }
    }
}

/*
type = 0 : output numebr in basic double style
type = 1 : output number in scientific style
mode = "w" || "at"
*/
IType Histrogram::outputTextFile_Histogram(const char* file, IType type, IType width, IType precision, const char mode[])
{
    FILE* f = fopen(file, mode);
    if (!f){
        printf("coudn't open file '%s'", file);
        return -1;
    }
    char str_type[1];
    if (type == 0)
        str_type[0] = 'f';
    else if (type == 1)
        str_type[0] = 'e';

    char format_str[8];
    
    for (int i = 0; i < M; i++){
        sprintf(format_str, "%s%d.%d%c, ", "%", width, precision, str_type[0]);
        fprintf(f, "[%6.3f, %6.3f]: ", cols[i].left_bord, cols[i].right_bord);
        for (int j = 0; j < cols[i].N; j++){
            if (j == cols[i].N - 1)
                sprintf(format_str, "%s%d.%d%c \n", "%", width, precision, str_type[0]);
            //printf("1fghjkformat_str='%s'\n", format_str);
            fprintf(f, format_str, cols[i].elems[j]);      
        }
        if (cols[i].N == 0){
            fprintf(f,"\n");
        }
    }
    fclose(f);
    return 0;
}

IType Histrogram::outputBinaryFile_Histogram(const char* file)
{
    FILE* f = fopen(file, "wb");
    if (!f){
        printf("coudn't open file '%s'", file);
        return -1;
    }
    fwrite(this, sizeof(*this), 1, f);
    fwrite(frequency, sizeof(NType), M, f);
    fwrite(cols, sizeof(His_col), M, f);
    for (int i = 0; i < M; i++){
        fwrite(cols[i].elems, sizeof(DType), cols[i].N, f);
    }
    return 0;
}

/*
кількість елементів в гісторгамі
*/
IType Histrogram::num()
{
    IType number_of_elements = 0;
    for (int i = 0; i < M; i++)
        number_of_elements += cols[i].N;
    return number_of_elements;
}

/*
частота відповідного стовпчика
і - індекс(перший стовпчик має індекс рівний нулю)
*/
IType Histrogram::numHist(IType i)
{
    return cols[i].N;
}

/*
середнє значення гісторгами
*/
DType Histrogram::mean()
{
    DType sample_mean = 0.0;
    for (int i = 0; i < M; i++){
        sample_mean += ( (cols[i].left_bord + cols[i].right_bord) / 2.0 ) * frequency[i];
    }
    
    sample_mean /= (DType)num();
    return sample_mean;
}

/*
середнє квадратичне всіх значень в гістограмі
*/
DType Histrogram::dispersion()
{
    DType dispersion_part_val = 0.0, dispersion_val = 0.0, mean_val = mean();
    IType n = 0;
    for (int i = 0; i < M; i++){
        dispersion_part_val += pow( (cols[i].left_bord + cols[i].right_bord) / 2.0 , 2) * frequency[i];
        n += frequency[i];
    }
    dispersion_val = (dispersion_part_val / (DType)n) - pow(mean_val, 2);
    return dispersion_val;
}

/*
медіана гісторграми(медіана послідовності всіх елементів гісторгами)
*/
DType Histrogram::median()
{
    DType med_val;
    DType* sorted_numbers = (DType*)malloc(0);
    DType* numbers = (DType*)malloc(0);
    NType sorted_numbers_len = 0, numbers_len = 0;
    IType num_val = num();

    for (int i = 0; i < M; i++){
        for (int j = 0; j < cols[i].N; j++){
            numbers_len++;
            numbers = (DType*)realloc(numbers, sizeof(DType) * numbers_len);
            numbers[numbers_len - 1] = cols[i].elems[j];
        }
    }
    DType min_el, min_el_idx;
    while (numbers_len != 0){
        min_el = numbers[0];
        min_el_idx = 0;
        for (int i = 0; i < numbers_len; i++){
            if (numbers[i] < min_el){
                min_el = numbers[i];
                min_el_idx = i;
            }
        }
        sorted_numbers_len++;
        sorted_numbers = (DType*)realloc(sorted_numbers, sizeof(DType) * sorted_numbers_len);
        sorted_numbers[sorted_numbers_len - 1] = exclude_from_mass(numbers, &numbers_len, min_el_idx);
        //printf("%f ", sorted_numbers[sorted_numbers_len - 1]);
    }
    //printf("\n");
    DType med_interval_left_bord, med_interval_len, med_interval_freq, prev_med_interval_acum_freq;
    IType idx = sorted_numbers_len / 2;
    if (sorted_numbers_len % 2 == 0){
        DType search_numbs[] = {sorted_numbers[idx], sorted_numbers[idx - 1] }, curr_elem;
        NType search_cols_idx[2], search_cols_numb = 0;
        prev_med_interval_acum_freq = 0;
        for (int i = 0; i < M; i++){
            for (int j = 0; j < cols[i].N; j++){
                curr_elem = cols[i].elems[j];
                if (curr_elem == search_numbs[0] || curr_elem == search_numbs[1]){
                    search_cols_numb++;
                    search_cols_idx[search_cols_numb - 1] = i;
                }
                if (search_cols_numb == 2){
                    break;
                }
            }
            if (search_cols_numb == 2){
                    break;
            }
            if (search_cols_numb == 0){
                prev_med_interval_acum_freq += frequency[i];
            }
        }
        if (search_cols_idx[0] != search_cols_idx[1]){
            med_interval_left_bord = cols[search_cols_idx[0]].left_bord;
            med_interval_len = 2 * ( cols[search_cols_idx[0]].right_bord - cols[search_cols_idx[0]].left_bord );
            med_interval_freq = frequency[search_cols_idx[0]] + frequency[search_cols_idx[1]];
        }
        else{
            med_interval_left_bord = cols[search_cols_idx[0]].left_bord;
            med_interval_len = cols[search_cols_idx[0]].right_bord - cols[search_cols_idx[0]].left_bord;
            med_interval_freq = frequency[search_cols_idx[0]];
        }

    }        
    else{
        NType search_col_numb = 0, search_col_idx;
        prev_med_interval_acum_freq = 0;
        for (int i = 0; i < M; i++){
            for (int j = 0; j < cols[i].N; j++){
            
                if (cols[i].elems[j] == sorted_numbers[idx]){
                    search_col_numb++;
                    search_col_idx = i;
                    break;
                }
            }
            if (search_col_numb == 1){
                break;
            }
            prev_med_interval_acum_freq += frequency[i];
        }
        med_interval_left_bord = cols[search_col_idx].left_bord;
        med_interval_len = cols[search_col_idx].right_bord - cols[search_col_idx].left_bord;
        med_interval_freq = frequency[search_col_idx];
    }
    med_val = med_interval_left_bord + med_interval_len * (0.5 * (DType)num_val - prev_med_interval_acum_freq) / med_interval_freq;
    return med_val;
}

/*
середнє відхилення (середнє відхилення значень гісторграми від середнього значення гісторграми)
*/
DType Histrogram::dev()
{
    DType med_mist = 0.0, med_val = mean();
    NType n = num();
    for (int i = 0; i < M; i++){
        for (int j = 0; j < cols[i].N; j++){
            med_mist += fabs(cols[i].elems[j] - med_val) / (DType)n;
        }
    }
    return med_mist;
}

/*
середнє квадратичне відхилення значень гістограми(не виправлене)
*/
DType Histrogram::dev_squared()
{
    DType S = dispersion(), dev_squared_val;
    dev_squared_val = sqrt(S);
    return dev_squared_val;
}

/*
центральний емпіричний момент порядка 4
*/
DType Histrogram::centr_empiric_moment4()
{
    DType centr_empiric_moment4_val, centr_empiric_moment4_part_val = 0.0, mean_val = mean(), interval_centr;
    NType n = num();
    for (int i = 0; i < M; i++){
        interval_centr = ( cols[i].left_bord + cols[i].right_bord ) / 2.0;
        centr_empiric_moment4_part_val += pow(interval_centr - mean_val, 4) * frequency[i];
    }
    centr_empiric_moment4_val = centr_empiric_moment4_part_val / (DType)n;
    return centr_empiric_moment4_val;
}

/*
центральний емпіричний момент порядка 3
*/
DType Histrogram::centr_empiric_moment3()
{
    DType centr_empiric_moment3_val, centr_empiric_moment3_part_val = 0.0, mean_val = mean(), interval_centr;
    NType n = num();
    for (int i = 0; i < M; i++){
        interval_centr = ( cols[i].left_bord + cols[i].right_bord ) / 2.0;
        centr_empiric_moment3_part_val += pow(interval_centr - mean_val, 3) * frequency[i];
    }
    centr_empiric_moment3_val = centr_empiric_moment3_part_val / (DType)n;
    return centr_empiric_moment3_val;
}

/*
коефіцієнт асиметрії всіх значень гістограми(вибірки)
*/
DType Histrogram::asymmetry()
{
    DType asymmetry_koef, mean_val = mean(), median_val = median(), dev_squared_val = dev_squared();
    asymmetry_koef = (mean_val - median_val) / dev_squared_val;
    return asymmetry_koef;

}

/*
коефіцієнт акцесу всіх значень гістограми
*/
DType Histrogram::access()
{
    DType access_val, dev_squared_val = dev_squared(), centr_empiric_moment4_val = centr_empiric_moment4();
    access_val = ( centr_empiric_moment4_val / pow(dev_squared_val, 4) ) - 3;
    return access_val;
}

/*
коефіцієнт варіації - це відношення стандартного відхилення(середнього квалратичного відхилення) до середньої(середнього значення в гістограмі)
*/
DType Histrogram::variance()
{
    DType variance_val, dev_squared_val = dev_squared(), mean_val = mean();
    variance_val = ( dev_squared_val / mean_val ) * 100;
    return variance_val;
}

/*
мода гістограми(стовпчик з найбільшою частотою) виводиться індекс стовпчика
*/
NType Histrogram::fash()
{
    IType req_idx = 0;
    NType max_freq = frequency[0];
    for (int i = 0; i < M; i++){
        if (frequency[i] > max_freq){
            max_freq = frequency[i];
            req_idx = i;
        }

    }
    return req_idx;
}

/*
int main()
{
    char str[] = "abcdefg";
    char str1[50];
    int h = -1;
    Histrogram H;
    

    H.setMax(2.4, "not_change");
    H.setMin(-2.4, "not_change");
    H.setM(5);
    H.update_Histogram("first_start");
    IType* numbers_len;
    IType num = 5;
    numbers_len = &num;
    DType* numbers = input_float_number(numbers_len, "not_file.txt");
    printf("dfghjk\n");
    
    //printf("\nnum: %d", *numbers_len);
    
    H.addNumber(-2.4, "not_change");
    
    output_Histogram(H, 0, 6, 3);
    addbatch(numbers, *numbers_len, &H, "change");
    //printf("\ninputed_n=%d\n",input_numbers_in_Histogram(&H, "not_file.txt", "change"));
    output_Histogram(H, 0, 6, 3);
    //inputTextFile_Historgam("Histogram_output.txt", &H, "new_Histogram");

    //output_Histogram(H, 0, 6, 3);
    //outputTextFile_Histogram("Histogram_output.txt", H, 0, 6, 3);
    //printf("\n%f, %f, %f,\n", centr_empiric_moment4(&H), access(&H), asymmetry(&H));
    //printf("sizeof(H): %d\n", sizeof(H));
    
    return 0;
}
*/