#ifndef GRUPPO_H
#define GRUPPO_H

typedef struct gruppo_s* gruppo;

void creaGruppo(gruppo* g);
void liberaGruppo(gruppo g);
void setBaricentro(gruppo g);

#endif //GRUPPO_H
