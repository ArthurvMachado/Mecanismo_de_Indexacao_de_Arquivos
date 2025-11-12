#include "textProcessor.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

TextProcessor::TextProcessor(){ stopWords.clear(); }
TextProcessor::~TextProcessor() {}

bool TextProcessor::loadStopWords(const std::string& filepath){
    std::ifstream words(filepath); // Carrega stopWords.txt

    if(!words) return false; // Arquivo não encontrado

    std::string str;
    while(words >> str) stopWords.insert(str); // Adiciona no set de Stop Words

    words.close(); // Fecha o arquivo
    return true;
}

bool TextProcessor::loadText(const std::string& filepath){
    std::ifstream text_a(filepath); // Carrega o texto desejado

    if(!text_a) return false; // Arquivo não encontrado

    std::stringstream buffer; // Buffer com o texto original
    buffer << text_a.rdbuf(); // Lê todo o arquivo para o buffer

    text = buffer.str(); // Copia o buffer para text

    text_a.close();
    return true;
}

std::vector<std::string> TextProcessor::breakWords(const std::string& text){
    std::vector<std::string> words; // Vetor de palavras separadas
    
    std::istringstream buffer(text); // Buffer com o texto informado
    
    std::string str;
    while(buffer >> str){
        normalize(str);
        if(!this->isStopWord(str)) words.push_back(str);
    }

    return words;
}

void TextProcessor::normalize(std::string& text){ this->lowerCase(text); this->removePunctuation(text); }

void TextProcessor::lowerCase(std::string& text){ for(char& c : text) if(std::isupper(c)) c = std::tolower(c); }
void TextProcessor::removePunctuation(std::string& text){ for(int i = 0; i < text.size(); i++) if(std::ispunct(text[i])) text.erase(i--, 1); }

bool TextProcessor::isStopWord(const std::string& text){ return (stopWords.find(text) != stopWords.end()) ? true : false; }

std::vector<std::string> TextProcessor::processar(std::string texto){
    std::vector<std::string> placeholder;
    
    if(!this->loadText("../machado/conto/contosFluminenses.txt")) return placeholder;
    if(!this->loadStopWords("../stopWords.txt")) return placeholder;

    std::vector<std::string> words = this->breakWords(this->text);
    for(std::string el : words) std::cout << el << std::endl;
    return placeholder;
}