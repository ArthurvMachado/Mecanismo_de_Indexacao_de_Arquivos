#include "commandLineInterface.hpp"
#include "../textProcessor/textProcessor.hpp"
#include "../index/index.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]){
    if(argc < 2) {
        std::cerr << "Insira o nome de um texto" << std::endl;
        return 1;
    }
    
    // TextProcessor processor;
    // std::vector<std::string> txt = processor.processText(argv[1]);
    // if(txt.empty()) return 1;

    // for(const std::string& el : txt) std::cout << el << std::endl;

    Index index;
    index.test(argv[1]);
    index.test(argv[2]);

    return 0;
}