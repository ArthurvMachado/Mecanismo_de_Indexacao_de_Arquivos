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

        bool loadStopWords(const std::string& filepath); // Carrega as Stop Words

        void normalize(std::string& txt); // Normaliza o texto
        
        std::vector<std::string> breakWords(const std::string& txt); // Separa todas as palavras do texto
        
        public:
        TextProcessor(); // Construtor
        ~TextProcessor(); // Destrutor
        
        std::vector<std::string> processText(std::string text); // Função pública que processa o texto
        void lowerCase(std::string& txt); // Converte para minúsculo
        void removePunctuation(std::string& txt); // Remove pontuação
        bool isStopWord(const std::string& word); // Detecta Stop Words
};