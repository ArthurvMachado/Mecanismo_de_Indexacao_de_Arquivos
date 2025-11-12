#include "textProcessor.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>

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

std::vector<std::string> TextProcessor::processar(std::string texto){
    std::vector<std::string> placeholder;
    
    if(!loadStopWords("../stopWords.txt")) return placeholder;

    for(std::string el : stopWords) std::cout << el << std::endl;
    return placeholder;
}