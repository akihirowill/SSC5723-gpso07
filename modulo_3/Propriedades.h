#ifndef _PROPRIEDADES_H_
#define _PROPRIEDADES_H_

#include <map>
#include <string>
#include <vector>

// Classe para ler o arquivo de configuração para configurar o MMU
class Propriedades
{
private:
    std::multimap<std::string, std::string> content;

public:
    Propriedades(const std::string &nomeArquivo);
    const std::vector<std::string> pegaValor(std::string const &key) const;
};

#endif