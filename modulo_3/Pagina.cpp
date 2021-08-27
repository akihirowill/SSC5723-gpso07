#include "Pagina.h"

Pagina::Pagina() : Pagina(-1, -1) {}

Pagina::Pagina(int numeroPagina) : Pagina(numeroPagina, -1) {}

Pagina::Pagina(int numeroPagina, int tempo)
{
    this->numeroPagina = numeroPagina;
    this->tempoAcesso = tempo;
    this->segundaChance = false;
}