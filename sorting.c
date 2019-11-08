#include <stdio.h>
#include <stdlib.h>
#include "cella.h"
#include "sorting.h"

void QuickSortR(cella* A, int l, int r, criterio specifica);
int partition(cella* A, int l, int r, criterio specifica);
void Swap(cella *v, int n1, int n2);

void Sort(cella* A, int N, criterio specifica)
{
    int l=0, r=N-1;
    QuickSortR(A, l, r, specifica);
}

void QuickSortR(cella* A, int l, int r, criterio specifica)
{
    int q;
    if (r <= l)		return;
    q = partition(A, l, r, specifica);
    QuickSortR(A, l, q-1, specifica);
    QuickSortR(A, q+1, r, specifica);

    return;
}

int partition(cella* A, int l, int r, criterio specifica)
{
    int i, j;
    cella x = A[r];
    i = l-1;
    j = r;
    for ( ; ; )
    {
        while(CELLAleq(A[++i], x, specifica));
        while(CELLAgt(A[--j], x, specifica))
        {
            if (j == l)		break;
            if (i >= j)		break;
        }
        Swap(A, i, j);
    }
    Swap(A, i, r);

    return i;
}

void Swap(cella *v, int n1, int n2)
{
    cella tmp;

    tmp  = v[n1];
    v[n1] = v[n2];
    v[n2] = tmp;

    return;
}