#pragma once
#include <string>

class Indexer{
    public:
        Indexer(); // Construtor
        ~Indexer(); // Destrutor

        int construir(std::string diretorio); // retorna Index
};
