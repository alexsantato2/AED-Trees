#include <iostream>
#include <vector>
#include "AVL.cpp"
#include "ABB.cpp"
#include "FileReader.h"

using namespace std;

// Definição dos comparadores
struct CompareById {
  bool operator()(const User &a, const User &b) const {
    return a.id < b.id;
  }
};

struct CompareByName {
  bool operator()(const User &a, const User &b) const {
    return a.name < b.name;
  }
};

struct CompareByBirthday {
  bool operator()(const User &a, const User &b) const {
    // Copiar e modificar as estruturas tm para evitar const_cast
    std::tm time1 = a.birthday;
    std::tm time2 = b.birthday;

    // Converter tm para time_t
    time_t time1_t = mktime(&time1);
    time_t time2_t = mktime(&time2);

    // Comparar usando difftime
    return difftime(time1_t, time2_t) < 0;
  }
};

int main() {
    // Pega os usuarios do csv
    vector<User> users = getUsers(); 

    // Criacao das AVLs
    AVL<User, CompareById> AVLById;
    AVL<User, CompareByName> AVLByName;
    AVL<User, CompareByBirthday> AVLByBirthday;

    // Criacao da ABBs
    ABB<User, CompareById> ABBById;
    ABB<User, CompareByName> ABBByName;
    ABB<User, CompareByBirthday> ABBByBirthday;

    // Insercao dos elementos users
    for (const auto& user : users) {
        AVLById.insert(user);
        AVLByName.insert(user);
        AVLByBirthday.insert(user);
        ABBById.insert(user);
        ABBByName.insert(user);
        ABBByBirthday.insert(user);
    }

    return 0;
}