#include "indexer.hpp"
#include <iostream>
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
bool Indexer::processFile(const std::string& filepath){
    std::string text;
    if(!this->readFile(filepath, text)) return false;

    std::vector<std::string> vec = this->processor->processText(text);
    for(std::string el : vec) this->index->addWord(el, filepath);

    return true;
}

// Verifica se o arquivo é .txt
bool Indexer::istxt(const std::filesystem::path& path){ return (path.extension() == ".txt"); }

// Constrói o índice
bool Indexer::buildIndex(const std::string& dirPath){
    this->index->setDirPath(dirPath);
    int filesProcessed = 0;
    
    try{
        for(const auto& file : std::filesystem::recursive_directory_iterator(dirPath)){
            if(!file.is_regular_file()) continue;
            const auto& path = file.path();   
            
            if(this->istxt(path)){
                if(processFile(file.path().string())) filesProcessed++;
                else std::cerr << "Falha ao processar: " << path << std::endl;
            }
        }
        std::cout << "Total de arquivos indexados: " << filesProcessed << std::endl;
    } catch(const std::exception& e){
        std::cerr << "Erro ao acessar diretório: " << e.what() << std::endl;
        return false;
    }
    return true;
}

// Retorna o total de arquivos indexado
int Indexer::getTotalFiles(){ return this->index->getTotalTexts(); }