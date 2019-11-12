#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "coordinata.h"
#include "cella.h"
#include "celle.h"
#include "testa.h"
#include "teste.h"
#include "allocazione.h"
#include "algoritmo.h"

#define PIUVICINE 4

void definisciNumeroTeste(int* n);
void generaInsiemiDiCelleContigue(celle c);
void definisciNumeroMaxCelle(int* n);
void path(celle c, int card);
void pathRic(cella u, celle c, int n, int card, int *coll);

void trovaPercorso()
{
    celle c;
    allocaCelle(&c);

    int nTeste;
    definisciNumeroTeste(&nTeste);

    teste t;
    allocaTeste(&t, nTeste);
}

void definisciNumeroTeste(int* n)
{
    FILE* f;
    if((f=fopen(FILE_INPUT_CONFIGURAZIONI, "r"))==NULL)
    {
        fprintf(stderr, "Errore nel caricamento del file di configurazione.\n");
        return;
    }

    *n=0;
    fscanf(f, "%*s %d", n);

    if(*n<=0)
    {
        fprintf(stderr, "Errore nel file di configurazione.\n");
        return;
    }
}

void generaInsiemiDiCelleContigue(celle c)
{
    int card;

    definisciNumeroMaxCelle(&card);
    int i, j, k;
    for(i=1; i<=card; i++)
    {
        path(c, card);
    }
}

void definisciNumeroMaxCelle(int* n)
{
    FILE* f;
    if((f=fopen(FILE_INPUT_CONFIGURAZIONI, "r"))==NULL)
    {
        fprintf(stderr, "Errore nel caricamento del file di configurazione.\n");
        return;
    }

    fscanf(f, "%*s %*d\n%*s %*s %*s %*s %*s %n", n);

    if(*n<=0)
    {
        fprintf(stderr, "Errore nel file di configurazione.\n");
        return;
    }
}

void path(celle c, int card)
{
    cella* insieme = getInsieme(c);
    int dim = getDim(c);

    int i;
    for(i=0; i<dim; i++)
    {
        cella u = insieme[i];
        int n = 0;
        int* coll = malloc(card*sizeof(int));

        pathRic(u, c, n, card, coll);

        free(coll);
    }
}

void pathRic(cella u, celle c, int n, int card, int *coll)
{
    coll[n++] = getId(u);
    if(n!=card)
    {
        cella* vicine = malloc(PIUVICINE*sizeof(cella)); getNCellePiuVicina(c, u, PIUVICINE, vicine);
        int j;
        for(j=0; j<PIUVICINE; j++)
        {
            cella s = vicine[j];
            int k;
            int giaCons = 0;
            for(k=0; k<n; k++)
            {
                if(coll[k]==getId(s))
                {
                    giaCons = 1;
                    break;
                }
            }
            if(!giaCons)    pathRic(s, c, n, card, coll);
        }
        free(vicine);
    }
    else
    {
        int i;
        for(i=0; i<n; i++)
        {
            printf("%d ", coll[i]);
        }
        printf("\n");
    }
}