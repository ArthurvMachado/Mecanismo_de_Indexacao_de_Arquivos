#pragma once
#include "../index/index.hpp"
#include <string>
#include <vector>
#include <unordered_set>

class QueryProcessor{
    private:
        Index* index;
    
        std::unordered_set<int> intersectSets(const std::unordered_set<int>& s1, const std::unordered_set<int>& s2); // Faz a interseção (ADD) entre dois sets
        std::unordered_set<int> intersectMultSets(const std::vector<std::unordered_set<int>>& sets); // Faz  interseção (ADD) entre múltiplos sets

    public:
        QueryProcessor(Index* idx); // Construtor
        ~QueryProcessor(); // Destrutor

        std::vector<std::string> searchWord(std::string word); // Procura uma palavra
        std::vector<std::string> searchMultWord(std::vector<std::string> words); // Procura múltiplas palavras
};