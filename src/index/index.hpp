#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

class Index{
    private:
        std::unordered_map<std::string, std::unordered_set<int>> invertedIndex; // Índice invertido (Palavra → IDs)
        std::unordered_map<std::string, int> nameToId; // (NomeArquivo → ID)
        std::unordered_map<int, std::string> idToName; // (ID → NomeArquivo)
        int nextId; // Contador de IDs

        int generateId(const std::string& filename); // Cria um ID para o arquivo, retorna, se existente

    public:
        Index(); // Construtor
        ~Index(); // Destrutor

        void test(const std::string& filename); // Teste
};

