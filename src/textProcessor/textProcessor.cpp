#include "textProcessor.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream> // std::ifstream()
#include <sstream> // std::stringstream()

// Construtor
TextProcessor::TextProcessor(){
    stopWords.clear(); // stopWords inicialize limpa
    accents = ACCENT_MAP; // set accents recebe ACCENT_MAP
    textsFilepath = TEXTS_FILEPATH_MAP; // set com endereços dos textos recebe TEXTS_FILEPATH_MAP
}

// Destrutor
TextProcessor::~TextProcessor() {} 

// Carrega as Stop Words
bool TextProcessor::loadStopWords(const std::string& filepath){
    std::ifstream words(filepath); // Carrega stopWords.txt

    if(!words) return false; // Arquivo não encontrado

    std::string str;
    // Separa o texto do arquivo a cada quebra de linha ou espaço e o copia para str 
    while(words >> str) this->stopWords.insert(str); // Adiciona no set de Stop Words

    words.close(); // Fecha o arquivo
    return true;
}

// Carrega o texto a ser processado
bool TextProcessor::loadText(const std::string& filepath){
    std::ifstream text_a(filepath); // Carrega o texto desejado
    
    if(!text_a) return false; // Arquivo não encontrado
    
    std::stringstream buffer; // Buffer de string orientada a entrada e saída
    buffer << text_a.rdbuf(); // Lê todo o arquivo e insere no buffer 
    
    this->text = buffer.str(); // Copia o buffer para text no formato str
    
    text_a.close(); // Fecha o arquivo
    return true;
}

// Normaliza o texto
void TextProcessor::normalize(std::string& txt){
    this->lowerCase(txt); this->removePunctuation(txt); // Deixa text em minúsculo e retira suas pontuações
}

// Converte para minúsculo
void TextProcessor::lowerCase(std::string& txt){ 
    for(int i = 0; i < txt.size(); i++){
        if(i + 1 < txt.size()){ // Caracteres acentuadas ocupam dois bytes, por isso deve-se verificar se existem dois caracteres na string
            std::string c = txt.substr(i, 2); // Substring com os próximos dois bytes
            if(accents.find(c) != accents.end()){ // Verifica se o caractere é um acento 
                txt.replace(i, 2, accents[c]); // Substitui o caractere pela sua versão minúscula
                i++; continue; // Avança um carctere na string e continua o loop
            } 
        } 
        // Se não for um caractere acentuado
        if(std::isupper(txt[i])) txt[i] = std::tolower(txt[i]); // Verifica se o caractere é uma letra maiúscula e a transforma em minúscuala
    }
}

// Remove pontuação
void TextProcessor::removePunctuation(std::string& txt){
    for(int i = 0; i < txt.size(); i++) if(std::ispunct(txt[i])) txt.erase(i--, 1); // Se o caractere for uma pontuação é removido
    // i--, pois deve retornar o índice, pois o indíce da pontuação, após sua remoção, é ocupado por outro caractere
}

// Detecta Stop Words
bool TextProcessor::isStopWord(const std::string& txt){
    return (stopWords.find(txt) != stopWords.end()) ? true : false; // Retorna se text está no set stopWords
}

// Separa todas as palavras do texto
std::vector<std::string> TextProcessor::breakWords(const std::string& txt){
    std::vector<std::string> words; // Vetor de palavras separadas
    
    std::istringstream buffer(txt); // Buffer com o conteúdo de text
    
    std::string str;
    while(buffer >> str){ // Separa o texto a cada quebra de linha ou espaço e insere em str
        normalize(str); // Normaliza cada palavra individualmente
        if(!this->isStopWord(str)) words.push_back(str); // Se não é stopWord, adiciona no vector de words 
    }

    return words;
}

// Processa o texto
std::vector<std::string> TextProcessor::processText(std::string textName){
    lowerCase(textName); // Padroniza text em minúsculo
    std::string filepath; // String com filepath de text
    if(textsFilepath.find(textName) != textsFilepath.end()) filepath = textsFilepath[textName]; // filepath recebe o filepath de text
    else return {}; // Se não existir text em textsFilepath, retorna um vetor nulo

    if(!this->loadText(filepath)) return {}; // Retorna um vetor nulo, caso não conseguir abrir o texto
    if(!this->loadStopWords("../stopWords.txt")) return {}; // Retorna um vetor nulo, caso não consefuir abrir o texto

    return this->breakWords(this->text); // Retorna o vetor de palavras separadas retornado por breakWords
}