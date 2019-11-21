#ifndef GRUPPI_H
#define GRUPPI_H

typedef struct gruppi_s* gruppi;

void creaGruppi(gruppi* g);
void liberaGruppi(gruppi c);
void aggiungiGruppo(gruppi g, gruppo gr);
void stampaGruppi(gruppi g);
void ordinaGruppi(gruppi g); //Relazione d'ordine totale: criterio di cardinalità insieme decescente
void raggruppaPerTopologia(gruppi g);
int getDimG(gruppi g);
gruppo* getGruppi(gruppi g);
int getDimRaggruppamentiPerTopologia(gruppi g);
gruppi* getRaggruppamentiPerTopologia(gruppi g);
gruppo* getGruppiConCella(gruppi g, cella c, gruppo** cont);
gruppi getRaggruppamentoPerTopologiaContenenteGruppo(gruppi gr, gruppo g);
void aggiornaTest(gruppi g);

#endif //GRUPPI_H
