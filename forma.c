#include <stdlib.h>
#include "coordinata.h"
#include "forma.h"

typedef enum
{
    quadrato,
    rettangolo,
    rombo
} figura;

struct forma_s
{
    figura forma;
    //vertice 0 in (a, b)
    coordinata* offSet;  //altri vertici in (a+coordinata[i]->x, b+coordinata[i]->y)
    int nVertici;
};

void creaForma(forma* f)
{
    *f = malloc(sizeof(struct forma_s));
}

void liberaForma(forma f)
{
    free(f);
}