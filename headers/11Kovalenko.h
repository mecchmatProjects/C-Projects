#ifndef __HIST_H__
#define _CRT_SECURE_NO_WARNINGS
#define __HIST_H__
#include "common.h"
#include "stdlib.h"
#define true 1
#define false 0

struct hist {
	DType minHist;
	DType maxHist;
	// each bucket defined with it's left side (width is known), 
	// each element in histogram is assigned to a particular bucket (he is greater than left side and less than left side + bucket width
	DType bWidth;	// bucket width
	NType M;
	NType *frequency;
};



void initStruct(DType minHist, DType maxHist, NType M, struct hist *res);

void setMax(DType m, struct hist *h);

void setMin(DType m, struct hist *h);

void setM(NType n, struct hist *h);

int addNumber(DType x, struct hist *h);

int addBatch(DType data[], size_t dataSize, struct hist *h);

int addBatchFromFile(char *filename, char mode, struct hist *h);

int _batchHelperText(char *filename, DType *data, size_t size, long *fpos);

int _batchHelperBin(char *filename, DType *data, size_t size, long *fpos);

NType num(struct hist *h);

NType numHist(struct hist *h, NType i);

DType mean(struct hist *h);

DType median(struct hist *h);

DType dev(struct hist *h);

DType var(struct hist *h);

DType kurtosis(struct hist *h);


#endif