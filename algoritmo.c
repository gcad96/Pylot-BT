#include <stdio.h>
#include <stdlib.h>
#include "cella.h"
#include "celle.h"
#include "allocazione.h"

void trovaPercorso()
{
    celle c;
    allocaCelle(&c);
    stampaCelle(c);
}
