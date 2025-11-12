#pragma once
#include <string>

class Serializer{
    public:
        Serializer(); // Construtor
        ~Serializer(); // Destrutor

        void salvar(int index, std::string arquivo);
        int carregar(std::string arquivo);
};
