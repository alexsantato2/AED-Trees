#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

// Estrutura para armazenar os dados do usuário
struct User {
    int id;
    std::string name;
    std::string birthday;
};

// Declaração das funções para ler o arquivo CSV e obter os usuários
std::vector<User> readCSV(const std::string& filename);
std::vector<User> getUsers();

#endif 
