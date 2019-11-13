#include <stdlib.h>
#include "coordinata.h"
#include "cella.h"
#include "gruppo.h"
#include "gruppi.h"

#define START 4
#define CRESCITA 2

struct gruppi_s
{
    gruppo* insieme;
    int dim;
    int realDim;
};

void creaGruppi(gruppi* g)
{
    *g = malloc(sizeof(struct gruppi_s));
    (*g)->dim = 0;
    (*g)->realDim = START;
    (*g)->insieme = malloc(((*g)->realDim) * sizeof(gruppo));
}

void liberaGruppi(gruppi g)
{
    free(g->insieme);
    free(g);
}

void aggiungiGruppo(gruppi g, gruppo gr)
{
    if((g->dim) + 1 > (g->realDim) )
    {
        (g->realDim) *= CRESCITA;
        g->insieme = realloc(g->insieme, (g->realDim) * sizeof(gruppo));
    }

    g->insieme[(g->dim)++] = gr;
}