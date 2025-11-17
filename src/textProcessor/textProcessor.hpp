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

static const std::unordered_map<std::string, std::string> TEXTS_FILEPATH_MAP = {
    {"contos fluminenses", "../machado/conto/contosFluminenses.txt"},
    {"historias da meia noite", "../machado/conto/historiasMeiaNoite.txt"},
    {"historias sem data", "../machado/conto/historiasSemData.txt"},
    {"paginas recolhidas", "../machado/conto/paginasRecolhidas.txt"},
    {"papeis avulsos", "../machado/conto/papeisAvulsos.txt"},
    {"reliquias da casa velha", "../machado/conto/reliquias.txt"},
    {"varias historias", "../machado/conto/variasHistorias.txt"},
    {"casa velha", "../machado/romance/casaVelha.txt"},
    {"dom casmurro", "../machado/romance/domCasmurro.txt"},
    {"esaú e jacó", "../machado/romance/esau.txt"},
    {"helena", "../machado/romance/helena.txt"},
    {"iaia garcia", "../machado/romance/iaia.txt"},
    {"a mão e a luva", "../machado/romance/maoLuva.txt"},
    {"memorial de aires", "../machado/romance/memorialAires.txt"},
    {"memorias póstumas de brás cubas", "../machado/romance/memoriasBras.txt"},
    {"quincas borba", "../machado/romance/quincas.txt"},
    {"ressurreição", "../machado/romance/ressurreicao.txt"},
    {"oliver twist", "../machado/tradução/oliverTwist.txt"},
    {"suplício de uma mulher", "../machado/tradução/suplicioMulher.txt"},
    {"os trabalhadores do mar", "../machado/tradução/trabalhadoresMar.txt"},
};

class TextProcessor{
    private:
        std::unordered_set<std::string> stopWords;  // Stop words
        std::unordered_map<std::string, std::string> accents;  // Acentuação
        std::unordered_map<std::string, std::string> textsFilepath;  // Endereço dos textos
        std::string text; // Texto a ser processado

        bool loadStopWords(const std::string& filepath); // Carrega as Stop Words
        bool loadText(const std::string& filepath); // CCarrega o texto a ser processado

        void normalize(std::string& txt); // Normaliza o texto
        void lowerCase(std::string& txt); // Converte para minúsculo
        void removePunctuation(std::string& txt); // Remove pontuação

        bool isStopWord(const std::string& word); // Detecta Stop Words

        std::vector<std::string> breakWords(const std::string& txt); // Separa todas as palavras do texto

    public:
        TextProcessor(); // Construtor
        ~TextProcessor(); // Destrutor
        
        std::vector<std::string> processText(std::string textName); // Função pública que processa o texto
};