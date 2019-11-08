#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "cella.h"
#include "celle.h"
#include "testa.h"
#include "teste.h"
#include "allocazione.h"

int definisciNumeroTeste(int* n);

void trovaPercorso()
{
    celle c;
    allocaCelle(&c);

    int nTeste;
    int out = definisciNumeroTeste(&nTeste);
    if(out==-1)
    {
        fprintf(stderr, "Errore nel caricamento del file di configurazione.\n");
        return;
    }
    if(out==0)
    {
        fprintf(stderr, "Errore nel caricamento del file di configurazione.\n");
        return;
    }

    teste t;
    allocaTeste(&t, nTeste);
}

int definisciNumeroTeste(int* n)
{
    FILE* f;
    if((f=fopen(FILE_INPUT_CONFIGURAZIONI, "r"))==NULL)     return -1;

    *n=0;
    fscanf(f, "%*s %d", n);

    if(*n<=0)       return 0;

    return 1;
}
