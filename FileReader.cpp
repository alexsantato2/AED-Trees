#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::vector<User> readCSV(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line, word;

    // Verificar se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return users;
    }

    // Ignorar a primeira linha (cabeçalho)
    std::getline(file, line);

    // Ler o arquivo linha por linha
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        User user;

        // Ler e atribuir ID (inteiro)
        std::getline(ss, word, ',');
        user.id = std::stoi(word);

        // Ler e atribuir Nome (string)
        std::getline(ss, word, ',');
        user.name = word;

        // Ler e atribuir Data de Nascimento (data tm da lib <ctime>)
        std::getline(ss, word, ',');
        user.birthday = word;

        users.push_back(user);
    }

    // Fechar o arquivo
    file.close();
    return users;
}

std::vector<User> getUsers() {
    std::string filename = "users.csv";

    // Ler os dados do arquivo CSV e criar um vetor "users". Ao final do processamento, cada usuário estará em "users".
    std::vector<User> users = readCSV(filename);

    // Aqui você pode adicionar a lógica para inserir os usuários nas árvores BST e AVL

    return users;
}
