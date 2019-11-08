#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "coordinata.h"
#include "cella.h"

struct cella_s
{
    char* nome;
    coordinata coordinata;
    int test;
};

void creaCella(cella* c, char* nome, float x, float y)
{
    *c = malloc(sizeof(struct cella_s));
    (*c)->nome = strdup(nome);
    creaCoordinata(&((*c)->coordinata), x, y);
    (*c)->test = 0;
}

void liberaCella(cella c)
{
    free(c->nome);
    liberaCoordinata(c->coordinata);
    free(c);
}

void stampaCella(cella c)
{
    printf("Cella denominata: %s, con coordinate: ", c->nome);
    stampaCoordinata(c->coordinata);
}

int CELLAleq(cella a, cella b, criterio c)
{
    switch(c)
    {
        case ascissa:
            return ( getAscissa(a->coordinata) <= getAscissa(b->coordinata) );
            break;
        case ordinata:
            return ( getOrdinata(a->coordinata) <= getOrdinata(b->coordinata) );
            break;
        case matrice:
            if( getOrdinata(a->coordinata) == getOrdinata(b->coordinata) )
            {
                return ( getAscissa(a->coordinata) <= getAscissa(b->coordinata) );
            }
            else
            {
                return ( getOrdinata(a->coordinata) <= getOrdinata(b->coordinata) );
            }
            break;
        case altro:
            return 1;
            break;
        default:
            return 1;
            break;
    }
}

int CELLAgt(cella a, cella b, criterio c)
{
    switch(c)
    {
        case ascissa:
            return ( getAscissa(a->coordinata) > getAscissa(b->coordinata) );
            break;
        case ordinata:
            return ( getOrdinata(a->coordinata) > getOrdinata(b->coordinata) );
            break;
        case matrice:
            if( getOrdinata(a->coordinata) == getOrdinata(b->coordinata) )
            {
                return ( getAscissa(a->coordinata) > getAscissa(b->coordinata) );
            }
            else
            {
                return ( getOrdinata(a->coordinata) > getOrdinata(b->coordinata) );
            }
            break;
        case altro:
            return -1;
            break;
        default:
            return -1;
            break;
    }
}

double distanza(cella a, cella b)
{
    return sqrt( pow( (getAscissa(a->coordinata)-getAscissa(b->coordinata)), 2) + pow( (getOrdinata(a->coordinata)-getOrdinata(b->coordinata)), 2) );
}
