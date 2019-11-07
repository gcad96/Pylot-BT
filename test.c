#include <stdio.h>
#include <stdlib.h>
#include "cella.h"
#include "celle.h"
#include "allocazione.h"

int main(void)
{
    celle c;
    allocaCelle(&c);
    stampaCelle(c);
}