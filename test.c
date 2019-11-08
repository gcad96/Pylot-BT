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
    celle c;
    allocaCelle(&c);
    stampaCelle(c);
    liberaCelle(c);

    teste t;
    allocaTeste(&t, NTESTE);
    //stampaTeste(t); //implementare per test
    liberaTeste(t);

    /*TEST DI CELLA.H E CELLE.H*/
}