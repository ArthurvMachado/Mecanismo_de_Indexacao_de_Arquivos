# FERREIRINHA'S INDEX

## Trabalho Prático de Algoritmos e Estrutura de Dados II - BCC4001

**Autores:** Arthur Vinicius Machado & Mateus Batichotti Silva

**Professor:** Juliano Henrique Foleis  

**Instituição:** UTFPR - CM

---

Este projeto implementa um mecanismo de busca para documentos de texto via linha de comando, simulando funcionalidades de sistemas de indexação e recuperação de informações.

![Capa do projeto](ferreirinhas_logo.png)

### Funcionalidades

- **Indexação de arquivos:** Processa e armazena índices invertidos para busca eficiente.
- **Processamento de texto:** Normalização, remoção de stopwords e tokenização.
- **Consultas:** Permite buscas por termos, retornando documentos relevantes.
- **Serialização:** Salva e carrega índices para persistência.
- **Interface de linha de comando:** Interação simples para indexação e consulta.

### Estrutura do Projeto

```plaintext
src/
├── main.cpp
├── Makefile
├── ferreirinha
├── commandLineInterface/
│   ├── commandLineInterface.cpp
│   └── commandLineInterface.hpp
├── index/
│   ├── index.cpp
│   └── index.hpp
├── indexer/
│   ├── indexer.cpp
│   └── indexer.hpp
├── queryProcessor/
│   ├── queryProcessor.cpp
│   └── queryProcessor.hpp
├── serializer/
│   ├── serializer.cpp
│   └── serializer.hpp
└── textProcessor/
    ├── textProcessor.cpp
    └── textProcessor.hpp
```

### Como Compilar

```sh
cd src
make
```

### Como Executar

```sh
./ferreirinha
```

A interface permite comandos para indexar arquivos e realizar buscas.

### Principais Módulos

- **commandLineInterface:** Gerencia entrada e saída do usuário.
- **index:** Estruturas e operações do índice invertido.
- **indexer:** Indexação dos documentos.
- **queryProcessor:** Processamento das consultas.
- **serializer:** Persistência dos dados.
- **textProcessor:** Limpeza e preparação dos textos.

### Requisitos

- Compilador C++ compatível com C++11 ou superior.

### Referências

- Algoritmos de Estruturas de Dados II
- UTFPR - BCC

---

**Observação:** Para detalhes sobre a arquitetura e algoritmos utilizados, consulte a documentação interna dos arquivos fonte.
