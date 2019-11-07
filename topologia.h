#ifndef TOPOLOGIA_H
#define TOPOLOGIA_H

typedef struct topologia_s* topologia;

void creaTopologia(topologia* t, int dim, coordinata* c);
void liberaTopologia(topologia t);

#endif //TOPOLOGIA_H
