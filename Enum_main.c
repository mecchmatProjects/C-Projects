

//Вітаю! Ви перегядаєте курсову роботу Кучеренка Володимира, студента 2-го курсу комп'ютерної математики.
//Це головний файл з викликом функцій. Якщо бажаєте перевірити ту чи іншу функцію, запустіть программу та введіть номер завдання.


#include <stdio.h>
#include "Enum_header.h"


int main() {
    int number,letter;
    printf("Number of task:");
    scanf("%d", &number);

    switch (number) {
        case 1:
            printf("Letter of task (a=1, c=2, b=3, d=4): ");
            scanf("%d", &letter);
            switch (letter) {
                case 1:
                    days_of_week();
                    break;
                case 2:
                    month_of_year();
                    break;
                case 3:
                    color_of_spectrum();
                    break;
                case 4:
                    chess_piece();
                    break;
                default:
                printf("There is no such task\n");
                }
                break;
        case 2:
            card_fighting();
            break;
        case 3:
            lenght_convertation();
            break;
        case 4:
            inflect_of_Word();
            break;
        case 5:
            counter_of_syllables();
            break;
        case 6:
            way_of_boat();
            break;
        default:
            printf("There is no such task\n");
    }

    return 0;
}








