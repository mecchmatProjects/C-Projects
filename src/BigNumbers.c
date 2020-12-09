#include "../headers/BigNumbers.h"

const char GLOBAL_NUMBERS[] = "0123456789abcdefghijklmnopqrstuvwxyz";



INT binPow(INT a, SMALL_INT n) {
    INT res = 1;
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}


SMALL_INT convert2int(SYMBOL numb) {
    SMALL_INT res = -1;
    // find the given character in GLOBAL_NUMBERS
    for (SMALL_INT itr = 0; itr < 36; ++itr){
        if (GLOBAL_NUMBERS[itr] == numb){
            res = itr;
            break;
        }
    }
    return res;
}

BigInteger *fromInt(ELEM_TYPE num) {
    ELEM_TYPE base = binPow(10, ELEM_SIZE_NUM);    // for checking if the given number won't overflow
    ELEM_TYPE abs_num = num < 0 ? -num : num;      // absolute value
    BigInteger *res = (BigInteger*) malloc(sizeof(BigInteger));
    res->sign = num < 0 ? -1 : 1;    // sign

    // if number less than the base - just write it at the begining of the array
    if (abs_num < base){
        res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE));
        res->body[0] = num;
        res->intsAmount = 1;

    // else split it on the 2 elements of array
    } else {
        res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * 2);
        res->body[0] = abs_num % base;
        res->body[1] = abs_num / base;
        res->intsAmount = 2;
    }
    return res;
}

BigInteger *fromChars(const SYMBOL *number, SIZE size) {
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
    SMALL_INT start = 0;   // start of number (0 if there is no '-' and 1 otherwise)
    if (number[0] == '-') {    // check if the first char == '-'
        res->sign = -1;
        res->intsAmount = (size-1) / ELEM_SIZE_NUM + 1;
        start = 1;
    } else {
        res->sign = 1;
        res->intsAmount = size / ELEM_SIZE_NUM + 1;
    }

    // create array of size/ELEM_SIZE_NUM elements - result BigInteger
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * (res->intsAmount));
    for (SIZE itr = 0; itr < res->intsAmount; itr++){
        res->body[itr] = 0;
    }

    SMALL_INT tmp = 0;
    SIZE elemIndex = 0;

    // read each of ELEM_SIZE_NUM digits starting at the end of number and write it
    // to array
    for (SMALL_INT itr = size-1; itr >= start; --itr){
        for (SMALL_INT itr2 = 0; itr2 < ELEM_SIZE_NUM; ++itr2){
            SYMBOL tmp_char = number[itr];
            tmp = atoi(&tmp_char);
            tmp *= (SMALL_INT ) binPow(10, itr2);
            res->body[elemIndex] += tmp;
            --itr;
            if (itr < start) break;
        }
        if (itr == -1) break;
        ++itr;
        ++elemIndex;
    }
    return res;
}


BigInteger *fromOtherChars(const SYMBOL *number, SIZE size, SMALL_INT base) {
    BigInteger *res = fromInt(0);
    SMALL_INT start = 0;              // start index of number digits
    if (number[start] == '-'){  // check if the first char is '-'
        res->sign = -1;
        start = 1;
    }
    if (base > 36 || base < 2){   // check the correctness of the given base
        exit(1);
    }
    BigInteger *tmpAdd;    // i-th char * base^i
    BigInteger *tmpRes;    // tmpAdd + res on the i-th step of cycle
    BigInteger *tmpMul;    // i-th char

    BigInteger *multiplier = fromInt(1);     // base^i
    BigInteger *bigBase = fromInt(base);     // BigInteger(base)
    SMALL_INT tmp_num;

    // read each char of given number, multiply it by base^i and add to the result number
    for (SIZE itr = size-1; itr >= start; --itr){
        tmp_num = convert2int(number[itr]);
        if (tmp_num == -1 || tmp_num >= base){
            exit(1);
        }

        tmpMul = fromInt(tmp_num);            // temporary results of operations
        tmpAdd = mul(tmpMul, multiplier);
        tmpRes = add(res, tmpAdd);

        free(res->body);                      // free memory of temporary results
        free(res);
        free(tmpAdd->body);
        free(tmpAdd);
        free(tmpMul->body);
        free(tmpMul);

        res = tmpRes;                         // update result

        tmpMul = mul(multiplier, bigBase);    // increase 10^i
        free(multiplier->body);
        free(multiplier);
        multiplier = tmpMul;
        if (itr == 0) break;
    }
    free(multiplier->body);    // free memory of local variables
    free(multiplier);
    free(bigBase->body);
    free(bigBase);
    return res;
}


void print(const BigInteger *a) {
    fprint(stdout, a);
}


void fprint(FILE *file, const BigInteger *a){
    if (a->sign == -1){
        fprintf(file, "-");
    }
    SIZE start = a->intsAmount -1;

    // miss the leading zero elements if given BigInteger hasn't been normalized
    while (a->body[start] == 0 && start > 0) start--;
    fprintf(file, "%ld", a->body[start]);    // print the last element without zero separators
    if (start > 0) {

        // print other elements with zero separators
        for (SMALL_INT itr = start - 1; itr >= 0; itr--)
            fprintf(file, "%08ld", a->body[itr]);
    }
    fprintf(file, "\n");
}

void delRedundantZeros(BigInteger *a) {

    // decrease size while the leading element is zero
    while (a->body[a->intsAmount-1] == 0 && a->intsAmount > 1) a->intsAmount--;

    // prepare new memory for BigInteger and move values there
    ELEM_TYPE *res = (ELEM_TYPE * ) malloc(sizeof(ELEM_TYPE) * a->intsAmount);
    for (SIZE itr = 0; itr < a->intsAmount; itr++) {
        res[itr] = a->body[itr];
    }
    free(a->body);
    a->body = res;
}


BigInteger *add(const BigInteger *a, const BigInteger *b) {

    // create the local absolute values of given parameters
    BigInteger *tmp_a = copy(a);
    tmp_a->sign = 1;
    BigInteger *tmp_b = copy(b);
    tmp_b->sign = 1;
    BigInteger *res;

    // do different operation for each of signs combinations
    if (a->sign == 1 && b->sign == 1) res = _add(tmp_a, tmp_b);
    else if (a->sign == 1 && b->sign == -1) res = sub(tmp_a, tmp_b);
    else if (a->sign == -1 && b->sign == 1) res = sub(tmp_b, tmp_a);
    else {
        res = _add(tmp_a, tmp_b);
        res->sign = -1;
    }

    // free the memory of temporary variables
    free(tmp_a->body);
    free(tmp_b->body);
    free(tmp_a);
    free(tmp_b);
    delRedundantZeros(res);   // prepare the result
    return res;
}


BigInteger *_add(const BigInteger *a, const BigInteger *b) {

    SMALL_INT carry = 0;
    SMALL_INT base = binPow(10, ELEM_SIZE_NUM);

    // create the result BigInteger of length equal to max of lengths a and b
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
    res->sign = 1;
    res->intsAmount = (MAX(a->intsAmount, b->intsAmount)) + 1;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE i = 0; i < res->intsAmount; ++i){   // write zeros
        res->body[i] = 0;
    }

    // doing the school addition
    for (SIZE i = 0; i < res->intsAmount || carry; ++i){
        res->body[i] = (i < a->intsAmount ? a->body[i] : 0) + carry + (i < b->intsAmount ? b->body[i] : 0);
        carry = res->body[i] >= base;
        if (carry) res->body[i] -= base;
    }
    return res;
}


BigInteger *sub(const BigInteger *a, const BigInteger *b) {

    // create local absolute values of given parameters
    BigInteger *tmp_a = copy(a);
    BigInteger *tmp_b = copy(b);
    tmp_a->sign = 1;
    tmp_b->sign = 1;

    BigInteger *res;
    SMALL_INT rel = absRelation(tmp_a, tmp_b);

    // do different operations for each of possible situations
    if (a->sign == 1 && b->sign == 1 && rel >= 0) res = _sub(tmp_a, tmp_b);

    else if (a->sign == 1 && b->sign == 1 && rel == -1){
        res = _sub(tmp_b, tmp_a);
        res->sign = -1;
    }
    else if (a->sign == -1 && b->sign == 1){
        res = _add(tmp_a, tmp_b);
        res->sign = -1;
    }
    else if (a->sign == 1 && b->sign == -1) res = _add(tmp_a, tmp_b);

    else {
        res = sub(b, a);
    }

    // free the memory of temporary variables
    free(tmp_a->body);
    free(tmp_b->body);
    free(tmp_a);
    free(tmp_b);
    delRedundantZeros(res);  // prepare the result
    return res;
}


BigInteger *_sub(const BigInteger *a, const BigInteger *b) {

    SMALL_INT carry = 0;
    SMALL_INT base = binPow(10, ELEM_SIZE_NUM);

    // create the result BigInteger of length equal to max of lengths a and b
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
    res->sign = 1;
    res->intsAmount = MAX(a->intsAmount, b->intsAmount);
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE i = 0; i< res->intsAmount; ++i){
        res->body[i] = 0;
    }

    // doing the school subtraction
    for (SIZE i = 0; i < a->intsAmount || carry; i++){
        res->body[i] = a->body[i] - carry - (i < b->intsAmount ? b->body[i] : 0);
        carry = res->body[i] < 0;
        if (carry) res->body[i] += base;
    }
    while (res->intsAmount > 1 && res->body[res->intsAmount-1] == 0){
        res->intsAmount--;
    }
    delRedundantZeros(res);
    return res;
}



void normalize(BigInteger *n) {

    ELEM_TYPE base = binPow(10, ELEM_SIZE_NUM);

    // recompute each of element adding the overflow remainders to the next element
    for (SIZE i = 0; i < n->intsAmount; ++i) {
        n->body[i + 1] += n->body[i] / base;

        n->body[i] %= base;
        if (n->body[i] < 0) n->body[i] = base - n->body[i];
    }
}


void extendBigInteger(BigInteger *x, SIZE n) {
    if (n & 1){    // check if n is odd
        n++;
    }
    if (n >= x->intsAmount){

        // create the new BigInteger and rewrite the values there
        ELEM_TYPE *new_array = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * n);
        for (SIZE itr = 0; itr < n; itr++){
            if (itr < x->intsAmount){
                new_array[itr] = x->body[itr];
            } else {
                new_array[itr] = 0;   // adding the leading zeros
            }
        }
        x->intsAmount = n;
        free(x->body);
        x->body = new_array;
    }
}


BigInteger *mul(const BigInteger *X, const BigInteger *Y) {

    // create local absolute values of given parameters
    BigInteger *tmp_X = copy(X);
    BigInteger *tmp_Y = copy(Y);
    tmp_X->sign = 1;
    tmp_Y->sign = 1;

    // compute the absolute value of multiplication
    BigInteger *res = karatsuba_mul(tmp_X, tmp_Y);
    normalize(res);
    delRedundantZeros(res);           // prepare the result
    res->sign = X->sign * Y->sign;    // compute the sign

    // free the memory of temporary variables
    free(tmp_X->body);
    free(tmp_Y->body);
    free(tmp_X);
    free(tmp_Y);
    return res;
}


BigInteger *karatsuba_mul(BigInteger *X, BigInteger *Y) {

    SIZE n = MAX(X->intsAmount, Y->intsAmount);  // extend X and Y to make the same even length
    if (n > 1){
        extendBigInteger(X, n);
        extendBigInteger(Y, n);
    }

    // Preparing the result BigInteger
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
    res->sign = 1;
    res->intsAmount = X->intsAmount * 2;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE itr = 0; itr < res->intsAmount; itr++){
        res->body[itr] = 0;
    }

    // If integers small - doing built-in multiplication
    if (X->intsAmount == 1){
        res->body[0] = X->body[0] * Y->body[0];
        return res;
    }

    // split the numbers on 2 pieces
    SIZE k = X->intsAmount / 2;
    BigInteger *Xr = (BigInteger *) malloc(sizeof(BigInteger));
    BigInteger *Xl = (BigInteger *) malloc(sizeof(BigInteger));
    BigInteger *Yr = (BigInteger *) malloc(sizeof(BigInteger));
    BigInteger *Yl = (BigInteger *) malloc(sizeof(BigInteger));

    Xr->intsAmount = Yr->intsAmount = k;
    Xl->intsAmount = Yl->intsAmount = X->intsAmount - k;
    Xr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xr->intsAmount);
    Xl->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xl->intsAmount);
    Yr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Yr->intsAmount);
    Yl->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Yl->intsAmount);
    for (SIZE itr = 0; itr < X->intsAmount; ++itr){
        if (itr < k){
            Xr->body[itr] = X->body[itr];
            Yr->body[itr] = Y->body[itr];
        } else {
            Xl->body[itr - k] = X->body[itr];
            Yl->body[itr - k] = Y->body[itr];
        }
    }

    // do recursively multiplication to each of them
    BigInteger *P1 = karatsuba_mul(Xl, Yl);
    BigInteger *P2 = karatsuba_mul(Xr, Yr);

    // find the sum of pieces (non-normalized, so don't use the add(BigInteger, BigInteger)
    BigInteger *Xlr = (BigInteger *) malloc(sizeof(BigInteger));
    BigInteger *Ylr = (BigInteger *) malloc(sizeof(BigInteger));
    Xlr->intsAmount = Ylr->intsAmount = Xr->intsAmount;
    Xlr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xlr->intsAmount);
    Ylr->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * Xlr->intsAmount);
    for (SIZE itr = 0; itr < Xlr->intsAmount; itr++){
        Xlr->body[itr] = Xl->body[itr] + Xr->body[itr];
        Ylr->body[itr] = Yl->body[itr] + Yr->body[itr];
    }

    // do recursively multiplication to the sums
    BigInteger *P3 = karatsuba_mul(Xlr, Ylr);

    // compute the final non-normalized sum
    for (SIZE itr = 0; itr < X->intsAmount; ++itr){
        P3->body[itr] -= P2->body[itr] + P1->body[itr];
        res->body[itr] = P2->body[itr];
    }
    for (SIZE itr = X->intsAmount; itr < 2 * X->intsAmount; ++itr){
        res->body[itr] = P1->body[itr - X->intsAmount];
    }
    for (SIZE itr = k; itr < X->intsAmount + k; ++itr){
        res->body[itr] += P3->body[itr - k];
    }

    // free the memory of temporary variables
    free(P1->body);
    free(P2->body);
    free(P3->body);
    free(Xl->body);
    free(Xr->body);
    free(Yr->body);
    free(Yl->body);
    free(Xlr->body);
    free(Ylr->body);

    free(P1);
    free(P2);
    free(P3);
    free(Xl);
    free(Xr);
    free(Yr);
    free(Yl);
    free(Xlr);
    free(Ylr);

    return res;
}


BigInteger *copy(const BigInteger *a) {

    // create new BigInteger and copy all the values
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
    res->sign = a->sign;
    res->intsAmount = a->intsAmount;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);
    for (SIZE itr = 0; itr < res->intsAmount; ++itr){
        res->body[itr] = a->body[itr];
    }
    return res;
}

SMALL_INT absRelation(BigInteger *a, BigInteger *b) {
    delRedundantZeros(a);    // prepare parameters
    delRedundantZeros(b);
    normalize(a);
    normalize(b);

    // if numbers have different lengths answer is obvious
    if (a->intsAmount > b->intsAmount) return 1;
    else if (a->intsAmount < b->intsAmount) return -1;

    // else call the recursive checking
    else return _absRelation(a, b, a->intsAmount-1);
}

SMALL_INT _absRelation(const BigInteger *a, const BigInteger *b, SIZE last_index) {

    // recursively check i-th elements of BigIntegers
    if (a->body[last_index] > b->body[last_index]) return 1;
    else if (a->body[last_index] < b->body[last_index]) return -1;
    else if (last_index == 0) return 0;

    // if its equal - continue while index != 0
    else return _absRelation(a, b, last_index - 1);
}


void shiftRight(BigInteger *number) {

    delRedundantZeros(number);                         // prepare parameter
    extendBigInteger(number, number->intsAmount+1);    // increase memory for array

    // move values
    for (SIZE itr = number->intsAmount-1; itr > 0; --itr){
        number->body[itr] = number->body[itr-1];
    }
    number->body[0] = 0;
}


BigInteger *divide(const BigInteger *X, const BigInteger *Y) {

    // check division by zero
    if (Y->intsAmount == 1 && Y->body[0] == 0){
        exit(1);
    }
    BigInteger *tmp_y = copy(Y);    // local mutable copy
    tmp_y->sign = 1;

    // prepare the result
    BigInteger *res = (BigInteger *) malloc(sizeof(BigInteger));
    res->sign = 1;
    res->intsAmount = X->intsAmount;
    res->body = (ELEM_TYPE *) malloc(sizeof(ELEM_TYPE) * res->intsAmount);

    // remainder at i-th step of school algorithm
    BigInteger *cur = fromInt(0);
    for (SIZE i = X->intsAmount-1; i >= 0; --i){
        shiftRight(cur);
        cur->body[0] = X->body[i];   // prepare to the i-th step
        delRedundantZeros(cur);

        // find the quotient using binary search
        SMALL_INT x = 0, l = 0, r = binPow(10, ELEM_SIZE_NUM);
        while (l <= r){
            SMALL_INT m = (l + r) / 2;
            BigInteger *tmp_m = fromInt(m);
            BigInteger *tmp = mul(tmp_y, tmp_m);
            if (absRelation(tmp, cur) <= 0){
                x = m;
                l = m + 1;
            } else r = m - 1;

            // free the memory of temporary variables
            free(tmp->body);
            free(tmp);
            free(tmp_m->body);
            free(tmp_m);
        }
        // adding quotient to result
        res->body[i] = x;

        // prepare cur to the next step
        BigInteger *tmp_x = fromInt(x);
        BigInteger *tmp_cur = mul(tmp_y, tmp_x);
        BigInteger *tmp_cur2 = sub(cur, tmp_cur);
        free(cur->body);
        free(cur);                // free the memory of temporary variables
        cur = tmp_cur2;
        free(tmp_cur->body);
        free(tmp_cur);
        free(tmp_x->body);
        free(tmp_x);
        if (i == 0){
            break;
        }
    }
    free(tmp_y->body);
    free(tmp_y);

    // compute the sign
    res->sign = X->sign * Y->sign;

    // check the correctness of division of numbers with different signs
    if (res->sign == -1 && !(cur->intsAmount == 1 && cur->body[0] == 0)){
        res->body[0] += 1;    // must add 1 guided by c rules of integer division
        normalize(res);       // for example -11 / 3 == -4; 11 / 3 == 3
    }
    delRedundantZeros(res);
    return res;
}


BigInteger *gcd(const BigInteger *a, const BigInteger *b) {

    // local absolute values of parameters
    BigInteger *tmp_a = copy(a);
    tmp_a->sign = 1;
    BigInteger *tmp_b = copy(b);
    tmp_b->sign = 1;

    // iterative algorithm of computing gcd
    while (!(tmp_b->intsAmount == 1 && tmp_b->body[0] == 0)){
        BigInteger *q = divide(tmp_a, tmp_b);
        BigInteger *tmp = mul(q, tmp_b);
        BigInteger *remainder = sub(tmp_a, tmp);

        free(q->body);
        free(q);
        free(tmp->body);   // free the memory of temporary variables
        free(tmp);
        free(tmp_a->body);
        free(tmp_a);

        tmp_a = tmp_b;
        tmp_b = remainder;
    }
    return tmp_a;
}


BigInteger *lcm(const BigInteger *a, const BigInteger *b) {

    // lcm(a, b) = a * b / gcd(a, b)
    BigInteger *tmp = mul(a, b);
    BigInteger *_gcd = gcd(a, b);
    BigInteger *res = divide(tmp, _gcd);
    res->sign = a->sign * b->sign;
    free(tmp->body);
    free(tmp);
    free(_gcd->body);
    free(_gcd);
    return res;
}


BigInteger *readBigInt(FILE *input) {
    SYMBOL *number = (SYMBOL *) malloc(sizeof(char) * 1000);
    fgets(number, 1000, input);
    SIZE size = 0;
    while ((number[size] != '\n' && number[size] != ' ') && size < 1000) size++;
    BigInteger *res = fromChars(number, size);
    free(number);
    return res;
}

BigInteger *readAnyBigInt(SMALL_INT base, FILE *input) {
    SYMBOL *number = (SYMBOL *) malloc(sizeof(char) * 1000);
    fgets(number, 1000, input);
    SIZE size = 0;
    while ((number[size] != '\n' && number[size] != ' ') && size < 1000) size++;
    BigInteger *res = fromOtherChars(number, size, base);
    free(number);
    return res;
}

BigInteger *inputAnyBigInt(SMALL_INT base) {
    return readAnyBigInt(base, stdin);
}

BigInteger *inputBigInt() {
    return readBigInt(stdin);
}

BigInteger **xgcd(const BigInteger *a, const BigInteger *b) {
    // local absolute values of parameters
    BigInteger *tmp_a = copy(a);
    tmp_a->sign = 1;
    BigInteger *tmp_b = copy(b);
    tmp_b->sign = 1;

    // if b > a - swap each other
    if (absRelation(tmp_a, tmp_b) == -1) {
        BigInteger **res = _xgcdHelper(tmp_b, tmp_a);
        BigInteger *tmp = res[0];
        res[0] = res[1];
        res[1] = tmp;
        return res;
    } else {
        return _xgcdHelper(tmp_a, tmp_b);
    }
}


BigInteger **_xgcdHelper(BigInteger *a, BigInteger *b) {

    // prepare the result - array of BigIntegers
    BigInteger **resArray = (BigInteger **) malloc(sizeof(BigInteger *) * 3);

    // if b == 0 answer is obvious
    if (b->intsAmount == 1 && b->body[0] == 0){
        resArray[0] = fromInt(1);
        resArray[1] = fromInt(0);
        resArray[2] = copy(a);

    } else {
        // compute values of quotient and remainder
        BigInteger *q = divide(a, b);
        BigInteger *tmp = mul(q, b);
        BigInteger *r = sub(a, tmp);
        free(tmp->body);
        free(tmp);
//
//        // for debugging
//        if (absRelation(b, r) != 1){
//            exit(1);
//        }

        // recursively compute xgcd for b and remainder
        // and compute the answer
        BigInteger **preArray = xgcd(b, r);
        resArray[0] = preArray[1];
        tmp = mul(q, preArray[1]);
        resArray[1] = sub(preArray[0], tmp);
        free(tmp->body);
        free(tmp);

        resArray[2] =preArray[2];
        free(preArray[0]->body);
        free(preArray[0]);          // free the memory of temporary variables
        free(q->body);
        free(q);
        free(r->body);
        free(r);
    }
    free(a->body);
    free(b->body);
    return resArray;
}