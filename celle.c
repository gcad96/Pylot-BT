#include <stdio.h>
#include <stdlib.h>
#include "cella.h"
#include "sorting.h"
#include "celle.h"

#define START 4
#define CRESCITA 2

struct celle_s
{
    cella* insieme;
    int dim;
    int realDim;
};

void creaCelle(celle* c)
{
    *c = malloc(sizeof(struct celle_s));
    (*c)->dim = 0;
    (*c)->realDim = START;
    (*c)->insieme = malloc(((*c)->realDim)*sizeof(cella));
}

void liberaCelle(celle c)
{
    free(c->insieme);
    free(c);
}

void aggiungiCella(celle c, cella cel)
{
    if( (c->dim)+1 > (c->realDim) )
    {
        (c->realDim) *= CRESCITA;
        c->insieme = realloc(c->insieme, (c->realDim)*sizeof(cella));
    }

    c->insieme[(c->dim)++] = cel;
}

void stampaCelle(celle c)
{
    int i;
    for(i=0; i<c->dim; i++)
    {
        stampaCella(c->insieme[i]);
        printf("\n");
    }
}

void ordinaCelle(celle c, criterio crit)
{
    switch(crit)
    {
        case ascissa:
            Sort(c->insieme, c->dim, ascissa);
            break;
        case ordinata:
            Sort(c->insieme, c->dim, ordinata);
            break;
        case matrice:
            Sort(c->insieme, c->dim, matrice);
            break;
        case altro:
            break;
        default:
            break;
    }
}

void generaDistanze(celle c, double*** m)
{
    int i, j;

    *m = malloc((c->dim) * sizeof(double*));
    for(i=0; i<c->dim; i++)
    {
        (*m)[i] = malloc((c->dim) * sizeof(double));
        for(j=0; j<c->dim; j++)
        {
            (*m)[i][j] = distanza(c->insieme[i], c->insieme[j]);
        }
    }
}

int getDim(celle c)
{
    return c->dim;
}