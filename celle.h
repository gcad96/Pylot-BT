#ifndef CELLE_H
#define CELLE_H

typedef struct celle_s* celle;

void creaCelle(celle* c);
void liberaCelle(celle c);
void aggiungiCella(celle c, cella cel);
void stampaCelle(celle c);
void ordinaCelle(celle c, criterio crit);
void generaDistanze(celle c, double ***m);
void getNCellePiuVicina(celle c, cella a, int N, cella* vic);
int getDim(celle c);
cella* getInsieme(celle c);
void calcolaDimensioniBatteria(celle c, float* base, float* altezza);

#endif //CELLE_H