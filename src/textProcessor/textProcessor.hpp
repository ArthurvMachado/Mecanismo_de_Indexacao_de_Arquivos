#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class TextProcessor{
    private:
        std::unordered_set<std::string> stopWords;  // Stop words
        std::unordered_map<char, char> accents;  // Acentuação
        std::string text; // Texto de exemplo

        bool loadStopWords(const std::string& filepath); // Carrega as Stop Words
        bool loadText(const std::string& filepath); // Carrega o texto de exemplo

        void normalize(std::string& text); // Normaliza o texto
        void lowerCase(std::string& text); // Converte para minúsculo
        void removePunctuation(std::string& text); // Remove pontuação

        bool isStopWord(const std::string& word); // Remove Stop Words

        std::vector<std::string> breakWords(const std::string& text); // Separa todas as palavras so texto

    public:
        TextProcessor(); // Construtor
        ~TextProcessor(); // Destrutor
        
        std::vector<std::string> processar(std::string texto);
};