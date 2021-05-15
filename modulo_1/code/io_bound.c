#include <stdio.h>

#define SIZE 1000000

int main(int argc, char * argv[]){
	FILE * arquivo = fopen("arquivo.txt", "wb");
	char vetor[SIZE];
	
	// escreve um byte de cada vez
	for(int i = 0; i < SIZE; ++i){
		vetor[i] = (char) i;
		fwrite(vetor + i, sizeof(char), 1, arquivo);
	}

	// escreve o vetor todo de uma vez
	fwrite(vetor, sizeof(char), SIZE, arquivo);

	fclose(arquivo);
}