#pragma once
#include "../index/index.hpp"
#include <string>
#include <vector>
#include <unordered_set>

class QueryProcessor{
    private:
        Index* index;
    
        std::unordered_set<int> intersectSets(const std::unordered_set<int>& s1, const std::unordered_set<int>& s2);
        std::unordered_set<int> intersectMultSets(const std::vector<std::unordered_set<int>>& sets);
    public:
        QueryProcessor(Index* idx); // Construtor
        ~QueryProcessor(); // Destrutor

        std::vector<std::string> searchWord(std::string word);
        std::vector<std::string> searchMultWord(std::vector<std::string> words);
};