#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Lista
{
    float num;
    struct Lista *prox;
} Lista;

typedef struct Pilha
{
    Lista *topo;
} Pilha;

typedef struct calc
{
    char info[21];
    Pilha* p;
} calc;

Pilha* pilha_cria()
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo=NULL;
    return p;
}

void insere_pilha (Pilha* p,float num)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->num = num;
    novo->prox = p->topo;
    p->topo = novo;
}

int verifica_vazia(Pilha *p)
{
    return (p->topo == NULL);
}

void pilha_libera (Pilha* p)
{
    Lista* q = p->topo;
    while (q!=NULL)
    {
        Lista* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
}

float pilha_topo (Pilha* p)
{
    return (p->topo->num);
}

void exibe_pilha (Pilha *p)
{
    Lista* q;
    for(q=p->topo;q!=NULL;q=q->prox)
        printf("%.2f",q->num);
}

float remove_pilha (Pilha* p)
{
    Lista* t;
    float v;

    if (verifica_vazia(p))
    {
        printf("Pilha vazia.\n");
        exit(1);
    }

    t=p->topo;
    v=t->num;
    p->topo=t->prox;
    free(t);
    return v;
}

calc* calc_cria (char* formato)
{
  calc* c = (calc*) malloc(sizeof(calc));
  strcpy(c->info,formato);
  c->p = pilha_cria();
  return c;
}

void calc_operando (calc* c,float num)
{
    insere_pilha(c->p,num);
    printf(c->info,num);
}
void calc_operador(calc* c,char op)
{
    float v,v1,v2;
    int expoente;

    if(verifica_vazia(c->p))
    {
        v2=0.0;
    }
    else
    {
        v2=remove_pilha(c->p);
    }
    if(verifica_vazia(c->p))
    {
        v1=0.0;
    }
    else
    {
        v1=remove_pilha(c->p);
    }

    switch(op)
    {
        case '+':
            v = v2+v1;
            break;
        case '-':
            v = v1-v2;
            break;
        case '*':
            v = v1*v2;
            break;
        case '/':
            v=v1/v2;
            break;
        case '^':
        
        printf("Digite o valor do expoente:\n");
        scanf("%d",&expoente);
        expoente = 1/expoente;

        v = sqrt(v2);
        printf("Valor de v2^ = %f\n",v );
        break;

        default:
            printf("Opcao invalida!!\n");
            break;
    }

    insere_pilha(c->p,v);
    printf(c->info,v);

}
void calc_libera (calc* c)
{
    pilha_libera(c->p);
    free(c);
}
int main()
{
    char c;
    float v;
    calc* calc;

    calc = calc_cria("%.2f\n");
    do
    {
        scanf("%c",&c);
        if (c == '+' || c == '-' || c == '*' ||c == '/' || c == '^')
        {
            calc_operador(calc,c);
        }
        else
        {
            ungetc(c,stdin);
            if (scanf("%f",&v)==1)
            {
                calc_operando(calc,v);
            }
        }
    } while(c!='f');

    calc_libera(calc);
    return 0;
}


