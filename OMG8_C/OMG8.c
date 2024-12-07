//
// OMG8
// Created by Ю. Петрова
// Комп мат 1
// OMG8.c source file
//

#include "OMG8.h"
#include <stdio.h>
#include <stdlib.h>

OMG8 initializeOMG8(int length){
    OMG8 structure;
    structure.length = length;
    structure.data = (unsigned long long*)malloc(length * sizeof(unsigned long long));
    for (int idx = 0; idx < length; idx++)
        structure.data[idx] = 0;
    return structure;
}

OMG8 duplicate(OMG8* original){
    OMG8 newStructure = initializeOMG8(original->length);

    for (int idx = 0; idx < original->length; idx++){
        newStructure.data[idx] = original->data[idx];
    }

    return newStructure;
}

void inputData(OMG8* structure, int length, FILE* input){
    *structure = initializeOMG8(length);
    for (int idx = 0; idx < length; idx++)
        fscanf(input, "%lld", structure->data + idx);
}

void outputData(OMG8* structure, FILE* output){
    for (int idx = 0; idx < structure->length; idx++)
        fprintf(output, "%llu ", structure->data[idx]);
    fprintf(output, "\n");
}

void insertElement(OMG8* structure, int index, unsigned long long value){
    unsigned long long *newData = (unsigned long long*)malloc((structure->length + 1) * sizeof(unsigned long long));

    for (int idx = 0; idx < index; idx++)
        newData[idx] = structure->data[idx];
    newData[index] = value;

    for (int idx = index; idx < structure->length; idx++)
        newData[idx + 1] = structure->data[idx];

    free(structure->data);
    structure->data = newData;
    structure->length++;
}

void mergeStructures(OMG8* primary, int index, OMG8* secondary){
    unsigned long long *newData = (unsigned long long*)malloc((primary->length + secondary->length) * sizeof(unsigned long long));

    for (int idx = 0; idx < index; idx++)
        newData[idx] = primary->data[idx];

    for (int idx = 0; idx < secondary->length; idx++)
        newData[index + idx] = secondary->data[idx];

    for (int idx = index; idx < primary->length; idx++)
        newData[idx + secondary->length] = primary->data[idx];

    free(primary->data);
    primary->data = newData;
    primary->length += secondary->length;
}

OMG8 extractSubset(OMG8* structure, int start, int end){
    OMG8 subset = initializeOMG8(end - start);

    for (int idx = start; idx < end; idx++)
        subset.data[idx - start] = structure->data[idx];

    return subset;
}

int locateSubstructure(OMG8* primary, OMG8* secondary){
    if (primary->length < secondary->length)
        return -1;
    for (int i = 0; i <= primary->length - secondary->length; i++){
        for (int j = 0; j < secondary->length; j++){
            if (primary->data[i + j] != secondary->data[j])
                break;
            if (j + 1 == secondary->length)
                return i;
        }
    }
    return -1;
}

unsigned char* encodeStructure(OMG8* structure, int* size){
    int len = 0;
    unsigned char buf;
    unsigned long long k;
    for (int i = 0; i < structure->length; i++) {
        k = structure->data[i];
        if (structure->data[i] == 0)
            len++;
        while (k > 0) {
            k /= 128;
            len++;
        }
    }

    unsigned char* encodedData = (unsigned char*)malloc(len * sizeof(char));
    int t = 0;

    for (int i = 0; i < structure->length; i++) {
        k = structure->data[i];
        while (1) {
            buf = k & 127;
            if (k < 128) {
                encodedData[t++] = buf;
                break;
            }
            else {
                encodedData[t++] = buf + 128;
                k -= buf + 128;
                k /= 128;
            }
        }
    }
    *size = len;
    return encodedData;
}

OMG8 decodeStructure(unsigned char* bytes, int size){
    int len = 0;
    for (int i = 0; i < size; i++) {
        if ((bytes[i] & 128) == 0)
            len++;
    }

    OMG8 decodedStructure = initializeOMG8(len);
    int t = 0;
    unsigned long long k = 1;

    for (int i = 0; i < size; i++) {
        decodedStructure.data[t] += (k * bytes[i]);
        k *= 128;

        if ((bytes[i] & 128) == 0) {
            t++;
            k = 1;
        }
    }
    return decodedStructure;
}

long long convertToInteger(OMG8* primary, int base){
    long long result = 0;
    for (int i = 0; i < primary->length; i++){
        if (primary->data[i] >= base){
            return -1;
        }
        result *= base;
        result += primary->data[i];
    }
    return result;
}

OMG8 convertFromInteger(int number, int base){
    unsigned long long k = number;
    int len = 0;
    while (k > 0) {
        len++;
        k /= base;
    }
    if (len == 0)
        len = 1;

    OMG8 resultStructure = initializeOMG8(len);
    k = number;
    for (int i = len - 1; i >= 0; i--){
        resultStructure.data[i] = k % base;
        k /= base;
    }
    return resultStructure;
}