#include <stdio.h>
#include <stdlib.h>
#include "cella.h"
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