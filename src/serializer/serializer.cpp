#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "serializer.hpp"

Serializer::Serializer(){}

Serializer::~Serializer(){}

void Serializer::save(Index index, std::string file){
    std::ofstream fileToSave(file + ".dat"); // Abre o arquivo .dat, permitindo sua criação e edição
    
    if (!fileToSave.is_open()) { std::cerr << "Erro ao abrir arquivo para salvar: " << file << ".dat\n"; return; } // Caso algo dê errado e o .dat não seja criado cai nesse pequeno fallback
    
    std::string dirPath = index.getDirPath(); // salva localmente o dirPath do Index
    int nextId = index.getNextId(); // salva localmente o nextId (tamanho) do Index
    auto invertedIndex = index.getInvertedIndex(); // salva localmente o Indice Invertido do Index
    auto idToName = index.getIdToName(); // salva localmente a relação idToName do Index

    // Linha 1: dirPath,nextId
    fileToSave << dirPath << "," << nextId << "\n"; // persiste na primeira linha do .dat o dirPath e o nextId, separados por vírgula

    // Seção idToName
    fileToSave << "idToName\n"; // adiciona uma linha que indica o começo da relação id e nome sendo salva
    for (int i = 0; i < nextId; i++){
        fileToSave << i << "," << idToName.at(i) << "\n"; // salva id e nome, separados por virgula
    }

    // Seção invertedIndex
    fileToSave << "invertedIndex\n"; // adiciona uma linha que indica o começo da relação do indice invertido
    for(const auto& it : invertedIndex){ // cada linha segue o padrão: {palavra}, {id 1}, {id 2}, {id 3}, ..., {id n}
        fileToSave << it.first << ",";
        for (const auto& id : it.second){
            fileToSave << id << ",";
        }
        fileToSave << "\n"; // IMPORTANTE: quebra de linha! Aqui há a indicação do começo de um novo iterador a ser computado
    }

    fileToSave.close();
}

Index Serializer::load(std::string file){
    std::ifstream fileToRead(file + ".dat"); // loga o arquivo .dat
    std::string line; // variável buffer que recebe cada linha que será processada

    int nextId = 0; // instância local de nextId
    std::string dirPath; // instância local de dirPath
    std::unordered_map<std::string, std::unordered_set<int>> invertedIndex; // instância local do Indice Invertido
    std::unordered_map<std::string, int> nameToId; // instância local da relação nome e id
    std::unordered_map<int, std::string> idToName; // instância local de relação id e nome

    Index index; // criação de um Index a ser retornado
    bool idToNameFlag = false; // flag para avisar quando nameToId e idToName serão carregados
    bool invertedIndexFlag = false; // flag para avisar quando Inverted Index será carregado

    if (!fileToRead.is_open()) { std::cerr << "Erro ao abrir arquivo para carregar: " << file << ".dat\n"; return index; } // fallback para problemas de load do arquivo

    while(getline(fileToRead, line)){
        // Ignorar linhas vazias
        if(line.empty()) continue;

        if(line == "idToName") { // utiliza o marcador idToName para acionar a flag idToName e apagar a invertedIndex
            idToNameFlag = true;
            invertedIndexFlag = false;
            continue;
        }
        
        if(line == "invertedIndex") { // utiliza o marcador idToName para acionar a flag invertedIndex e apagar a idToName
            invertedIndexFlag = true;
            idToNameFlag = false;
            continue;
        }

        if (!idToNameFlag && !invertedIndexFlag) {
            // Primeira linha: dirPath,nextId
            size_t pos = line.find(',');
            if(pos != std::string::npos) { // verifica se a posição da linha é valida
                dirPath = line.substr(0, pos); // salva dirPath
                nextId = std::stoi(line.substr(pos + 1)); // ignora a vírgula e salva nextId
            }

        } else if (idToNameFlag && !invertedIndexFlag){    
            // Lê nameToId e idToName
            size_t pos = line.find(',');
            if(pos != std::string::npos) { // verifica se a posição da linha é valida
                int id = std::stoi(line.substr(0, pos)); // salva o id (valor até a virgula)
                std::string name = line.substr(pos + 1); // salva o nome (valor após a virgula)

                nameToId[name] = id; // salva no set
                idToName[id] = name; // salva no set
            }

        } else if (invertedIndexFlag){
            // Lê invertedIndex
            size_t pos = line.find(',');
            if(pos == std::string::npos) continue; // verifica se a posição da linha é valida
            
            std::string word = line.substr(0, pos); // salva a palavra chave
            std::string ids = line.substr(pos + 1); // separa os ids da palavra chave
            
            invertedIndex[word] = std::unordered_set<int>(); // cria o set para a relação palavra -> ids
            
            // Parse dos IDs
            while (!ids.empty()){
                size_t commaPos = ids.find(',');
                if(commaPos == std::string::npos) break; // verifica se a posição na linha é valida
                
                std::string idStr = ids.substr(0, commaPos);
                if(!idStr.empty()) { // Se a string lida não for vazia
                    invertedIndex[word].insert(std::stoi(idStr)); // adiciona o id para o set
                }
                ids = ids.substr(commaPos + 1); // vai para o próximo id 'jogando fora' a parte da strign até a primeira vírgula encontrada
            }
        }
    }
    
    index.setDirPath(dirPath); // popula o Index com o dirPath
    index.setIdToName(idToName); // popula o Index com a relação idToName
    index.setNameToId(nameToId); // popula o Index com a relação nameToId
    index.setInvertedIndex(invertedIndex); // popula o Index com o indíce invertido
    index.setNextId(nextId); // popula o Index o nextId (tamanho)
    
    fileToRead.close(); // fecha o arquivo
    
    return index;
}