#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrice_s* Matrice;

void creaMatrice(Matrice* m);
void liberaMatrice(Matrice m);
void aggiungiVettore(Matrice m, int* a);
int checkDuplicati(Matrice m, int* v);

#endif //MATRIX_H
