#ifndef GRUPPI_H
#define GRUPPI_H

typedef struct gruppi_s* gruppi;

void creaGruppi(gruppi* c);
void liberaGruppi(gruppi c);
void aggiungiGruppo(gruppi g, gruppo gr);
void stampaGruppi(gruppi g);
void raggruppaPerTopologia(gruppi g, topologia* t, int dimT);
int getDimG(gruppi g);
gruppo* getGruppi(gruppi g);
int getDimRaggruppamentiPerTopologia(gruppi g);
gruppi* getRaggruppamentiPerTopologia(gruppi g);

#endif //GRUPPI_H
