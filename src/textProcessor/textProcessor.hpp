#pragma once
#include <string>
#include <vector>
#include <unordered_set>

class TextProcessor{
    private:
        std::unordered_set<std::string> stopWords;  // Stop words
        std::string text;

        bool loadStopWords(const std::string& datapath); // Carrega as Stop Words
        bool loadText(const std::string& datapath); // Carrega o texto de exemplo

        std::vector<std::string> breakWords(const std::string& text); // Separa todas as palavras so texto

    public:
        TextProcessor(); // Construtor
        ~TextProcessor(); // Destrutor
        
        std::vector<std::string> processar(std::string texto);
};