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

//variavel global de ordem
int ord=1;

void inicializarGrafo(NO* grafo[], int n){
for(int i=0; i<n; i++){
 NO* novo = (NO*) malloc(sizeof(NO));
 novo->nVertice = i;
 novo->cor = 'B';
 novo->pai = -1;
 novo->ordem = 0;
 novo->minor = i;
 novo->critico = false;
 grafo[i] = novo;
}
}

void inicializarAdj(ADJ* adj[], int n, NO* grafo[]){

for(int i=0; i<n; i++){
 ADJ* novo = (ADJ*) malloc(sizeof(ADJ));
 novo->vertice = grafo[i];
 novo->prox = NULL;
 adj[i] = novo;
}
}


void DFS(ADJ* adj[], int i, int n){
ADJ* p;

    //verifica se o iterator nao ultrapassou o tamanho do vetor de adjacencias
    if(i<n){
        // verifica se existe vertices adjancentes na posicao e caso nao ele vai para a proxima posicao
        if(adj[i]->prox) p = adj[i]->prox;
        else DFS(adj,i+1,n);
    }else return;

            while(p){

            //caso o vizinho seja o pai ele passa para a proxima adjacencia
            if(p->vertice->nVertice == adj[i]->vertice->pai){
                p=p->prox;
                continue;
            }


            if(p->vertice->cor=='B'){
                    //Faz a primeira visita e atualiza as informacoes do vertice
                p->vertice->cor = 'C';
                ord++;
                p->vertice->ordem = ord;
                p->vertice->pai = i;


                        //verificar se a primeira adjacencia nao e o pai do vertice
                        if(adj[i]->prox->vertice->pai != p->vertice->nVertice){
                        //visita os adjacentes da adjacencia
                            DFS(adj,p->vertice->nVertice,n);

                            //Verificacao do minor na ida depois da ultima visitacao
                            if(p->vertice->nVertice != adj[i]->vertice->pai){
                                if(p->vertice->minor < adj[i]->vertice->minor){
                                    adj[i]->vertice->minor = p->vertice->minor;
                                }
                            }

                        }

            }else if(p->vertice->nVertice != adj[i]->vertice->pai){
                //Verificacao do minor na volta nas demais visitacoes da recursao
                    if(p->vertice->minor < adj[i]->vertice->minor){
                           adj[i]->vertice->minor = p->vertice->minor;
                    }
                }

                //verificacao do vertice critca a cada passada apos a atualizacao dos minors
                if(p->vertice->minor == p->vertice->nVertice && p->vertice->nVertice != 0) p->vertice->critico = true;
                else p->vertice->critico = false;

        //passa para a proxima adjacencia da lista ligado do vetor de adjacencias
        p=p->prox;

   }//while

    //vertice visitou todos os caminhos
   adj[i]->vertice->cor = 'P';

}//DFS

void printVertices(NO* ver[], int n){

    for(int i=0;i<n;i++){
        printf("========= VERTICE %d =========\n", i+1);
        printf("cor: %c \n",ver[i]->cor);
        printf("minor: %d \n",ver[i]->minor+1);
        printf("nVertice: %d \n",ver[i]->nVertice+1);
        printf("ordem: %d \n",ver[i]->ordem);
        printf("pai: %d \n",ver[i]->pai+1);
        printf("vertice critico: ");
        printf(ver[i]->critico ? "sim" : "nao");
        printf("\n");
    }
}

void inserir(NO* grafo[], int n, ADJ* adj[]){

    for(int i=0; i<n; i++){
        int x=1;
        ADJ* p = adj[i];

            while(x >= 0){

                printf("Digite o vertice adjacente de %d (numeros negativos para cancelar): \n", i+1);
                scanf("%d", &x);
                x--;
                    if(x<0)  break;


                    if(x>n){
                        printf("Digite um numero de vertice valido\n");
                        continue;
                        }

                ADJ* novo = (ADJ*) malloc(sizeof(ADJ));
                novo->vertice = grafo[x];
                novo->prox = NULL;

                    if(!adj[i]->prox) adj[i]->prox = novo;
                        else p->prox = novo;

                p = p->prox;

            }//while
    }//for
}//inserir

bool ehConexo(int n){
    if(ord!=n) return false;
        return true;
}

bool ehBiconexo(ADJ*adj[],int n){
    //comeca da segunda posicao pois a primeira � a raiz
    for(int i=1; i<n;i++){
        if(adj[i]->vertice->nVertice == adj[i]->vertice->minor) return false;
    }
    return true;
}


int main(){

printf("Insira o numero de vertices: ");
int n;
scanf("%d",&n);

//inicializar vertice do grafo
NO* grafo[n];
inicializarGrafo(grafo,n);

//inicializar adjacencias dos vertices
ADJ* adj[n];
inicializarAdj(adj,n,grafo);

//criar grafo com as adjacencias e vertices
inserir(grafo, n, adj);

//pintando o vertice inicial
adj[0]->vertice->cor = 'C';

//passeando pelo grafo, achando o minor e verificando o vertice critico
DFS(adj,0, n);

//visualizar status de cada vertice
printVertices(grafo, n);


printf("\n $$$$$$$$$$$ RESULTADO $$$$$$$$$$$$ \n");
if(ehConexo){
                          printf("E Conexo\n");
    if(ehBiconexo(adj, n)) printf("E biconexo\n");
        else printf("Nao e Biconexo\n");
        }else printf("Nao e Conexo\n");

}


