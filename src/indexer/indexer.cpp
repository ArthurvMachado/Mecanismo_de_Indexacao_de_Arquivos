#include "indexer.hpp"
#include <string>
#include <fstream>
#include <sstream>

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