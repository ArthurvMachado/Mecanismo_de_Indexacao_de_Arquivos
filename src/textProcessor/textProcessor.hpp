#pragma once
#include <string>
#include <vector>

class textProcessor{
    public:
        textProcessor(); // Construtor
        ~textProcessor(); // Destrutor
        
        std::vector<std::string> processar(std::string texto);
};