#include <stdio.h>
#include "utility.h"
#include "cella.h"
#include "celle.h"
#include "allocazione.h"

#define DAFILE 1
#define UFFICIALE 0
#define ALTRO 0

int acquisisciDati(void** gen, int* stop, char* nome, float* x, float* y);

void allocaCelle(celle* cel)
{
    cella c;
    creaCelle(& (*cel));
    void* service = NULL;
    int stop = 0;
    char nome[L]; float x; float y;
    if(acquisisciDati(&service, &stop, nome, &x, &y))
    {
         while(!stop)
         {
             creaCella(&c, nome, x, y);
             aggiungiCella(*cel, c);
         }
    }
    else
    {
        liberaCelle(*cel);
        fprintf(stderr, "Errore durante il caricamento dei dati, celle non allocate\n");
    }
}

int acquisisciDati(void** gen, int* stop, char* nome, float* x, float* y)
{

#if DAFILE

    if(*gen==NULL)
    {
        FILE* f = fopen(FILE_INPUT, "r");
        if(f==NULL)     return 0;

        fgets(NULL, L, f);

        *gen = (void*) f;
    }
    else
    {
        FILE* f = (FILE*) (*gen);
        if ( fscanf(f, "%s %f %f", nome, x, y)!=3 )
        {
            *stop=1;
            fclose(f);
        }
    }

#elif UFFICIALE

#elif ALTRO

#else

#endif


    return 1;
}
