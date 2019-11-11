#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "coordinata.h"
#include "forma.h"

#define B "base"
#define H "altezza"
#define DD "diagonaleMaggiore"
#define D "diagonaleMinore"

typedef enum figura_e
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

void creaForma(forma* f, float d1, float d2, char* line)
{
    *f = malloc(sizeof(struct forma_s));
    char dd1[L];
    char dd2[L];
    sscanf(line, "%*s %s %s", dd1, dd2);
    if( (strcmp(dd1, B)==0) && (strcmp(dd2, H)==0) )
    {
        if(d1==d2)
        {
            (*f)->forma = quadrato;
            (*f)->nVertici = 4;
            (*f)->offSet = malloc(3* sizeof(coordinata));
            creaCoordinata(&((*f)->offSet[0]), d1, 0);
            creaCoordinata(&((*f)->offSet[1]), 0, d1);
            creaCoordinata(&((*f)->offSet[2]), d1, d1);
        }
        else
        {
            (*f)->forma = rettangolo;
            (*f)->nVertici = 4;
            (*f)->offSet = malloc(3* sizeof(coordinata));
            creaCoordinata(&((*f)->offSet[0]), d1, 0);
            creaCoordinata(&((*f)->offSet[1]), 0, d2);
            creaCoordinata(&((*f)->offSet[2]), d1, d2);
        }
    }
    else if( (strcmp(dd1, DD)==0) && (strcmp(dd2, D)==0) )
    {
        (*f)->forma = rombo;
        (*f)->nVertici = 4;
        (*f)->offSet = malloc(3* sizeof(coordinata));
        creaCoordinata(&((*f)->offSet[0]), d1/2, d2/2);
        creaCoordinata(&((*f)->offSet[1]), 0, d2);
        creaCoordinata(&((*f)->offSet[2]), -d1/2, d2/2);
    }
    else
    {
        fprintf(stderr, "Errore nella forma della testa.\n");
    }
}

void liberaForma(forma f)
{
    int i;
    for(i=0; i<f->nVertici; i++)
    {
        liberaCoordinata(f->offSet[i]);
    }
    free(f->offSet);

    free(f);
}

void stampaForma(forma f)
{
    printf("vertici con coordinate: ");

    coordinata v0;
    creaCoordinata(&v0, 0, 0);
    stampaCoordinata(v0);
    liberaCoordinata(v0);
    printf(", ");
    int i;
    for(i=0; i<f->nVertici-2; i++)
    {
        stampaCoordinata(f->offSet[i]);
        printf(", ");
    }
    stampaCoordinata(f->offSet[i]);

    printf("\n");
}