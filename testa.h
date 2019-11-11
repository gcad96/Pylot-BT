#ifndef TESTA_H
#define TESTA_H

typedef struct testa_s* testa;

void creaTesta(testa* t, char* nome, float d1, float d2, char* line);
void liberaTesta(testa t);
void stampaTesta(testa t);

#endif //TESTA_H
