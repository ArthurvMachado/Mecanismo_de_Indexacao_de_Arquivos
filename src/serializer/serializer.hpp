#pragma once
#include <string>
#include "../index/index.hpp"

class Serializer{
    public:
        Serializer(); // Construtor
        ~Serializer(); // Destrutor

        void salvar(Index index, std::string arquivo);
        Index carregar(std::string arquivo);
};
