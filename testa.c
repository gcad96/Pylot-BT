#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coordinata.h"
#include "forma.h"
#include "topologia.h"
#include "cella.h"
#include "gruppo.h"
#include "gruppi.h"
#include "testa.h"

struct testa_s
{
    gruppi accettabili;
    int fase;

    char* nome;
    topologia caratteristiche;

    forma forma;

    int cod;
};

void creaTesta(testa* t, char* nome, float d1, float d2, char* line)
{
    *t = malloc(sizeof(struct testa_s));
    (*t)->nome = strdup(nome);
    int fase = 0;
    (*t)->caratteristiche = NULL;
    //creaTopologia(&((*t)->caratteristiche), dim, c);
    creaForma(&((*t)->forma), d1, d2, line);
    (*t)->cod = -1;
}

void liberaTesta(testa t)
{
    free(t->nome);
    liberaTopologia(t->caratteristiche);
    liberaForma(t->forma);
    free(t);
}

void stampaTesta(testa t)
{
    printf("Testa denominata: %s, con superficie occupata: ", t->nome);
    stampaForma(t->forma);
}

int getCod(testa t)
{
    return t->cod;
}

void setCod(testa t, int id)
{
    t->cod = id;
}
