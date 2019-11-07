#ifndef TESTA_H
#define TESTA_H

typedef struct testa_s* testa;

void creaTesta(testa* t, char* nome, coordinata* c, int dim);
void liberaTesta(testa t);

#endif //TESTA_H
