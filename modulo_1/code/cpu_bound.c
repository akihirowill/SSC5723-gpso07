#define SIZE 999

void main(int argc, char * argv[]) {

	int matriz[SIZE][SIZE];

	for(int i = 0; i < SIZE; ++i)
		for(int j = 0; j < SIZE; ++j)
			matriz[i][j] = i + j;

}
