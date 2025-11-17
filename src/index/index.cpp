#include "index.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Construtor
Index::Index(){
    invertedIndex.clear(); // inverteIndex inicializa vazio
    nameToId.clear(); // nameToId inicializa vazio
    idToName.clear(); // idToName inicializa vazio

    nextId = 0; // Próximo ID = 0
} 

// Destrutor
Index::~Index() {} 

//
int Index::generateId(const std::string& filename){    
    if(nameToId.find(filename) == nameToId.end()){ 
        nameToId.insert({filename, nextId});
        idToName.insert({nextId++, filename});
    } // Se não estiver já inserido, o insere 

    return nameToId[filename]; // Retorna o ID
}

// Adiciona palavras no índice invertido
void Index::addWord(const std::string& word, const std::string& filename){
    int id = generateId(filename); // ID do arquivo
    invertedIndex[word].insert(id); // Insere o arquivo com a chave word
}

/*===== Busca =====*/
// Retorna os documentos que apresentam word 
const std::unordered_set<int> Index::getTexts(const std::string& word) const{ 
    auto it = this->invertedIndex.find(word);
    return (it != this->invertedIndex.end()) ? it->second : std::unordered_set<int>(); // Retorna o set de textos. Vazio se não existir
}

// Retorna o arquivo correspendente ao id
const std::string Index::getFilename(int id) const{
    auto it = this->idToName.find(id);
    return (it != this->idToName.end()) ? it->second : nullptr; // Retorna o nome do texto. Nulo se não existir
}

// Retorna o id correspondente ao arquivo
int Index::getFileId(const std::string& filename) const{
    auto it = this->nameToId.find(filename);
    return (it != this->nameToId.end()) ? it->second : -1; // Retorna o id do texto. -1 se não existir
}
/* ===== - ===== */

/* ===== Auxiliares ===== */
// Verifica se palavra existe no índice
bool Index::wordExists(const std::string& word){ (this->invertedIndex.find(word) != this->invertedIndex.end()) ? true : false; } 

// Retorna total de documentos indexados
int Index::getTotalTexts(){ return this->idToName.size(); }

// Retorna total de palavras indexadas
int Index::getTotalWords(){ return this->invertedIndex.size(); }

// Limpa o índice
void Index::clear(){ this->invertedIndex.clear(); }
/* ===== - =====*/

/* ===== Setters e Getters ===== */
// Índice invertido

// Retorna o índice invertido
const std::unordered_map<std::string, std::unordered_set<int>>& Index::getInvertedIndex() const{ return this-> invertedIndex; } 
// Define o índice invertido
void Index::setInvertedIndex(const std::unordered_map<std::string, std::unordered_set<int>>& index){ this->invertedIndex = index; } 
    
// (nomeArquivo → ID)

// Retorna a relação (nomeArquivo → ID)
const std::unordered_map<std::string, int>& Index::getNameToId() const{ return this->nameToId; } 
// Define a relação (nomeArquivo → ID)
void Index::setNameToId(const std::unordered_map<std::string, int>& map){ this->nameToId = map; } 

// (ID → nomeArquivo)

// Retorna a relação (ID → nomeArquivo)
const std::unordered_map<int, std::string>& Index::getIdToName() const{ return this->idToName; } 
// Define a relação (ID → nomeArquivo)
void Index::setIdToName(const std::unordered_map<int, std::string>& map){ this->idToName = map; } 

// nextId

// Retorna o próximo ID
int Index::getNextId() const{ return this->nextId; } 
// Define o próximo ID
void Index::setNextId(int id){ this->nextId = id; } 

// invertedID

// Retorna o índice invertido
const std::string Index::getIndexedDir() const{ return this->indexedDir; }
// Define o índice invertido
void Index::setIndexedDir(const std::string& path){ this->indexedDir = path; }
/* ===== - ===== */

void Index::test(const std::string& filename){
    generateId(filename);

    for(auto el : nameToId) std::cout << el.first << ": " << el.second << std::endl;
}