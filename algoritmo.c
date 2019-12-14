/* Giovanni Cadau © */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include "utility.h"
#include "partitore.h"
#include "combinatore.h"
#include "matrix.h"
#include "coordinata.h"
#include "topologia.h"
#include "cella.h"
#include "celle.h"
#include "gruppo.h"
#include "sortingGruppi.h"
#include "gruppi.h"
#include "movimento.h"
#include "soluzione.h"
#include "testa.h"
#include "teste.h"
#include "allocazione.h"
#include "algoritmo.h"

#define PIUVICINE 2
#define NSCELTE 1
#define MAXMOVIMENTITOLLERATI 200
#define LIVELLO_RIDONDANZA 0

void definisciNumeroTeste(int* n);
void generaInsiemiDiCelle(celle c, gruppi* gr, teste t);;
void definisciNumeroMaxCelle(int* n);
void path(celle c, int card, Matrice m);
void pathRic(cella u, celle c, int n, int card, int *coll, Matrice m);
bool movimentoTeste(teste t, celle c, gruppi g);
bool movimentoTesteRic(gruppo* attuale, int dim, teste t, celle c, gruppi g, int count, int* best, soluzione* s, movimento* movs);
void estraiGruppi(gruppo** start, teste t, celle c, gruppi g);
bool sceltaGruppi(gruppo* i, gruppo** scelte, int dim, teste tes, gruppi g);
bool sceltaGruppiRidondanti(gruppo* prec, gruppo* i, int dim, teste tes, gruppi g);
void eseguiTest(gruppo* g, int dim, gruppi gr);
void resetTest(celle c, gruppi g);
void ordinaPerCardinalita(gruppo* g);
void salvaDatiPerBacktrackInterno(gruppo* val, gruppo** backup, int dim);
void backtrackInterno(gruppo* val, gruppo* backup, int index);
void eliminaDatiPerBacktrackInterno(gruppo* backup);
void salvaDatiPerBacktrack(celle c, gruppi g, int* test, int* fasi);
void BackTrack(celle c, gruppi g, int* testt, int* fasi);
int compatibilita(teste t, gruppo* g, int dim);
void stampaAvanzamento(int passo, int tot);
void stampaCompletamento(int passo, int tot);
void stampaIntroduzione();
int ottimizzaGruppi(gruppo* g, int dim);

void trovaPercorso()
{
    celle c;
    allocaCelle(&c);

    teste t; int nTeste;
    definisciNumeroTeste(&nTeste);
    allocaTeste(&t, nTeste);

    gruppi g;
    generaInsiemiDiCelle(c, &g, t);

    bool successo;
    successo = movimentoTeste(t, c, g);
}

void definisciNumeroTeste(int* n)
{
    FILE* f;
    if((f=fopen(FILE_INPUT_CONFIGURAZIONI, "r"))==NULL)
    {
        fprintf(stderr, "Errore nel caricamento del file di configurazione.\n");
        return;
    }

    *n=0;
    fscanf(f, "%*s %d", n);

    if(*n<=0)
    {
        fprintf(stderr, "Errore nel file di configurazione.\n");
        return;
    }
}

void generaInsiemiDiCelle(celle c, gruppi* gr, teste t)
{
    int card;

    definisciNumeroMaxCelle(&card);
    Matrice m;
    creaMatrice(&m);
    int i, j;
    for(i=1; i<=card; i++)
    {
        path(c, i, m);
    }

    creaGruppi(gr);
    for(i=0; i<m->dim; i++)
    {
        gruppo g;
        creaGruppo(&g);
        int a;
        j=0;
        cella ins[L];
        while((a=m->v[i][j++])!=-1)
        {
            cella cel = (getInsieme(c))[a];
            ins[j-1] = cel;
        }
        int quantita = j-1;
        impostaGruppo(g, ins, quantita);
        if(gruppoCompatibile(t, g))
            aggiungiGruppo(*gr, g);
        else
            liberaGruppo(g);
    }

    raggruppaPerTopologia(*gr);
}

void definisciNumeroMaxCelle(int* n)
{
    FILE* f;
    if((f=fopen(FILE_INPUT_CONFIGURAZIONI, "r"))==NULL)
    {
        fprintf(stderr, "Errore nel caricamento del file di configurazione.\n");
        return;
    }

    fscanf(f, "%*s %*d\n%*s %*s %*s %*s %*s %d\n", n);

    if(*n<=0)
    {
        fprintf(stderr, "Errore nel file di configurazione.\n");
        return;
    }
}

void path(celle c, int card, Matrice m)
{
    cella* insieme = getInsieme(c);
    int dim = getDimC(c);

    int* coll = malloc(card*sizeof(int));
    int i;
    for(i=0; i<dim; i++)
    {
        cella u = insieme[i];
        int n = 0;

        pathRic(u, c, n, card, coll, m);
    }

    free(coll);
}

void pathRic(cella u, celle c, int n, int card, int *coll, Matrice m)
{
    coll[n++] = getId(u);
    if(n!=card)
    {
        cella* vicine = malloc(PIUVICINE*sizeof(cella));
        getNCellePiuVicine(c, u, PIUVICINE, vicine);
        int j;
        for(j=0; j<PIUVICINE; j++)
        {
            cella s = vicine[j];
            int k;
            int giaCons = 0;
            for(k=0; k<n; k++)
            {
                if(coll[k]==getId(s))
                {
                    giaCons = 1;
                    break;
                }
            }
            if(!giaCons) pathRic(s, c, n, card, coll, m);
        }
        free(vicine);
    }
    else
    {
        coll[n] = -1;
        if(!checkDuplicati(m, coll))
            aggiungiVettore(m, coll);
    }
}

bool movimentoTeste(teste t, celle c, gruppi g)
{
    bool successo = false;
    gruppo** estratti = malloc((getDimT(t))* sizeof(gruppo*));
    estraiGruppi(estratti, t, c, g);
    gruppo* start = malloc((getDimT(t))* sizeof(gruppo));

    Combinatore comb;
    int* val = malloc(getDimT(t)* sizeof(int));
    int i, j, k;
    for(i=0; i<getDimT(t); i++)
    {
        k = 0;
        while(!isGruppoNullo(estratti[i][k++]));
        k--;
        val[i] = k;
    }
    creaCombinatore(&comb, val, getDimT(t));
    free(val);

    int best = MAXMOVIMENTITOLLERATI;
    soluzione s = NULL;
    int caso = 0;
    stampaIntroduzione();
    while(caso<comb->dim)
    {
        int acc = 1;
        for(i=0; i<getDimT(t); i++)
        {
            start[i] = estratti[i][comb->v[caso][i]];
            int ok = 1;
            for(j=0; j<i; j++)
            {
                if(!checkCompatibilitaTeste(t, i, j, start[i], start[j])) // + ottimizzazione al contrario
                {
                    ok = 0;
                    break;
                }
            }
            if(!ok)
            {
                acc = 0;
                break;
            }
        }

        if(acc && ottimizzaGruppi(start, getDimT(t)))
        {
            movimento* movs = malloc(MAXMOVIMENTITOLLERATI* sizeof(movimento));
            eseguiTest(start, getDimT(t), g);
            int count = 1;
            movimento m; creaMovimento(&m, start, getDimT(t), count); movs[count-1] = m;
            if(movimentoTesteRic(start, getDimT(t), t, c, g, count + 1, &best, &s, movs))
                successo = true;
            resetTest(c, g);
            free(movs);
        }
        if(caso%100==0)
            stampaAvanzamento(caso, comb->dim);
        caso++;
    }
    stampaCompletamento(caso, comb->dim);

    if(successo)
        stampaSoluzione(s);
    else
        printf("Nessun movimento possibile.\n");

    return successo;
}

void estraiGruppi(gruppo** start, teste t, celle c, gruppi g)
{
    float base; float altezza;
    calcolaDimensioniBatteria(c, &base, &altezza);
    float porzioneX = base / (float) getDimT(t);
    float porzioneY = altezza / (float) getDimT(t);
    coordinata* coords = malloc(4*sizeof(coordinata));
    calcolaEstremiBatteria(c, coords, NULL);
    cella* cel = malloc(getDimT(t)* sizeof(cella));
    coordinata coor = coords[ASx];
    int i;
    for(i=0; i<getDimT(t); i++)
    {
        cel[i] = getCellaPiuVicina(c, coor);
        float asc = getAscissa(coor);
        float ord = getOrdinata(coor);
        liberaCoordinata(coor);
        creaCoordinata(&coor, asc+porzioneX, ord);
        getGruppiConCella(g, cel[i], &(start[i]));
        //ordinaPerCardinalita(start[i]);
    }
    liberaCoordinata(coor);

    for(i=0; i<4; i++)
    {
        if(i!=ASx)  liberaCoordinata(coords[i]);
    }
    free(coords);
    free(cel);
}

bool movimentoTesteRic(gruppo* attuale, int dim, teste t, celle c, gruppi g, int count, int* best, soluzione* s, movimento* movs)
{
    if(count-1 > *best)
        return false;

    if(batteriaTestata(c))
    {
        *best = count-1;
        memorizza(s, count-1, movs);
        return true;
    }


    gruppo** scelte = malloc(NSCELTE*sizeof(gruppo*));
    int j, k;
    for(k=0; k<NSCELTE; k++)
    {
        for(j=0; k<dim; k++)
        {
            scelte[k] = malloc(dim*sizeof(gruppo));
            scelte[k][j] = NULL;
        }
    }
    if(!sceltaGruppi(attuale, scelte, dim, t, g))      return false;

    Combinatore comb;
    int* val = malloc(getDimT(t)* sizeof(int));
    for(j=0; j<getDimT(t); j++)
    {
        k = 0;
        while(!isGruppoNullo(scelte[j][k++]));
        k--;
        val[j] = k;
    }
    creaCombinatore(&comb, val, getDimT(t));
    free(val);

    gruppo* next = malloc(dim*sizeof(gruppo));
    bool* succ = malloc((comb->dim)* sizeof(bool));
    int* test = malloc(getDimC(c)*sizeof(int)); int* fasi = malloc(getDimG(g)*sizeof(int));
    int caso = 0;
    while(caso<comb->dim)
    {
        for (j=0; j<dim; j++)
        {
            next[j] = scelte[j][comb->v[caso][j]];
            Partitore p;
            creaPartitore(&p, getDimT(t));
            for(j=0; j<p->dim; j++)
            {
                gruppo* v;  salvaDatiPerBacktrackInterno(next, &v, p->dimInterna);
                for(k=0; k<p->dimInterna; k++)
                {
                    if(!p->v[j][k])
                    {
                        gruppo superfluo; setGruppoSuperfluo(&superfluo);
                        next[k] = superfluo;
                    }
                }
                if(!sceltaGruppiRidondanti(attuale, next, dim, t, g))       return false;
                if(compatibilita(t, next, getDimT(t)))
                {
                    salvaDatiPerBacktrack(c, g, test, fasi);
                    eseguiTest(next, dim, g);
                    movimento m; creaMovimento(&m, next, getDimT(t), count); movs[count-1] = m;
                    succ[0] = movimentoTesteRic(next, dim, t, c, g, count + 1, best, s, movs);
                    BackTrack(c, g, test, fasi);
                }
                else  //backtrack
                {
                    for(k=0; k<p->dimInterna; k++)
                    {
                        if(!p->v[j][k])
                            backtrackInterno(next, v, k);
                    }
                    eliminaDatiPerBacktrackInterno(v);
                }
            }
        }
    }

    free(test); free(fasi);
    for(j=0; j<comb->dim; j++)
    {
        if(succ[j])
            return true;
    }

    return false;
}

bool sceltaGruppi(gruppo* i, gruppo** scelte, int dim, teste tes, gruppi g)
{
    int l;
    for(l=0; l<dim; l++)
    {
        int fase = -1;
        gruppo p = i[l];
        if(isGruppoVuoto(p))    p = getPrec(p);
        gruppi elementi = getRaggruppamentoPerTopologiaContenenteGruppo(g, p);
        gruppo* t = getGruppi(elementi);
        int dimT = getDimG(elementi);
        int maxFase = getMaxFase(p);
        int j;
        double min = DBL_MAX;
        int m;
        for(m=0; m<NSCELTE; m++)
        {
            while(scelte[l][m]==NULL && fase+1<=maxFase)
            {
                fase++;
                for(j=0; j<dimT; j++)
                {
                    if((getFase(t[j]))==fase)
                    {
                        double d = distanzaG(p, t[j]);
                        if(d<min && d!=0) // + comparazione e mediazione
                        {
                            min = distanzaG(p, t[j]);
                            scelte[l][m] = t[j];
                        }
                    }
                }
            }
            if(scelte[l][m]==NULL)
            {
                gruppo nullo; setGruppoNullo(&nullo);
                scelte[l][m] = nullo;
            }
            if(fase == (maxFase - LIVELLO_RIDONDANZA))
            {
                gruppo superfluo; setGruppoSuperfluo(&superfluo);
                scelte[l][m] = superfluo;
            }
        }
    }

    bool presente;
    for(l=0; l<dim; l++)
    {
        presente = false;
        int m;
        for(m=0; m<NSCELTE; m++)
        {
            if(scelte[l][m]!=NULL)
                presente = true;
        }
       if(!presente)    return false;
    }

    return true;
}

bool sceltaGruppiRidondanti(gruppo* prec, gruppo* i, int dim, teste tes, gruppi g)
{
    int first=0; int last=dim-1;
    int l;
    for(l=0; l<dim; l++)
    {
        if(isGruppoSuperfluo(i[l]))
        {
            gruppo p = prec[l];
            if(isGruppoVuoto(p))    p = getPrec(p);
            gruppi elementi = getRaggruppamentoPerTopologiaContenenteGruppo(g, p);
            gruppo* t = getGruppi(elementi);
            int dimT = getDimG(elementi);
            double min = DBL_MAX;
            int j;
            for(j=0; j<dimT; j++)
            {
                double d = distanzaG(p, t[j]);
                if(d<min && d!=0) // + comparazione e mediazione
                {
                    int k;
                    int ok = 1;
                    for(k=0; k<l; k++)
                    {
                        if(!isGruppoVuoto(i[k]))
                        {
                            if(!checkCompatibilitaTeste(tes, l, k, t[j], i[k])) // + ottimizazzione al contrario
                            {
                                ok = 0;
                                break;
                            }
                        }
                    }
                    if(ok)
                    {
                        min = distanzaG(p, t[j]);
                        i[l] = t[j];
                    }
                }
            }
        }
        if(isGruppoSuperfluo(i[l]))
        {
            if(l==first || l==last)
            {
                gruppo vuoto; setGruppoVuoto(&vuoto); setPrec(vuoto, prec[l]);
                i[l] = vuoto;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

void eseguiTest(gruppo* g, int dim, gruppi gr)
{
    int i;
    for(i=0; i<dim; i++)
    {
        if(!isGruppoVuoto(g[i]) && (!isGruppoSuperfluo(g[i])))    testGruppo(g[i]);
    }
    aggiornaTest(gr);
}

void resetTest(celle c, gruppi g)
{
    resetBatteria(c);

    gruppo* grs = getGruppi(g);
    int dim = getDimG(g);
    int i;
    for(i=0; i<dim; i++)
    {
        resetFase(grs[i]);
    }
}

void ordinaPerCardinalita(gruppo* g)
{
    int dim = 0;
    while(!isGruppoNullo(g[dim++]));
    SortGruppi(g, --dim);
}

void salvaDatiPerBacktrackInterno(gruppo* val, gruppo** backup, int dim)
{
    *backup = malloc(dim*sizeof(gruppo));
    int i;
    for(i=0; i<dim; i++)
        (*backup)[i] = val[i];
}

void backtrackInterno(gruppo* val, gruppo* backup, int index)
{
    val[index] = backup[index];
}

void eliminaDatiPerBacktrackInterno(gruppo* backup)
{
    free(backup);
}

void salvaDatiPerBacktrack(celle c, gruppi g, int* test, int* fasi)
{
    int i;

    cella* cel = getInsieme(c);
    int dimC = getDimC(c);
    for(i=0; i<dimC; i++)
        test[i] = isTest(cel[i]);

    gruppo* gru = getGruppi(g);
    int dimG = getDimG(g);
    for(i=0; i<dimG; i++)
        fasi[i] = getFase(gru[i]);
}

void BackTrack(celle c, gruppi g, int* testt, int* fasi)
{
    int i;

    cella* cel = getInsieme(c);
    int dimC = getDimC(c);
    for(i=0; i<dimC; i++)
    {
        if(testt[i])
            test(cel[i]);
        else
            reset(cel[i]);
    }

    gruppo* gru = getGruppi(g);
    int dimG = getDimG(g);
    for(i=0; i<dimG; i++)
    {
        setFase(gru[i], fasi[i]);
    }
}

int compatibilita(teste t, gruppo* g, int dim)
{
    int i;
    for(i=0; i<getDimT(t); i++)
    {
        if(!isGruppoVuoto(g[i]))
        {
            int k;
            for(k=i+1; k<getDimT(t); k++)
            {
                if(!isGruppoVuoto(g[k]))
                {
                    if(!checkCompatibilitaTeste(t, k, i, g[k], g[i]))
                        return 0;
                }
            }
        }
    }

    return 1;
}

void stampaAvanzamento(int passo, int tot)
{
    float agg = (float) passo / (float) tot;
    agg*=100.0f;
    printf("Working... %f%% \r", agg);
}

void stampaCompletamento(int passo, int tot)
{
    float agg = (float) passo / (float) tot;
    agg*=100.0f;
    printf("Working... %f%% \r", agg);
    printf("Completed.\n");
}

void stampaIntroduzione()
{
    printf("Un software realizzato da Giovanni Cadau ©.\n");
    printf("L'algoritmo e' ottimizzato in modo tale da trovare un percorso\ndelle teste che garantisca la totale copertura dell'intera\nbatteria, nel rispetto dei vincoli, minimizzando la distanza\ntotale percorsa dalle teste.\n");
    printf("\nAl fine di garantire una rapida esecuzione, l'algoritmo e'\nottimizzato in modo tale da iniziare l'esplorazione dello spazio\ndelle soluzioni partendo da punti diversi della batteria,\nche possono differire da un'esecuzione all'altra.\nTuttavia, le varie soluzioni proposte differiscono di una\nminima quantita' in termini di distanza totale percorsa (parametro\nda minimizzare) e, iterando l'esecuzione per 10 volte,\nsi ha una garanzia di convergenza alla soluzione ottima pari\nal 98%%.\n");
}

int ottimizzaGruppi(gruppo* g, int dim)
{
    int* dims = malloc(dim* sizeof(int));
    int i;
    for(i=0; i<dim; i++)
        dims[i] = getDimensione(g[i]);
    int ok;

    ok=0;
    for(i=0; i<dim; i++)
    {
        if(dims[i]==4)
            ok=1;
    }

    return ok;
}