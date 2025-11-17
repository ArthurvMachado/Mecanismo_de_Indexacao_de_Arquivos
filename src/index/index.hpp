#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

class Index{
    private:
        std::unordered_map<std::string, std::unordered_set<int>> invertedIndex; // Índice invertido (Palavra → IDs)
        std::unordered_map<std::string, int> nameToId; // (NomeArquivo → ID)
        std::unordered_map<int, std::string> idToName; // (ID → NomeArquivo)
        int nextId; // Contador de IDs
        std::string indexedDir; // Diretório Indexado
        
        int generateId(const std::string& filename); // Cria um ID para o arquivo, retorna, se existente
        
        public:
        Index(); // Construtor
        ~Index(); // Destrutor
        
        void addWord(const std::string& word, const std::string& filename); // Adiciona palavra no índice invertido
        
        /* ===== Getters e Setter ===== */
        // Índice ivertido
        const std::unordered_map<std::string, std::unordered_set<int>>& getInvertedIndex() const; // Retorna o índice invertido
        void setInvertedIndex(const std::unordered_map<std::string, std::unordered_set<int>>& index); // Define o índice invertido
        
        // (NomeArquivo → ID)
        const std::unordered_map<std::string, int>& getNameToId() const; // Retorna a relação (NomeArquivo → ID)
        void setNameToId(const std::unordered_map<std::string, int>& map); // Define a relação (NomeArquivo → ID)
        
        // (ID → NomeArquivo)
        const std::unordered_map<int, std::string>& getIdToName() const; // Retorna relação (ID → NomeArquivo)
        void setIdToName(const std::unordered_map<int, std::string>& map); // Define a relação (ID → NomeArquivo)
        
        // nextID
        int getNextId() const; // Retorna o próximo ID
        void setNextId(int id); // Define o próximo ID

        // indexedDir
        const std::string getIndexedDir() const; // Retorna o diretório indexado
        void setIndexedDir(const std::string& path); // Define o diretório indexado
        /* ===== - ===== */
        
        /* ===== Busca ===== */
        const std::unordered_set<int> getTexts(const std::string& word) const; // Retorna os documentos que apresentam word
        const std::string getFilename(int id) const; // Retorna o arquivo correspendente ao id
        int getFileId(const std::string& filename) const; // Retorna o id correspondente ao arquivo
        /* ===== - ===== */
        
        /* ===== Auxiliares ===== */
        bool wordExists(const std::string& word); // Verifica se palavra existe no índice
        int getTotalTexts(); // Retorna total de documentos indexados
        int getTotalWords(); // Retorna total de palavras indexadas
        void clear(); // Limpa o índice
        /* ===== - =====*/



        // void test(); // Teste
    };
    
    