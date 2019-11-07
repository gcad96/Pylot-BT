#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"

struct topologia_s
{
    //cella 0 in (a, b)
    coordinata* offSet;  //altre celle in (a+coordinata[i]->x, b+coordinata[i]->y)
    int dimensione;
};

void creaTopologia(topologia* t, int dim, coordinata* c)
{
    *t = malloc(sizeof(struct topologia_s));
    (*t)->dimensione = dim;
    int i;
    for(i=0; i<dim; i++)
    {
        (*t)->offSet[i] = c[i];
    }
}

void liberaTopologia(topologia t)
{
    free(t);
}
