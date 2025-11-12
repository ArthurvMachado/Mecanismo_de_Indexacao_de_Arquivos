#pragma once
#include <string>

class queryProcessor{
    public:
        queryProcessor(); // Construtor
        ~queryProcessor(); // Destrutor

        std::string* buscar(std::string consulta);
};