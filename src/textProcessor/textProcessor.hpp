#pragma once
#include <string>
#include <vector>
#include <unordered_set>

class TextProcessor{
    private:
        std::unordered_set<std::string> stopWords;  // Stop words

        bool loadStopWords(const std::string& datapath);

    public:
        TextProcessor(); // Construtor
        ~TextProcessor(); // Destrutor
        
        std::vector<std::string> processar(std::string texto);
};