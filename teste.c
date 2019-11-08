#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "testa.h"
#include "teste.h"

#define START 4
#define CRESCITA 2

struct teste_s
{
    testa* insieme;
    int dim;
    int realDim;
};

void creaTeste(teste* t)
{
    *t = malloc(sizeof(struct teste_s));
    (*t)->dim = 0;
    (*t)->realDim = START;
    (*t)->insieme = malloc(((*t)->realDim) * sizeof(testa));
}

void liberaTeste(teste t)
{
    free(t->insieme);
    free(t);
}

void aggiungiTesta(teste t, testa tes)
{
    if((t->dim) + 1 > (t->realDim) )
    {
        (t->realDim) *= CRESCITA;
        t->insieme = realloc(t->insieme, (t->realDim) * sizeof(testa));
    }

    t->insieme[(t->dim)++] = tes;
}