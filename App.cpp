#include <iostream>
#include <vector>
#include <string>
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
    tm time1 = a.birthday;
    tm time2 = b.birthday;

    // Converter tm para time_t
    time_t time1_t = mktime(&time1);
    time_t time2_t = mktime(&time2);

    // Comparar usando difftime
    return difftime(time1_t, time2_t) < 0;
  }
};

// Métodos auxiliares
void menu() {
  cout << "--| Menu Principal |--" << endl;
  cout << "1. Buscar uma tupla" << endl;
  cout << "2. Adicionar uma nova tupla" << endl;
  cout << "3. Remover uma tupla" << endl << endl;
  cout << "0. Encerrar programa" << endl << endl;
  cout << "> ";
}

void searchMenu() {
  cout << "--| Menu de Busca |--" << endl;
  cout << "a. Busca por ID" << endl;
  cout << "b. Busca por nome" << endl;
  cout << "c. Busca por data de nascimento" << endl << endl;
  cout << "q. Voltar para o menu anterior" << endl << endl;
  cout << "> ";
}

User newUser() {
  User user;

  cout << "| Adicionando usuario |" << endl;
  
  cout << "Digite o ID: ";
  cin >> user.id;

  cout << "Digite o nome: ";
  getline(cin, user.name);

  string dataNasc;
  cout << "Digite a data de nascimento: ";
  cin >> dataNasc;
  user.birthday = stringToDate(dataNasc);

  return user;
}

void searchById(AVL avl, ABB abb) {
  int id;
  cout << "Digite o ID: ";
  cin >> id;

  User user = new User(id, "", stringToDate("1500-01-01"));
  cout << boolalpha << "Encontrado AVL: " << avl.search(user);
  cout << boolalpha << "Encontrado ABB: " << abb.search(user);
}

void searchByName(AVL avl, ABB abb) {
  string name;
  cout << "Digite o nome (case sensitive): ";
  getline(cin, name);

  User user = new User(0, name, stringToDate("1500-01-01"));
  cout << boolalpha << "Encontrado AVL: " << avl.search(user);
  cout << boolalpha << "Encontrado ABB: " << abb.search(user);
}

void searchByBirthday(AVL avl, ABB abb) {
  string birthday;
  cout << "Digite a data de nascimento (YYYY-MM-DD): ";
  getline(cin, birthday);

  User user = new User(0, "", stringToDate(birthday));
  cout << boolalpha << "Encontrado AVL: " << avl.search(user);
  cout << boolalpha << "Encontrado ABB: " << abb.search(user);
}

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

  string opt;
  do {
    menu();
    cin >> opt;

    switch(opt) {
      case "1":
        do {
          searchMenu();
          cin >> opt;

          switch(opt) {
            case "a":
              searchById(AVLById, ABBById);
              break;

            case "b":
              searchByName(AVLById, ABBById);
              break;

            case "c":
              searchByBirthday(AVLById, ABBById);
              break;

            case "q":
              cout << "Voltando para o menu principal...";
              break;

            default:
              cout << "Comando não reconhecido!";
              break;
          }
        } while(opt != "q");
        break;
      
      case "2":
        User newUser = newUser();

        AVLById.insert(newUser);
        AVLByName.insert(newUser);
        AVLByBirthday.insert(newUser);
        ABBById.insert(newUser);
        ABBByName.insert(newUser);
        ABBByBirthday.insert(newUser);
        break;
      
      case "3":
        cout << "Remover" << endl;
        break;
      
      case "0":
        cout << "Encerrando..." << endl;
        break;
      
      default:
        cout << "Comando não reconhecido!" << endl;
        break;
    }
  } while(opt != 0);

  return 0;
}
