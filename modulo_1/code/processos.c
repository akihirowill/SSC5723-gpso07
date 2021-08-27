#include <stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char * argv[]){

	//Cria o processo
	int pid = fork();
	//fork retorna o pid filho na execucação dos pid pai

	if(pid != 0){
		printf("Sou o PID pai e o filho é: %d\n", pid);
		printf("PID pai aguardando o filho terminar...\n");

		//O processo pai fica bloqueado ate o pid filho terminar
		waitpid(pid,NULL,0);
		printf("O processo pai terminou!\n");
	}else{
		// o comando getpid retorna o pid do processo em execução
		printf("Eu sou um processo filho e meu pid é: %d\n", getpid());
		printf("Processo filho em execução\n");
		printf("Processo filho encerrado\n");
	}

	return 0;
}