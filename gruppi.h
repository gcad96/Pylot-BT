#ifndef GRUPPI_H
#define GRUPPI_H

typedef struct gruppi_s* gruppi;

void creaGruppi(gruppi* c);
void liberaGruppi(gruppi c);
void aggiungiGruppo(gruppi g, gruppo gr);
void stampaGruppi(gruppi g);

#endif //GRUPPI_H
