#ifndef GRUPPI_H
#define GRUPPI_H

typedef struct gruppi_s* gruppi;

void creaGruppi(gruppi* c);
void liberaGruppi(gruppi c);
void aggiungiGruppo(gruppi g, gruppo gr);
void stampaGruppi(gruppi g);
void raggruppaPerTopologia(gruppi g);
int getDimG(gruppi g);
gruppo* getGruppi(gruppi g);
int getDimRaggruppamentiPerTopologia(gruppi g);
gruppi* getRaggruppamentiPerTopologia(gruppi g);
gruppo* getGruppiConCella(gruppi g, cella c, gruppo** cont);
void aggiornaTest(gruppi g);

#endif //GRUPPI_H
