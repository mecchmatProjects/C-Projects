

//Вітаю! Ви перегядаєте курсову роботу Кучеренка Володимира, студента 2-го курсу комп'ютерної математики.
//Це заголовний файл з описом функцій. Якщо бажаєте перевірити ту чи іншу функцію, запустіть программу та введіть номер завдання.
//Між функціями до різних завданнь вставлений коментар з назвою завдання та його вмістом.

#include <stdio.h>
#include "Enum_header.h"

//Завдання №1 Створити та реалізувати за допомогою перерахування базові функції вводу-виводу
//            для сутності "день тижня", "місяць у році","колір спектру","шахова фігура".

// Функція вводу дня тижня
enum Days inputDay() {
    int choice;

    printf("Input a number of a week (0 - MON, 1 - TUE, ..., 6 - SUN): ");
    scanf("%d", &choice);

    // Перевірка правильності введеного номера
    if (choice < MON || choice > SUN) {
        printf("ERROR input. Input correct number day of week.\n");
        return inputDay();
    }

    return (enum Days)choice;
}

// Функція виводу дня тижня
void outputDay(enum Days day) {
    switch (day) {
        case MON:
            printf("Monday\n");
            break;
        case TUE:
            printf("Tuesday\n");
            break;
        case WED:
            printf("Wednesday\n");
            break;
        case THU:
            printf("Thursday\n");
            break;
        case FRI:
            printf("Friday\n");
            break;
        case SAT:
            printf("Saturday\n");
            break;
        case SUN:
            printf("Sunday\n");
            break;
        default:
            printf("Undefined day of week\n");
    }
}

// Загальна функція вводу-виводу для дня тижня
void days_of_week(){
    enum Days today = inputDay();
    printf("Today is: ");
    outputDay(today);
}

// Визначення функції вводу місяця
enum Months inputMonth() {
    int choice;

    printf("Enter the month number (1 - Jan, 2 - Feb, ..., 12 - Dec): ");
    scanf("%d", &choice);

    // Перевірка правильності введеного номера
    if (choice < JAN + 1 || choice > DEC + 1) {
        printf("Invalid input. Enter a valid month number.\n");
        return inputMonth();
    }

    return (enum Months)(choice - 1);
}

// Визначення функції виводу місяця
void outputMonth(enum Months month) {
    switch (month) {
        case JAN:
            printf("January\n");
            break;
        case FEB:
            printf("February\n");
            break;
        case MAR:
            printf("March\n");
            break;
        case APR:
            printf("April\n");
            break;
        case MAY:
            printf("May\n");
            break;
        case JUN:
            printf("June\n");
            break;
        case JUL:
            printf("July\n");
            break;
        case AUG:
            printf("August\n");
            break;
        case SEP:
            printf("September\n");
            break;
        case OCT:
            printf("October\n");
            break;
        case NOV:
            printf("November\n");
            break;
        case DEC:
            printf("December\n");
            break;
        default:
            printf("Unknown month\n");
    }
}

// Загальна функція вводу-виводу для місяця
void month_of_year() {
    enum Months thisMonth = inputMonth();
    printf("This month is: ");
    outputMonth(thisMonth);
}

// Визначення функції вводу кольору спектру
enum SpectrumColors inputColor() {
    int choice;

    printf("Enter the color number (0 - Red, 1 - Orange, ..., 6 - Violet): ");
    scanf("%d", &choice);

    // Перевірка правильності введеного номера
    if (choice < RED || choice > VIOLET) {
        printf("Invalid input. Enter a valid color number.\n");
        return inputColor();
    }

    return (enum SpectrumColors)choice;
}

// Визначення функції виводу кольору спектру
void outputColor(enum SpectrumColors color) {
    switch (color) {
        case RED:
            printf("Red\n");
            break;
        case ORANGE:
            printf("Orange\n");
            break;
        case YELLOW:
            printf("Yellow\n");
            break;
        case GREEN:
            printf("Green\n");
            break;
        case BLUE:
            printf("Blue\n");
            break;
        case INDIGO:
            printf("Indigo\n");
            break;
        case VIOLET:
            printf("Violet\n");
            break;
        default:
            printf("Unknown color\n");
    }
}

// Загальна функція вводу-виводу для кольору спектру
void color_of_spectrum(){
    enum SpectrumColors thisColor = inputColor();
    printf("This color: ");
    outputColor(thisColor);
}


// Визначення функції вводу шахової фігури
enum ChessPieces inputChessPiece() {
    int choice;

    printf("Enter the chess piece number (0 - King, 1 - Queen, ..., 5 - Pawn): ");
    scanf("%d", &choice);

    // Перевірка правильності введеного номера
    if (choice < KING || choice > PAWN) {
        printf("Invalid input. Enter a valid chess piece number.\n");
        return inputChessPiece();
    }

    return (enum ChessPieces)choice;
}

// Визначення функції виводу шахової фігури
void outputChessPiece(enum ChessPieces piece) {
    switch (piece) {
        case KING:
            printf("King\n");
            break;
        case QUEEN:
            printf("Queen\n");
            break;
        case ROOK:
            printf("Rook\n");
            break;
        case BISHOP:
            printf("Bishop\n");
            break;
        case KNIGHT:
            printf("Knight\n");
            break;
        case PAWN:
            printf("Pawn\n");
            break;
        default:
            printf("Unknown chess piece\n");
    }
}

// Загальна функція вводу-виводу для шахової фігури
void chess_piece(){
    enum ChessPieces thisPiece = inputChessPiece();
    printf("This chess piece: ");
    outputChessPiece(thisPiece);
}


//Завдання №2 Описати тип - структуру Card для карти з колоди для преферансу. Для цього створити перерахування Масть = {Піка, Трефи, Бубна, Чирва}
//            та Ранг = {7,8,9,10, 'Jack','Queen','King','Ace'}. Реалізувати точну функцію beat(Card x, Card y, Масть z),
//            що вказує чи б'є перша карта другу, а третій параметр вказує яка масть є козирною.



// Реалізація функції beat
int beat(struct Card x, struct Card y, enum Suit trump) {
    // Логіка порівняння карт
    if (x.suit == trump && y.suit != trump) {
        return 1;  // x > y, бо x - козир, y - ні
    } else if (x.suit != trump && y.suit == trump) {
        return 0;  // y > x, бо y - козир, x - ні
    } else {
        // Обидві карти або козирі, або не козирі
        if (x.rank > y.rank) {
            return 1;  // x > y за рангом
        } else {
            return 0;  // y > x за рангом або рівні
        }
    }
}

// Реалізація функції конвертації рядка у ранг
enum Rank strToRank(const char* str) {
    if (strcmp(str, "SEVEN") == 0) return SEVEN;
    if (strcmp(str, "EIGHT") == 0) return EIGHT;
    if (strcmp(str, "NINE") == 0) return NINE;
    if (strcmp(str, "TEN") == 0) return TEN;
    if (strcmp(str, "JACK") == 0) return JACK;
    if (strcmp(str, "QUEEN") == 0) return QUEN;
    if (strcmp(str, "KING") == 0) return KINGS;
    if (strcmp(str, "ACE") == 0) return ACE;

    //Якщо ранг не визначено, повертаємо SEVEN
    return SEVEN;
}

// Реалізація функції конвертації рядка у масть
enum Suit strToSuit(const char* str) {
    if (strcmp(str, "SPADES") == 0) return SPADES;
    if (strcmp(str, "CLUBS") == 0) return CLUBS;
    if (strcmp(str, "DIAMONDS") == 0) return DIAMONDS;
    if (strcmp(str, "HEARTS") == 0) return HEARTS;

    //Якщо масть не визначено, повертаємо SPADES
    return SPADES;
}

// Загальна функція вводу-виводу для карт
void card_fighting() {
    // Введення першої карти
    char suitStr[20], rankStr[20];
    printf("Enter the first card (e.g., SPADES KING): ");
    scanf("%s %s", suitStr, rankStr);
    struct Card card1 = {strToSuit(suitStr), strToRank(rankStr)};

    // Введення другої карти
    printf("Enter the second card (e.g., HEARTS SEVEN): ");
    scanf("%s %s", suitStr, rankStr);
    struct Card card2 = {strToSuit(suitStr), strToRank(rankStr)};

    // Введення козирної масті
    printf("Enter the trump suit (e.g., SPADES): ");
    scanf("%s", suitStr);
    enum Suit trump = strToSuit(suitStr);

    // Порівняння кард за допомогою функції beat
    if (beat(card1, card2, trump)) {
        printf("Card 1 beats Card 2\n");
    } else {
        printf("Card 2 beats Card 1\n");
    }
}


//Завдання №3 Створити перелік величин довжини (мм, см, дм, м, км) та реалізувати функцію
//            яка за введеною довжиною  та величиною виміру виводить довжину в метрах.



// Реалізація функції конвертації довжини у метри
double convertToMeter(double length, enum LengthUnit unit) {
    switch (unit) {
        case MILLIMETER:
            return length / 1000.0;
        case CENTIMETER:
            return length / 100.0;
        case DECIMETER:
            return length / 10.0;
        case METER:
            return length;
        case KILOMETER:
            return length * 1000.0;
        default:
            return length;
    }
}

// Загальна функція вводу-виводу для довжини та величини виміру
void lenght_convertation() {
    double length;
    int unit;
    printf("Enter the length: ");
    scanf("%lf", &length);
    printf("Enter the unit (0 - Millimeter, 1 - Centimeter, 2 - Decimeter, 3 - Meter, 4 - Kilometer): ");
    scanf("%d", &unit);

    double result = convertToMeter(length, (enum LengthUnit)unit);
    printf("Length in meters: %lf\n", result);
}


//Завдання №4 Створити перерахування "Відмінок" {ім, бат, дат, ...} та за вказаним відмінком
//            провідмінити слова: програмування, мова, комп'ютер.



// Реалізація функції для провідмінювання слів
void inflectWord(char* word, enum Case grammaticalCase) {
    switch (grammaticalCase) {
        case NOMINATIVE:
            break;
        case GENITIVE:
            strcat(word, "а");
            break;
        case DATIVE:
            strcat(word, "у");
            break;
        case ACCUSATIVE:
            strcat(word, "а");
            break;
        case INSTRUMENTAL:
            strcat(word, "ом");
            break;
        case LOCATIVE:
            strcat(word, "і");
            break;
        case VOCATIVE:
            strcat(word, "е");
            break;
    }
}

//Зауваження!!! У мене не ідентифікується українські символи тому я не впевнений у коректності даної функції
// Загальна функція вводу-виводу для відмінювання слів
void inflect_of_Word() {

    char programming[] = "програмування";
    char language[] = "мова";
    char computer[] = "комп'ютер";


    inflectWord(programming, GENITIVE);
    inflectWord(language, LOCATIVE);
    inflectWord(computer, ACCUSATIVE);

    printf("Провідмінені слова:\n");
    printf("Програмування: %s\n", programming);
    printf("Мова: %s\n", language);
    printf("Комп'ютер: %s\n", computer);

}


//Завдання №5 Створити перерахування "Голосні", яке містить всі англійські голосні
//            та за допомогою цього типу визначити яка кількість складів в даному речені
//            (вважаючи, що склад містить лише одну голосну).


// Реалізація функції для підрахунку кількості складів у реченні
int countSyllables(const char* sentence) {
    int syllableCount = 0;

    // Перебір символів у реченні
    for (int i = 0; sentence[i] != '\0'; i++) {
        char currentChar = toupper(sentence[i]);

        // Перевірка чи є символ голосною
        switch (currentChar) {
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                syllableCount++;
                break;
            default:
                break;
        }
    }

    return syllableCount;
}

// Загальна функція вводу-виводу для підрахунку кількості складів
void counter_of_syllables() {

    char sentence[100];
    printf("Enter a sentence: ");
    scanf("%s", sentence);

    int syllables = countSyllables(sentence);
    printf("Number of syllables: %d\n", syllables);
}


//Завдання №6 Створити перерахування Course = {N,S,W,E} та Order = {Fowrard, Back, Left, Right} .
//            В нас задано початковий курс корабля та масив команд як він рухався. Вивести кінцевий напрямок корабля.
//            Ввести також швидкість судна та масив дійсних чисел, що відповідає часу - скільки воно рухалося за даним курсом
//            та за допомогою цих даних визначити на яку абсолютну відстань від початкової змістився корабель.



// Реалізація функції для визначення кінцевого напрямку
enum Course determineFinalCourse(enum Course initialCourse, enum Order* orders, int ordersCount) {
    // Логіка визначення кінцевого напрямку за допомогою команд
    enum Course finalCourse = initialCourse;
    for (int i = 0; i < ordersCount; i++) {
        switch (orders[i]) {
            case FORWARD:
                break;
            case BACK:
                finalCourse = (finalCourse + 2) % 4;
                break;
            case LEFT:
                finalCourse = (finalCourse + 3) % 4;
                break;
            case RIGHT:
                finalCourse = (finalCourse + 1) % 4;
                break;
        }
    }
    return finalCourse;
}

// Реалізація функції для визначення абсолютної відстані
double calculateAbsoluteDistance(double speed, double* durations, int durationsCount) {
    double totalDistance = 0.0;
    for (int i = 0; i < durationsCount; i++) {
        totalDistance += speed * durations[i];
    }
    return totalDistance;
}

// Загальна функція вводу-виводу для визначення курсу корабля і т.п.
void way_of_boat() {
    // Початковий курс корабля
    enum Course initialCourse = EAST;

    // Масив команд корабля
    enum Order orders[] = {FORWARD, LEFT, RIGHT, BACK, FORWARD};

    // Визначення кінцевого напрямку
    enum Course finalCourse = determineFinalCourse(initialCourse, orders, sizeof(orders) / sizeof(orders[0]));

    // Вивід кінцевого напрямку
    printf("Final course of boat: ");
    switch (finalCourse) {
        case NORTH:
            printf("Nprth\n");
            break;
        case SOUTH:
            printf("South\n");
            break;
        case WEST:
            printf("West\n");
            break;
        case EAST:
            printf("East\n");
            break;
    }

    // Швидкість корабля та масив дійсних чисел - час руху відповідно до команд
    double speed = 10.0;                              // швидкість в м/с
    double durations[] = {2.5, 1.0, 0.5, 3.0, 2.0};   // час руху в секундах

    // Визначення абсолютної відстані
    double absoluteDistance = calculateAbsoluteDistance(speed, durations, sizeof(durations) / sizeof(durations[0]));

    // Виведення абсолютної відстані
    printf("Absolute distance: %lf meters\n", absoluteDistance);
}
