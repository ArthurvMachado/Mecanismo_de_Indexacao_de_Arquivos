#pragma once
#include "../textProcessor/textProcessor.hpp"
#include "../index/index.hpp"
#include <string>

class Indexer{
    private:
        Index* index; // Ponteiro do índice
        TextProcessor* processor; // Ponteiro do porcessador de textos

        bool readFile(const std::string& filepath, std::string& content); // Lê o conteúdo do arquivo para a string de referência
    public:
        Indexer(Index* idx, TextProcessor* proc); // Construtor
        ~Indexer(); // Destrutor
};
