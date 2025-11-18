#include "indexer.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

// Construtor
Indexer::Indexer(Index* idx, TextProcessor* proc){
    this->index = idx;
    this->processor = proc;
} 

Indexer::~Indexer() {} // Destrutor

bool Indexer::readFile(const std::string& filepath, std::string& content){
    std::ifstream file(filepath); // Carrega o texto desejado
    
    if(!file) return false; // Arquivo não encontrado
    
    std::stringstream buffer; // Buffer de string orientada a entrada e saída
    buffer << file.rdbuf(); // Lê todo o arquivo e insere no buffer 
    
    content = buffer.str(); // Copia o buffer para text no formato str
    
    file.close(); // Fecha o arquivo
    return true;
}

// Processa o arquivo e o insere no índice
bool Indexer::processFile(const std::string& filepath){
    std::string text;
    if(!this->readFile(filepath, text)) return false;

    std::vector<std::string> vec = this->processor->processText(text);
    for(std::string el : vec) this->index->addWord(el, filepath);

    return true;
}

// Verifica se o arquivo é .txt
bool Indexer::istxt(const std::filesystem::path& path){ return (path.extension() == ".txt"); }

// Constrói o índice
bool Indexer::buildIndex(const std::string& dirPath){
    this->index->setDirPath(dirPath);
    int filesProcessed = 0;
    
    try{
        for(const auto& file : std::filesystem::recursive_directory_iterator(dirPath)){
            if(!file.is_regular_file()) continue;
            const auto& path = file.path();   
            
            if(this->istxt(path)){
                if(processFile(file.path().string())) filesProcessed++;
                else std::cerr << "Falha ao processar: " << path << std::endl;
            }
        }
        std::cout << "Total de arquivos indexados: " << filesProcessed << std::endl;
    } catch(const std::exception& e){
        std::cerr << "Erro ao acessar diretório: " << e.what() << std::endl;
        return false;
    }
    return true;
}

// Retorna o total de arquivos indexado
int Indexer::getTotalFiles(){ return this->index->getTotalTexts(); }

// void Indexer::test() {
//     std::cout << "\n========== TESTE DA CLASSE INDEXER ==========\n\n";
    
//     // Criar objetos necessários
//     Index testIndex;
//     TextProcessor testProcessor;
    
//     // Criar indexer com os objetos criados
//     Indexer indexer(&testIndex, &testProcessor);
    
//     std::cout << "1. INDEXER CRIADO\n";
//     std::cout << "   Objetos Index e TextProcessor inicializados\n\n";
    
//     // Testar buildIndex
//     std::cout << "2. CONSTRUINDO INDICE\n";
//     std::cout << "   Diretorio: C:\\Users\\DELL\\Documents\\GitHub\\Mecanismo_de_Indexacao_de_Arquivos\\machado\n";
//     std::cout << "   Iniciando indexacao...\n\n";
    
//     std::string dirPath = "C:\\Users\\DELL\\Documents\\GitHub\\Mecanismo_de_Indexacao_de_Arquivos\\machado";
    
//     if(indexer.buildIndex(dirPath)) {
//         std::cout << "   V Indexacao concluida com sucesso!\n\n";
//     } else {
//         std::cout << "   X Falha na indexacao!\n\n";
//         return;
//     }
    
//     // Estatísticas
//     std::cout << "3. ESTATISTICAS DA INDEXACAO\n";
//     std::cout << "   Total de arquivos indexados: " << indexer.getTotalFiles() << "\n";
//     std::cout << "   Total de palavras unicas: " << testIndex.getTotalWords() << "\n";
//     std::cout << "   Diretorio indexado: " << testIndex.getDirPath() << "\n\n";
    
//     // Testar busca de algumas palavras conhecidas
//     std::cout << "4. TESTE DE BUSCA (Palavras comuns em Machado de Assis)\n";
//     std::cout << "   --------------------------------------------------\n";
    
//     std::vector<std::string> testWords = {"capitu", "bentinho", "rubiao", "amor", "morte", "sociedade"};
    
//     for(const auto& word : testWords) {
//         auto docs = testIndex.getTexts(word);
//         std::cout << "   Palavra: '" << word << "'\n";
//         std::cout << "   Encontrada em " << docs.size() << " documento(s)\n";
        
//         if(docs.size() > 0 && docs.size() <= 3) {
//             std::cout << "   Arquivos:\n";
//             for(int id : docs) {
//                 std::string fullPath = testIndex.getFilename(id);
//                 // Extrair apenas o nome do arquivo
//                 size_t lastSlash = fullPath.find_last_of("\\/");
//                 std::string filename = (lastSlash != std::string::npos) 
//                     ? fullPath.substr(lastSlash + 1) 
//                     : fullPath;
//                 std::cout << "      - " << filename << "\n";
//             }
//         }
//         std::cout << "\n";
//     }
    
//     // Listar alguns arquivos indexados
//     std::cout << "5. AMOSTRA DE ARQUIVOS INDEXADOS\n";
//     std::cout << "   -------------------------------\n";
    
//     int maxFiles = std::min(5, testIndex.getTotalTexts());
//     for(int i = 0; i < maxFiles; i++) {
//         std::string fullPath = testIndex.getFilename(i);
//         size_t lastSlash = fullPath.find_last_of("\\/");
//         std::string filename = (lastSlash != std::string::npos) 
//             ? fullPath.substr(lastSlash + 1) 
//             : fullPath;
//         std::cout << "   [ID " << i << "] " << filename << "\n";
//     }
//     std::cout << "   ... e mais " << (testIndex.getTotalTexts() - maxFiles) << " arquivo(s)\n\n";
    
//     // Teste de palavra inexistente
//     std::cout << "6. TESTE COM PALAVRA INEXISTENTE\n";
//     std::cout << "   ------------------------------\n";
//     std::string fakeWord = "xyzabc123";
//     auto fakeDocs = testIndex.getTexts(fakeWord);
//     std::cout << "   Palavra: '" << fakeWord << "'\n";
//     std::cout << "   Encontrada em " << fakeDocs.size() << " documento(s)";
//     std::cout << " (esperado: 0)\n\n";
    
//     // Teste de interseção manual (simular busca AND)
//     std::cout << "7. TESTE DE INTERSECAO (Busca AND)\n";
//     std::cout << "   ---------------------------------\n";
//     std::cout << "   Buscando documentos com 'capitu' AND 'bentinho'\n";
    
//     auto docs1 = testIndex.getTexts("capitu");
//     auto docs2 = testIndex.getTexts("bentinho");
    
//     std::cout << "   'capitu' aparece em: " << docs1.size() << " documento(s)\n";
//     std::cout << "   'bentinho' aparece em: " << docs2.size() << " documento(s)\n";
    
//     // Interseção manual
//     std::unordered_set<int> intersection;
//     for(int id : docs1) {
//         if(docs2.find(id) != docs2.end()) {
//             intersection.insert(id);
//         }
//     }
    
//     std::cout << "   Intersecao: " << intersection.size() << " documento(s)\n";
//     if(intersection.size() > 0) {
//         std::cout << "   Arquivos com ambas palavras:\n";
//         for(int id : intersection) {
//             std::string fullPath = testIndex.getFilename(id);
//             size_t lastSlash = fullPath.find_last_of("\\/");
//             std::string filename = (lastSlash != std::string::npos) 
//                 ? fullPath.substr(lastSlash + 1) 
//                 : fullPath;
//             std::cout << "      - " << filename << "\n";
//         }
//     }
//     std::cout << "\n";
    
//     std::cout << "========== TESTE CONCLUIDO ==========\n\n";
// }