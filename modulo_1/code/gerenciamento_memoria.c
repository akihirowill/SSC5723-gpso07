#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){

	char nome[90];
	char *descricao;

	strcpy(nome, "William Aisawa");

	/* Aloca memoria dinamicamente */
	descricao = malloc(35 * sizeof(char));


	if(descricao == NULL){
		fprintf(stderr,"Erro! Nao foi possivel alocar a memoria\n");
	} else{
		strcpy(descricao, "William é estudande de Doutorado\n");
	}

	/* aumentar o tamanho da descrição */
	descricao = realloc(descricao, 100 * sizeof(char));

	if(descricao == NULL){
		fprintf(stderr, "Erro!, nao foi possivel alocar a memoria\n");
	} else{
		strcat(descricao, "Sua area de pesquisa é Redes");
	}

	printf("Nome: %s\n", nome);
	printf("Descricao: %s\n", descricao);


	/* libera memoria alocada */
	free(descricao);

}