#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>
#include <ctime>

// Estrutura para armazenar os dados do usuário
struct User {
    int id;
    std::string name;
    std::tm birthday;
};

// Declaração das funções para ler o arquivo CSV e obter os usuários, alem de sobrecarga de operador

std::ostream& operator<<(std::ostream& os, const User& user);
std::tm stringToDate(const std::string& date);
std::vector<User> readCSV(const std::string& filename);
std::vector<User> getUsers();

#endif 