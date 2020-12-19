#include "../headers/Histogram.h"

//#include "input_funcs.c"

#define Max_elems_in_column 1024

/*
видаляє елемент з динамічного массиву, змінюючи його розмір, який передається як параметр, 
та змінюючи кількість пам'яті, яка була виділина на массив, 
та повертає цей елемент
*/
DType exclude_from_mass(DType* mass, IType* n, IType idx)
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

/*
якщо number не входить у iнтервал [min_hist, max_hist]:
 1) та mode = 'change' number змінює інтервал [min_hist, max_hist] та додається до певного стовпця;
 2) та mode = 'not_change' number не запусується в Histogram;
якщо number входить у інтервал [min_hist, max_hist]: 
 1) тa mode = 'not_change' number додається то певного стовпця;
 2) та mode = 'change' те ж саме що і mode = 'not_change';
*/
void addNumber(DType number, Histrogram* H, char mode[])
{
    if (equal_strs(mode, "not_change")){
        if (number >= H->min_hist && number <= H->max_hist){
            //printf("\nin add_number_ number: %f\n", number);
            int state = 0;
            for (int i = 0; i < H->M; i++){
                state = number >= H->cols[i].left_bord && number < H->cols[i].right_bord;
                if (state || i == H->M - 1 && number == H->cols[i].right_bord){
                    H->cols[i].N++;
                    H->cols[i].elems = (DType*)realloc(H->cols[i].elems, sizeof(DType) * H->cols[i].N);
                    H->cols[i].elems[H->cols[i].N - 1] = number;
                    H->frequency[i]++;
                    break;
                }
            }
        }
    }
    else if (equal_strs(mode, "change")){
        if (number > H->max_hist){
            H->max_hist = number;
            update_Histogram(H, "not_first_start");
            addNumber(number, H, "not_change");
        }
        else if (number < H->min_hist){
            H->min_hist = number;
            update_Histogram(H, "not_first_start");
            addNumber(number, H, "not_change");
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
void addbatch(DType data[], size_t dataSize, Histrogram* H, char* mode){
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
            //printf("add_batch_el:'%f'\n", data[i]);
        }
        if (min_el < H->min_hist)
            addNumber(data[min_idx], H, "change");
        else if (min_el > H->min_hist){
            setMin(min_el, H, "change");
            addNumber(min_el, H, "not_change");
            //printf("min_idx=%d, max_el=%f\n", min_idx, max_el);
        }
        else if (min_el == H->min_hist){
            addNumber(min_el, H, "not_change");
        }
        //printf("min_idx=%d\n", min_idx);
        
        
        if (max_el > H->max_hist)
            addNumber(data[max_idx], H, "change");
        else if(max_el < H->max_hist){
            setMax(max_el, H, "change");
            addNumber(max_el, H, "not_change");
        }
        else if (max_el == H->max_hist){
            addNumber(max_el, H, "not_change");
        }
        
    }
    //printf("min_idx=%d, max_idx=%d\n", min_idx, max_idx);
    for (int i = 0; i < dataSize; i++){
        if (equal_strs(mode, "not_change")){
            addNumber(data[i], H, mode);
            //printf("not_change_adding number %f\n", data[i]);
        }
        else if (equal_strs(mode, "change")){
            if ((i != min_idx) && (i != max_idx)){
                //printf("add_batch_el:'%f'\n", data[i]);
                addNumber(data[i], H, "not_change");
            }
        }
    }

}


/*
кількість елементів в гісторгамі
*/
IType num(Histrogram* H)
{
    IType number_of_elements = 0;
    for (int i = 0; i < H->M; i++)
        number_of_elements += H->cols[i].N;
    return number_of_elements;
}

/*
частота відповідного стовпчика
і - індекс(перший стовпчик має індекс рівний нулю)
*/
IType numHist(Histrogram* H, IType i)
{
    return H->cols[i].N;
}

/*
вибіркове середнє гісторгами
*/
DType mean(Histrogram* H)
{
    DType sample_mean = 0.0;
    for (int i = 0; i < H->M; i++){
        sample_mean += ( (H->cols[i].left_bord + H->cols[i].right_bord) / 2.0 ) * H->frequency[i];
    }
    
    sample_mean /= (DType)num(H);
    return sample_mean;
}

/*
середнє квадратичне всіх значень в гістограмі
*/
DType dispersion(Histrogram* H)
{
    DType dispersion_part_val = 0.0, dispersion_val = 0.0, mean_val = mean(H);
    IType n = 0;
    for (int i = 0; i < H->M; i++){
        dispersion_part_val += pow( (H->cols[i].left_bord + H->cols[i].right_bord) / 2.0 , 2) * H->frequency[i];
        n += H->frequency[i];
    }
    dispersion_val = (dispersion_part_val / (DType)n) - pow(mean_val, 2);
    return dispersion_val;
}

/*
медіана гісторграми(медіана послідовності всіх елементів гісторгами)
*/
DType median(Histrogram* H)
{
    DType med_val;
    DType* sorted_numbers = (DType*)malloc(0);
    DType* numbers = (DType*)malloc(0);
    NType sorted_numbers_len = 0, numbers_len = 0;
    IType num_val = num(H);

    for (int i = 0; i < H->M; i++){
        for (int j = 0; j < H->cols[i].N; j++){
            numbers_len++;
            numbers = (DType*)realloc(numbers, sizeof(DType) * numbers_len);
            numbers[numbers_len - 1] = H->cols[i].elems[j];
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
        for (int i = 0; i < H->M; i++){
            for (int j = 0; j < H->cols[i].N; j++){
                curr_elem = H->cols[i].elems[j];
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
                prev_med_interval_acum_freq += H->frequency[i];
            }
        }
        if (search_cols_idx[0] != search_cols_idx[1]){
            med_interval_left_bord = H->cols[search_cols_idx[0]].left_bord;
            med_interval_len = 2 * ( H->cols[search_cols_idx[0]].right_bord - H->cols[search_cols_idx[0]].left_bord );
            med_interval_freq = H->frequency[search_cols_idx[0]] + H->frequency[search_cols_idx[1]];
        }
        else{
            med_interval_left_bord = H->cols[search_cols_idx[0]].left_bord;
            med_interval_len = H->cols[search_cols_idx[0]].right_bord - H->cols[search_cols_idx[0]].left_bord;
            med_interval_freq = H->frequency[search_cols_idx[0]];
        }

    }        
    else{
        NType search_col_numb = 0, search_col_idx;
        prev_med_interval_acum_freq = 0;
        for (int i = 0; i < H->M; i++){
            for (int j = 0; j < H->cols[i].N; j++){
            
                if (H->cols[i].elems[j] == sorted_numbers[idx]){
                    search_col_numb++;
                    search_col_idx = i;
                    break;
                }
            }
            if (search_col_numb == 1){
                break;
            }
            prev_med_interval_acum_freq += H->frequency[i];
        }
        med_interval_left_bord = H->cols[search_col_idx].left_bord;
        med_interval_len = H->cols[search_col_idx].right_bord - H->cols[search_col_idx].left_bord;
        med_interval_freq = H->frequency[search_col_idx];
    }
    med_val = med_interval_left_bord + med_interval_len * (0.5 * (DType)num_val - prev_med_interval_acum_freq) / med_interval_freq;
    return med_val;
}

/*
середнє відхилення (середнє відхилення значень гісторграми від середнього значення гісторграми)
*/
DType dev(Histrogram* H)
{
    DType med_mist = 0.0, med_val = mean(H);
    NType n = num(H);
    for (int i = 0; i < H->M; i++){
        for (int j = 0; j < H->cols[i].N; j++){
            med_mist += fabs(H->cols[i].elems[j] - med_val) / (DType)n;
        }
    }
    return med_mist;
}

/*
середнє квадратичне відхилення значень гістограми(не виправлене)
*/
DType dev_squared(Histrogram* H)
{
    DType S = dispersion(H), dev_squared_val;
    dev_squared_val = sqrt(S);
    return dev_squared_val;
}

/*
центральний емпіричний момент порядка 4
*/
DType centr_empiric_moment4(Histrogram* H)
{
    DType centr_empiric_moment4_val, centr_empiric_moment4_part_val = 0.0, mean_val = mean(H), interval_centr;
    NType n = num(H);
    for (int i = 0; i < H->M; i++){
        interval_centr = ( H->cols[i].left_bord + H->cols[i].right_bord ) / 2.0;
        centr_empiric_moment4_part_val += pow(interval_centr - mean_val, 4) * H->frequency[i];
    }
    centr_empiric_moment4_val = centr_empiric_moment4_part_val / (DType)n;
    return centr_empiric_moment4_val;
}

/*
центральний емпіричний момент порядка 3
*/
DType centr_empiric_moment3(Histrogram* H)
{
    DType centr_empiric_moment3_val, centr_empiric_moment3_part_val = 0.0, mean_val = mean(H), interval_centr;
    NType n = num(H);
    for (int i = 0; i < H->M; i++){
        interval_centr = ( H->cols[i].left_bord + H->cols[i].right_bord ) / 2.0;
        centr_empiric_moment3_part_val += pow(interval_centr - mean_val, 3) * H->frequency[i];
    }
    centr_empiric_moment3_val = centr_empiric_moment3_part_val / (DType)n;
    return centr_empiric_moment3_val;
}

/*
коефіцієнт асиметрії всіх значень гістограми(вибірки)
*/
DType asymmetry(Histrogram* H)
{
    DType asymmetry_koef, mean_val = mean(H), median_val = median(H), dev_squared_val = dev_squared(H);
    asymmetry_koef = (mean_val - median_val) / dev_squared_val;
    return asymmetry_koef;

}

/*
коефіцієнт акцесу всіх значень гістограми
*/
DType access(Histrogram* H)
{
    DType access_val, dev_squared_val = dev_squared(H), centr_empiric_moment4_val = centr_empiric_moment4(H);
    access_val = ( centr_empiric_moment4_val / pow(dev_squared_val, 4) ) - 3;
    return access_val;
}

/*
коефіцієнт варіації - це відношення стандартного відхилення(середнього квалратичного відхилення) до середньої(середнього значення в гістограмі)
*/
DType variance(Histrogram* H)
{
    DType variance_val, dev_squared_val = dev_squared(H), mean_val = mean(H);
    variance_val = ( dev_squared_val / mean_val ) * 100;
    return variance_val;
}

/*
мода гістограми(стовпчик з найбільшою частотою) виводиться індекс стовпчика
*/
NType fash(Histrogram* H)
{
    IType req_idx = 0;
    NType max_freq = H->frequency[0];
    for (int i = 0; i < H->M; i++){
        if (H->frequency[i] > max_freq){
            max_freq = H->frequency[i];
            req_idx = i;
        }

    }
    return req_idx;
}

/*
присвоює динамічним массивам певний вказівник та робить ці динамічні массиви спроможними до зміни пам'яті (realloc)
*/
void prepare_Histogram(Histrogram* H)
{
    H->frequency = (NType*)malloc(sizeof(NType) * 0);
    H->cols = (His_col*)malloc(sizeof(His_col) * 0);
}



/* 
mode = "first_start" || "not_first_start" || "rewrite_borders"
*/
void update_Histogram(Histrogram* H, char mode[])
{
    if (equal_strs(mode, "first_start")){
        prepare_Histogram(H);
        H->frequency = (NType*)realloc(H->frequency, sizeof(NType) * H->M);
        H->cols = (His_col*)realloc(H->cols, sizeof(His_col) * H->M);

        update_Histogram(H, "rewrite_borders");
        //printf("M: %d\ninterval: %f\n", H->M, interval_len);
        for(int i = 0; i < H->M; i++){
            H->frequency[i] = 0;
            H->cols[i].elems = (DType*)malloc(sizeof(DType) * 0);
            H->cols[i].N = 0;
            //printf("l_bord: %f\nr_bord: %f\n\n", H->cols[i].left_bord, H->cols[i].right_bord);
        }
    }
    else if (equal_strs(mode, "rewrite_borders")){
        H->cols[0].left_bord = H->min_hist;
        DType interval_len = (H->max_hist - H->min_hist) / (DType)H->M;
        for(int i = 0; i < H->M; i++){
            if (i < H->M - 1){
                H->cols[i].right_bord = H->min_hist + interval_len * (i + 1);

                H->cols[i + 1].left_bord = H->cols[i].right_bord;
            }
            else{
                H->cols[i].right_bord = H->max_hist;
            }
        }
    }
    else if (equal_strs(mode, "not_first_start")){
        DType* numbers = (DType*)malloc(sizeof(DType) * 0);
        IType n = 0, start_idx;
        for (int i = 0; i < H->M; i++){
            start_idx = n;
            n += H->cols[i].N;
            numbers = (DType*)realloc(numbers, sizeof(DType) * n);
            for (int j = start_idx; j < n; j++){
                numbers[j] = H->cols[i].elems[j - start_idx];
                //printf("el:'%f'\n", numbers[j]);
            }
            H->cols[i].N = 0;
            H->frequency[i] = 0;
            H->cols[i].elems = (DType*)realloc(H->cols[i].elems, sizeof(DType) * 0);
        }
        //printf("\nn=%d ,dfghjk\n", n);
        update_Histogram(H, "rewrite_borders");
        //printf("dfghjk\n");
        if (n != 0)
            addbatch(numbers, n, H, "not_change");
    }
}

/*
mode = 'change' || 'not_change'
*/
void setMax(DType m, Histrogram* H, char mode[]) 
{
    H->max_hist = m;
    if (equal_strs(mode, "change")){
        update_Histogram(H, "not_first_start");
    }
}

/*
mode = 'change' || 'not_change'
*/
void setMin(DType m, Histrogram* H, char mode[])
{
    H->min_hist = m;
    if (equal_strs(mode, "change")){
        update_Histogram(H, "not_first_start");
    }
}

void setM(NType m, Histrogram* H)
{
    H->M = m;
}


/*
mode = "new_Histogram" || "used_Historgam"
*/
void prepare_clean_Histogram(Histrogram* H, IType col_number, DType min_hist, DType max_hist, char mode[])
{
    if (equal_strs(mode, "new_Histogram")){
        setM(col_number, H);
        setMin(min_hist, H, "not_change");
        setMax(max_hist, H, "not_change");
        //printf("Histogram: M=%d, max_hist=%f, min_hist=%f\n", H->M, H->max_hist, H->min_hist);
        update_Histogram(H, "first_start");
    }
    else if (equal_strs(mode, "used_Histogram")){
        H->frequency = (NType*)realloc(H->frequency, sizeof(NType) * col_number);
        H->cols = (His_col*)realloc(H->cols, sizeof(His_col) * col_number);
        //printf("123\n");
        for (int i = 0; i < col_number; i++){
            //printf(":i=%d\n", i);
            H->frequency[i] = 0;
            H->cols[i].N = 0;
            if (i >= H->M)
                H->cols[i].elems = (DType*)malloc(sizeof(DType) * 0);
            else
                H->cols[i].elems = (DType*)realloc(H->cols[i].elems, sizeof(DType) * 0);

            //printf("end_iterarion\n");
        }
        setM(col_number, H);
        setMin(min_hist, H, "not_change");
        setMax(max_hist, H, "not_change");
        update_Histogram(H, "rewrite_borders");
    }
}

/*
якщо мається на увазі ввід не с файлу(с консолі) filename = "not_file", 
в іншому випадку  filename рівний назві файлу в купі з розширенням файлу (".txt", ".dat")
mode = "change" || "not_change"
*/
IType input_numbers_in_Histogram(Histrogram* H, char filename[], char mode[])
{
    DType* numbers;
    IType n, inputed_n = 0;
    for (int i = 0; i < H->M; i++){
        inputed_n += H->frequency[i];
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
        addNumber(numbers[0], H, mode);
    else if(n > 1){
        
        addbatch(numbers, n, H, mode);
        //printf("hi girls\n");
    }
    else
    {
        printf("\nyou don't write any DType number\n");
    }
    for (int i = 0; i < H->M; i++){
        //printf("freq[%d]=%d\n", i,H->frequency[i]);
        inputed_n -= H->frequency[i];
    }
    inputed_n = abs(inputed_n);
    return inputed_n;
}


/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType input_Histogram(Histrogram* H, char mode[])
{
    IType col_number, numbers_len = 0;
    DType min_hist, max_hist;
    
    printf("please input 3 values: \nnumber of columns(natural number), \nmin value(double number) in Histogram, \nmax value(double number) in Histogram using one button 'Enter' to split these values:\n");
    scanf("%d %lf %lf", &col_number, &min_hist, &max_hist);
    //printf("%d %f %f", col_number, min_hist, max_hist);
    prepare_clean_Histogram(H, col_number, min_hist, max_hist, mode);
    printf("input all numbers that your Histogram consists in it's columns\n");
    
    input_numbers_in_Histogram(H, "not_file", "not_change");
}

/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType inputTextFile_Historgam(char* file, Histrogram* H, char mode[])
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
    DType number, min_hist, max_hist;
    DType* numbers = (DType*)malloc(sizeof(DType) * 0);
    while(1)
    {
        c = getc(f);
        //printf("el:'%c'\n",c);
        if (strchr(c_seps, c) != NULL || c == c_end){
            if (strin_len != 0){
                strin_len++;
                strin = (char*)realloc(strin, sizeof(char) * strin_len);
                strin[strin_len - 1] = '\0';
                
                number = atof(strin);
                
                //printf("\nstrin='%s',strin_len=%d\n", strin, strin_len);
                
                strin_len = 0;
                if (col_token_idx == 0 && col_number == 0){
                    min_hist = number;
                    max_hist = number;
                }
                else if (col_token_idx >= 2){
                    numbers_len++;
                    numbers = (DType*)realloc(numbers, sizeof(DType) * numbers_len);
                    numbers[numbers_len - 1] = number;
                    //printf("\n%f, strin: %s, col_token_idx=%d", numbers[numbers_len - 1], strin, col_token_idx);
                }
                if (col_token_idx > 0 || col_number != 0){
                    if (number > max_hist)
                        max_hist = number;
                    else if(number < min_hist)
                        min_hist = number;
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
    /*printf("numbers_len=%d, min_hist=%f, max_hist=%f, col_number=%d, col_token_idx=%d\n", numbers_len, min_hist, max_hist, col_number, col_token_idx);
    printf("His,min_hist=%f, max_hist=%f, M=%d\n", H->min_hist, H->max_hist, H->M);
    for (int i = 0; i < numbers_len; i++)
        printf("numb:%f \n", numbers[i]);
    printf("startprepare\n");*/
    prepare_clean_Histogram(H, col_number, min_hist, max_hist, mode);
    /*printf("His,min_hist=%f, max_hist=%f, M=%d\n", H->min_hist, H->max_hist, H->M);
    printf("endprepare, =%d\n", H->M);*/

    addbatch(numbers, numbers_len, H, "not_change");
    //printf("smth else?\n");
    return 0;

}

/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType inputBinaryFile_Histogram(char* file, Histrogram* H, char mode[])
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
    prepare_clean_Histogram(H, H_buff.M, H_buff.min_hist, H_buff.max_hist, mode);
    H->cols = H_buff.cols;
    H->frequency = H_buff.frequency;
    
    fread(H->frequency, sizeof(DType), H->M, f);
    printf("2fghjk\n");
    fread(H->cols, sizeof(His_col), H->M, f);
    printf("2fghjk\n");
    for (int i = 0; i < H->M; i++){
        fread(H->cols[i].elems, sizeof(DType), H->cols[i].N, f);
    }
    printf("2fghjk\n");

}


/*
type = 0 : output numebr in basic double style
type = 1 : output number in scientific style
*/
void output_Histogram(Histrogram H, IType type, IType width, IType precision)
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
    for (int i = 0; i < H.M; i++){
        printf("\ncolumn_%d[%6.3f, %6.3f]: ", i, H.cols[i].left_bord, H.cols[i].right_bord);
        for (int j = 0; j < H.cols[i].N; j++){
            printf(format_str, H.cols[i].elems[j]);
            //printf("*");
        }
    }
    printf("\n");
}

/*
type = 0 : output numebr in basic double style
type = 1 : output number in scientific style
mode = "w" || "at"
*/
IType outputTextFile_Histogram(char* file, Histrogram H, IType type, IType width, IType precision, char mode[])
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
    
    for (int i = 0; i < H.M; i++){
        sprintf(format_str, "%s%d.%d%c, ", "%", width, precision, str_type[0]);
        fprintf(f, "[%6.3f, %6.3f]: ", H.cols[i].left_bord, H.cols[i].right_bord);
        for (int j = 0; j < H.cols[i].N; j++){
            if (j == H.cols[i].N - 1)
                sprintf(format_str, "%s%d.%d%c \n", "%", width, precision, str_type[0]);
            //printf("1fghjkformat_str='%s'\n", format_str);
            fprintf(f, format_str, H.cols[i].elems[j]);      
        }
        if (H.cols[i].N == 0){
            fprintf(f,"\n");
        }
    }
    fclose(f);
    return 0;
}

IType outputBinaryFile_Histogram(char* file, Histrogram H)
{
    FILE* f = fopen(file, "wb");
    if (!f){
        printf("coudn't open file '%s'", file);
        return -1;
    }
    fwrite(&H, sizeof(H), 1, f);
    fwrite(H.frequency, sizeof(NType), H.M, f);
    fwrite(H.cols, sizeof(His_col), H.M, f);
    for (int i = 0; i < H.M; i++){
        fwrite(H.cols[i].elems, sizeof(DType), H.cols[i].N, f);
    }
    return 0;
}
/*
int main()
{
    Histrogram H;
    inputTextFile_Historgam("Histogram_input_test.txt", &H, "new_Histogram");
    output_Histogram(H, 0, 5, 2);
    printf("%f\n", mean(&H));*/
/*
    setMax(2.4, &H, "not_change");
    setMin(-2.4, &H, "not_change");
    setM(5, &H);
    update_Histogram(&H, "first_start");
    IType* numbers_len;//malloc(sizeof(IType) * 1);
    IType num = 5;
    numbers_len = &num;
    //DType* numbers = input_float_number(numbers_len, "not_file.txt");
    printf("dfghjk\n");
    
    printf("\nnum: %d", *numbers_len);
    
    addNumber(-2.4, &H, "not_change");
    
    output_Histogram(H, 0, 6, 3);
    //addbatch(numbers, *numbers_len, &H, "change");
    printf("\ninputed_n=%d\n",input_numbers_in_Histogram(&H, "not_file.txt", "change"));
    output_Histogram(H, 0, 6, 3);*/
    //inputTextFile_Historgam("Histogram_output.txt", &H, "new_Histogram");

    //output_Histogram(H, 0, 6, 3);
    //outputTextFile_Histogram("Histogram_output.txt", H, 0, 6, 3);
    //printf("\n%f, %f, %f,\n", centr_empiric_moment4(&H), access(&H), asymmetry(&H));
    //printf("sizeof(H): %d\n", sizeof(H));
    
//    return 0;
//}
