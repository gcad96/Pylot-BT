/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "gruppo.h"
#include "gruppi.h"
#include "movimento.h"
#include "soluzione.h"

struct soluzione_s
{
    movimento* movimenti;
    int dim;
};

void memorizza(soluzione* s, int dim, movimento* movimenti)
{
    if((*s)!=NULL)
    {
        (*s) = malloc(sizeof(struct soluzione_s));
        (*s)->movimenti = malloc(dim * sizeof(movimento));
    }
    else
    {
        (*s)->movimenti = realloc((*s)->movimenti, (dim * sizeof(movimento)));
    }
    (*s)->dim = dim;

    int i;
    for(i=0; i<(*s)->dim; i++)
        (*s)->movimenti[i] = movimenti[i];

}

void stampaSoluzione(soluzione s)
{
    int i;
    for(i=0; i<s->dim; i++)
    {
        stampaMovimento(s->movimenti[i]);
    }
}