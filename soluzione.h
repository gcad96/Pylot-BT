/* Giovanni Cadau © */

#ifndef SOLUZIONE_H
#define SOLUZIONE_H

typedef struct soluzione_s* soluzione;

void memorizza(soluzione* s, int dim);
void aggiungiMovimento(soluzione s, gruppo* gr, int dim, int n);

#endif //SOLUZIONE_H