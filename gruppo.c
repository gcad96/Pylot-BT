#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "celle.h"
#include "gruppo.h"

struct gruppo_s
{
    celle insieme;
    int fase;
    topologia topologia;
    coordinata baricentro;
};

void creaGruppo(gruppo* g)
{
    *g = malloc(sizeof(struct gruppo_s));

    creaCelle(&(*g)->insieme);

    (*g)->fase = 0;

    (*g)->topologia = NULL;

    (*g)->baricentro = NULL;
}

void liberaGruppo(gruppo g)
{
    liberaCoordinata(g->baricentro);

    free(g);
}

void setBaricentro(gruppo g)
{
    cella* ins = getInsieme(g->insieme);
    int dim = getDim(g->insieme);

    float x = 0;
    float y = 0;

    int i;
    for(i=0; i<dim; i++)
    {
        x += getAscissa(getCoordinata(ins[i]));
        y += getOrdinata(getCoordinata(ins[i]));
    }

    x /= (float) dim;
    y /= (float) dim;

    coordinata c;
    creaCoordinata(&c, x, y);

    g->baricentro = c;
}