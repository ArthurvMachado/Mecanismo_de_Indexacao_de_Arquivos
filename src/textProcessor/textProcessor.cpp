#include "textProcessor.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <cctype>

TextProcessor::TextProcessor() { stopWords.clear(); }
TextProcessor::~TextProcessor() {}

bool TextProcessor::loadStopWords(const std::string& datapath){
    std::ifstream words(datapath); // Carrega stopWords.txt

    if(!words) return false; // Arquivo não encontrado

    std::string str;
    while(words >> str) stopWords.insert(str); // Adiciona no set de Stop Words

    words.close();
    return true;
}

bool TextProcessor::loadText(const std::string& datapath){
    std::ifstream text_a(datapath); // Carrega o texto desejado

    if(!text_a) return false; // Arquivo não encontrado

    std::stringstream buffer; // Buffer com o texto original
    buffer << text_a.rdbuf(); // Lê todo o arquivo para o buffer

    text = buffer.str();
    return true;
}

std::vector<std::string> TextProcessor::breakWords(const std::string& text){
    std::vector<std::string> words; // Vetor de palavras separadas
    
    std::istringstream buffer(text); // Buffer com o texto informado
    
    std::string str;
    while(buffer >> str){
        lowerCase(str);
        words.push_back(str);
    }

    return words;
}

void TextProcessor::lowerCase(std::string& text){
    for(char c : text) text[c] = std::tolower(text[c]);
}

std::vector<std::string> TextProcessor::processar(std::string texto){
    std::vector<std::string> placeholder;
    
    if(!loadText("../machado/conto/contosFluminenses.txt")) return placeholder;
    std::vector<std::string> words = breakWords(this->text);

    for(std::string el : words) std::cout << el << std::endl;
    return placeholder;
}