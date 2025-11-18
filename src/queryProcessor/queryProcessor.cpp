#include "queryProcessor.hpp"
#include "../index/index.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_set>

QueryProcessor::QueryProcessor(Index* idx) { this->index = idx; } // Construtor

QueryProcessor::~QueryProcessor() {} // Destrutor

std::unordered_set<int> QueryProcessor::intersectSets(const std::unordered_set<int>& set1, const std::unordered_set<int>& set2){
    std::unordered_set<int> res;
    std::unordered_set<int> sml = (set1.size() < set2.size()) ? set1 : set2;
    std::unordered_set<int> lgr = (set1.size() >= set2.size()) ? set1 : set2;

    for(int el : sml) if(lgr.find(el) != lgr.end()) res.insert(el);
    return res;
}

std::unordered_set<int> QueryProcessor::intersectMultSets(const std::vector<std::unordered_set<int>>& sets){
    if(sets.size() == 0) return std::unordered_set<int>();
    if(sets.size() == 1) return sets[0];
    
    std::unordered_set<int> res = intersectSets(sets[0], sets[1]);
    for(int i = 2; i < sets.size(); i++) res = intersectSets(res, sets[i]);
    return res;
}

std::string extractFilename(const std::string& fullPath){ return std::filesystem::path(fullPath).filename().string(); }

std::vector<std::string> QueryProcessor::searchWord(std::string word){
    std::vector<std::string> res;
    auto ids = this->index->getTexts(word);
    for(int el : ids) res.push_back(this->index->getFilename(el));

    return res;
}

std::vector<std::string> QueryProcessor::searchMultWord(std::vector<std::string> words){
    std::vector<std::string> res;
    std::vector<std::unordered_set<int>> ids;
    
    for(std::string word : words) ids.push_back(this->index->getTexts(word));
    std::unordered_set<int> intersecID = intersectMultSets(ids);

    for(int el : intersecID) res.push_back(this->index->getFilename(el));

    return res;
}