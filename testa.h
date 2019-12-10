/* Giovanni Cadau © */

#ifndef TESTA_H
#define TESTA_H

typedef struct testa_s* testa;

void creaTesta(testa* t, char* nome, float d1, float d2, char* line, float offset);
void liberaTesta(testa t);
void stampaTesta(testa t, FILE *f);
int getCod(testa t);
void setCod(testa t, int id);
void getOffsetSxeDx(testa t, float* sx, float* dx);
void getOffsetAltoeBasso(testa t, float* alto, float* basso);

#endif //TESTA_H