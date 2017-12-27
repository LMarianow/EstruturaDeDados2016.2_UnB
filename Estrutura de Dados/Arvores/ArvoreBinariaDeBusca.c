#include <stdio.h>
#include <stdlib.h>

/** Estrutura do NÓ da árvore **/
typedef struct No
{
    int dado; /*Valor numerico*/
    struct No *esq, *dir; /*Ponteiro pra Esquerda e pra direita*/
} No;

No* arv_criavazia ()
{
    return NULL;
}

No* arv_cria (int dado, No* sae, No* sad)
{
    No* p = (No*)malloc(sizeof(No));
    p->dado = dado;
    p->esq = sae;
    p->dir = sad;
    return p;
}

int arv_vazia (No* a)
{
  return a == NULL;
}

No* arv_libera (No* a)
{
    if (!arv_vazia(a))
    {
        arv_libera(a->esq); /* libera sae*/
        arv_libera(a->dir); /* libera sad*/
        free(a);            /* libera raiz*/
    }
    return NULL;
}

/* percorrer uma árvore utilizando o algoritmo de pré-ordem */
void percorre_preordem(No * arvore)
{
    if( arvore == NULL )
    {
        return;
    }

    printf(" %d", arvore->dado);
    percorre_preordem(arvore->esq);
    percorre_preordem(arvore->dir);

    return;
}

/* percorrer uma árvore utilizando o algoritmo de pós-ordem */
void percorre_posordem(No * arvore)
{
    if( arvore == NULL )
    {
        return;
    }

    percorre_posordem(arvore->esq);
    percorre_posordem(arvore->dir);
    printf(" %d", arvore->dado);

    return;
}
/* percorrer uma árvore utilizando no modo em-ordem */
void percorre_emordem(No * arvore)
{
    if( arvore == NULL )
    {
        return;
    }

    percorre_emordem(arvore->esq);
    printf(" %d", arvore->dado);
    percorre_emordem(arvore->dir);

    return;
}

void imprimir(No* v, int nivel)
{
    int i;

    if( v != NULL )
    {
        imprimir(v->esq, nivel+1);
        for(i=0; i<nivel; i++)
        {
            printf(" ");
        }
        printf("%d\n", v->dado);
        imprimir(v->dir, nivel+1);
    }
    return;
}

/* mostra os nós de um intervalo informado */
int busca (No* t, int v)
{
    if (arv_vazia(t))
        return 0; /*árvore vazia: não encontrou*/
    else if (v == t->dado)
        return 1; /*Valor encontrado*/
    else if (busca(t->esq, v))
        return 1; /*Valor encontrado na esquerda*/
    else
        return busca(t->dir, v); /*Valor encontrado na direita*/
}

int altura (No* a)
{
    int e,d;

    if (arv_vazia(a))
        return 0;

    e = altura(a->esq);
    d = altura(a->dir);

    if(e > d)
        return e+1;

    return d+1;
}

No* remove_ArvBin (No* r, int valor)
{
    if (arv_vazia(r))
        return NULL;
    else if (r->dado > valor)
        r->esq = remove_ArvBin(r->esq, valor);
    else if (r->dado < valor)
        r->dir = remove_ArvBin(r->dir, valor);
    else
    { /* achou o nó a remover */
        /* nó sem filhos (Folhas) */
        if (r->esq == NULL && r->dir == NULL)
        {
            free (r);
            r = NULL;
        }
        /* nó só tem filho à direita */
        else if (r->esq == NULL)
        {
            No* t = r;
            r = r->dir;
            free (t);
        }
        /* só tem filho à esquerda */
        else if (r->dir == NULL)
        {
            No* t = r;
            r = r->esq;
            free (t);
        }
        /* nó tem os dois filhos */
        else
        {
            No* f = r->esq;
            while (f->dir != NULL)
            {
                f = f->dir;
            }
            r->dado = f->dado; /* troca as informações */
            f->dado = valor;
            r->esq = remove_ArvBin(r->esq,valor);
        }
    }
    return r;
}

int main()
{
  int x, y, opcao;
  No* arv = arv_criavazia();

  do
  {
    printf("\nEntre com a opcao:");
    printf("\n ---1:Inserir");
    printf("\n ---2:Pesquisar");
    printf("\n ---3:Excluir");
    printf("\n ---4:Altura da arvore");
    printf("\n ---5:Imprimir ordem:");
    printf("\n ---6:Imprimir pre-ordem");
    printf("\n ---7:Imprimir pos-ordem");
        printf("\n ---8:Imprimir Arvore!\n");
    printf("\n ---9:sair do programa\n");
    printf("\n->");
    scanf("%d", &opcao);

    switch(opcao)
    {
      case 1:
      {
        printf("\n Informe o valor a ser inserido:\n");
        scanf("%d", &x);
        arv=abb_insere(arv, x);
        break;
      }
      case 2:
      {
        printf("\n Informe o valor a ser pesquisado:\n");
        scanf("%d", &x);
        if(busca(arv, x) != 0)
        {
          printf(" Encontrado\n");
        }
        else
        {
          printf(" Nao encontrado!\n");
        }
        break;
      }
      case 3:
      {
        printf("\n Informe o valor a ser excluido:\n");
        scanf("%d", &x);
        remove_ArvBin(arv, x);
        break;
      }
      case 4:
      {
        printf("A altura da arvore e:%d\n",altura(arv));
        break;
      }
      case 5:
      {
        printf("\nImprimindo arvore:\n");
        percorre_emordem(arv);
        printf("\n");
        break;
      }
      case 6:
      {
        printf("\nImprimindo arvore pre-ordem:\n");
        percorre_preordem(arv);
        printf("\n");
        break;
      }
      case 7:
      {
        printf("Imprimindo arvore pos-ordem:\n");
        percorre_posordem(arv);
        printf("\n");
        break;
      }
            case 8:
      {
        printf("Imprimindo formato arvore:\n");
        imprimir(arv,0);
        printf("\n");
        break;
      }
      case 9:
      {
          exit(0);
        break;
      }
      default:
            {
                exit(0);
                break;
            }
    }
  } while(opcao!=10);

  return 0;
}