/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "celle.h"
#include "gruppo.h"
#include "testa.h"
#include "teste.h"

#define START 4
#define CRESCITA 2

struct teste_s
{
    testa* insieme;
    int dim;
    int realDim;
};

void creaTeste(teste* t)
{
    *t = malloc(sizeof(struct teste_s));
    (*t)->dim = 0;
    (*t)->realDim = START;
    (*t)->insieme = malloc(((*t)->realDim) * sizeof(testa));
}

void liberaTeste(teste t)
{
    free(t->insieme);
    free(t);
}

void aggiungiTesta(teste t, testa tes)
{
    if((t->dim) + 1 > (t->realDim) )
    {
        (t->realDim) *= CRESCITA;
        t->insieme = realloc(t->insieme, (t->realDim) * sizeof(testa));
    }

    setCod(tes, t->dim);
    t->insieme[(t->dim)++] = tes;
}

void stampaTeste(teste t)
{
    int i;
    for(i=0; i<t->dim; i++)
    {
        stampaTesta(t->insieme[i]);
        printf("\n");
    }
}

int getDimT(teste t)
{
    return t->dim;
}

int checkCompatibilitaTeste(teste t, int cod1, int cod2, gruppo g1, gruppo g2)
{
    testa t1 = t->insieme[cod1];
    float sx1, dx1;
    getOffsetSxeDx(t1, &sx1, &dx1);
    testa t2 = t->insieme[cod2];
    float sx2, dx2;
    getOffsetSxeDx(t2, &sx2, &dx2);
    coordinata c1 = posizioneMedia(g1);
    coordinata c2 = posizioneMedia(g2);
    if(getAscissa(c1)>=getAscissa(c2))
    {
        if(getAscissa(c2)+dx2 >= getAscissa(c1)-sx1)
        {
            return 0;
        }
    }
    else
    {
        if(getAscissa(c1)+dx1 >= getAscissa(c2)-sx2)
        {
            return 0;
        }
    }

    float* estremi1 = malloc(4* sizeof(float));
    estremiGruppo(estremi1, g1);
    float* estremi2 = malloc(4* sizeof(float));
    estremiGruppo(estremi2, g2);
    if(estremi1[Alto]>=estremi2[Alto])
    {
        if(estremi1[Basso]<=estremi2[Alto])
        {
            if(estremi1[Destra]>=estremi2[Destra])
            {
                if(estremi1[Sinistra]<=estremi2[Destra])
                {
                    free(estremi1);     free(estremi2);
                    return 0;
                }
            }
            else
            {
                if(estremi2[Destra]<=estremi1[Sinistra])
                {
                    free(estremi1);     free(estremi2);
                    return 0;
                }
            }
        }
    }
    else
    {
        if(estremi2[Basso]<=estremi1[Alto])
        {
            if(estremi1[Destra]>=estremi2[Destra])
            {
                if(estremi1[Sinistra]<=estremi2[Destra])
                {
                    free(estremi1);     free(estremi2);
                    return 0;
                }
            }
            else
            {
                if(estremi2[Destra]<=estremi1[Sinistra])
                {
                    free(estremi1);     free(estremi2);
                    return 0;
                }
            }
        }
    }

    free(estremi1);     free(estremi2);

    return 1;
}

int checkPosizioneTeste(teste t, gruppo* g, int*** compatibilita)
{
    *compatibilita = malloc(getDimT(t)*sizeof(int*));
    int successo = 1;

    int i, j;
    for(i=0; i<getDimT(t); i++)
    {
        (*compatibilita)[i] = malloc(getDimT(t)* sizeof(int));
        for(j=0; j<getDimT(t); j++)
        {
            (*compatibilita)[i][j] = 1; (*compatibilita)[j][i] = 1; io
        }
    }

    float* estremi1 = malloc(4* sizeof(float));     float* estremi2 = malloc(4* sizeof(float));

    for(i=0; i<getDimT(t); i++)
    {
        estremiGruppo(estremi1, g[i]);
        for(j=i+1; j<getDimT(t); j++)
        {
            estremiGruppo(estremi2, g[j]);
            if(estremi1[Sinistra]>=estremi2[Destra])
            {
                (*compatibilita)[i][j] = 0;
                successo = 0;
            }
        }
    }

    free(estremi1);     free(estremi2);

    return successo;
}