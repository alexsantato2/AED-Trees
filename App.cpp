#include <iostream>
#include <vector>
#include "AVL.h"
#include "ABB.h"
#include "FileReader.h" // Se getUsers() estiver definido em FileReader.h

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
    return a.birthday < b.birthday;
  }
};

int main() {
    vector<User> users = getUsers(); 

    AVL<User, CompareById> AVLById;
    AVL<User, CompareByName> AVLByName;
    AVL<User, CompareByBirthday> AVLByBirthday;

    ABB<User, CompareById> ABBById;
    ABB<User, CompareByName> ABBByName;
    ABB<User, CompareByBirthday> ABBByBirthday;


    for (const auto& user : users) {
        AVLById.insert(user);
        AVLByName.insert(user);
        AVLByBirthday.insert(user);
        ABBById.insert(user);
        ABBByName.insert(user);
        ABBByBirthday.insert(user);
    }

    AVLById.print(); 

    return 0;
}
