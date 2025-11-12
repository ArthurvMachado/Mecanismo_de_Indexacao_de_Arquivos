#pragma once
#include <string>

class QueryProcessor{
    public:
        QueryProcessor(); // Construtor
        ~QueryProcessor(); // Destrutor

        std::string* buscar(std::string consulta);
};