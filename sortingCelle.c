#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "cella.h"
#include "sortingCelle.h"

void QuickSortRC(cella* A, int l, int r, criterio specifica);
int partitionC(cella* A, int l, int r, criterio specifica);
void SwapC(cella *v, int n1, int n2);

void SortCelle(cella* A, int N, criterio specifica)
{
    int l=0, r=N-1;
    QuickSortRC(A, l, r, specifica);
}

void QuickSortRC(cella* A, int l, int r, criterio specifica)
{
    int q;
    if (r <= l)		return;
    q = partitionC(A, l, r, specifica);
    QuickSortRC(A, l, q - 1, specifica);
    QuickSortRC(A, q + 1, r, specifica);

    return;
}

int partitionC(cella* A, int l, int r, criterio specifica)
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
        SwapC(A, i, j);
    }
    SwapC(A, i, r);

    return i;
}

void SwapC(cella *v, int n1, int n2)
{
    cella tmp;

    tmp  = v[n1];
    v[n1] = v[n2];
    v[n2] = tmp;

    return;
}