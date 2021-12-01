#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

struct arrInfo1
{
	int *arr;
	int head;
	int tail;
};
struct arrInfo2
{
	int *arr;
	int head;
	int middle;
	int tail;
};
/* function definitions */
void bubble_sort(struct arrInfo1 *);
void merge(struct arrInfo2 *);

int main(int argc, const char *argv[])
{
	int array[1000000];
	int all = 0;
	struct arrInfo1 a1[4];
	struct arrInfo2 a2[3];
	/* Use STDIN (e.g. scanf, cin) to take the input */
	while (cin >> array[all++])
		;

	/* Do the sorting */
	int m = all / 2;
	int l = m / 2;
	int r = m + (all - m) / 2;

	//thread create
	for (int i = 0; i < 4; i++)
	{
		a1[i].arr = array;
	}

	a1[0].head = 0;
	a1[0].tail = l;

	a1[1].head = l;
	a1[1].tail = m;

	a1[2].head = m;
	a1[2].tail = r;

	a1[3].head = r;
	a1[3].tail = all;
	for (int i = 0; i < 4; i++)
	{
		bubble_sort(&(a1[i]));
	}

	//merge
	for (int i = 0; i < 3; i++)
	{
		a2[i].arr = array;
	}
	a2[0].head = 0;
	a2[0].middle = l;
	a2[0].tail = m;

	a2[1].head = m;
	a2[1].middle = r;
	a2[1].tail = all;

	a2[2].head = 0;
	a2[2].middle = m;
	a2[2].tail = all;

	for (int i = 0; i < 3; i++)
	{
		merge(&(a2[i]));
	}

	/* Use STDOUT (e.g. printf, cout) to output the sorted array */
	for (int i = 0; i < all; i++)
	{
		cout << array[i] << " ";
	}

	return 0;
}
void bubble_sort(struct arrInfo1 *input_tinfo)
{
	struct arrInfo1 arr;
	arr = *input_tinfo;
	int h = arr.head;
	int t = arr.tail;
	for (int i = h; i < t; i++)
	{

		for (int j = h; j < t - 1; j++)
		{
			if (arr.arr[j] > arr.arr[j + 1])
			{
				int temp;
				temp = arr.arr[j];
				arr.arr[j] = arr.arr[j + 1];
				arr.arr[j + 1] = temp;
			}
		}
	}
}

void merge(struct arrInfo2 *input_tinfo)
{
	struct arrInfo2 list;
	list = *input_tinfo;
	int start = list.head;
	int middle = list.middle;
	int end = list.tail;
	int temp1[middle - start];
	int temp2[end - middle];
	int total = end - start;
	int now1 = 0;
	int now2 = 0;
	int i;
	for (i = 0; i < middle - start; i++)
	{
		temp1[i] = list.arr[i + start];
	}
	for (i = 0; i < end - middle; i++)
	{
		temp2[i] = list.arr[i + middle];
	}
	for (i = 0; i < total; i++)
	{
		if (temp1[now1] < temp2[now2])
		{
			list.arr[i + start] = temp1[now1];

			now1++;
			if (now1 >= middle - start)
				break;
		}
		else
		{
			list.arr[i + start] = temp2[now2];

			now2++;
			if (now2 >= end - middle)
				break;
		}
	}
	i++;

	if (i < total)
	{
		if (now1 < middle - start)
		{
			for (; i < total; i++)
			{
				list.arr[i + start] = temp1[now1];

				now1++;
			}
		}
		else
		{
			for (; i < total; i++)
			{
				list.arr[i + start] = temp2[now2];
				now2++;
			}
		}
	}
}