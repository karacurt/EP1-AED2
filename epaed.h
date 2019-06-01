#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>



typedef struct s {
int nVertice;
int pai;
char cor;
int minor;
int ordem;
bool critico;
}NO;


typedef struct g{
NO* vertice;
struct g* prox;
}ADJ;
