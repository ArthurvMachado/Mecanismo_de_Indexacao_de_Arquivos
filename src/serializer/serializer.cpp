#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "serializer.hpp"

Serializer::Serializer(){}

Serializer::~Serializer(){}

void Serializer::salvar(Index index, std::string arquivo){
    std::ofstream fileToSave(arquivo.append(".dat"));
    
    if (fileToSave.is_open()) {
        std::string indexedDir = index.getIndexedDir();
        int nextId = index.getNextId();
        auto invertedIndex = index.getInvertedIndex();
        // auto nameToId = index.getNameToId();
        auto idToName = index.getIdToName();

        std::string lines = "";
        std::unordered_set<std::string> names;

        lines.append(indexedDir);
        lines.append(",");
        lines.append(std::to_string(nextId));
        lines.append("\n");

        // persiste idToName & possibilita gerar no carregamento nameToId
        lines.append("idToName\n");
        for (int i = 0; i < nextId; i++){
            std::string row = "";

            row.append(std::to_string(i));
            row.append(",");
            row.append(idToName[i]);

            names.insert(idToName[i]);

            lines.append(row);
            lines.append("\n");
        }

        // persiste invertedIndex
        lines.append("invertedIndex\n");
        for(auto it : invertedIndex){
            lines.append(it.first);
            lines.append(",");
            for (auto id : it.second){
                lines.append(std::to_string(id));
                lines.append(",");
            }
        }

        fileToSave << lines;
        fileToSave.close();
    }
}

Index Serializer::carregar(std::string arquivo){
    std::ifstream fileToRead(arquivo.append(".dat"));
    std::string line;

    int nextId;
    std::string indexedDir;
    std::unordered_map<std::string, std::unordered_set<int>> invertedIndex;
    std::unordered_map<std::string, int> nameToId;
    std::unordered_map<int, std::string> idToName;

    Index index;
    bool idToNameFlag = false;
    bool invertedIndexFlag = false;

    if (fileToRead.is_open()) {
        while(getline(fileToRead, line)){

            if(line == "idToName") {idToNameFlag = true; continue;}
            if(line == "invertedIndex") {invertedIndexFlag = true; continue;}

            if (!idToNameFlag && !invertedIndexFlag) {
                indexedDir = line.substr(0, line.find(',')); // lê IndexedDir
                nextId = std::stoi(line.substr(line.find(',')+1)); // lê nextId
                idToNameFlag = true;

            } else if (idToNameFlag && !invertedIndexFlag){    
                // lê nameToId e idToName
                int id = std::stoi(line.substr(0, line.find(',')));
                std::string name = line.substr(line.find(',')+1);

                nameToId[name] = id;
                idToName[id] = name;

            } else if (idToNameFlag && invertedIndexFlag){
                // lê invertedIndex
                std::string s = line.substr(0, line.find(',')); // cada linha é  uma relação (Palavra → IDs)
                std::string ids = line.substr(line.find(',')+1); // mantém apenas os ID's
                invertedIndex.insert({s, {}}); // separa e salva o primeiro item como palavra
                while (ids != ""){
                    invertedIndex[s].insert(std::stoi(ids.substr(0, ids.find(',')))); // salva o número até o primeira vírgula
                    ids = ids.substr(ids.find(',')+1); // remove o número salvo
                }
            }
        }
        
        index.setIndexedDir(indexedDir);
        index.setIdToName(idToName);
        index.setNameToId(nameToId);
        index.setInvertedIndex(invertedIndex);
        index.setNextId(nextId);
        
        fileToRead.close();
    }
    return index;
}
