#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct No
{
	int teste;
	struct No *prox;
	struct No *ant;
}No;

typedef struct Aponta
{
	No* inicio;
	No* fim;
	int qtd;
}Aponta;

Aponta* cria_lista()
{
	Aponta* novo = (Aponta*) malloc (sizeof(Aponta));
	novo->inicio=NULL;
	novo->fim=NULL;
	novo->qtd=0;
	return novo;
}

void insere_inicio(Aponta* lis,int teste)
{
	No *novo = (No*) malloc(sizeof(No));
	novo->teste=teste;
	if(lis->inicio == NULL)
	{
		lis->inicio = novo;
		lis->fim = novo;
		novo->prox = NULL;
		novo->ant = NULL;
	}
	else
	{
	novo->ant=lis->inicio;
	novo->prox=lis->fim;
	lis->inicio=novo;
	lis->fim=novo;
	lis->qtd++;
	}
}

No* retornaNo (Aponta* elem,int indice)
{
	if (indice>=0 && indice<elem->qtd)
	{
		No* aux = elem->inicio;
		int i;
		for(i=0;i<indice;++i)
		{
			aux=aux->prox;
		}
		return aux;
	}
	else
	{
		printf("Indice invalido!\n");
		return NULL;
	}
}

void insere_ordenado (Aponta* lis,int teste)
{
	No* aux2 = NULL;
	No* aux = lis->inicio;
	int i=0;
	while(aux->prox!=NULL && aux->teste < teste) /*BUCAS NO*/
	{
		aux2=aux;
		aux=aux->prox;
		i++;
	}
	printf("Rodou o while\n");
	No* novo = (No*) malloc(sizeof(No));
	novo->teste = teste;
	novo->prox = retornaNo(lis, i+1);
	printf("retornaNo\n");
	retornaNo(lis, i+1)->ant = novo;
	aux2->prox = novo;

	printf("Novo->prox = aux2!\n");
	novo->ant=aux2;
	lis->qtd++;
}

No* buscaNO(No* lis,int busca)
{
	No* p;
	for(p=lis;p!=NULL;p=p->prox)
	{
		if(p->teste == busca)
		{
			return p;
		}
	}
	return NULL;
}

void insere_indice (Aponta* lis,int teste,int indice)
{
	No* novo = (No*) malloc(sizeof(No));
	novo->teste=teste;
	novo->prox=retornaNo(lis,indice)->prox;
	novo->ant=retornaNo(lis,indice);

	if (retornaNo(lis,indice)->prox == NULL)
	{
		lis->fim = novo;
	}
	else
	{
		retornaNo(lis,indice)->prox->ant = novo;
	}
	retornaNo(lis,indice)->prox = novo;
	lis->qtd++;
}

void retira (No* lis,int elem_a_ser_retirado)
{
	No* p = buscaNO(lis,elem_a_ser_retirado);

	if (p == NULL)
	{
	    printf("ELEMENTO NAO ENCONTRADO NA LISTA !!!\n");
	}
	/* CONDIÇÕES PARA RETIRAR DO ENCADEAMENTO.*/
	if (lis == p) /* TESTA SE É PRIMEIRO ELEMENTO.*/
	{
		lis=p->prox;
	}
	else
	{
		p->ant->prox = p->prox;
	}
	if (p->prox != NULL) /* TESTA SE É O ULTIMO ELEMENTO.*/
	{
		p->prox->ant = p->ant;
	}
	free(p);
}

int vazia(No* lis)
{
	if(lis->prox == NULL)
		return 1;
	else
		return 0;
}

void exibe(Aponta* lis)
{
	No* p =	lis->inicio;
	for(;p!=NULL;p=p->prox)
	{
		printf("%d\n",p->teste);
	}
}

void insere_fim (Aponta* lis,int teste)
{
	No* novo = (No*) malloc(sizeof(No));
	novo->teste=teste;
	if(lis->inicio == NULL)
	{
		lis->inicio = novo;
		lis->fim = novo;
		novo->prox = NULL;
		novo->ant = NULL;
	}
	else
	{
	novo->prox=NULL;
	novo->ant=lis->fim;
	lis->fim->prox=novo;
	lis->fim=novo;
	lis->qtd++;
	}
}

int main()
{
	int opcao,indice,elemento;
	Aponta* novo = cria_lista();
	
	do
	{
		printf("1 Inserir um elemento no inicio da lista!\n");
		printf("2 Inserir um elemento no fim da lista!\n");
		printf("3 Inserir um elemento ordenado na lista!\n");
		printf("4 Inserir um elemento a partir do indice na lista!\n");
		printf("5 Retirar um elemento no fim da lista\n");
		printf("6 Retirar um elemento no inicio da lista\n");
		printf("7 Retirar um elemento a partir do indice na lista\n");
		printf("8 Mostrar o tamanho da lista:\n");
		printf("9 Exibir a lista!\n");
		printf("Digite a opcao:\n");
		scanf("%d",&opcao);

		switch(opcao)
		{
			case 1:
				printf("Informe o elemento a ser inserido:\n");
				scanf("%d",&elemento);
				insere_inicio(novo,elemento);
				system("clear");
				break;
			case 2:
				printf("Informe o elemento a ser inserido:\n");
				scanf("%d",&elemento);
				insere_fim(novo,elemento);
				system("clear");
				break;
			case 3:
				printf("Informe o elemento a ser inserido:\n");
				scanf("%d",&elemento);
				insere_ordenado(novo,elemento);
				break;
			case 4:
				printf("Insira a posicao a ser inserido na lista:\n");
				scanf("%d",&indice);
				printf("Informe o elemento a ser inserido:\n");
				scanf("%d",&elemento);
				insere_indice(novo,elemento,indice);
				break;
			case 5:
				/*exibe(elem);*/
				break;
			case 6:
				/*retira_fim(elem);*/
				break;
			case 7:
				system("clear");
				exibe(novo);
				break;
			case 8:
				system("clear");
				printf("O tamanho da lista e: %d\n",novo->qtd);
				break;
			case 9:
				system("clear");
				exibe(novo);
				break;
			default:
				printf("opcao invalida!!\n");
				break;
		}
	} while(opcao!='i');

	return 0;
}