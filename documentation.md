# Опис алгоритмів та функцій проєкту OMG8

## 1. Ініціалізація структури `initializeOMG8`

```c
OMG8 initializeOMG8(int length){
    OMG8 structure;
    structure.length = length;
    structure.data = (unsigned long long*)malloc(length * sizeof(unsigned long long));
    
    // Ініціалізуємо всі елементи нулями 
    for (int idx = 0; idx < length; idx++)
        structure.data[idx] = 0;
    
    return structure;
}
```

### Алгоритм роботи:
1. Створюємо порожню структуру `OMG8`
2. Встановлюємо довжину структури
3. Виділяємо динамічну пам'ять під масив даних
4. Заповнюємо масив нулями
5. Повертаємо ініціалізовану структуру

**Складність:** O(n), де n - довжина структури

## 2. Кодування структури `encodeStructure`

```c
unsigned char* encodeStructure(OMG8* structure, int* size){
    int len = 0;
    unsigned long long k;
    
    // Обчислення розміру закодованих даних
    for (int i = 0; i < structure->length; i++) {
        k = structure->data[i];
        
        // Спеціальний випадок для нуля
        if (structure->data[i] == 0)
            len++;
        
        // Визначаємо кількість байт для кожного числа
        while (k > 0) {
            k /= 128;
            len++;
        }
    }

    // Виділення пам'яті під закодовані дані
    unsigned char* encodedData = (unsigned char*)malloc(len * sizeof(char));
    int t = 0;

    // Власне кодування
    for (int i = 0; i < structure->length; i++) {
        k = structure->data[i];
        while (1) {
            unsigned char buf = k & 127;  // Беремо молодші 7 біт
            
            if (k < 128) {
                encodedData[t++] = buf;
                break;
            }
            else {
                // Встановлюємо старший біт, щоб позначити continuation byte
                encodedData[t++] = buf + 128;
                k -= buf + 128;
                k /= 128;
            }
        }
    }
    
    *size = len;
    return encodedData;
}
```

### Алгоритм кодування:
1. Підраховуємо необхідну кількість байт для кодування
2. Спеціальна обробка нульових значень
3. Кодування числа частинами по 7 біт
4. Встановлення старшого біту для continuation bytes
5. Повернення масиву закодованих байт

**Особливості**:
- Використовує механізм continuation bytes
- Дозволяє кодувати великі цілі числа
- Економить місце порівняно зі стандартним представленням

## 3. Декодування структури `decodeStructure`

```c
OMG8 decodeStructure(unsigned char* bytes, int size){
    // Визначаємо кількість елементів у вихідній структурі
    int len = 0;
    for (int i = 0; i < size; i++) {
        if ((bytes[i] & 128) == 0)
            len++;
    }

    // Створюємо нову структуру
    OMG8 decodedStructure = initializeOMG8(len);
    
    int t = 0;  // Поточний індекс у структурі
    unsigned long long k = 1;  // Множник для відновлення числа

    // Декодування байт
    for (int i = 0; i < size; i++) {
        decodedStructure.data[t] += (k * bytes[i]);
        k *= 128;

        // Завершення декодування поточного числа
        if ((bytes[i] & 128) == 0) {
            t++;
            k = 1;
        }
    }
    
    return decodedStructure;
}
```

### Алгоритм декодування:
1. Підрахунок кількості елементів
2. Створення нової структури
3. Декодування байт з використанням multiplication
4. Відстеження закінчення чергового числа за допомогою молодшого біта

**Складність:** O(n), де n - кількість байт

## 4. Пошук підструктури `locateSubstructure`

```c
int locateSubstructure(OMG8* primary, OMG8* secondary){
    // Перевірка можливості пошуку
    if (primary->length < secondary->length)
        return -1;

    // Послідовний пошук підструктури
    for (int i = 0; i <= primary->length - secondary->length; i++){
        int found = 1;
        
        // Перевірка збігу на поточній позиції
        for (int j = 0; j < secondary->length; j++){
            if (primary->data[i + j] != secondary->data[j]) {
                found = 0;
                break;
            }
        }
        
        // Повертаємо індекс, якщо знайдено
        if (found) return i;
    }
    
    return -1;  // Підструктура не знайдена
}
```

### Алгоритм пошуку:
1. Перевірка можливості пошуку
2. Послідовний прохід по первинній структурі
3. Перевірка часткового збігу
4. Повернення індексу або -1

**Складність:** O(n*m), де n - довжина первинної структури, m - довжина підструктури

## 5. Конвертація в число `convertToInteger`

```c
long long convertToInteger(OMG8* primary, int base){
    long long result = 0;
    
    // Перетворення чисел у заданій системі числення
    for (int i = 0; i < primary->length; i++){
        // Перевірка коректності цифр
        if (primary->data[i] >= base){
            return -1;  // Некоректне число
        }
        
        // Накопичення результату
        result *= base;
        result += primary->data[i];
    }
    
    return result;
}
```

### Алгоритм конвертації:
1. Ініціалізація результату
2. Перевірка коректності цифр
3. Перетворення послідовності цифр у число
4. Підтримка довільної системи числення

**Складність:** O(n), де n - довжина структури

## Висновок

Представлені алгоритми демонструють гнучкий підхід до роботи з символьними структурами, забезпечуючи ефективне кодування, декодування та маніпуляцію даними.