#include "queryProcessor.hpp"
#include "../index/index.hpp"
#include <iostream>
#include <vector>
#include <string>
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