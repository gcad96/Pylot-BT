#ifndef COORDINATA_H
#define COORDINATA_H

typedef struct coordinata_s* coordinata;

void creaCoordinata(coordinata* c, float x, float y);
void liberaCoordinata(coordinata c);

#endif //COORDINATA_H