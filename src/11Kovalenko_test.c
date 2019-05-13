#include "../headers/11Kovalenko.h"


extern int _batchHelperText(char *filename, DType *data, size_t size, long *fpos);

extern int _batchHelperBin(char *filename, DType *data, size_t size, long *fpos);

extern int _printFreqs(struct hist *h);

extern DType median(struct hist *h);

extern DType var(struct hist *h);

extern DType dev(struct hist *h);

extern DType mean(struct hist *h);


int testFileIOText()
{
	DType data[3] = { 0 };
	size_t s = 3;
	DType data2[3] = { 0 };
	long *posptr = (long*)calloc(1, sizeof(NType));
	*posptr = 0;
	int amt = _batchHelperText("E:\\UserData\\inpt.txt", data, s, posptr);
	printf("Numbers read: %d\nwhich are:\n", amt);
	for (NType i = 0; i < s; i++)
	{
		printf("%lf\n", data[i]);
	}
	amt = _batchHelperText("E:\\UserData\\inpt.txt", data2, s, posptr);
	printf("Numbers read: %d\nwhich are:\n", amt);
	for (NType i = 0; i < s; i++)
	{
		printf("%lf\n", data2[i]);
	}
	return 0;
}


int testFileIOBin()
{
	DType data[3] = { 0 };
	size_t s = 3;
	DType data2[3] = { 0 };
	long *posptr = (long*)calloc(1, sizeof(NType));
	*posptr = 0;
	//printf("helper start======================\n");
	int amt = _batchHelperBin("E:\\UserData\\data.bin", data, s, posptr);
	//printf("helper end========================\n");
	amt = _batchHelperBin("E:\\UserData\\data.bin", data2, s, posptr);
	printf("\n\nNumbers read: %d\nwhich are:\n", amt);
	for (NType i = 0; i < s; i++)
	{
		printf("%lf\n", data[i]);
	}
	printf("Numbers read: %d\nwhich are:\n", amt);
	for (NType i = 0; i < s; i++)
	{
		printf("%lf\n", data2[i]);
	}
	return 0;
}


int testHist1()
{
	struct hist *h = (struct hist*)malloc(sizeof(struct hist));
	DType mnHist = 0, mxHist = 100;
	NType M = 10;
	initStruct(mnHist, mxHist, M, h);
	addBatchFromFile("E:\\UserData\\norm1000.txt", 't', h);
	_printFreqs(h);
	printf("\nAmt of elements in hist is: %d\n", num(h));
	printf("\nmedian: %lf", median(h));
	printf("\nmean: %lf", mean(h));
	printf("\ndev: %lf", dev(h));
	printf("\nvar: %lf", var(h));
	return 0;
}