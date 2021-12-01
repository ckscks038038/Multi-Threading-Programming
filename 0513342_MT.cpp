#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;
/*structure definition*/
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

/*function definition*/
void *bubble_sort(void *);
void *merge(void *);

int main(int listc, const char *listv[])
{
    int array[1000000];
    struct arrInfo1 a1[4];
    struct arrInfo2 a2[3];
    int all = 0;
    while (cin >> array[all++])
        ;

    all--;
    int m = all / 2;
    int l = m / 2;
    int r = m + (all - m) / 2;

    //thread create
    for (int i = 0; i < 4; i++)
    {
        a1[i].arr = array;
    }
    pthread_t p1[4];
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
        pthread_create(&p1[i], NULL, bubble_sort, (void *)&(a1[i]));
    }
    //thread determine
    for (int i = 0; i < 4; i++)
    {
        pthread_join(p1[i], NULL);
    }

    //output
    pthread_t p2[3];
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

    pthread_create(&p2[0], NULL, merge, (void *)&(a2[0]));
    pthread_create(&p2[1], NULL, merge, (void *)&(a2[1]));

    pthread_join(p2[0], NULL);
    pthread_join(p2[1], NULL);

    pthread_create(&p2[2], NULL, merge, (void *)&(a2[2]));
    pthread_join(p2[2], NULL);

    for (int i = 0; i < all; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}

void *bubble_sort(void *input_tinfo)
{
    struct arrInfo1 arr;
    arr = *(struct arrInfo1 *)input_tinfo;
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
    pthread_exit(NULL);
}

void *merge(void *input_tinfo)
{

    struct arrInfo2 list;
    list = *(struct arrInfo2 *)input_tinfo;
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

    pthread_exit(NULL);
}
