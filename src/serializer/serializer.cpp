#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "serializer.hpp"

Serializer::Serializer(){}

Serializer::~Serializer(){}

void Serializer::save(Index index, std::string file){
    std::ofstream fileToSave(file + ".dat");
    
    if (!fileToSave.is_open()) {
        std::cerr << "Erro ao abrir arquivo para salvar: " << file << ".dat\n";
        return;
    }
    
    std::string dirPath = index.getDirPath();
    int nextId = index.getNextId();
    auto invertedIndex = index.getInvertedIndex();
    auto idToName = index.getIdToName();

    // Linha 1: dirPath,nextId
    fileToSave << dirPath << "," << nextId << "\n";

    // Seção idToName
    fileToSave << "idToName\n";
    for (int i = 0; i < nextId; i++){
        fileToSave << i << "," << idToName.at(i) << "\n";
    }

    // Seção invertedIndex
    fileToSave << "invertedIndex\n";
    for(const auto& it : invertedIndex){
        fileToSave << it.first << ",";
        for (const auto& id : it.second){
            fileToSave << id << ",";
        }
        fileToSave << "\n"; // IMPORTANTE: quebra de linha!
    }

    fileToSave.close();
}

Index Serializer::load(std::string file){
    std::ifstream fileToRead(file + ".dat");
    std::string line;

    int nextId = 0;
    std::string dirPath;
    std::unordered_map<std::string, std::unordered_set<int>> invertedIndex;
    std::unordered_map<std::string, int> nameToId;
    std::unordered_map<int, std::string> idToName;

    Index index;
    bool idToNameFlag = false;
    bool invertedIndexFlag = false;

    if (!fileToRead.is_open()) {
        std::cerr << "Erro ao abrir arquivo para carregar: " << file << ".dat\n";
        return index;
    }

    while(getline(fileToRead, line)){
        // Ignorar linhas vazias
        if(line.empty()) continue;

        if(line == "idToName") {
            idToNameFlag = true;
            invertedIndexFlag = false;
            continue;
        }
        
        if(line == "invertedIndex") {
            invertedIndexFlag = true;
            idToNameFlag = false;
            continue;
        }

        if (!idToNameFlag && !invertedIndexFlag) {
            // Primeira linha: dirPath,nextId
            size_t pos = line.find(',');
            if(pos != std::string::npos) {
                dirPath = line.substr(0, pos);
                nextId = std::stoi(line.substr(pos + 1));
            }

        } else if (idToNameFlag && !invertedIndexFlag){    
            // Lê nameToId e idToName
            size_t pos = line.find(',');
            if(pos != std::string::npos) {
                int id = std::stoi(line.substr(0, pos));
                std::string name = line.substr(pos + 1);

                nameToId[name] = id;
                idToName[id] = name;
            }

        } else if (invertedIndexFlag){
            // Lê invertedIndex
            size_t pos = line.find(',');
            if(pos == std::string::npos) continue;
            
            std::string word = line.substr(0, pos);
            std::string ids = line.substr(pos + 1);
            
            invertedIndex[word] = std::unordered_set<int>();
            
            // Parse dos IDs
            while (!ids.empty()){
                size_t commaPos = ids.find(',');
                if(commaPos == std::string::npos) break;
                
                std::string idStr = ids.substr(0, commaPos);
                if(!idStr.empty()) {
                    invertedIndex[word].insert(std::stoi(idStr));
                }
                ids = ids.substr(commaPos + 1);
            }
        }
    }
    
    index.setDirPath(dirPath);
    index.setIdToName(idToName);
    index.setNameToId(nameToId);
    index.setInvertedIndex(invertedIndex);
    index.setNextId(nextId);
    
    fileToRead.close();
    
    return index;
}