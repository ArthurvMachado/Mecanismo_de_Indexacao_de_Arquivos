#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class TextProcessor{
    private:
        std::unordered_set<std::string> stopWords;  // Stop words
        std::string text; // Texto de exemplo

        bool loadStopWords(const std::string& datapath); // Carrega as Stop Words
        bool loadText(const std::string& datapath); // Carrega o texto de exemplo
        void lowerCase(std::string& word); // Converte para minúsculo
        void removePunctuation(std::string& word); // Remove pontuação

        std::vector<std::string> breakWords(const std::string& text); // Separa todas as palavras so texto

    public:
        TextProcessor(); // Construtor
        ~TextProcessor(); // Destrutor
        
        std::vector<std::string> processar(std::string texto);
};