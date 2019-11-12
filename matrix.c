#include <stdlib.h>
#include "sortingInt.h"
#include "matrix.h"

#define START 4
#define CRESCITA 2

struct matrice_s
{
    int** v;
    int dim;
    int realDim;
};

int equalVett(int* a, int* b);

void creaMatrice(Matrice* m)
{
    (*m) = malloc(sizeof(struct matrice_s));
    (*m)->dim = 0;
    (*m)->realDim = START;
    (*m)->v = malloc(((*m)->realDim)*sizeof(int*));
}

void liberaMatrice(Matrice m)
{
    free(m->v);
    free(m);
}

void aggiungiVettore(Matrice m, int* a)
{
    if( (m->dim)+1 > (m->realDim) )
    {
        (m->realDim) *= CRESCITA;
        m->v = realloc(m->v, (m->realDim)*sizeof(int*));
    }

    m->v[(m->dim)++] = a;
}

int checkDuplicati(Matrice m, int* v)
{
    int** a = m->v;
    int dimA = m->dim;
    int i;
    for(i=0; i<dimA; i++)
    {
        if(equalVett(a[i], v))
            return 0;
    }

    return 0;
}

int equalVett(int* a, int* b)
{
    int i;

    i=0;
    while(a[i++]!=-1);
    int dimA = i-1;
    i=0;
    while(b[i++]!=-1);
    int dimB = i-1;

    if(dimA!=dimB)
        return 0;

    SortInt(a, dimA);
    SortInt(b, dimB);

    for(i=0; i<dimA; i++)
    {
        if(a[i]!=b[i])
            return 0;
    }

    return 1;
}