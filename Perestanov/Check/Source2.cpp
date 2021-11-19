#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int i, int j)
{
	int s = a[i];
	a[i] = a[j];
	a[j] = s;
}
bool NextSet(int* a, int n)
{
	int j = n - 2;
	while (j != -1 && a[j] >= a[j + 1]) j--;
	if (j == -1)
		return false; // больше перестановок нет
	int k = n - 1;
	while (a[j] >= a[k]) k--;
	swap(a, j, k);
	int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
	while (l < r)
		swap(a, l++, r--);
	return true;
}
void Print(int* a, int n, int num)  // вывод перестановки
{
 // номер перестановки
	printf("%d : ", num + 1);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}




int** HaveMas(int* m, int N, int* nx)
{

	int mx = 1, k = 0, no;
	for (int i = 0; i < N; i++)
		mx *= 2;  // Вместо pow(2, N)
	int** x = new int* [mx];
	//int* nx = new int[mx];

	for (int i = 0; i < mx; i++)
	{
		k = 0;
		for (int j = 0; j < N; j++)
		{
			if ((i >> j) & 1)
				k++;
		}

		nx[i] = k;
		x[i] = new int[k];

		no = 0;
		for (int j = 0; j < N; j++)
			if ((i >> j) & 1)
			{
				x[i][no] = m[j];
				no++;
			}
	}

	return x;
}


void			show_menu();
int				choice();





int main()
{
	show_menu();
}




void show_menu()
{
	switch (choice())
	{
	case 1:
	{
		int n;
		printf("N = ");
		scanf_s("%d", &n);
		int mx = 1;
		for (int i = 0; i < n; i++)
		{
			mx *= 2; // pow
		}

		int** x = new int* [mx];
		int* arr = new int[n];
		int* nx = new int[mx];

		for (int i = 0; i < n; i++)
		{
			printf("arr[%d] = ", i);
			scanf_s("%d", &arr[i]);
		}


		x = HaveMas(arr, n, nx);

		int k;
		for (int p = 0; p < n + 1; p++)
		{
			for (int i = 0; i < mx; i++)
			{
				k = nx[i];
				if (k == p)
				{
					for (int j = 0; j < k; j++)
					{
						printf("%d ", x[i][j]);
					}
					printf("\n");
				}
			}
		}


		delete[] nx;
		delete[] x;
		delete[] arr;

		system("pause");
		system("cls");
		show_menu();
		return;
	}
	case 2:
	{
		int n;
		printf("N = ");
		scanf_s("%d", &n);
		printf("pow = ");;
		int pow;
		scanf_s("%d", &pow);

		int mx = 1;
		for (int i = 0; i < n; i++)
		{
			mx *= 2; // pow
		}

		int** x = new int* [mx];
		int* arr = new int[n];
		int* nx = new int[mx];

		for (int i = 0; i < n; i++)
		{
			printf("arr[%d] = ", i);
			scanf_s("%d", &arr[i]);
		}


		x = HaveMas(arr, n, nx);

		int k;
		for (int i = 0; i < mx; i++)
		{
			k = nx[i];
			if (k == pow)
			{
				for (int j = 0; j < k; j++)
				{
					printf("%d ", x[i][j]);
				}
				printf("\n");
			}
		}
		


		delete[] nx;
		delete[] x;
		delete[] arr;

		system("pause");
		system("cls");
		show_menu();
		return;
	}
	case 3:
	{
		int n;
		printf("N = ");
		scanf_s("%d", &n);

		int* arr = new int[n];

		for (int i = 0; i < n; i++)
		{
			printf("arr[%d] = ", i);
			scanf_s("%d", &arr[i]);
		}


		int num = 0;
		Print(arr, n, num);
		while (NextSet(arr, n))
		{
			num++;
			Print(arr, n, num);
		}

		system("pause");
		system("cls");
		show_menu();
		return;
	}
	case 4:
	{

		return;
	}
	default:
		return;
	}
}

int choice()
{
	bool answer = false;
	do
	{
		printf("\t\t\tMenu\n\n");
		printf("All tasks:\n\t1. A) All subsets \n\t2. B) subsets with power pow \n\t3. C)Perestanovki \n\t4. D). Exit\n\n");
		printf("Please, enter your choice (1-5): ");
		int choice;
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 4;
		default: answer = true; system("cls"); break;
		}
	} while (answer);

	return -1;
}

