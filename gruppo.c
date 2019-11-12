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
    liberaTopologia(g->topologia);

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

void setTopologia(gruppo g)
{
    celle c = g->insieme;
    ordinaCelle(c, matrice);
    cella* i = getInsieme(c);
    int dim = getDim(c);
    cella c1 = i[0];
    coordinata* cc = malloc((dim-1)*sizeof(coordinata));
    int j;
    for(j=1; j<dim; j++)
    {
        float xOff = getAscissa(getCoordinata(i[j])) - getAscissa(getCoordinata(c1));
        float yOff = getOrdinata(getCoordinata(i[j])) - getOrdinata(getCoordinata(c1));
        coordinata coo; creaCoordinata(&coo, xOff, yOff);
        cc[j-1] = coo;
    }

    topologia t;
    creaTopologia(&t, dim-1, cc);
}