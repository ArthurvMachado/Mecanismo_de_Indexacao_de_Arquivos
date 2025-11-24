#pragma once
#include <string>
#include "../index/index.hpp"

class Serializer{
    public:
        Serializer(); // Construtor
        ~Serializer(); // Destrutor

        void save(Index index, std::string file); // persiste o Index parametrizado em um arquivo {file}.dat
        Index load(std::string file); // carrega o Index parametrizado de um arquivo {file}.dat
};
