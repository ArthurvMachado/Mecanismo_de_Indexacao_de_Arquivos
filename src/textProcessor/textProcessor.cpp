#include "textProcessor.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream> // std::ifstream()
#include <sstream> // std::stringstream()

// Construtor
TextProcessor::TextProcessor(){
    stopWords.clear(); // stopWords inicializa limpa
    accents = ACCENT_MAP; // set accents recebe ACCENT_MAP
}

// Destrutor
TextProcessor::~TextProcessor() {}

// Carrega as Stop Words
bool TextProcessor::loadStopWords(const std::string& filepath){
    std::ifstream words(filepath); // Carrega stopWords.txt

    if(!words) return false; // Arquivo não encontrado

    std::string str;
    // Separa o texto do arquivo a cada quebra de linha ou espaço e o copia para str 
    while(words >> str) this->stopWords.insert(str); // Adiciona no set de Stop Words

    words.close(); // Fecha o arquivo
    return true;
}

// Normaliza o texto
void TextProcessor::normalize(std::string& txt){
    this->lowerCase(txt); this->removePunctuation(txt); // Deixa text em minúsculo e retira suas pontuações
}

// Converte para minúsculo
void TextProcessor::lowerCase(std::string& txt){ 
    for(int i = 0; i < txt.size(); i++){
        if(i + 1 < txt.size()){ // Caracteres acentuados ocupam dois bytes, por isso deve-se verificar se existem dois caracteres na string
            std::string c = txt.substr(i, 2); // Substring com os próximos dois bytes
            if(accents.find(c) != accents.end()){ // Verifica se o caractere é um acento 
                txt.replace(i, 2, accents[c]); // Substitui o caractere pela sua versão minúscula
                i++; continue; // Avança um carctere na string e continua o loop
            } 
        } 
        // Se não for um caractere acentuado
        if(std::isupper(txt[i])) txt[i] = std::tolower(txt[i]); // Verifica se o caractere é uma letra maiúscula e a transforma em minúscuala
    }
}

// Remove pontuação
void TextProcessor::removePunctuation(std::string& txt){
    for(int i = 0; i < txt.size(); i++) if(std::ispunct(txt[i])) txt.erase(i--, 1); // Se o caractere for uma pontuação é removido
    // i--, pois deve retornar o índice, pois o indíce da pontuação, após sua remoção, é ocupado por outro caractere
}

// Detecta Stop Words
bool TextProcessor::isStopWord(const std::string& txt){
    return (stopWords.find(txt) != stopWords.end()) ? true : false; // Retorna se text está no set stopWords
}

// Separa todas as palavras do texto
std::vector<std::string> TextProcessor::breakWords(const std::string& txt){
    std::vector<std::string> words; // Vetor de palavras separadas
    
    std::istringstream buffer(txt); // Buffer com o conteúdo de text
    
    std::string str;
    while(buffer >> str){ // Separa o texto a cada quebra de linha ou espaço e insere em str
        normalize(str); // Normaliza cada palavra individualmente
        if(!this->isStopWord(str)) words.push_back(str); // Se não é stopWord, adiciona no vector de words 
    }

    return words;
}

// Processa o texto
std::vector<std::string> TextProcessor::processText(std::string text){
    if(!this->loadStopWords("../stopWords.txt")) {
        std::cerr << "Falha ao carregar stopWords\n";
        return {}; // Retorna um vetor nulo, caso não consefuir abrir o texto
    }

    auto words = this->breakWords(text); // Obtem palavras processadas
    return words; // Retorna o vetor de palavras separadas retornado por breakWords
}