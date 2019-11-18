#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "utility.h"
#include "matrix.h"
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "celle.h"
#include "gruppo.h"
#include "gruppi.h"
#include "testa.h"
#include "teste.h"
#include "allocazione.h"
#include "algoritmo.h"

#define PIUVICINE 4

void definisciNumeroTeste(int* n);
void generaInsiemiDiCelle(celle c, gruppi* gr);
void definisciNumeroMaxCelle(int* n);
void path(celle c, int card, Matrice m);
void pathRic(cella u, celle c, int n, int card, int *coll, Matrice m);

void trovaPercorso()
{
    celle c;
    allocaCelle(&c);

    teste t; int nTeste;
    definisciNumeroTeste(&nTeste);
    allocaTeste(&t, nTeste);

    gruppi g;
    generaInsiemiDiCelle(c, &g);
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

void generaInsiemiDiCelle(celle c, gruppi* gr)
{
    int card;

    definisciNumeroMaxCelle(&card);
    Matrice m;
    creaMatrice(&m);
    int i, j;
    for(i=1; i<=card; i++)
    {
        path(c, i, m);
    }

    creaGruppi(gr);
    for(i=0; i<m->dim; i++)
    {
        gruppo g;
        creaGruppo(&g);
        int a;
        j=0;
        cella ins[L];
        while((a=m->v[i][j++])!=-1)
        {
            cella cel = (getInsieme(c))[a];
            ins[j-1] = cel;
        }
        int quantita = j-1;
        impostaGruppo(g, ins, quantita);
        aggiungiGruppo(*gr, g);
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

    fscanf(f, "%*s %*d\n%*s %*s %*s %*s %*s %d\n", n);

    if(*n<=0)
    {
        fprintf(stderr, "Errore nel file di configurazione.\n");
        return;
    }
}

void path(celle c, int card, Matrice m)
{
    cella* insieme = getInsieme(c);
    int dim = getDimC(c);

    int* coll = malloc(card*sizeof(int));
    int i;
    for(i=0; i<dim; i++)
    {
        cella u = insieme[i];
        int n = 0;

        pathRic(u, c, n, card, coll, m);
    }

    free(coll);
}

void pathRic(cella u, celle c, int n, int card, int *coll, Matrice m)
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
            if(!giaCons) pathRic(s, c, n, card, coll, m);
        }
        free(vicine);
    }
    else
    {
        coll[n] = -1;
        if(!checkDuplicati(m, coll))
            aggiungiVettore(m, coll);
    }
}
