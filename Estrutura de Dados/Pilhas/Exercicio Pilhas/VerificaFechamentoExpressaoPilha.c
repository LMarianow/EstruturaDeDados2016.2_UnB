#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pontua {
	char sinais;
	struct pontua *prox;
	
}pontua;

typedef struct pilha
{
	struct pontua *topo;
	
	int quant;
}pilha;


pilha *cria_pilha()
{
	pilha *novo = (pilha*)malloc(sizeof(pilha));
	novo->topo = NULL;
	
	novo->quant=0;
	return novo;
}
int vazia (pilha *aux)
{
	if(aux->topo == NULL)
	{		
		return 0;
	}
	else
		return 1;
}
pontua *aloca()
{
	pontua *novo = (pontua *)malloc(sizeof(pontua));
	if(novo== NULL)
	{
		printf("Erro na alocacao!!");
		exit(1);
	}
	
	return novo;
}
pilha *insere(pilha *abertura,char str)
{
	pontua *novo = aloca();
	printf("Conteudo: %c\n",str );
	novo->sinais = str;
	if(vazia(abertura)==0)
	{
		abertura->topo = novo;		
		abertura->topo->prox = NULL;		
		abertura->quant++;
		return abertura;
	}
	else
	{		
		/*pontua * aux = abertura->topo;*/
		/*abertura->topo = novo;		
		novo->prox = aux;	*/			
		novo->prox = abertura->topo;
		abertura->topo = novo;
		abertura->quant++;
		return abertura;
	}

}

char retira(pilha *abertura)
{
	char recebe;
 pontua* t= abertura->topo;
 	recebe = t->sinais;
    abertura->topo = t->prox;
    free(t);

    return recebe;

}
/* Cria funcoes */

char corresp(char c)
{

    if(c== ')')
    {
        return '(';
    }

    else if(c== ']')
    {
        return '[';
    }
    else if(c== '}')
    
        return '{';
    
    
}

void percorre_armazena (pilha *abertura, char *string)
{
	char fechamento;


	int valido=1,i;
	printf("PERCORRE STRING = %s\n",string );
	int tamanho = strlen(string);
	
	for (i=0; i<tamanho; i++)
	{
		if(string[i] == '{' || string[i] == '[' || string[i] == '('  )
		{

			abertura= insere(abertura,string[i]);
			
		}

		if(string[i] == '}' || string[i] == ']' || string[i] == ')' )
		{

			if(vazia(abertura)==0) /*SE Pilha estiver vazia , eh porque tem mais fechadores do que sinais de abertura */
			{
				
            	valido = 0; /* O que ja torna a equacao invalida */
        	}
        	else
        	{
        		
            	fechamento= retira(abertura);
            	if(fechamento!= corresp(string[i]))
                	valido = 0;
        	}
			/*insere(fechamento,string[i]);
			printf("INSERE fechamento\n");*/
		}
	}

	if(!vazia(abertura) == 0) /* Ao contrario do anterior, se a pilha ficar vazia no final eh porque cada abridor encontrou seu fechador */
	
    	valido = 0;
	
	if(valido==1)
	{
		printf("Equacao Valida!%d\n", valido);		
	}
	else if(valido ==0)
	{
		printf("Equacao invalida!%d\n",valido );
	}

}


void exibe(pilha *abertura)
{
	pontua * aux = abertura->topo;
	
	for(; aux!=NULL ; aux = aux->prox )
	{
		printf("EXIBE\n");
		printf("%c\n",aux->sinais );
	}	
}

int main()
{
	char string[40];
	pilha * abertura = cria_pilha();
	

	printf("Digite a sua Equacao junto com Sinais:\n");
	scanf("%[^\n]",string);
	char *apontastr = string;

	percorre_armazena(abertura , apontastr);
			
	return 0;
}








