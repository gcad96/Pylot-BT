#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "cella.h"
#include "celle.h"
#include "testa.h"
#include "teste.h"
#include "allocazione.h"

void definisciNumeroTeste(int* n);
void generaInsiemiDiCelleContigue(celle c);
void definisciNumeroMaxCelle(int* n);

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