

//Вітаю! Ви перегядаєте курсову роботу Кучеренка Володимира, студента 2-го курсу комп'ютерної математики.
//Це header файл з оголощенням функцій. Якщо бажаєте перевірити ту чи іншу функцію, запустіть программу та введіть номер завдання.
//Між описами функцій до різних завданнь вставлений коментар з назвою завдання та його вмістом.

#ifndef HEADER_H
#define HEADER_H

//Завдання №1 Створити та реалізувати за допомогою перерахування базові функції вводу-виводу
//            для сутності "день тижня", "місяць у році","колір спектру","шахова фігура".

// Оголошення перерахування для днів тижня
enum Days {
    MON, TUE, WED, THU, FRI, SAT, SUN
};

// Оголошення функцій
enum Days inputDay();
void outputDay(enum Days day);
void days_of_week();


// Оголошення перерахування для місяців
enum Months {
    JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

// Оголошення функцій
enum Months inputMonth();
void outputMonth(enum Months month);
void month_of_year();


// Оголошення перерахування для кольорів спектру
enum SpectrumColors {
    RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET
};

// Оголошення функцій
enum SpectrumColors inputColor();
void outputColor(enum SpectrumColors color);
void color_of_spectrum();


// Оголошення перерахування для шахових фігур
enum ChessPieces {
    KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN
};

// Оголошення функцій
enum ChessPieces inputChessPiece();
void outputChessPiece(enum ChessPieces piece);
void chess_piece();


//Завдання №2 Описати тип - структуру Card для карти з колоди для преферансу. Для цього створити перерахування Масть = {Піка, Трефи, Бубна, Чирва}
//            та Ранг = {7,8,9,10, 'Jack','Queen','King','Ace'}. Реалізувати точну функцію beat(Card x, Card y, Масть z),
//            що вказує чи б'є перша карта другу, а третій параметр вказує яка масть є козирною.


// Оголошення перерахування для мастей
enum Suit {
    SPADES, CLUBS, DIAMONDS, HEARTS
};

// Оголошення перерахування для рангів
enum Rank {
    SEVEN, EIGHT, NINE, TEN, JACK, QUEN, KINGS, ACE
};

// Структура для представлення карти
struct Card {
    enum Suit suit;
    enum Rank rank;
};

// Оголошення функції beat and card_fighting
int beat(struct Card x, struct Card y, enum Suit trump);
void card_fighting();

// Оголошення функцій конвертації рядків у перерахування
enum Rank strToRank(const char* str);
enum Suit strToSuit(const char* str);


//Завдання №3 Створити перелік величин довжини (мм, см, дм, м, км) та реалізувати функцію
//            яка за введеною довжиною  та величиною виміру виводить довжину в метрах.


// Оголошення перерахування для величин довжини
enum LengthUnit {
    MILLIMETER, CENTIMETER, DECIMETER, METER, KILOMETER
};

// Сигнатура функції для конвертації довжини у метри
double convertToMeter(double length, enum LengthUnit unit);
void lenght_convertation();


//Завдання №4 Створити перерахування "Відмінок" {ім, бат, дат, ...} та за вказаним відмінком
//            провідмінити слова: програмування, мова, комп'ютер.


// Оголошення перерахування для відмінків
enum Case {
    NOMINATIVE, GENITIVE, DATIVE, ACCUSATIVE, INSTRUMENTAL, LOCATIVE, VOCATIVE
};

// Сигнатура функції для провідмінювання слів
void inflectWord(char* word, enum Case grammaticalCase);
void inflect_of_Word();


//Завдання №5 Створити перерахування "Голосні", яке містить всі англійські голосні
//            та за допомогою цього типу визначити яка кількість складів в даному речені
//            (вважаючи, що склад містить лише одну голосну).


// Оголошення перерахування для голосних
enum Vowels {
    A, E, I, O, U
};

// Сигнатура функції для підрахунку кількості складів у реченні
int countSyllables(const char* sentence);
void counter_of_syllables();


//Завдання №6 Створити перерахування Course = {N,S,W,E} та Order = {Fowrard, Back, Left, Right} .
//            В нас задано початковий курс корабля та масив команд як він рухався. Вивести кінцевий напрямок корабля.
//            Ввести також швидкість судна та масив дійсних чисел, що відповідає часу - скільки воно рухалося за даним курсом
//            та за допомогою цих даних визначити на яку абсолютну відстань від початкової змістився корабель.


// Оголошення перерахування для курсу
enum Course {
    NORTH, SOUTH, WEST, EAST
};

// Оголошення перерахування для команд
enum Order {
    FORWARD, BACK, LEFT, RIGHT
};

// Сигнатура функції для визначення кінцевого напрямку
enum Course determineFinalCourse(enum Course initialCourse, enum Order* orders, int ordersCount);

// Сигнатура функції для визначення абсолютної відстані
double calculateAbsoluteDistance(double speed, double* durations, int durationsCount);
void way_of_boat();


#endif
