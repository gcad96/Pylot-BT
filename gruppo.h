#ifndef GRUPPO_H
#define GRUPPO_H

typedef struct gruppo_s* gruppo;

void creaGruppo(gruppo* g);
void impostaGruppo(gruppo g, cella* cel, int q);
int getFase(gruppo g);
void setFase(gruppo g, int fase);
int getMaxFase(gruppo g);
topologia getTopologia(gruppo g);
void liberaGruppo(gruppo g);
void stampaGruppo(gruppo g);
double distanzaG(gruppo a, gruppo b);
int ckeckPresenzaCella(gruppo g, cella c);
void setGruppoNullo(gruppo* g);
int isGruppoNullo(gruppo g);
#endif //GRUPPO_H
