#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoElemento
{
	char nomePlanta[40];
	char tipo[20];
    int diasEstimadosParaPrimeiraColheita;
    int regadasAoDia;
    char estacaoBoaParaPlantar[10];
    char adubo[50];
}TElemento;

typedef struct tipoNo
{
	TElemento elemento;
	struct tipoNo *esq, *dir;
}TNo;

TNo* inserir (TNo *raiz, TElemento *elemento)
{
	if (raiz == NULL)
	{
		raiz = new TNo;
		strcpy(raiz->elemento.nomePlanta, elemento->nomePlanta);
		strcpy(raiz->elemento.tipo, elemento->tipo);
		raiz->elemento.diasEstimadosParaPrimeiraColheita = elemento->diasEstimadosParaPrimeiraColheita;
		raiz->elemento.regadasAoDia = elemento->regadasAoDia;
		strcpy(raiz->elemento.estacaoBoaParaPlantar, elemento->estacaoBoaParaPlantar);
		strcpy(raiz->elemento.adubo, elemento->adubo);
		raiz->esq = NULL;
		raiz->dir = NULL;
	}
	else
	{
		if (strcmp(elemento->nomePlanta, raiz->elemento.nomePlanta) < 0)
		{
			 raiz->esq = inserir (raiz->esq, elemento);
		}
		else
		{
			raiz->dir = inserir (raiz->dir, elemento);
		}
	}
	return raiz;
}

void lerDados (TElemento *elemento)
{
	fflush(stdin);
	printf("\n Informe a espécie da planta: ");
	gets(elemento->nomePlanta);
	fflush(stdin);
	printf("\n Informe o tipo da planta: ");
	gets(elemento->tipo);
	fflush(stdin);
	printf("\n Informe os dias estimados para a colheita da planta: ");
	scanf("%d", &elemento->diasEstimadosParaPrimeiraColheita);
	fflush(stdin);
	printf("\n Informe quantas vezes a planta precisa ser regada por dia: ");
	scanf("%d", &elemento->regadasAoDia);
	fflush(stdin);
	printf("\n Informe a estação boa para plantar a planta ");
	gets(elemento->estacaoBoaParaPlantar);
	fflush(stdin);
	printf("\n Informe o tipo de adubo bom para a planta: ");
	gets(elemento->adubo);
}

void preOrdem (TNo *raiz)
{
	if (raiz != NULL)
	{
		printf("\n Nome: %s", raiz->elemento.nomePlanta);
		printf("\n Tipo: %s", raiz->elemento.tipo);
		printf("\n Dias estimados para a colheita: %d", raiz->elemento.diasEstimadosParaPrimeiraColheita);
		printf("\n Quantas vezes a planta precisa ser regada ao dia: %d", raiz->elemento.regadasAoDia);
		printf("\n Estação boa para plantar a planta: %s", raiz->elemento.estacaoBoaParaPlantar);
		printf("\n Tipo de adubo com para a planta: %s \n", raiz->elemento.adubo);
		preOrdem (raiz->esq);
		preOrdem (raiz->dir);
	}
}

void emOrdem (TNo *raiz)
{
	if (raiz != NULL)
	{
		emOrdem (raiz->esq);
		printf("\n Nome: %s", raiz->elemento.nomePlanta);
		printf("\n Tipo: %s", raiz->elemento.tipo);
		printf("\n Dias estimados para a colheita: %d", raiz->elemento.diasEstimadosParaPrimeiraColheita);
		printf("\n Quantas vezes a planta precisa ser regada ao dia: %d", raiz->elemento.regadasAoDia);
		printf("\n Estação boa para plantar a planta: %s", raiz->elemento.estacaoBoaParaPlantar);
		printf("\n Tipo de adubo com para a planta: %s \n", raiz->elemento.adubo);
		emOrdem (raiz->dir);
	}
}

void posOrdem (TNo *raiz)
{
	if (raiz != NULL)
	{
		posOrdem (raiz->esq);
		posOrdem (raiz->dir);
		printf("\n Nome: %s", raiz->elemento.nomePlanta);
		printf("\n Tipo: %s", raiz->elemento.tipo);
		printf("\n Dias estimados para a colheita: %d", raiz->elemento.diasEstimadosParaPrimeiraColheita);
		printf("\n Quantas vezes a planta precisa ser regada ao dia: %d", raiz->elemento.regadasAoDia);
		printf("\n Estação boa para plantar a planta: %s", raiz->elemento.estacaoBoaParaPlantar);
		printf("\n Tipo de adubo com para a planta: %s \n", raiz->elemento.adubo);
	}
}

TNo* consultarRecursivo (TNo *auxRaiz, char auxNomePlanta[40])
{
	if (auxRaiz == NULL)
	{
		return auxRaiz;
	}
	else
	{
		if (strcmp(auxRaiz->elemento.nomePlanta, auxNomePlanta) == 0)
		{
			return auxRaiz;
		}
		else
		{
			if (auxNomePlanta < auxRaiz->elemento.nomePlanta)
			{
				return consultarRecursivo (auxRaiz->esq, auxNomePlanta);
			}
			else
			{
				return consultarRecursivo (auxRaiz->dir, auxNomePlanta);
			}
		}
	}
}

//função para procurar e retornar o elemento mais a direita da sub-árvore a esquerda.
TElemento sobeMaiorDireita (TNo *aux)
{
	while (aux->dir != NULL)
	{
		aux = aux->dir;
	}
	return (aux->elemento);
}


TNo* remover (TNo *raiz, TElemento auxElemento)
{
	//Se chegarmos ao final da árvore e o elemento ainda não for encontrado então retornamos esta mensagem.
	if (raiz == NULL)
	{
		printf("\n Elemento nao encontrado!");
	}
	else
	{
		//Se o valor procurado for menor que o do nó da raiz seguiremos para a esquerda.
		if (strcmp(auxElemento.nomePlanta, raiz->elemento.nomePlanta) < 0)
		{
			raiz->esq = remover (raiz->esq, auxElemento);
		}
		else
		{
			//Se o valor procurado for maior que o do nó da raiz seguiremos para a direita.
			if (strcmp(auxElemento.nomePlanta, raiz->elemento.nomePlanta) > 0)
			{
				raiz->dir = remover (raiz->dir, auxElemento);
			}
			else //encontrei o valor.
			{
				//se o elemento não tiver sub-árvore direita passaremos a sub-árvore a esquerda para a posição do elemento a ser excluído e excluiremos o elemento.
				{
					if (raiz->dir == NULL)
					{
						TNo *aux;
						aux = raiz;
						raiz = raiz->esq;
						free(aux);
					}
					else
					{
						//Se o elemento não tiver sub-árvore esquerda passaremos a sub-árvore a direita para a posição do elemento a ser excluído e excluiremos o elemento.
						if (raiz->esq == NULL)
						{
							TNo *aux;
							aux = raiz;
							raiz = raiz->dir;
							free(aux);
						}
						else //Caso o nó possua 2 sub-árvores
						{
							//recebendo o elemento mais a direita da sub-árvore a esquerda e passando para o local do valor que será excluído.
							raiz->elemento = sobeMaiorDireita (raiz->esq);
							//apagando o elemento que subiu para ocupar o lugar do que foi excluído.
							raiz->esq = remover (raiz->esq, raiz->elemento);
						}
					}
				}
			}
		}
	}
	return raiz;
}


int main()
{
	TNo *raiz;
	raiz = NULL; //inicialização da raiz da árvore
	
	TElemento elemento;
	
	int opcao;
	
	do
	{
		printf("\n 1 - Inserir planta na arvore");
		printf("\n 2 - Apresentar pre-ordem");
		printf("\n 3 - Apresentar em ordem");
		printf("\n 4 - Apresentar pos-ordem");
		printf("\n 5 - Consultar planta");
		printf("\n 6 - Remover planta");
		printf("\n 0 - Sair");
		printf("\n Escolha uma opcao: ");
		scanf("%d", &opcao);
		
		switch (opcao)
		{
			case 1:
				{
					lerDados(&elemento);
					raiz = inserir (raiz, &elemento); break;
				}
			case 2: preOrdem (raiz); break;
			case 3: emOrdem (raiz); break;
			case 4: posOrdem (raiz); break;
			case 5:
				{
					TNo *encontrou;
					char auxNomePlanta[40];
					fflush(stdin);
					printf("\n Informe o nome da planta a ser consultada: ");
					gets(auxNomePlanta);
					encontrou = consultarRecursivo(raiz, auxNomePlanta);
					if (encontrou != NULL)
					{
						printf("\n Planta Encontrada!");
					}
					else
					{
						printf("\n Planta nao encontrada!");
					}
					break;
				}
			case 6:
				{
					char auxNomePlanta[40];
					fflush(stdin);
					printf("\n Informe o nome da planta a ser excluida: ");
					gets(auxNomePlanta);
					TNo *planta;
					planta = consultarRecursivo(raiz, auxNomePlanta);
					if (planta != NULL) {
						raiz = remover (raiz, planta->elemento);
						printf("Planta encontrada e excluida");
						break;
					} else {
						printf("Planta nao encontrada");
						break;
					}
					
				}
		}
		
	}while (opcao != 0);
}


