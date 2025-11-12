#pragma once

#include <string>

int adicionar(std::string palavra, std::string nome_arquivo);

int* getArquivosPorPalavra(std::string palavra); // retorna conjunto de ids

std::string getNomeArquivoPorId(int id);
