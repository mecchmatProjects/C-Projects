#include "../headers/11Kovalenko.h"


void* memzero(void* ptr, size_t n)
{
	return memset(ptr, 0, n);
}

void initStruct(DType minHist, DType maxHist, NType M, struct hist *res)
{
	res->maxHist = maxHist;
	res->minHist = minHist;
	res->M = M;
	res->frequency = (NType*)calloc(M, sizeof(NType));
	res->bWidth = (maxHist - minHist) / M;
}

void setMax(DType m, struct hist *h)
{
	h->maxHist = m;
}

void setMin(DType m, struct hist *h)
{
	h->minHist = m;
}

void setM(NType n, struct hist *h)	// changes will totaly reset histogram
{
	h->M = n;
	free(h->frequency);				// right here it will reset histogram
	h->frequency = (NType*)calloc(n, sizeof(NType));
	h->bWidth = (h->maxHist - h->minHist) / n;
}

int addNumber(DType x, struct hist *h)
{
	if (x < h->minHist || x > h->maxHist)	// error check
	{
		return -1;
	}
	int indx;
	indx = (int)((x - h->minHist) / h->bWidth);
	h->frequency[indx]++;
	return 0;
}

int addBatch(DType data[], size_t dataSize, struct hist *h)
{
	for (NType i = 0; i < dataSize; i++)
	{
		int status = addNumber(data[i], h);
		if (status == -1)
		{
			return -1;
		}
	}
	return 0;
}

int addBatchFromFile(char *filename, char mode, struct hist *h)
/// mode = {'t', 'b'} for text/binary
{
	if (mode == 'b')
	{
		DType data[128] = {0};
		size_t size = 128;
		long *fpos = (long*)calloc(1, sizeof(long));
		while (true)
		{
			int stat = _batchHelperBin(filename, data, size, fpos);
			if (stat == -1)
			{
				free(fpos);
				return -1;
			}
			else if (stat < (int)size)
			{
				addBatch(data, stat, h);	// stat(status) - amount of proceeded elements, otherwise we will be adding zeroes
				return 0;
			}
			else
			{
				addBatch(data, size, h);
			}
		}
	}
	else if (mode == 't')
	{
		DType data[128] = { 0 };
		size_t size = 128;
		long *fpos = (long*)calloc(1, sizeof(long));
		while (true)
		{
			int stat = _batchHelperText(filename, data, size, fpos);
			if (stat == -1)
			{
				free(fpos);
				return -1;
			}
			else if (stat < (int)size)
			{
				addBatch(data, stat, h);	// stat(status) - amount of proceeded elements, otherwise we will be adding zeroes
				return 0;
			}
			else
			{
				addBatch(data, size, h);
			}
		}
	}
	else return -1;
}

int _batchHelperText(char *filename, DType *data, size_t size, long *fpos)
/// read from text file helper function
{
	FILE *inpt = NULL;
	inpt = fopen(filename, "r");
	fseek(inpt, *fpos, 0);
	if (inpt == NULL)					// file was not opened properly
	{
		fclose(inpt);
		return -1;
	}
	int processedAmt = 0;
	for (NType i = 0; i < size; i++)	// read each integer into specific place in array data[]
	{
		if (feof(inpt))					// if reached end of file
		{
			fclose(inpt);
			return processedAmt;
		}
		fscanf(inpt, "%lf", &data[i]);	// read data into double
		processedAmt++;
	}
	*fpos = ftell(inpt);
	fclose(inpt);
	return processedAmt;
}

int _batchHelperBin(char *filename, DType *data, size_t size, long *fpos)
/// read from binary file helper function
{
	FILE *inpt = NULL;
	inpt = fopen(filename, "rb");
	fseek(inpt, *fpos, 0);							// continue reading right from the place of interruption
	if (inpt == NULL)								// if was not opened properly
	{
		fclose(inpt);
		return -1;
	}
	int processedAmt = 0;
	for (NType j = 0; j < size; j++)
	{
		char str[20];								// string which will be casted to double (~20 digits in c unsigned double)
		char flag = 0;
		for (NType i = 0; i < 10; i++)
		{
			char temp;								// although binary supposed to have separated int nums we read it byte-by-byte as a string and build number upon that string
			fread(&temp, sizeof(char), 1, inpt);	// another character read
			if (feof(inpt))							// if finished reading
			{
				flag = 1;							// EOF sub-flag
				break;
			}
			if (temp == 10 || temp == 32 || temp == 9)		// newline, space or tab charater
			{
				break;
			}
			str[i] = temp;
		}
		data[j] = (DType)atof(str);
		processedAmt++;
		if (flag)									// end of file reached, no more reading is needed
		{
			break;
		}
	}
	*fpos = ftell(inpt);							// refresh current file position
	fclose(inpt);
	return processedAmt;
}

int _printFreqs(struct hist *h)
{
	for (NType i = 0; i < h->M; i++)
	{
		printf("-.-%d-.-", h->frequency[i]);
	}
	printf("\n");
	for (NType i = 0; i < h->M; i++)
	{
		printf("-%.2f-", h->minHist + i * h->bWidth);
	}
	return 0;
}

NType num(struct hist *h)	// amount of elements in histogramm
{
	NType res = 0;
	for (NType i = 0; i < h->M; i++)
	{
		res += h->frequency[i];
	}
	return res;
}

NType numHist(struct hist *h, NType i)    // amount of elements in a certain column
{
	if (i < 0 || i > h->M - 1)
	{
		return -1;
	}
	return h->frequency[i];
}

DType mean(struct hist *h)  // mean value of histogram
{
	DType res = 0;
	DType cur = h->minHist + h->bWidth / 2;
	for (NType i = 0; i < h->M; i++)
	{
		res += h->frequency[i] * cur;
		cur += h->bWidth;
	}
	return (DType)res/(DType)(num(h));
}

DType median(struct hist *h) // median value of histogram
{
	NType amt = num(h);			// amount of elements in histogram
	DType res = h->minHist,		// result value (minimum value of hist by default)
		  mid = (DType)amt/2;   // middle value
	NType cur = 0;
	for (NType i = 0; i < h->M; i++)
	{
		cur += h->frequency[i];
		if (cur >= mid)			// if we passed half-way in amount of considered elements, therefore median is supposed to be in previous bucket 
		{
			res += h->bWidth / 2;	// consider median value 'somewhere in between' in bucket segment
			return res;
		}
		else
		{
			res += h->bWidth;
		}
	}
	return res;
}

DType dev(struct hist *h) // standart deviance of histogram
{
	return pow(var(h), 0.5);	// dev = sqrt(var)
}

DType var(struct hist *h) // variance of histogram
{
	DType res = 0;
	DType m = mean(h);
	NType n = num(h); 
	DType curEst = h->minHist + h->bWidth/2;
	for (NType i = 0; i < h->M; i++)
	{
		res += pow((curEst - m), 2) * h->frequency[i];
		curEst += h->bWidth;
	}
	return res/(n);
}

DType kurtosis(struct hist *h) // ексцесс
{
	return 0;
}
