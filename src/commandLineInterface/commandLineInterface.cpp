#include "commandLineInterface.hpp"
#include <iostream>
#include <filesystem>
#include <algorithm>

// Construtor
CommandLineInterface::CommandLineInterface() {}

// Destrutor
CommandLineInterface::~CommandLineInterface() {}

// Extrai apenas o nome do arquivo
std::string CommandLineInterface::extractFilename(const std::string& fullPath) {
    for(int i = fullPath.size() - 1; i >= 0; i--) // Varre o caminho do arquivo ao contrário
        if(fullPath[i] == '\\' || fullPath[i] == '/') return fullPath.substr(i + 1); // Ao encontrar / ou \ retorna a substring correspondente ao nome do aruqivo
    
    return fullPath; // Retorna o nome completo caso não ache / ou \ na string
}

// Exibe os resultados da busca
void CommandLineInterface::displayResults(const std::vector<std::string>& results, const std::string& query) {
    std::cout << "\n========================================\n";
    std::cout << "Resultados para: \"" << query << "\"\n"; // query = palavra(s) na busca
    std::cout << "========================================\n";
    
    if(results.empty()) std::cout << "Nenhum documento encontrado.\n"; // Caso não existir nos textos
    else {
        std::cout << "Encontrado(s) " << results.size() << " documento(s):\n\n"; // Número de documentos onde a busca está presente
        for(const std::string& filepath : results) std::cout << " - " << extractFilename(filepath) << "\n"; // Arquivos onde a busca está presente
    }
    std::cout << "========================================\n\n";
}

// Verifica se index.dat existe
bool CommandLineInterface::indexExists() { return std::filesystem::exists("index.dat"); }

// Trata o comando "construir"
bool CommandLineInterface::handleBuild(const std::string& directoryPath) {
    std::cout << "\n>>> Iniciando indexacao do diretorio: " << directoryPath << "\n\n";
    
    // Verifica se o diretório existe
    if(!std::filesystem::exists(directoryPath)) {
        std::cerr << "ERRO: Diretorio nao encontrado: " << directoryPath << "\n";
        return false;
    }
    
    if(!std::filesystem::is_directory(directoryPath)) {
        std::cerr << "ERRO: O caminho fornecido nao e um diretorio: " << directoryPath << "\n";
        return false;
    }
    
    Index index;
    TextProcessor processor;
    Indexer indexer(&index, &processor);

    std::cout << "Processando arquivos...\n";
    if(!indexer.buildIndex(directoryPath)) {
        std::cerr << "ERRO: Falha ao construir o indice.\n";
        return false;
    }
    
    std::cout << "\n>>> Indexacao concluida!\n";
    std::cout << "    Total de arquivos indexados: " << indexer.getTotalFiles() << "\n";
    std::cout << "    Total de palavras unicas: " << index.getTotalWords() << "\n\n";
    
    // Serializar o índice
    std::cout << "Salvando indice em 'index.dat'...\n";
    Serializer serializer;
    serializer.save(index, "index");
    
    std::cout << ">>> Indice salvo com sucesso!\n\n";
    return true;
}

// Trata o comando "buscar"
bool CommandLineInterface::handleSearch(const std::vector<std::string>& terms) {
    // Verifica se o índice existe
    if(!indexExists()) {
        std::cerr << "\nERRO: Arquivo de indice 'index.dat' nao encontrado.\n";
        std::cerr << "Execute primeiro: indice construir <diretorio>\n\n";
        return false;
    }
    
    std::cout << "\n>>> Carregando indice...\n";
    
    // Desserializar o índice
    Serializer serializer;
    Index index = serializer.load("index");
    
    std::cout << ">>> Indice carregado com sucesso!\n";
    std::cout << "    Diretorio indexado: " << index.getDirPath() << "\n";
    std::cout << "    Total de documentos: " << index.getTotalTexts() << "\n";
    std::cout << "    Total de palavras: " << index.getTotalWords() << "\n";
    
    // Processar as palavras de busca (normalizar)
    TextProcessor processor;
    std::vector<std::string> processedTerms;
    
    for(const auto& term : terms) {
        std::string normalized = term;
        processor.lowerCase(normalized);
        processor.removePunctuation(normalized);
        
        if(!processor.isStopWord(normalized) && !normalized.empty()) {
            processedTerms.push_back(normalized);
        }
    }
    
    if(processedTerms.empty()) {
        std::cerr << "\nERRO: Nenhum termo valido para busca (apenas stop words ou termos vazios).\n\n";
        return false;
    }
    
    // Criar query string para exibição
    std::string queryStr;
    for(size_t i = 0; i < processedTerms.size(); i++) {
        queryStr += processedTerms[i];
        if(i < processedTerms.size() - 1) queryStr += " ";
    }
    
    // Realizar a busca
    QueryProcessor queryProc(&index);
    std::vector<std::string> results;
    
    if(processedTerms.size() == 1) {
        std::cout << "\n>>> Buscando por: \"" << processedTerms[0] << "\"\n";
        results = queryProc.searchWord(processedTerms[0]);
    } else {
        std::cout << "\n>>> Buscando por: \"" << queryStr << "\" (AND)\n";
        results = queryProc.searchMultWord(processedTerms);
    }
    
    // Exibir resultados
    displayResults(results, queryStr);
    
    return true;
}

// Exibe instruções de uso
void CommandLineInterface::showHelp() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  MECANISMO DE INDEXACAO DE ARQUIVOS\n";
    std::cout << "========================================\n\n";
    std::cout << "USO:\n";
    std::cout << "  indice construir <diretorio>\n";
    std::cout << "  Indexa todos os arquivos .txt do diretorio especificado\n";
    std::cout << "  e salva o indice em 'index.dat'.\n\n";
    std::cout << " indice buscar <termo1> [termo2] ... [termoN]\n";
    std::cout << "  Busca pelos termos no indice previamente construido.\n";
    std::cout << "  Multiplos termos funcionam como operacao AND.\n\n";
    std::cout << "EXEMPLOS:\n";
    std::cout << "  indice construir ../machado\n";
    std::cout << "  indice buscar capitu\n";
    std::cout << "  indice buscar capitu bentinho amor\n\n";
    std::cout << "========================================\n\n";
}

// Função principal que processa os argumentos
int CommandLineInterface::run(int argc, char* argv[]) {
    // Se não houver argumentos suficientes, mostra ajuda
    if(argc < 2) {
        showHelp();
        return 1;
    }
    
    std::string command = argv[1];
    
    // Converter comando para minúscula
    TextProcessor processor;
    processor.lowerCase(command);
    
    // Comando: construir
    if(command == "construir") {
        if(argc < 3) {
            std::cerr << "\nERRO: Diretorio nao especificado.\n";
            std::cerr << "USO: indice construir <diretorio>\n\n";
            return 1;
        }
        
        std::string directoryPath = argv[2];
        return handleBuild(directoryPath) ? 0 : 1;
    }
    
    // Comando: buscar
    else if(command == "buscar") {
        if(argc < 3) {
            std::cerr << "\nERRO: Nenhum termo de busca especificado.\n";
            std::cerr << "USO: indice buscar <termo1> [termo2] ... [termoN]\n\n";
            return 1;
        }
        
        // Coletar todos os termos de busca
        std::vector<std::string> terms;
        for(int i = 2; i < argc; i++) terms.push_back(argv[i]);
        
        return handleSearch(terms) ? 0 : 1;
    }
    
    else {
        std::cerr << "\nERRO: Comando desconhecido: " << command << "\n";
        showHelp();
        return 1;
    }
}