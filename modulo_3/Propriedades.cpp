#include "Propriedades.h"
#include <fstream>

Propriedades::Propriedades(const std::string &nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo.c_str());
    std::string linha, nome, valor, token;
    size_t pos;

    while (std::getline(arquivo, linha))
    {
        if (!linha.length() || linha[0] == '#')
            continue;

        pos = linha.find('=');
        nome = linha.substr(0, pos);
        valor = linha.substr(pos + 1);

        while ((pos = valor.find_first_of(" ;")) != std::string::npos)
        {
            token = valor.substr(0, pos);
            content.insert(std::pair<std::string, std::string>(nome, token));
            valor.erase(0, pos + 1);
        }
    }

    arquivo.close();
}

const std::vector<std::string> Propriedades::pegaValor(std::string const &key) const
{
    std::vector<std::string> resultado;
    std::pair<std::multimap<std::string, std::string>::const_iterator, std::multimap<std::string, std::string>::const_iterator> range = content.equal_range(key);

    std::multimap<std::string, std::string>::const_iterator it = range.first;
    do
    {
        resultado.push_back(it->second);
        ++it;
    } while (it != range.second);

    return resultado;
}