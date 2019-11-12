#include <stdio.h>
#include <stdlib.h>
#include "sortingInt.h"

void QuickSortRI(int* A, int l, int r);
int partitionI(int* A, int l, int r);
void SwapI(int *v, int n1, int n2);

void SortInt(int* A, int N)
{
    int l=0, r=N-1;
    QuickSortRI(A, l, r);
}

void QuickSortRI(int* A, int l, int r)
{
    int q;
    if (r <= l)		return;
    q = partitionI(A, l, r);
    QuickSortRI(A, l, q - 1);
    QuickSortRI(A, q + 1, r);

    return;
}

int partitionI(int* A, int l, int r)
{
    int i, j;
    int x = A[r];
    i = l-1;
    j = r;
    for ( ; ; )
    {
        while(A[++i] <= x);
        while(A[--j] > x)
        {
            if (j == l)		break;
            if (i >= j)		break;
        }
        SwapI(A, i, j);
    }
    SwapI(A, i, r);

    return i;
}

void SwapI(int *v, int n1, int n2)
{
    int tmp;

    tmp  = v[n1];
    v[n1] = v[n2];
    v[n2] = tmp;
}