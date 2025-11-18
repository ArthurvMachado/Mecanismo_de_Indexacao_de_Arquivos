#pragma once
#include <string>
#include "../index/index.hpp"

class Serializer{
    public:
        Serializer(); // Construtor
        ~Serializer(); // Destrutor

        void save(Index index, std::string arquivo);
        Index load(std::string arquivo);
};
