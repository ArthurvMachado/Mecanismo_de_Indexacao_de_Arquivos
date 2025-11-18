#include "index.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Construtor
Index::Index(){
    invertedIndex.clear(); // inverteIndex inicializa vazio
    nameToId.clear(); // nameToId inicializa vazio
    idToName.clear(); // idToName inicializa vazio

    nextId = 0; // Próximo ID = 0
} 

// Destrutor
Index::~Index() {} 

//
int Index::generateId(const std::string& filename){    
    if(nameToId.find(filename) == nameToId.end()){ 
        nameToId.insert({filename, nextId});
        idToName.insert({nextId++, filename});
    } // Se não estiver já inserido, o insere 

    return nameToId[filename]; // Retorna o ID
}

// Adiciona palavras no índice invertido
void Index::addWord(const std::string& word, const std::string& filename){
    int id = generateId(filename); // ID do arquivo
    invertedIndex[word].insert(id); // Insere o arquivo com a chave word
}

/*===== Busca =====*/
// Retorna os documentos que apresentam word 
const std::unordered_set<int> Index::getTexts(const std::string& word) const{ 
    auto it = this->invertedIndex.find(word);
    return (it != this->invertedIndex.end()) ? it->second : std::unordered_set<int>(); // Retorna o set de textos. Vazio se não existir
}

// Retorna o arquivo correspendente ao id
const std::string Index::getFilename(int id) const{
    auto it = this->idToName.find(id);
    return (it != this->idToName.end()) ? it->second : ""; // Retorna o nome do texto. Nulo se não existir
}

// Retorna o id correspondente ao arquivo
int Index::getFileId(const std::string& filename) const{
    auto it = this->nameToId.find(filename);
    return (it != this->nameToId.end()) ? it->second : -1; // Retorna o id do texto. -1 se não existir
}
/* ===== - ===== */

/* ===== Auxiliares ===== */
// Verifica se palavra existe no índice
bool Index::wordExists(const std::string& word){ return (this->invertedIndex.find(word) != this->invertedIndex.end()) ? true : false; } 

// Retorna total de documentos indexados
int Index::getTotalTexts(){ return this->idToName.size(); }

// Retorna total de palavras indexadas
int Index::getTotalWords(){ return this->invertedIndex.size(); }

// Limpa o índice
void Index::clear(){
    this->invertedIndex.clear();
    this->nameToId.clear();
    this->idToName.clear();
}
/* ===== - =====*/

/* ===== Setters e Getters ===== */
// Índice invertido

// Retorna o índice invertido
const std::unordered_map<std::string, std::unordered_set<int>>& Index::getInvertedIndex() const{ return this-> invertedIndex; } 
// Define o índice invertido
void Index::setInvertedIndex(const std::unordered_map<std::string, std::unordered_set<int>>& index){ this->invertedIndex = index; } 
    
// (nomeArquivo → ID)

// Retorna a relação (nomeArquivo → ID)
const std::unordered_map<std::string, int>& Index::getNameToId() const{ return this->nameToId; } 
// Define a relação (nomeArquivo → ID)
void Index::setNameToId(const std::unordered_map<std::string, int>& map){ this->nameToId = map; } 

// (ID → nomeArquivo)

// Retorna a relação (ID → nomeArquivo)
const std::unordered_map<int, std::string>& Index::getIdToName() const{ return this->idToName; } 
// Define a relação (ID → nomeArquivo)
void Index::setIdToName(const std::unordered_map<int, std::string>& map){ this->idToName = map; } 

// nextId

// Retorna o próximo ID
int Index::getNextId() const{ return this->nextId; } 
// Define o próximo ID
void Index::setNextId(int id){ this->nextId = id; } 

// invertedID

// Retorna o índice invertido
const std::string Index::getDirPath() const{ return this->dirPath; }
// Define o índice invertido
void Index::setDirPath(const std::string& path){ this->dirPath = path; }
/* ===== - ===== */



// void Index::test() {
//     std::cout << "========== TESTE DA CLASSE INDEX ==========\n\n";
    
//     // Limpar índice antes de começar
//     this->clear();
//     std::cout << "1. Indice limpo\n";
//     std::cout << "   Total documentos: " << getTotalTexts() << "\n";
//     std::cout << "   Total palavras: " << getTotalWords() << "\n\n";
    
//     // Testar adição de palavras
//     std::cout << "2. Adicionando palavras...\n";
//     addWord("capitu", "../machado/romance/domCasmurro.txt");
//     addWord("bentinho", "../machado/romance/domCasmurro.txt");
//     addWord("capitu", "../machado/romance/memorialAires.txt");
//     addWord("rubiao", "../machado/romance/quincas.txt");
//     addWord("bentinho", "../machado/romance/quincas.txt");
//     std::cout << "   Palavras adicionadas!\n\n";
    
//     // Verificar totais
//     std::cout << "3. Estatisticas:\n";
//     std::cout << "   Total documentos: " << getTotalTexts() << "\n";
//     std::cout << "   Total palavras: " << getTotalWords() << "\n\n";
    
//     // Testar mapeamento ID <-> Nome
//     std::cout << "4. Mapeamento ID <-> Nome:\n";
//     for(const auto& pair : idToName) {
//         std::cout << "   ID " << pair.first << ": " << pair.second << "\n";
//     }
//     std::cout << "\n";
    
//     // Testar getFileId
//     std::cout << "5. Testando getFileId:\n";
//     std::string testFile = "../machado/romance/domCasmurro.txt";
//     int id = getFileId(testFile);
//     std::cout << "   ID de '" << testFile << "': " << id << "\n";
    
//     std::string fakeFile = "naoExiste.txt";
//     int fakeId = getFileId(fakeFile);
//     std::cout << "   ID de '" << fakeFile << "': " << fakeId << " (deve ser -1)\n\n";
    
//     // Testar getFilename
//     std::cout << "6. Testando getFilename:\n";
//     std::string filename = getFilename(0);
//     std::cout << "   Nome do ID 0: " << filename << "\n";
    
//     std::string fakeName = getFilename(999);
//     std::cout << "   Nome do ID 999: '" << fakeName << "' (deve estar vazio)\n\n";
    
//     // Testar wordExists
//     std::cout << "7. Testando wordExists:\n";
//     std::cout << "   'capitu' existe? " << (wordExists("capitu") ? "SIM" : "NAO") << "\n";
//     std::cout << "   'inexistente' existe? " << (wordExists("inexistente") ? "SIM" : "NAO") << "\n\n";
    
//     // Testar getTexts (busca)
//     std::cout << "8. Testando getTexts (busca por palavra):\n";
    
//     std::cout << "   Documentos com 'capitu':\n";
//     auto capituDocs = getTexts("capitu");
//     for(int docId : capituDocs) {
//         std::cout << "      ID " << docId << ": " << getFilename(docId) << "\n";
//     }
    
//     std::cout << "   Documentos com 'bentinho':\n";
//     auto bentinhoDocs = getTexts("bentinho");
//     for(int docId : bentinhoDocs) {
//         std::cout << "      ID " << docId << ": " << getFilename(docId) << "\n";
//     }
    
//     std::cout << "   Documentos com 'rubiao':\n";
//     auto rubiaoDocs = getTexts("rubiao");
//     for(int docId : rubiaoDocs) {
//         std::cout << "      ID " << docId << ": " << getFilename(docId) << "\n";
//     }
    
//     std::cout << "   Documentos com 'inexistente':\n";
//     auto vazios = getTexts("inexistente");
//     std::cout << "      Quantidade: " << vazios.size() << " (deve ser 0)\n\n";
    
//     // Testar índice invertido completo
//     std::cout << "9. Indice Invertido Completo:\n";
//     for(const auto& pair : invertedIndex) {
//         std::cout << "   '" << pair.first << "' -> { ";
//         for(int id : pair.second) {
//             std::cout << id << " ";
//         }
//         std::cout << "}\n";
//     }
//     std::cout << "\n";
    
//     // Testar diretório indexado
//     std::cout << "10. Testando diretorio indexado:\n";
//     setIndexedDir("../machado");
//     std::cout << "    Diretorio definido: " << getIndexedDir() << "\n\n";
    
//     // Testar getters de serialização
//     std::cout << "11. Testando getters para serializacao:\n";
//     std::cout << "    getNextId(): " << getNextId() << "\n";
//     std::cout << "    getInvertedIndex().size(): " << getInvertedIndex().size() << "\n";
//     std::cout << "    getNameToId().size(): " << getNameToId().size() << "\n";
//     std::cout << "    getIdToName().size(): " << getIdToName().size() << "\n\n";
    
//     std::cout << "========== TESTE CONCLUIDO ==========\n";
// }