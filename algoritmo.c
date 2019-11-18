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
void movimentoTeste(teste t, celle c, gruppi g);
void movimentoTesteRic(gruppo* attuale, int dim, celle c, gruppi g);
void estraiGruppi(gruppo** start, teste t, celle c, gruppi g);
void sceltaGruppi(gruppo* i, gruppo* scelte, int dim, gruppi g);

void trovaPercorso()
{
    celle c;
    allocaCelle(&c);

    teste t; int nTeste;
    definisciNumeroTeste(&nTeste);
    allocaTeste(&t, nTeste);

    gruppi g;
    generaInsiemiDiCelle(c, &g);

    movimentoTeste(t, c, g);
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
        cella* vicine = malloc(PIUVICINE*sizeof(cella));
        getNCellePiuVicine(c, u, PIUVICINE, vicine);
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

void movimentoTeste(teste t, celle c, gruppi g)
{
    gruppo** estratti = malloc((getDimT(t))* sizeof(gruppo*));
    estraiGruppi(estratti, t, c, g);
    gruppo* start = malloc((getDimT(t))* sizeof(gruppo));
    int i; for(i=0; i<getDimT(t); i++)
    {
        start[i] = estratti[i][0];
    }
    movimentoTesteRic(start, getDimT(t), c, g);
}

void estraiGruppi(gruppo** start, teste t, celle c, gruppi g)
{
    float base; float altezza;
    calcolaDimensioniBatteria(c, &base, &altezza);
    float porzioneX = base / (float) getDimT(t);
    float porzioneY = altezza / (float) getDimT(t);
    coordinata* coords = malloc(4*sizeof(coordinata));
    calcolaEstremiBatteria(c, coords, NULL);
    cella* cel = malloc(getDimT(t)* sizeof(cella));
    coordinata coor = coords[ASx];
    int i;
    for(i=0; getDimT(t); i++)
    {
        cel[i] = getCellaPiuVicina(c, coor);
        float asc = getAscissa(coor);
        float ord = getOrdinata(coor);
        liberaCoordinata(coor);
        creaCoordinata(&coor, asc+porzioneX, ord);
        getGruppiConCella(g, cel[i], &(start[i]));
    }
    liberaCoordinata(coor);

    for(i=0; i<4; i++)
    {
        if(i!=ASx)  liberaCoordinata(coords[i]);
    }
    free(coords);
    free(cel);
}

void movimentoTesteRic(gruppo* attuale, int dim, celle c, gruppi g)
{
    if(batteriaTestata(c))
        return;

    gruppo* next = malloc(dim*sizeof(gruppo));
    int j;
    for(j=0; j<dim; j++)    next[j] = NULL;
    sceltaGruppi(attuale, next, dim, g);
    movimentoTesteRic(next, dim, c, g);
}

void sceltaGruppi(gruppo* i, gruppo* scelte, int dim, gruppi g)
{
    gruppi* raggruppamenti = getRaggruppamentiPerTopologia(g);

    int l;
    for(l=0; l<dim; l++)
    {
        int fase = -1;
        gruppi elementi = raggruppamenti[l];
        gruppo p = i[l];
        gruppo* t = getGruppi(elementi);
        int dimT = getDimG(elementi);
        int j;
        double min = DBL_MAX;
        while(scelte[l] == NULL)
        {
            fase++;
            for(j=0; j<dimT; j++)
            {
                if((getFase(t[j]))==fase)
                {
                    double d = distanzaG(p, t[j]);
                    if(d<min && d!=0) // + comparazione e mediazione
                    {
                        int k;
                        int ok = 1;
                        for(k=0; k<l; k++)
                        {
//                            if(!checkCompatibilitaTeste(t[j], scelte[k])) // + ottimizazzione al contrario
                            {
                                ok = 0;
                                break;
                            }
                        }
                        if(ok)
                        {
                            min = distanzaG(p, t[j]);
                            scelte[l] = t[j];
                        }
                    }
                }
            }
        }
    }

    for(l=0; l<dim; l++)
    {

    }
}
