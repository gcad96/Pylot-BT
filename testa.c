#include <stdlib.h>
#include <string.h>
#include "coordinata.h"
#include "forma.h"
#include "topologia.h"
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
};

void creaTesta(testa* t, char* nome, float d1, float d2, char* line)
{
    *t = malloc(sizeof(struct testa_s));
    (*t)->nome = strdup(nome);
    int fase = 0;
    (*t)->caratteristiche = NULL;
    //creaTopologia(&((*t)->caratteristiche), dim, c);
    creaForma(&((*t)->forma), d1, d2, line);
}

void liberaTesta(testa t)
{
    free(t->nome);
    liberaTopologia(t->caratteristiche);
    liberaForma(t->forma);
    free(t);
}