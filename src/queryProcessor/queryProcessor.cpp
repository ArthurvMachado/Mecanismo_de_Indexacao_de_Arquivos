#include "queryProcessor.hpp"
#include "../index/index.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

QueryProcessor::QueryProcessor(Index* idx) { this->index = idx; } // Construtor

QueryProcessor::~QueryProcessor() {} // Destrutor

// Faz a interseção (ADD) entre dois sets
std::unordered_set<int> QueryProcessor::intersectSets(const std::unordered_set<int>& set1, const std::unordered_set<int>& set2){
    std::unordered_set<int> res; // Set de interseção
    std::unordered_set<int> sml = (set1.size() < set2.size()) ? set1 : set2; // Verifica qual set é menor
    std::unordered_set<int> lgr = (set1.size() >= set2.size()) ? set1 : set2; // Verifica qual set é maior

    for(int el : sml) if(lgr.find(el) != lgr.end()) res.insert(el); // Verifica cada elemento no segundo set
    return res; // Retorna a interseção
}

// Faz a interseção (ADD) entre múltiplos sets
std::unordered_set<int> QueryProcessor::intersectMultSets(const std::vector<std::unordered_set<int>>& sets){
    if(sets.size() == 0) return std::unordered_set<int>(); // Se vazio, retorna set vazio
    if(sets.size() == 1) return sets[0]; // Se possui apenas um set retorna ele
    
    std::unordered_set<int> res = intersectSets(sets[0], sets[1]); // Interseção entre os dois primeiros sets
    for(int i = 2; i < sets.size(); i++) res = intersectSets(res, sets[i]); // Interseção com os próximos sets
    return res; // Retorna a interseção
}

// Procura uma palavra
std::vector<std::string> QueryProcessor::searchWord(std::string word){
    std::vector<std::string> res; // Vetor de nomes de arquivos onde a palavra está presente
    std::unordered_set<int> ids = this->index->getTexts(word); // Set com os IDs dos documentos com a palavra
    for(int el : ids) res.push_back(this->index->getFilename(el)); // Insere no vetor os nomes correspondentes aos IDs

    return res; // Retorna o vetor de nomes dos arquivos
}

// Procura múltiplas palavra
std::vector<std::string> QueryProcessor::searchMultWord(std::vector<std::string> words){
    std::vector<std::string> res; // Vetor de nomes de arquivos onde as palavras então presentes
    std::vector<std::unordered_set<int>> ids; // Vetor de sets de IDs correspondentes as palavras
    
    for(std::string word : words) ids.push_back(this->index->getTexts(word)); // Para cada palavra insere no set os IDs onde está presente
    std::unordered_set<int> intersecID = intersectMultSets(ids); // Interseção entre os sets de IDs

    for(int el : intersecID) res.push_back(this->index->getFilename(el)); // Insere no vetor os nomes correspondentes aos IDs

    return res; // Retorna o vetor de nomes dos arquivos
}