#include "indexer.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

// Construtor
Indexer::Indexer(Index* idx, TextProcessor* proc){
    this->index = idx;
    this->processor = proc;
} 

Indexer::~Indexer() {} // Destrutor

bool Indexer::readFile(const std::string& filepath, std::string& content){
    std::ifstream file(filepath); // Carrega o texto desejado
    
    if(!file) return false; // Arquivo não encontrado
    
    std::stringstream buffer; // Buffer de string orientada a entrada e saída
    buffer << file.rdbuf(); // Lê todo o arquivo e insere no buffer 
    
    content = buffer.str(); // Copia o buffer para text no formato str
    
    file.close(); // Fecha o arquivo
    return true;
}

// Processa o arquivo e o insere no índice
void Indexer::processFile(const std::string& filepath){
    std::string text;
    if(!this->readFile(filepath, text)) return;

    std::vector<std::string> vec = this->processor->processText(text);
    for(std::string el : vec) this->index->addWord(el, filepath);
}

// Verifica se o arquivo é .txt
bool Indexer::istxt(const std::string& filepath){ return (std::filesystem::path(filepath).extension() == ".txt"); }

