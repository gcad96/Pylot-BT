#include <stdlib.h>
#include <string.h>
#include "coordinata.h"
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
};

void creaTesta(testa* t, char* nome, coordinata* c, int dim)
{
    *t = malloc(sizeof(struct testa_s));
    (*t)->nome = strdup(nome);
    int fase = 0;
    creaTopologia(&((*t)->caratteristiche), dim, c);
}

void liberaTesta(testa t)
{
    free(t->nome);
    free(t);
}