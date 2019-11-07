#ifndef CELLA_H
#define CELLA_H

typedef struct cella_s* cella;

void creaCella(cella* c, char* nome, float x, float y);
void liberaCella(cella c);

#endif //CELLA_H