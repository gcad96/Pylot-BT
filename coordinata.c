#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"

struct coordinata_s
{
    float x;
    float y;
};

void creaCoordinata(coordinata* c, float x, float y)
{
    *c = malloc(sizeof(struct coordinata_s));
    (*c)->x = x;
    (*c)->y = y;
}

void liberaCoordinata(coordinata c)
{
    free(c);
}

void stampaCoordinata(coordinata c)
{
    printf("(%f, %f)", c->x, c->y);
}