#pragma once
#include <string>

class index{
    private:
        std::string getNomeArquivoPorId(int id);
    
    public:
        index(); // Construtor
        ~index(); // Destrutor

        int adicionar(std::string palavra, std::string nome_arquivo);
        int* getArquivosPorPalavra(std::string palavra);
};

