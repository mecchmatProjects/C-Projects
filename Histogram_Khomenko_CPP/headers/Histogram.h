#ifndef __Histogram__
#define __Histogram__

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cmath>

#include "../headers/common.h"
#include "His_col.h"

class Histrogram
{   
    public:
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

        void setM(NType m);

        /*
        mode = 'change' || 'not_change'
        */
        void setMin(DType m, const char mode[]);

        /*
        mode = 'change' || 'not_change'
        */
        void setMax(DType m, const char mode[]);

        /*
        присвоює динамічним массивам(всередині Гістограми) певний вказівник та робить ці динамічні массиви спроможними до зміни пам'яті (realloc)
        */
        void prepare_Histogram();

        /* 
        mode = "first_start" || "not_first_start" || "rewrite_borders"
        */
        void  update_Histogram(const char mode[]);

        /*
        якщо number не входить у iнтервал [min_hist, max_hist]:
        1) та mode = 'change' number змінює інтервал [min_hist, max_hist] та додається до певного стовпця;
        2) та mode = 'not_change' number не запусується в Histogram;
        якщо number входить у інтервал [min_hist, max_hist]: 
        1) тa mode = 'not_change' number додається то певного стовпця;
        2) та mode = 'change' те ж саме що і mode = 'not_change';
        */
        void addNumber(DType number, const char mode[]);

        /*
        number is in data
        якщо number не входить у iнтервал [min_hist, max_hist]:
        1) та mode = 'change' number змінює інтервал [min_hist, max_hist] та додається до певного стовпця;
        2) та mode = 'not_change' number не запусується в Histogram;
        якщо number входить у інтервал [min_hist, max_hist]: 
        1) тa mode = 'not_change' number додається то певного стовпця;
        2) та mode = 'change' те ж саме що і mode = 'not_change';
        */
        void addbatch(DType data[], size_t dataSize, const char mode[]);

        /*
        mode = "new_Histogram" || "used_Historgam"
        */
        void prepare_clean_Histogram(IType col_number, DType min_hist, DType max_hist, const char mode[]);

        /*
        якщо мається на увазі ввід не с файлу(с консолі) filename = "not_file", 
        в іншому випадку  filename рівний назві файлу в купі з розширенням файлу (".txt", ".dat")
        mode = "change" || "not_change"
        */
        IType input_numbers_in_Histogram(const char filename[], const char mode[]);

        /*        
        mode = "new_Histogram" || "used_Historgam"
        mode == "new_Histogram": Histogram H is not after using any functions
        mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
        */
        IType input_Histogram(const char mode[]);

        /*
        mode = "new_Histogram" || "used_Historgam"
        mode == "new_Histogram": Histogram H is not after using any functions
        mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
        */
        IType inputTextFile_Historgam(const char* file, const char mode[]);

        /*
        mode = "new_Histogram" || "used_Historgam"
        mode == "new_Histogram": Histogram H is not after using any functions
        mode == "used_Histogram": Histogram H have some elements and is after using function 'update_Histogram' with mode == "first_start"
        */
        IType inputBinaryFile_Histogram(const char* file, const char mode[]);

        /*
        type = 0 : output numebr in basic double style
        type = 1 : output number in scientific style
        */
        void output_Histogram(IType type, IType width, IType precision);

        /*
        type = 0 : output numebr in basic double style
        type = 1 : output number in scientific style
        */
        IType outputTextFile_Histogram(const char* file, IType type, IType width, IType precision, const char mode[]);

        IType outputBinaryFile_Histogram(const char* file);

        /*
        кількість елементів в гісторгамі
        */
        IType num();

        /*
        частота відповідного стовпчика
        і - індекс(перший стовпчик має індекс рівний нулю)
        */
        IType numHist(IType i);

        /*
        середнє значення гісторгами
        */
        DType mean();

        /*
        середнє квадратичне всіх значень в гістограмі
        */
        DType dispersion();

        /*
        медіана гісторграми(медіана послідовності всіх елементів гісторгами)
        */
        DType median();

        /*
        середнє відхилення (середнє відхилення значень гісторграми від середнього значення гісторграми)
        */
        DType dev();

        /*
        середнє квадратичне відхилення значень гістограми
        */
        DType dev_squared();

        /*
        центральний емпіричний момент порядка 4
        */
        DType centr_empiric_moment4();

        /*
        центральний емпіричний момент порядка 3
        */
        DType centr_empiric_moment3();

        /*
        коефіцієнт асиметрії всіх значень гістограми(вибірки)
        */
        DType asymmetry();

        /*
        коефіцієнт акцесу всіх значень гістограми
        */
        DType access();

        /*
        коефіцієнт варіації - це відношення стандартного відхилення(середнього квалратичного відхилення) до середньої(середнього значення в гістограмі)
        */
        DType variance();

        /*
        мода гістограми(стовпчик з найбільшою частотою) виводиться індекс стовпчика
        */
        NType fash();

};

#endif /* __Histogram__ end */