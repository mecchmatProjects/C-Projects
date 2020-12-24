#ifndef __Histogram__
#define __Histogram__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../headers/common.h"
#include "His_col.h"
#include "input_funcs.h"
#include "other_funcs.h"

typedef struct
{
    /* мінімально можливе значення елемента в гісторграмі*/
    DType min_hist;
    
    /* максимально можливе значення елемента в гістограмі*/
    DType max_hist;
    
    /* кількість стопвців*/
    NType M;

    /* динамічний масив кожен елемент якого це - кількість елементів в кожному стовпці гістограми*/
    NType* frequency;

    /* динамічній масив стовпців
    кожна ліва границя інтервалу не строга(>=), 
    кожна права границя інтервалу строга(<), 
    окрім останнього стовпця права границя інтервалу якого не строга(<=)*/
    His_col* cols;
}Histrogram;

/*
якщо number не входить у iнтервал [min_hist, max_hist]:
 1) та mode = 'change' number змінює інтервал [min_hist, max_hist] та додається до певного стовпця;
 2) та mode = 'not_change' number не запусується в Histogram;
якщо number входить у інтервал [min_hist, max_hist]: 
 1) тa mode = 'not_change' number додається то певного стовпця;
 2) та mode = 'change' те ж саме що і mode = 'not_change';
*/
void addNumber(DType number, Histrogram* H, char mode[]);

/*
number is in data
якщо number не входить у iнтервал [min_hist, max_hist]:
 1) та mode = 'change' number змінює інтервал [min_hist, max_hist] та додається до певного стовпця;
 2) та mode = 'not_change' number не запусується в Histogram;
якщо number входить у інтервал [min_hist, max_hist]: 
 1) тa mode = 'not_change' number додається то певного стовпця;
 2) та mode = 'change' те ж саме що і mode = 'not_change';
*/
void addbatch(DType data[], size_t dataSize, Histrogram* H, char mode[]);

/*
кількість елементів в гісторгамі
*/
IType num(Histrogram* H);

/*
частота відповідного стовпчика
і - індекс(перший стовпчик має індекс рівний нулю)
*/
IType numHist(Histrogram* H, IType i);

/*
середнє значення гісторгами
*/
DType mean(Histrogram* H);

/*
середнє квадратичне всіх значень в гістограмі
*/
DType dispersion(Histrogram* H);

/*
медіана гісторграми(медіана послідовності всіх елементів гісторгами)
*/
DType median(Histrogram* H);

/*
середнє відхилення (середнє відхилення значень гісторграми від середнього значення гісторграми)
*/
DType dev(Histrogram* H);

/*
середнє квадратичне відхилення значень гістограми
*/
DType dev_squared(Histrogram* H);

/*
центральний емпіричний момент порядка 4
*/
DType centr_empiric_moment4(Histrogram* H);

/*
центральний емпіричний момент порядка 3
*/
DType centr_empiric_moment3(Histrogram* H);

/*
коефіцієнт асиметрії всіх значень гістограми(вибірки)
*/
DType asymmetry(Histrogram* H);

/*
коефіцієнт акцесу всіх значень гістограми
*/
DType access(Histrogram* H);

/*
коефіцієнт варіації - це відношення стандартного відхилення(середнього квалратичного відхилення) до середньої(середнього значення в гістограмі)
*/
DType variance(Histrogram* H);

/*
мода гістограми(стовпчик з найбільшою частотою) виводиться індекс стовпчика
*/
NType fash(Histrogram* H);

/*
присвоює динамічним массивам певний вказівник та робить ці динамічні массиви спроможними до зміни пам'яті (realloc)
*/
void prepare_Histogram(Histrogram* H);

/* 
mode = "first_start" || "not_first_start" || "rewrite_borders"
*/
void update_Histogram(Histrogram* H, char mode[]);

void setMax(DType m, Histrogram* H, char mode[]);

void setMin(DType m, Histrogram* H, char mode[]);

void setM(NType m, Histrogram* H);

/*
mode = "new_Histogram" || "used_Historgam"
*/
void prepare_clean_Histogram(Histrogram* H, IType col_number, DType min_hist, DType max_hist, char mode[]);

/*
якщо мається на увазі ввід не с файлу(с консолі) filename = "not_file", 
в іншому випадку  filename рівний назві файлу в купі з розширенням файлу (".txt", ".dat")
mode = "change" || "not_change"
*/
IType input_numbers_in_Histogram(Histrogram* H, char filename[], char mode[]);

/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType input_Histogram(Histrogram* H, char mode[]);

/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType inputTextFile_Historgam(char* file, Histrogram* H, char mode[]);

/*
mode = "new_Histogram" || "used_Historgam"
mode == "new_Histogram": Histogram H is not after using any functions
mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
*/
IType inputBinaryFile_Histogram(char* file, Histrogram* H, char mode[]);

/*
type = 0 : output numebr in basic double style
type = 1 : output number in scientific style
*/
void output_Histogram(Histrogram H, IType type, IType width, IType precision);

/*
type = 0 : output numebr in basic double style
type = 1 : output number in scientific style
*/
IType outputTextFile_Histogram(char* file, Histrogram H, IType type, IType width, IType precision, char mode[]);

IType outputBinaryFile_Histogram(char* file, Histrogram H);

#endif /* __Histogram__ end */