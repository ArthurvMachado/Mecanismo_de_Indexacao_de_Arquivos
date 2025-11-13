#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

static const std::unordered_map<std::string, std::string> ACCENT_MAP = { // Mapa de caracteres acentuados
    {"Á", "á"}, {"Ã", "ã"}, {"À", "à"}, {"Â", "â"},
    {"É", "é"}, {"Ê", "ê"}, {"Í", "í"}, {"Ó", "ó"},
    {"Õ", "õ"}, {"Ô", "ô"}, {"Ú", "ú"}, {"Ü", "ü"},
    {"Ç", "ç"}
};

class TextProcessor{
    private:
        std::unordered_set<std::string> stopWords;  // Stop words
        std::unordered_map<std::string, std::string> accents;  // Acentuação
        std::string text; // Texto de exemplo

        bool loadStopWords(const std::string& filepath); // Carrega as Stop Words
        bool loadText(const std::string& filepath); // Carrega o texto de exemplo

        void normalize(std::string& text); // Normaliza o texto
        void lowerCase(std::string& text); // Converte para minúsculo
        void removePunctuation(std::string& text); // Remove pontuação

        bool isStopWord(const std::string& word); // Remove Stop Words

        std::vector<std::string> breakWords(const std::string& text); // Separa todas as palavras do texto

    public:
        TextProcessor(); // Construtor
        ~TextProcessor(); // Destrutor
        
        std::vector<std::string> processar(std::string texto); // Função pública que processa o texto
};