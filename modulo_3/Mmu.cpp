#include "Mmu.h"
#include <climits>
#include <cmath>
#include <iostream>

MMU::MMU(int tamanhoPagina, int tamanhoEnderecoLogico, int tamanhoMemoriaFisica, int tamanhoSwap, int algoritmoSubstituicao) : tamanhoPagina(tamanhoPagina),
                                                                                                                               tamanhoEnderecoLogico(tamanhoEnderecoLogico),
                                                                                                                               tamanhoMemoriaFisica(tamanhoMemoriaFisica),
                                                                                                                               tamanhoSwap(tamanhoSwap),
                                                                                                                               numBitsPgVirtual(int(tamanhoEnderecoLogico - log2(tamanhoPagina))),
                                                                                                                               algoritmoSubstituicao(algoritmoSubstituicao)
{
    this->memoriaFisica = new Pagina[tamanhoMemoriaFisica];
    this->tempo = 0;
    this->usoSwap = 0;
    this->numeroPaginas = 0;
}

MMU::~MMU()
{
    delete[] memoriaFisica;
}

bool MMU::mapeamentoProcessos(int id, int tamanho)
{
    if (usoSwap + numeroPaginas + tamanho <= tamanhoSwap + tamanhoMemoriaFisica)
    // Se houver espaço livre na RAM ou um processo pode ser movido para swap para alocar memória para o processo de entrada
    {
        processosMapeados.insert(id);
        numeroPaginas += tamanho;
        return true;
    }
    else
    // Caso contrário, o processo não é criado
    {
        return false;
    }
}

bool MMU::find(std::string virtualAddress)
{
    int numeroPaginas = std::stoi(virtualAddress.substr(0, numBitsPgVirtual), nullptr, 2);
    for (int i = 0; i < tamanhoMemoriaFisica; ++i)
    {
        if (memoriaFisica[i].numeroPagina == numeroPaginas)
        // Se a pagina estiver na memoria ram
        {
            std::cout << "Pagina " << numeroPaginas << " found!\n";
            if (algoritmoSubstituicao == CLOCK_ALG)
                memoriaFisica[i].segundaChance = true;
            else if (algoritmoSubstituicao == LRU_ALG)
            {
                memoriaFisica[i].tempoAcesso = tempo;
                ++tempo;
            }
            return true;
        }
    }
    std::cout << "Page fault " << numeroPaginas << "!\n";
    return false;
}

void MMU::replace(std::string virtualAddress)
{
    int numeroPaginas = std::stoi(virtualAddress.substr(0, numBitsPgVirtual), nullptr, 2);
    if (algoritmoSubstituicao == LRU_ALG)
        lru(numeroPaginas);
    else if (algoritmoSubstituicao == CLOCK_ALG)
        clockSegundaChance(numeroPaginas);
}

void MMU::clockSegundaChance(int key)
{
    static int ponteiro = 0;
    while (true)
    {
        if (!memoriaFisica[ponteiro].segundaChance)
        // Encontrando a página a ser removida da RAM
        {
            if (memoriaFisica[ponteiro].numeroPagina != -1)
                std::cout << "Page " << memoriaFisica[ponteiro].numeroPagina << " removed from RAM\n";
            memoriaFisica[ponteiro] = Pagina(key);
            ponteiro = (ponteiro + 1) % tamanhoMemoriaFisica;
            return;
        }
        memoriaFisica[ponteiro].segundaChance = false;
        ponteiro = (ponteiro + 1) % tamanhoMemoriaFisica;
    }
}

void MMU::lru(int key)
{
    int lru = INT_MAX, PaginaSubstituida;

    for (int i = 0; i < tamanhoMemoriaFisica; ++i)
    // Encontrando a página menos usada recentemente
    {
        if (memoriaFisica[i].tempoAcesso < lru)
        {
            lru = memoriaFisica[i].tempoAcesso;
            PaginaSubstituida = i;
        }
    }

    if (memoriaFisica[PaginaSubstituida].numeroPagina != -1)
        std::cout << "Página " << memoriaFisica[PaginaSubstituida].numeroPagina << " removida da memória RAM\n";
    memoriaFisica[PaginaSubstituida] = Pagina(key, tempo);
    ++tempo;
}

void MMU::informacao()
{
    std::cout << "Algoritmo de substituição: " << (algoritmoSubstituicao == CLOCK_ALG ? "Clock\n" : "LRU\n");
    std::cout << "Tamanho da página (em bits): " << tamanhoPagina << '\n';
    std::cout << "Tamanho da memória física (em páginas): " << tamanhoMemoriaFisica << '\n';
    std::cout << "Troque o tamanho da área (em páginas): " << tamanhoSwap << '\n';
    std::cout << "Tamanho do endereço lógico (em bits): " << tamanhoEnderecoLogico << '\n';
}