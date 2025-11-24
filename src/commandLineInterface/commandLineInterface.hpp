#pragma once
#include "../index/index.hpp"
#include "../textProcessor/textProcessor.hpp"
#include "../indexer/indexer.hpp"
#include "../queryProcessor/queryProcessor.hpp"
#include "../serializer/serializer.hpp"
#include <string>
#include <vector>

class CommandLineInterface {
private:
    std::string extractFilename(const std::string& fullPath); // Extrai apenas o nome do arquivo
    void displayResults(const std::vector<std::string>& results, const std::string& query); // Exibe resultados formatados
    
    bool handleBuild(const std::string& directoryPath); // Trata comando "construir"
    bool handleSearch(const std::vector<std::string>& terms); // Trata comando "buscar"
    
    bool indexExists(); // Verifica se index.dat existe
    
public:
    CommandLineInterface(); // Construtor
    ~CommandLineInterface(); // Destrutor
    
    int run(int argc, char* argv[]); // Processa argumentos da linha de comando
    void showHelp(); // Exibe instruções de uso
};