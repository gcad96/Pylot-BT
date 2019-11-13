#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "coordinata.h"
#include "cella.h"
#include "sortingCelle.h"
#include "celle.h"

#define START 4
#define CRESCITA 2

typedef enum estremo_s
{
    Alto,
    Basso,
    Destra,
    Sinistra
} estremo ;

struct celle_s
{
    cella* insieme;
    int dim;
    int realDim;
};

float estremiBatteria(celle c, estremo e);

void creaCelle(celle* c)
{
    *c = malloc(sizeof(struct celle_s));
    (*c)->dim = 0;
    (*c)->realDim = START;
    (*c)->insieme = malloc(((*c)->realDim)*sizeof(cella));
}

void liberaCelle(celle c)
{
    free(c->insieme);
    free(c);
}

void aggiungiCella(celle c, cella cel)
{
    if( (c->dim)+1 > (c->realDim) )
    {
        (c->realDim) *= CRESCITA;
        c->insieme = realloc(c->insieme, (c->realDim)*sizeof(cella));
    }

    setId(cel, c->dim);
    c->insieme[(c->dim)++] = cel;
}

void stampaCelle(celle c)
{
    int i;
    for(i=0; i<c->dim; i++)
    {
        stampaCella(c->insieme[i]);
        printf("\n");
    }
}

void ordinaCelle(celle c, criterio crit)
{
    switch(crit)
    {
        case ascissa:
            SortCelle(c->insieme, c->dim, ascissa);
            break;
        case ordinata:
            SortCelle(c->insieme, c->dim, ordinata);
            break;
        case matrice:
            SortCelle(c->insieme, c->dim, matrice);
            break;
        case altro:
            break;
        default:
            break;
    }
}

void generaDistanze(celle c, double*** m)
{
    int i, j;

    *m = malloc((c->dim) * sizeof(double*));
    for(i=0; i<c->dim; i++)
    {
        (*m)[i] = malloc((c->dim) * sizeof(double));
        for(j=0; j<c->dim; j++)
        {
            (*m)[i][j] = distanza(c->insieme[i], c->insieme[j]);
        }
    }
}

void getNCellePiuVicina(celle c, cella a, int N, cella* vic)
{
    int round=1;
    int index=0;
    double* mins = malloc(N* sizeof(double));
    mins[0] = 0;

    while(round<=N)
    {
        double min = DBL_MAX;
        int i;
        for(i=0; i<c->dim; i++)
        {
            double d=distanza(a, c->insieme[i]);
            if(d<min && d>mins[round-1])
            {
                min = d;
                index = i;
            }
        }

        mins[round] = min;
        vic[round-1] = c->insieme[index];
        round++;
    }

    free(mins);
}

int getDim(celle c)
{
    return c->dim;
}

cella* getInsieme(celle c)
{
    return c->insieme;
}

void calcolaDimensioniBatteria(celle c, float* base, float* altezza)
{
    *base = estremiBatteria(c, Alto) - estremiBatteria(c, Basso);
    *altezza = estremiBatteria(c, Destra) - estremiBatteria(c, Sinistra);
}

float estremiBatteria(celle c, estremo e)
{
    int i;
    float m;
    float v;
    switch(e)
    {
        case Alto:
        {
            m = FLT_MIN;
            for(i=0; i<c->dim; i++)
            {
                if((v=getOrdinata(getCoordinata(c->insieme[i])))>m)
                {
                    m = v;
                }
            }
            break;
        }
        case Basso:
        {
            m = FLT_MAX;
            for(i=0; i<c->dim; i++)
            {
                if((v=getOrdinata(getCoordinata(c->insieme[i])))<m)
                {
                    m = v;
                }
            }
            break;
        }
        case Destra:
        {
            m = FLT_MIN;
            for(i=0; i<c->dim; i++)
            {
                if((v=getAscissa(getCoordinata(c->insieme[i])))>m)
                {
                    m = v;
                }
            }
            break;
        }
        case Sinistra:
        {
            m = FLT_MAX;
            for(i=0; i<c->dim; i++)
            {
                if((v=getAscissa(getCoordinata(c->insieme[i])))<m)
                {
                    m = v;
                }
            }
            break;
        }
        default:
            return 0;
    }

    return m;
}