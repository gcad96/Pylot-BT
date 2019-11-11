#ifndef FORMA_H
#define FORMA_H

typedef struct forma_s* forma;

void creaForma(forma* f, float d1, float d2, char* line);
void liberaForma(forma f);
void stampaForma(forma f);

#endif //FORMA_H
