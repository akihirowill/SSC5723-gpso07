#include <iostream>
#include <fstream>
#include "Propriedades.h"
#include "Mmu.h"

using namespace std;

int main()
{
    // Configurando MMU
    Propriedades props("configuracao.cfg");

    int tamanhoPagina = stoi(props.pegaValor("tamanhoPagina")[0]);
    int tamanhoEnderecoLogico = stoi(props.pegaValor("tamanhoEnderecoLogico")[0]);
    int tamanhoMemoriaFisica = stoi(props.pegaValor("tamanhoMemoriaFisica")[0]);
    int tamanhoSwap = stoi(props.pegaValor("tamanhoSwap")[0]);

    // Pega valor da primeira possição do algoritmo e compara com lru, se verdade retorna valor de CLOCK_ALG(1) se não LRU_ALG(0)
    int algoritmoSubstituicao = props.pegaValor("algoritmoSubstituicao")[0].compare("lru") ? CLOCK_ALG : LRU_ALG;
    MMU mmu(tamanhoPagina, tamanhoEnderecoLogico, tamanhoMemoriaFisica, tamanhoSwap, algoritmoSubstituicao);

    //  Imprimindo informações MMU
    cout << '\n';
    mmu.informacao();
    cout << '\n';

    // Arquivo de entrada para o Simulador
    ifstream arquivo("simulador.txt");
    string linha, endereco;
    size_t pos;
    char operacao;
    int tamanhoProcesso, processoID;
    while (getline(arquivo, linha))
    {
        if (!linha.length() || linha[0] == '#')
            continue;
        cout << linha << "\n\n";
        operacao = linha[3];
        processoID = stoi(linha.substr(1, linha.find_first_of(' ') - 1));
        pos = linha.find_last_of(' ');
        endereco = linha.substr(pos + 1);
        switch (operacao)
        {
        case 'C':
            // processo de criação
            tamanhoProcesso = stoi(linha.substr(5));
            if (mmu.mapeamentoProcessos(processoID, tamanhoProcesso))
                cout << "Processo " << processoID << " criado com sucesso\n";
            else
            {
                cout << "Memória esta cheia! Processo não poderá ser criado!\n";
                cout << "Abortando...\n";
                exit(EXIT_FAILURE);
            }
            break;
        case 'W':
            // Acesso de memoria
        case 'R':
            cout << "Processo " << processoID << " acessando memória em " << endereco << '\n';
            if (!mmu.find(endereco))
                mmu.replace(endereco);
            break;
        case 'P':
            // Buscando instrução
            cout << "Processo " << processoID << " rodando instruções em " << endereco << '\n';
            if (!mmu.find(endereco))
                mmu.replace(endereco);
            break;
        case 'I':
            // Operação entrada/saída
            cout << "Processo " << processoID << " acessando dispositivo " << stoi(endereco, nullptr, 2) << '\n';
            break;
        }
        cout << '\n';
    }
    system("pause");
}