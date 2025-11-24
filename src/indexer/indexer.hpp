    #pragma once
    #include "../textProcessor/textProcessor.hpp"
    #include "../index/index.hpp"
    #include <string>
    #include <filesystem>

    class Indexer{
        private:
            Index* index; // Ponteiro do índice
            TextProcessor* processor; // Ponteiro do porcessador de textos

            bool readFile(const std::string& filepath, std::string& content); // Lê o conteúdo do arquivo para a string de referência
            bool processFile(const std::string& filepath); // Processa o arquivo e o insere no índice
            bool istxt(const std::filesystem::path& path); // Verifica se o arquivo é .txt

        public:
            Indexer(Index* idx, TextProcessor* proc); // Construtor
            ~Indexer(); // Destrutor

            bool buildIndex(const std::string& dirPath); // Constrói o índice
            int getTotalFiles(); // Retorna o total de arquivos indexado
        };
