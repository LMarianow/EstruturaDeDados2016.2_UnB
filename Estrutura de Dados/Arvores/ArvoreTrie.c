#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PALAVRA_MAX 16
#define TAMANHO_ALFABETO 26
#define PRIMEIRA_LETRA_ASCII 97

//Estrutura para nós da árvore// 
typedef struct TNode{ 

	//Cada nó aponta para um número n de filhos, onde n é o tamanho do alfabeto//
	struct TNode *filhos[TAMANHO_ALFABETO];

	//Indica o fim de uma palavra, 0 para não é fim e 1 para é fim//
	int finalPalavra; 

	//Indica quantas vezes dada palavra presente na árvore foi encontrada no texto//
	int frequenciaPalavra;

} TNode;

/*---------------------------------------------------------------------------------------------
Protótipo: TNode *criaNode(void);
Função: Aloca espaço para um novo nó e inicializa todos os seus filhos como NULL.
Entrada: Não recebe nada.
Saída: Retorna um ponteiro para um struct do tipo Tnode.
---------------------------------------------------------------------------------------------*/
TNode *criaNode(void);

/*---------------------------------------------------------------------------------------------
Protótipo: TNode *criaTrie(void);
Função: Cria uma árvore Trie alocando um nó vazio para simbolizar a raiz.
Entrada: Não recebe nada.
Saída: Retorna um ponteiro para struct do tipo TNode.
---------------------------------------------------------------------------------------------*/
TNode *criaTrie(void);

/*---------------------------------------------------------------------------------------------
Protótipo: void inserePalavra(TNode *node, char *palavra);
Função: Insere uma palavra na árvore.
Entrada: Recebe o nó raiz e a palavra que será inserida.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void inserePalavra(TNode *node, char *palavra);

/*---------------------------------------------------------------------------------------------
Protótipo: void procuraPalavra(TNode *node);
Função: Procura se palavras do texto estão presentes no dicionário e incrementa sua frequência.
Entrada: O nó raiz.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void procuraPalavra(TNode *node);

/*---------------------------------------------------------------------------------------------
Protótipo: void frequenciaPalavra(TNode *raiz, char **palavras, int nPalavrasDicionario);
Função: Imprime a frequência de cada palavra no texto de acordo com a ordem que elas foram 
inseridas.
Entrada: O nó raiz, a ordem incial das palavras e o número de palavras presentes no dicionário.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void frequenciaPalavra(TNode *raiz, char **palavras, int nPalavrasDicionario);

/*---------------------------------------------------------------------------------------------
Protótipo: void destroiTrie(TNode *node);
Função: Desaloca o espaço utilizado pela árvore Trie.
Entrada: O nó raiz.
Saída: Não retorna nada.
---------------------------------------------------------------------------------------------*/
void destroiTrie(TNode *node);


TNode *criaNode(void){

	int i;

	TNode *newNode;

	//Aloca espaço para o novo nó//
	newNode = (TNode*) malloc(sizeof(TNode));
	if(!newNode) { perror(NULL); exit(EXIT_FAILURE); }

	//Inicializa a variável do struct final como zero, quando em 1 representa o fim de uma palavra//
	newNode->finalPalavra = 0;

	//Inicializa o número de vezes que a palavra foi encontrada como zero//
	newNode->frequenciaPalavra = 0;

	//Inicializa todos os filhos do nó, correspondentes a tamanho do alfabeto, como NULL//
	for(i = 0; i < TAMANHO_ALFABETO; i++)
		newNode->filhos[i] = NULL;
	
	return newNode;
}

TNode *criaTrie(void){

	//Cria um nó para a raiz
	return criaNode();
}

void inserePalavra(TNode *node, char *palavra){

	int i;
	int tamanhoPalavra, indiceLetra;
	
	//Calcula o tamanho da palavra lida//
	tamanhoPalavra = strlen(palavra);

	//Enquanto não chegar ao fim da palavra//
	for(i = 0; i < tamanhoPalavra; i++){

		//Calculamos o indice correspondente a letra//
		indiceLetra = (int)palavra[i] - PRIMEIRA_LETRA_ASCII;
		
		//Se não existe um nó para o caractere correspondente, criamos o nó//
		if(node->filhos[indiceLetra] == NULL)
			node->filhos[indiceLetra] = criaNode();

		//Caminhamos para o nó criado//
		node = node->filhos[indiceLetra];
	}

	//Indicamos que é o final de uma palavra//
	node->finalPalavra = 1;
}

void procuraPalavra(TNode *node){

	int i;
	int tamanhoPalavra, indiceLetra;

	//Vetor temporário para armazenar a palavra do texto lida//
	char palavra[PALAVRA_MAX];

	//Lê uma palavra do texto e calcula seu tamanho//
	scanf("%s", palavra);
	tamanhoPalavra = strlen(palavra);

	for(i = 0; i < tamanhoPalavra; i++){

		//Calculamos o indice correspondente a letra//
		indiceLetra = (int)palavra[i] - PRIMEIRA_LETRA_ASCII;
		
		//Se ainda não existe um nó criado para determinado indice, retornamos pois a palavra não foi encontrada//
		if(node->filhos[indiceLetra] == NULL){
			return;
		}	

		//Caminhamos para o próximo nó//
		node = node->filhos[indiceLetra];
	}

	//Encontramos a palavra, logo incrementamos sua frequência//
	if(node->finalPalavra){
		node->frequenciaPalavra++;
	}
}

void frequenciaPalavra(TNode *raiz, char **palavras, int nPalavrasDicionario){

	int i, j;
	int tamanhoPalavra, indiceLetra;

	TNode *node;	

	//Enquanto não percorrer todas as palavras do dicionário//
	for(i = 0; i < nPalavrasDicionario; i++){
		
		//Sempre voltamos para raiz ao procurar uma nova palavra//		
		node = raiz;

		//Calculamos o tamanho da palavra//
		tamanhoPalavra = strlen(palavras[i]);

		//Caminhamos até o finalPalavra da palavra//
		for(j = 0; j < tamanhoPalavra; j++){

			indiceLetra = (int)palavras[i][j] - PRIMEIRA_LETRA_ASCII;
			node = node->filhos[indiceLetra];
		}

		//Imprimimos sua frequência no texto//
		if(node->finalPalavra)
			printf("%d", node->frequenciaPalavra);

		//Condição apenas para não imprimir espaço após o ultimo número//
		if(i != nPalavrasDicionario - 1)
			printf(" ");
	}
	
	printf("\n");
}

void destroiTrie(TNode *node){

	int i;
	
	//Verifica os 26 filhos, correspondentes aos caracteres, de cada nó//
	for(i = 0; i < TAMANHO_ALFABETO; i++){
		if(node->filhos[i] != NULL){
			//Chama a função recursivamente para o próximo filho que não é nulo//
			destroiTrie(node->filhos[i]);
		}
	}

	//Libera o nó que não é nulo//
	if(node != NULL)
		free(node);
}