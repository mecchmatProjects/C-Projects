//
// OMG8
// Created by Ю. Петрова
// Комп мат 1
// OMG8.c header file
//


#pragma once
#include <stdio.h>

typedef struct OMG8 {
    int length;
    unsigned long long *data;
} OMG8;

OMG8 initializeOMG8(int length);
OMG8 duplicate(OMG8* original);

void inputData(OMG8* structure, int length, FILE* input);
void outputData(OMG8* structure, FILE* output);

void insertElement(OMG8* structure, int index, unsigned long long value);
void mergeStructures(OMG8* primary, int index, OMG8* secondary);

OMG8 extractSubset(OMG8* structure, int start, int end);

int locateSubstructure(OMG8* primary, OMG8* secondary);

long long convertToInteger(OMG8* primary, int base);
OMG8 convertFromInteger(int number, int base);

unsigned char* encodeStructure(OMG8* structure, int* size);
OMG8 decodeStructure(unsigned char* bytes, int size);