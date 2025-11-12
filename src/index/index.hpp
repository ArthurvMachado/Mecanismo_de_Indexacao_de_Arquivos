#pragma once
#include <string>

class Index{
    private:
        std::string getNomeArquivoPorId(int id);
    
    public:
        Index(); // Construtor
        ~Index(); // Destrutor

        int adicionar(std::string palavra, std::string nome_arquivo);
        int* getArquivosPorPalavra(std::string palavra);
};

