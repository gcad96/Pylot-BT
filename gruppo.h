#ifndef GRUPPO_H
#define GRUPPO_H

typedef struct gruppo_s* gruppo;

void creaGruppo(gruppo* g);
void impostaGruppo(gruppo g, cella* cel, int q);
void liberaGruppo(gruppo g);
void stampaGruppo(gruppo g);

#endif //GRUPPO_H
