#include <stdio.h>
#include <stdlib.h>
#include "cella.h"
#include "celle.h"
#include "testa.h"
#include "teste.h"
#include "allocazione.h"

#define NTESTE 4

int main(void)
{
    setbuf(stdout, 0);
    setbuf(stderr, 0);

    celle c;
    allocaCelle(&c);
    stampaCelle(c);

    teste t;
    allocaTeste(&t, NTESTE);
    stampaTeste(t);

    ordinaCelle(c, ascissa);

    double**m; generaDistanze(c, &m);
    int i, j;
    for(i=0; i<getDim(c); i++)
    {
        for(j=0; j<getDim(c); j++)
        {
            printf("%lf  ", m[i][j]);
        }
        printf("\n");
    }

    liberaCelle(c);
    liberaTeste(t);
}