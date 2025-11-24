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
    std::string text; // String para receber o texto do arquivo
    if(!this->readFile(filepath, text)) return false; // Texto do arquivo de filepath em text, retorna falso caso erro

    std::vector<std::string> vec = this->processor->processText(text); // Processa o texto em text
    for(std::string el : vec) this->index->addWord(el, filepath); // Adiciona todas as palavras do vetor de palavras processadas 

    return true;
}

// Verifica se o arquivo é .txt
bool Indexer::istxt(const std::filesystem::path& path){ return (path.extension() == ".txt"); }

// Constrói o índice
bool Indexer::buildIndex(const std::string& dirPath){
    this->index->setDirPath(dirPath); // Seta dirPath do Index com o dirPath informado na chamada
    int filesProcessed = 0; // Contador de arquivos processador
    
    try{
        for(const auto& file : std::filesystem::recursive_directory_iterator(dirPath)){ // Varre recursivamente todos os arquivos e subpastas em dirPath
            if(!file.is_regular_file()) continue; // Se não é um arquivo regular, continua o loop
            const auto& path = file.path(); // Caminho do arquivo
            
            if(this->istxt(path)){ // Se é .txt
                if(processFile(file.path().string())) filesProcessed++; // Se conseguir processar o texto do arquivo, aumenta o contador 
                else std::cerr << "Falha ao processar: " << path << std::endl; // Falha ao processar
            }
        }
        std::cout << "Total de arquivos indexados: " << filesProcessed << std::endl; // Número de arquivos processados
    } catch(const std::exception& e){ // Caso erro
        std::cerr << "Erro ao acessar diretório: " << e.what() << std::endl; // Retorna o erro
        return false; // Retorna falso
    }
    return true;
}

// Retorna o total de arquivos indexado
int Indexer::getTotalFiles(){ return this->index->getTotalTexts(); }