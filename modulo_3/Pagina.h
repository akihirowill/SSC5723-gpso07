#ifndef _PAGINA_H_
#define _PAGINA_H_

class Pagina
{
public:
    int numeroPagina;   // Numero da pagina
    int tempoAcesso;    // Tempo de acesso para o algoritmo LRU de substituicao
    bool segundaChance; // Segunda chance para o algoritmo de clock de substituicao

    Pagina();
    Pagina(int numeroPagina);
    Pagina(int numeroPagina, int tempo);
};

#endif