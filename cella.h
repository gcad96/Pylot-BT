#ifndef CELLA_H
#define CELLA_H

typedef enum criterio_s
{
    ascissa,
    ordinata,
    matrice,
    altro
} criterio ;

typedef struct cella_s* cella;

void creaCella(cella* c, char* nome, float x, float y);
void liberaCella(cella c);
void stampaCella(cella c);
int CELLAleq(cella a, cella b, criterio c);
int CELLAgt(cella a, cella b, criterio c);
double distanza(cella a, cella b);

#endif //CELLA_H