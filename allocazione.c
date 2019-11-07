#include <stdio.h>
#include "utility.h"
#include "cella.h"
#include "celle.h"
#include "allocazione.h"

#define DAFILE 1
#define UFFICIALE 0
#define ALTRO 0

int acquisisciDati(celle c);

void allocaCelle()
{
    if(/*acquisisciDati()*/1)
    {

    }
    else
    {
        fprintf(stderr, "Errore durante l'apertura del file, celle non allocate\n");
    }
}

int acquisisciDati(celle c)
{

#if DAFILE

    FILE* f = fopen(FILE_INPUT, "r");
    if(f==NULL)     return 0;

    fgets(NULL, L, f);
#elif UFFICIALE

    #elif ALTRO

#else

#endif


    return 1;
}
