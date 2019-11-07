#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coordinata.h"
#include "cella.h"

struct cella_s
{
    char* nome;
    coordinata coordinata;
    int test;
};

void creaCella(cella* c, char* nome, float x, float y)
{
    *c = malloc(sizeof(struct cella_s));
    (*c)->nome = strdup(nome);
    creaCoordinata(&((*c)->coordinata), x, y);
    (*c)->test = 0;
}

void liberaCella(cella c)
{
    free(c->nome);
    liberaCoordinata(c->coordinata);
    free(c);
}

void stampaCella(cella c)
{
    printf("Cella denominata: %s, con coordinate: ", c->nome);
    stampaCoordinata(c->coordinata);
}
