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

void creaTesta(testa* t, char* nome, coordinata* c, int dim)
{
    *t = malloc(sizeof(struct testa_s));
    (*t)->nome = strdup(nome);
    int fase = 0;
    creaTopologia(&((*t)->caratteristiche), dim, c);
    creaForma(&((*t)->forma));
}

void liberaTesta(testa t)
{
    free(t->nome);
    liberaTopologia(t->caratteristiche);
    liberaForma(t->forma);
    free(t);
}