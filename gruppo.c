#include <stdlib.h>
#include "cella.h"
#include "celle.h"
#include "gruppo.h"

struct gruppo_s
{
    celle insieme;
    int fase;
};

void creaGruppo(gruppo* g)
{
    *g = malloc(sizeof(struct gruppo_s));

    creaCelle(&(*g)->insieme);

    (*g)->fase = 0;
}

void liberaGruppo(gruppo g)
{
    free(g);
}