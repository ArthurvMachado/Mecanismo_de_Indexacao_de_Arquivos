#include "textProcessor.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream> // std::ifstream()
#include <sstream> // std::stringstream()

TextProcessor::TextProcessor(){
    stopWords.clear();
    accents = ACCENT_MAP;
}

TextProcessor::~TextProcessor() {}

bool TextProcessor::loadStopWords(const std::string& filepath){
    std::ifstream words(filepath); // Carrega stopWords.txt

    if(!words) return false; // Arquivo não encontrado

    std::string str;
    // Separa o texto do arquivo a cada quebra de linha ou espaço e o copia para str 
    while(words >> str) stopWords.insert(str); // Adiciona no set de Stop Words

    words.close(); // Fecha o arquivo
    return true;
}

bool TextProcessor::loadText(const std::string& filepath){
    std::ifstream text_a(filepath); // Carrega o texto desejado
    
    if(!text_a) return false; // Arquivo não encontrado
    
    std::stringstream buffer; // Buffer de string orientada a entrada e saída
    buffer << text_a.rdbuf(); // Lê todo o arquivo e insere no buffer 
    
    text = buffer.str(); // Copia o buffer para text no formato str
    
    text_a.close(); // Fecha o arquivo
    return true;
}

std::vector<std::string> TextProcessor::breakWords(const std::string& text){
    std::vector<std::string> words; // Vetor de palavras separadas
    
    std::istringstream buffer(text); // Buffer com o conteúdo de text
    
    std::string str;
    while(buffer >> str){ // Separa o texto a cada quebra de linha ou espaço e insere em str
        normalize(str); // Normaliza cada palavra individualmente
        if(!this->isStopWord(str)) words.push_back(str); // Se não é stopWord, adiciona no vector de words 
    }

    return words;
}

void TextProcessor::normalize(std::string& text){
    this->lowerCase(text); this->removePunctuation(text); // Deixa text em minúsculo e retira suas pontuações
}

void TextProcessor::lowerCase(std::string& text){ 
    for(int i = 0; i < text.size(); i++){
        if(i + 1 < text.size()){ // Caracteres acentuadas ocupam dois bytes, por isso deve-se verificar se existem dois caracteres na string
            std::string c = text.substr(i, 2); // Substring com os próximos dois bytes
            if(accents.find(c) != accents.end()){ // Verifica se o caractere é um acento 
                text.replace(i, 2, accents[c]); // Substitui o caractere pela sua versão minúscula
                i++; continue; // Avança um carctere na string e continua o loop
            } 
        } 
        // Se não for um caractere acentuado
        if(std::isupper(text[i])) text[i] = std::tolower(text[i]); // Verifica se o caractere é uma letra maiúscula e a transforma em minúscuala
    }
}

void TextProcessor::removePunctuation(std::string& text){
    for(int i = 0; i < text.size(); i++) if(std::ispunct(text[i])) text.erase(i--, 1); // Se o caractere for uma pontuação é removido
    // i--, pois deve retornar o índice, pois o indíce da pontuação, após sua remoção, é ocupado por outro caractere
}

bool TextProcessor::isStopWord(const std::string& text){
    return (stopWords.find(text) != stopWords.end()) ? true : false; // Retorna se text está no set stopWords
}

std::vector<std::string> TextProcessor::processar(std::string texto){
    std::vector<std::string> placeholder;
    
    if(!this->loadText("../machado/conto/contosFluminenses.txt")) return placeholder;
    if(!this->loadStopWords("../stopWords.txt")) return placeholder;

    std::vector<std::string> words = this->breakWords(this->text);
    for(std::string el : words) std::cout << el << std::endl;
    return placeholder;
}