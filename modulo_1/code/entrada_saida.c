#include <stdio.h>

int main(int argc, char * argv[]){

	// abre o arquivo "exemplo.txt" para escrita no final do arquivo, caso o arquivo nao exista ele será criado
	FILE * arquivo = fopen("exemplo.txt", "wa");

	//escreve algo dentro do arquivo
	fputs("Trabalho do grupo gpso07", arquivo);

	//fecha o arquivo
	fclose(arquivo);
}