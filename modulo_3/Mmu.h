#ifndef _MMU_H_
#define _MMU_H_

#include <vector>
#include <string>
#include <set>
#include "Pagina.h"

#define LRU_ALG 0
#define CLOCK_ALG 1

class MMU
{
public:
    const int tamanhoPagina;         // Tamanho da página em bits
    const int tamanhoEnderecoLogico; // Tamanho do endereço lógico
    const int tamanhoMemoriaFisica;  // Tamanho da memória física em páginas
    const int numBitsPgVirtual;      // Numero de página em bits para endereçar uma página virtual
    const int tamanhoSwap;           // Tamanho da área de troca nas páginas
    const int algoritmoSubstituicao; // Algoritmo para substituir a página (LRU ou CLOCK)

    Pagina *memoriaFisica;           // Páginas na memória física
    std::set<int> processosMapeados; // Processos que estão em RAM ou Swap
    int tempo;                       // Hora do relógio em que uma página é referenciada (para algoritmo CLOCK)
    int usoSwap;                     // numero de páginas armazenadas em Swap
    int numeroPaginas;               // numero total de páginas em RAM e Swap

    MMU(int tamanhoPagina, int tamanhoEnderecoLogico, int tamanhoMemoriaFisica, int tamanhoSwap, int algoritmoSubstituicao);
    ~MMU();
    bool find(std::string enderecoVirtual);
    void replace(std::string enderecoVirtual);
    bool mapeamentoProcessos(int id, int tamanho);
    void informacao();

private:
    // Algoritmo de substituição
    void clockSegundaChance(int key);
    void lru(int key);
};

#endif