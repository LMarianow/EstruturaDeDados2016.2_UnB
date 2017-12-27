#include <stdio.h>
#include <stdlib.h>

typedef struct Lista
{
char aluno[40];
float nota;
struct Lista *prox;
struct Lista *ant;


}Lista;

typedef struct aponta{
	struct Lista *inicio;
	struct Lista *fim;
	int quantidade;
}aponta;


Lista *aloca(){
	Lista *novo = (Lista*)malloc(sizeof(Lista));
	if (novo !=NULL){
		return novo;
	}
	printf("ERRO NA ALOCACAO!\n");
	exit(1);	
}

aponta *Cria_Lista()
{
aponta *novo = (aponta *)malloc(sizeof(aponta));

novo->inicio = NULL;
novo->fim = NULL;
novo->quantidade = 0;
return novo;
}

int vazia (aponta *elem)
{

	if(elem == NULL)
	{/*Lista eh valida? */
		return 0;
	}

	else 
	{
		return 1; /*Lista nao esta vazia */
	}

}

void insere_inicio(aponta *elem)
{
	Lista *novo = aloca();
	novo->ant = NULL;
	printf("Digite o nome:\n");
	getchar();
	scanf("%[^\n]",novo->aluno);
	
	printf("Digite a nota:\n");
	scanf("%f",&novo->nota);
	printf("RODOU\n");
	if(elem->inicio == NULL) /*Se o inicio for NULL , eh pq a lista esta vazia*/
	{
		novo->ant = NULL;
		novo->prox = NULL;
		elem->inicio = novo;
		elem->fim = novo;
		elem->quantidade++;
		printf("Quantidade de elementos: %d\n", elem->quantidade);
	}

	else
	{
		printf("ELSE!\n");		
		novo->ant = NULL;
		novo->prox = elem->inicio; 
		elem->inicio = novo;
		elem->quantidade++;
		printf("Quantidade de elementos: %d\n", elem->quantidade);
		
	}
}

void insere_fim(aponta *elem)
{
	Lista *novo = aloca();
	novo->prox = NULL;
	printf("Digite o nome:\n");
	getchar();
	scanf("%[^\n]",novo->aluno);
	
	printf("Digite a nota:\n");
	scanf("%f",&novo->nota);
	
	if(elem->inicio == NULL)/*Se a lista esta vazia */
	{
		novo->prox=NULL;
		novo->ant = NULL;
		elem->inicio = novo;
		elem->fim = novo;
		elem->quantidade++;
		printf("Quantidade de elementos: %d\n", elem->quantidade);
	}
	else
	{
		Lista *aux = elem->inicio;
		while(aux->prox !=NULL)
		{
			aux = aux->prox;
		}
		printf("elem->fim = %s  %f\n",elem->fim->aluno , elem->fim->nota);
		aux->ant = aux;
		aux->prox = novo;
		elem->quantidade++;
		printf("Quantidade de elementos: %d\n", elem->quantidade);
		elem->fim = novo;
		elem->fim->ant = aux; /* O anterior do ultimo elemento aponta para o penultimo */		
	}
}
Lista *retorne_Lista(aponta *elem,int indice)
{
	if(indice >= 0 && indice < elem->quantidade)
	{
		Lista *aux = elem->inicio;
		int i;
		for(i=0;i< indice; i++)
		{
			aux = aux->prox;
		}

		return aux;
	}
	else{
	printf("Indice invalido!\n");
	return NULL;
		}
}

void insere_escolha(aponta *elem, int indice)
{	

	if(indice > elem->quantidade)
	{
		printf("Posicao inexistente!!\n");
		return ;
	}
	if (indice == 0)
	{
		insere_inicio(elem);
		return ;
	}

	if (indice == elem->quantidade)
	{
		insere_fim(elem);
		return ;
	}
	else
	{	

		Lista *novo = aloca();
		printf("Insira o nome do novo aluno:\n");
		getchar();
		scanf("%[^\n]",novo->aluno);
		printf("Digite a nota: \n");
		scanf("%f",&novo->nota);

		Lista *atual = retorne_Lista(elem,indice);
			if(atual != NULL)
			{
			Lista  *anterior = retorne_Lista(elem,indice-1); 
			  anterior->prox = novo;
			  novo->prox = atual;
			  novo->ant = anterior;
			  atual->ant = novo;
			  /*printf("Anterior->prox = %s , %f \n",anterior->prox->aluno , anterior->prox->nota );
			  printf("Listavo->anterior = %s , %f\n" , novo->ant->aluno , novo->ant->nota);
			  printf("PROXIMO ANTERIOR: %s , %f \n",anterior->prox->aluno , anterior->prox->nota);
			  printf("ANTERIOR Direita: %s , %f \n",atual->ant->aluno , atual->ant->nota);*/

			}
			  
		elem->quantidade++;
		printf("Quantidade de elementos: %d\n", elem->quantidade);
	}
}

void retira_fim(aponta *elem)
{
	if (vazia(elem) == 1) /*Lista nao esta vazia */
	{
		Lista *aux = elem->fim->ant; /* Guarde a referencia do fim em um auxiliar */
		aux->prox = NULL;
		free(elem->fim);
		printf("Elemento foi retirado!\n");
		printf("nome: %s , nota: %f\n",aux->aluno,aux->nota );
		elem->fim = aux; /* Agora o fim sera o elemento anterior do auxiliar */
		elem->quantidade--;

	}
	else {
	printf("Lista esta vazia!\n");
	return ;
	}
}

Lista *indice_no(aponta *Fila, int indice) /* Passando indice e devolvendo um no*/
{	
	if(indice >= 0 && indice < Fila->quantidade)
	{ /* Indice tem que ser menor que o tamanho da lista */
		Lista *noaux = Fila->inicio;
		int i;
		for(i=0; i<indice; i++)
		{
			noaux = noaux->prox;		
		}

		return noaux;
	}
	else {
		printf("Indice invalido!\n");
		return NULL;
	}
}

int retorna_indice(aponta *Fila , Lista *no){

	if (no != NULL) /* Se o noh for valido , faca */
	{
		Lista *auxiliar = Fila->inicio;
		int indice =0;

		while(auxiliar != no && auxiliar !=NULL)
		{
			auxiliar = auxiliar->prox;
			indice++;
		}

		if(auxiliar != NULL)
		{
			return indice;
	   	}
	}
	printf("Lista nao pertence a Fila!\n");
	return -1;
}

void Troca_nos(aponta *Fila, Lista *noA , Lista *noB)
{
	if(noA == noB) 
	{
		return;
	}

	int indiceA = retorna_indice(Fila, noA);/* Pegando indice de A */
	int indiceB = retorna_indice(Fila, noB);/* Pegando indice de B */

	if(indiceA > indiceB) /*Se a noh A for a cabeca,faca*/
	{
		noA = noB;
		noB  = indice_no(Fila, indiceA);

		indiceA = indiceB;
		indiceB = retorna_indice(Fila, noB);

	}
		Lista *pointB = indice_no(Fila, indiceB -1);

		if( noA == Fila->inicio) /*Se o ListaA for a cabeca da lista ,faca*/
		{
			Fila->inicio = noB; /*Atualize a cabeca da lista*/
		} 
		else
		{
			Lista *pointA = indice_no(Fila, indiceA -1);
			pointA->prox = noB; /*Proximo de A agora vai receber noB */
		}

		pointB->prox = noA;

		Lista *auxiliar = noA->prox; /*Armazena o ListaA para nao ser perdido a referencia do NO A */
		noA->prox= noB->prox; /*proximo  ListaA vai apontar para o proximo do noB */
		noB->prox= auxiliar; /* proximo ListaB vai apontar para o proximo do noA */
}

/*Lista *minimo(aponta *Fila , int indice)
{
	Lista *auxilia = indice_no(Fila , indice);

	if(auxilia !=NULL)
	{
		Lista *minimo = auxilia;
		while(auxilia != NULL)
		{
			if (auxilia->combA < minimo->combA) /* O valor do combustivel no auxiliar eh menor do que o minimo? */
			/*{
				minimo = auxilia;	
			}
			auxilia = auxilia->prox;	
		}
		return minimo;
	}
	return NULL;
}*/


void ordena_crescente (aponta *Fila)
{
	int i, j= Fila->quantidade-1 ; 

	for (i=0; i< Fila->quantidade-1; i++ ) 
	{
		Troca_nos(Fila , indice_no(Fila,i) , indice_no(Fila,j) );
		j--; 
		
	}
}




void exibe(aponta *elem)
{
	Lista *aux = elem->inicio;
	for(; aux != NULL; aux = aux->prox )
	{
		printf("Aluno: %s\n",aux->aluno );
		printf("Listata: %f\n",aux->nota );
	}
	/*printf("FIM DA LISTA: %s , %f\n",elem->fim->aluno , elem->fim->nota );
	/* Ao fazer isso , esta acessando memoria invalida */
	/*printf("Anterior do ultimo elemento: %s , %f\n",elem->fim->ant->aluno , elem->fim->ant->nota ); */
	/*printf("INICIO DA LISTA: %s , %f\n",elem->inicio->aluno , elem->inicio->nota );*/
}

int menu()
{
	int opcao;
	printf("1 Inserir um elemento no inicio da lista!\n");
	printf("2 Inserir um elemento no fim da lista!\n");
	printf("3 Inserir um elemento em qualquer posicao da lista!\n");
	printf("4 Retirar um elemento no fim da liOsta\n");
	printf("5 Exibir a lista!\n");
	printf("6 Troca_nos!\n");
	printf("Digite a opcao:\n");
	scanf("%d",&opcao);
	return opcao;
}
void escolha( int opcao, aponta *elem)
{
	int indice;
	switch(opcao)
	{
		case 1:
			insere_inicio(elem);
			break;
		case 2:
			insere_fim(elem);
			break;
		case 3:
			
			printf("Insira a posicao da lista:\n");
			scanf("%d",&indice);
			insere_escolha(elem ,indice);
			break;
		case 4:
			retira_fim(elem);
			break;
		case 5:
			exibe(elem);
			break;
		case 6:
			ordena_crescente(elem);	
			break;
		default:
			printf("opcao invalida!!\n");
			break;
	}
}

int main ()
{
aponta *Lista = Cria_Lista();
int opcao;
do {
opcao = menu();

escolha(opcao , Lista);

}while( opcao != 7);
return 0;
}