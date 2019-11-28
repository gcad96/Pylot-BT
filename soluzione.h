/* Giovanni Cadau © */

#ifndef SOLUZIONE_H
#define SOLUZIONE_H

typedef struct soluzione_s* soluzione;

void memorizza(soluzione* s, int dim, movimento* movimenti);
void stampaSoluzione(soluzione s);

#endif //SOLUZIONE_H