//
// OMG8
// Created by Ю. Петрова
// Комп мат 1
// OMG8.c test file
//

#include <stdio.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>

#include "OMG8.h"

int main(int argc, char** argv){
    FILE* inputFile = stdin;
    FILE* outputFile = stdout;

    if (argc > 2){
        inputFile = fopen(argv[1], "r");
        outputFile = fopen(argv[2], "w");
    }

    int primaryLength, secondaryLength;
    OMG8 primaryStruct, secondaryStruct, resultStruct;
    int encodedSize;
    unsigned long long elementValue;
    int startIndex, endIndex;

    fprintf(outputFile, "please enter lengths of 2 strings, enter their elemens:\n");
    fscanf(inputFile, "%d%d", &primaryLength, &secondaryLength);

    inputData(&primaryStruct, primaryLength, inputFile);
    inputData(&secondaryStruct, secondaryLength, inputFile);

    fprintf(outputFile, "here input strings:\n");
    outputData(&primaryStruct, outputFile);
    outputData(&secondaryStruct, outputFile);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "please enter index and value to insert\n");
    fscanf(inputFile, "%d%llu", &startIndex, &elementValue);
    fprintf(outputFile, "inserting %llu at index %d\n", elementValue, startIndex);
    resultStruct = duplicate(&primaryStruct);
    insertElement(&resultStruct, startIndex, elementValue);
    outputData(&resultStruct, outputFile);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "enter index and replacement value\n");
    fscanf(inputFile, "%d%llu", &startIndex, &elementValue);
    fprintf(outputFile, "replacing element at index %d with %llu\n", startIndex, elementValue);
    free(resultStruct.data);
    resultStruct = duplicate(&primaryStruct);
    resultStruct.data[startIndex] = elementValue;
    outputData(&resultStruct, outputFile);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "please enter merge index\n");
    fscanf(inputFile, "%d", &startIndex);
    fprintf(outputFile, "merging structures at index %d\n", startIndex);
    free(resultStruct.data);
    resultStruct = duplicate(&primaryStruct);
    mergeStructures(&resultStruct, startIndex, &secondaryStruct);
    outputData(&resultStruct, outputFile);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "secondary string locating in primary (index):\n%d\n\n",
            locateSubstructure(&primaryStruct, &secondaryStruct));

    fprintf(outputFile, "input extraction start and end indices\n");
    fscanf(inputFile, "%d%d", &startIndex, &endIndex);
    free(resultStruct.data);
    resultStruct = extractSubset(&primaryStruct, startIndex, endIndex);
    fprintf(outputFile, "extracted subset from index %d to %d:\n", startIndex, endIndex);
    outputData(&resultStruct, outputFile);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "encoding primary structure\n");
    unsigned char* encodedBytes = encodeStructure(&primaryStruct, &encodedSize);
    for (int i = 0; i < encodedSize; i++)
        fprintf(outputFile, "%d ", (int)encodedBytes[i]);
    fprintf(outputFile, "\n\n");

    fprintf(outputFile, "coding bytes\n");
    for (int i = 0; i < encodedSize; i++)
        fprintf(outputFile, "%d ", (int)encodedBytes[i]);
    fprintf(outputFile, "\n");
    free(resultStruct.data);
    resultStruct = decodeStructure(encodedBytes, encodedSize);
    outputData(&resultStruct, outputFile);
    fprintf(outputFile, "\n");

    free(primaryStruct.data);
    free(secondaryStruct.data);
    free(resultStruct.data);
    free(encodedBytes);

    if (argc > 2){
        fclose(inputFile);
        fclose(outputFile);
    }

    return 0;
}