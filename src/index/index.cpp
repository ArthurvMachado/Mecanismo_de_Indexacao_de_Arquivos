#include "index.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Construtor
Index::Index(){
    invertedIndex.clear();
    nameToId.clear();
    idToName.clear();

    nextId = 0;
} 

Index::~Index() {} // Destrutor

int Index::generateId(const std::string& filename){    
    if(nameToId.find(filename) != nameToId.end()) return nameToId[filename];

    nameToId.insert({filename, nextId});
    idToName.insert({nextId++, filename});

    return -1;
}

void Index::test(const std::string& filename){
    generateId(filename);

    for(auto el : nameToId) std::cout << el.first << ": " << el.second << std::endl;
}