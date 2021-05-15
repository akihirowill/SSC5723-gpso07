#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>

#define TAMANHO 500

int main(int argc, char * argv[]){
	char buffer[TAMANHO];

	//Pega o diretorio atual
	getcwd(buffer, TAMANHO);
	printf("O diretorio atual é %s\n", buffer);

	//fchdir muda o diretorio atual.
	if(fchdir("..") == 0){
		printf("O diretorio foi alterado para o diretorio pai.\n");
	}else{
		printf("Erro ao tentar mudar o diretorio.\n");
	}


	//abre o arquivo "exemplo.txt" se nao existir ele será criado.
	FILE * arquivo = fopen("exemplo.txt", "wa");
	fclose(arquivo);

	//muda a permissao do arquivo para somente leitura 
	int permissao = chmod("exemplo.txt", 0444);
	if(permissao == 0){
		printf("Permissão do arquivo alterada\n");
	}else{
		printf("Não foi possivel alterar a permissão do arquivo\n");
	}

	return 0;
}
