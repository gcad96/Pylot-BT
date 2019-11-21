/* Giovanni Cadau © */

#ifndef TESTE_H
#define TESTE_H

typedef struct teste_s* teste;

void creaTeste(teste* t);
void liberaTeste(teste t);
void aggiungiTesta(teste t, testa tes);
void stampaTeste(teste t);
int getDimT(teste t);
int checkCompatibilitaTeste(teste t, int cod1, int cod2, gruppo g1, gruppo g2);

#endif //TESTE_H