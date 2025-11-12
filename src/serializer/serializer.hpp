#pragma once
#include <string>

class serializer{
    public:
        serializer(); // Construtor
        ~serializer(); // Destrutor

        void salvar(int index, std::string arquivo);
        int carregar(std::string arquivo);
};
