#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>
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
void clearInputBuffer() {
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menu() {
  cout << "--| Menu Principal |--" << endl;
  cout << "1. Buscar uma tupla" << endl;
  cout << "2. Adicionar uma nova tupla" << endl;
  cout << "3. Remover uma tupla" << endl;
  cout << "4. Extrair métricas" << endl << endl;
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

void removeMenu() {
  cout << "--| Menu de Remoção |--" << endl;
  cout << "Deseja remover por:" << endl;
  cout << "a. ID" << endl;
  cout << "b. Nome" << endl;
  cout << "c. Data de nascimento" << endl << endl;
  cout << "> ";
}

User getNewUser() {
  User user;

  cout << "| Adicionando usuário |" << endl;
  
  cout << "Digite o ID: ";
  cin >> user.id;

  cout << "Digite o nome (case sensitive): ";
  clearInputBuffer();
  getline(cin, user.name);

  string dataNasc;
  cout << "Digite a data de nascimento (AAAA-MM-DD): ";
  cin >> dataNasc;
  user.birthday = stringToDate(dataNasc);

  return user;
}

void searchById(AVL<User, CompareById> &avl, ABB<User, CompareById> &abb) {
  User user;
  cout << "Digite o ID: ";
  cin >> user.id;

  cout << boolalpha << "Encontrado AVL: " << avl.search(user) << endl;
  cout << boolalpha << "Encontrado ABB: " << abb.search(user) << endl;
}

void searchByName(AVL<User, CompareByName> &avl, ABB<User, CompareByName> &abb) {
  User user;
  cout << "Digite o nome (case sensitive): ";
  clearInputBuffer();
  getline(cin, user.name);

  cout << boolalpha << "Encontrado AVL: " << avl.search(user) << endl;
  cout << boolalpha << "Encontrado ABB: " << abb.search(user) << endl;
}

void searchByBirthday(AVL<User, CompareByBirthday> &avl, ABB<User, CompareByBirthday> &abb) {
  string birthday;
  cout << "Digite a data de nascimento (AAAA-MM-DD): ";
  clearInputBuffer();
  getline(cin, birthday);

  User user;
  user.birthday = stringToDate(birthday);
  cout << boolalpha << "Encontrado AVL: " << avl.search(user) << endl;
  cout << boolalpha << "Encontrado ABB: " << abb.search(user) << endl;
}

int main() {

  // Pega os usuários do csv
  vector<User> users = getUsers(); 

  // Criação das AVLs
  AVL<User, CompareById> AVLById;
  AVL<User, CompareByName> AVLByName;
  AVL<User, CompareByBirthday> AVLByBirthday;

  // Criação da ABBs
  ABB<User, CompareById> ABBById;
  ABB<User, CompareByName> ABBByName;
  ABB<User, CompareByBirthday> ABBByBirthday;

  // Inserção dos elementos users
  for (const auto& user : users) {
    AVLById.insert(user);
    AVLByName.insert(user);
    AVLByBirthday.insert(user);
    ABBById.insert(user);
    ABBByName.insert(user);
    ABBByBirthday.insert(user);
  }

  // Inicio do programa (menu)
  string opt;
  do {
    menu();
    cin >> opt;

    if(opt == "1") {
      do {
        searchMenu();
        cin >> opt;

        if(opt == "a")
          searchById(AVLById, ABBById);
        else if(opt == "b")
          searchByName(AVLByName, ABBByName);
        else if(opt == "c")
          searchByBirthday(AVLByBirthday, ABBByBirthday);
        else if(opt == "q")
          cout << "Voltando para o menu principal..." << endl;
        else
          cout << "Comando não reconhecido!" << endl;
      } while(opt != "q");
    }
    else if(opt == "2") {
      User newUser = getNewUser();

      AVLById.insert(newUser);
      AVLByName.insert(newUser);
      AVLByBirthday.insert(newUser);
      ABBById.insert(newUser);
      ABBByName.insert(newUser);
      ABBByBirthday.insert(newUser);
    }
    else if(opt == "3") {
      removeMenu();
      cin >> opt;

      User user;
      if(opt == "a") {
        cout << "Digite o ID: ";
        cin >> user.id;

        cout << boolalpha << "Removido da AVL (ID): " << AVLById.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (ID): " << ABBById.remove(user) << endl;
        cout << boolalpha << "Removido da AVL (Nome): " << AVLByName.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (Nome): " << ABBByName.remove(user) << endl;
        cout << boolalpha << "Removido da AVL (Data Nascimento): " << AVLByBirthday.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (Data Nascimento): " << ABBByBirthday.remove(user) << endl;
      }
      else if(opt == "b") {
        cout << "Digite o nome (case sensitive): ";
        clearInputBuffer();
        getline(cin, user.name);

        cout << boolalpha << "Removido da AVL (Nome): " << AVLByName.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (Nome): " << ABBByName.remove(user) << endl;
        cout << boolalpha << "Removido da AVL (ID): " << AVLById.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (ID): " << ABBById.remove(user) << endl;
        cout << boolalpha << "Removido da AVL (Data Nascimento): " << AVLByBirthday.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (Data Nascimento): " << ABBByBirthday.remove(user) << endl;
      }
      else if (opt == "c") {
        string dataNasc;
        cout << "Digite a data de nascimento (AAAA-MM-DD): ";
        clearInputBuffer();
        getline(cin, dataNasc);
        user.birthday = stringToDate(dataNasc);

        cout << boolalpha << "Removido da AVL (Data Nascimento): " << AVLByBirthday.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (Data Nascimento): " << ABBByBirthday.remove(user) << endl;
        cout << boolalpha << "Removido da AVL (ID): " << AVLById.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (ID): " << ABBById.remove(user) << endl;
        cout << boolalpha << "Removido da AVL (Nome): " << AVLByName.remove(user) << endl;
        cout << boolalpha << "Removido da ABB (Nome): " << ABBByName.remove(user) << endl;
      }
    }
    else if(opt == "4") {
      cout << "--| Métricas |--" << endl;

      int numUsers = AVLById.nodes();
      cout << "A) Num. de usuários" << endl;
      cout << "  AVL (ID): " << numUsers << endl;
      cout << "  ABB (ID): " << numUsers << endl;
      cout << "  AVL (Nome): " << numUsers << endl;
      cout << "  ABB (Nome): " << numUsers << endl;
      cout << "  AVL (Data Nascimento): " << numUsers << endl;
      cout << "  ABB (Data Nascimento): " << numUsers << endl << endl;

      int hMinArvore = ceil(log2(numUsers + 1) - 1);
      cout << "B) Tamanho da árvore mínima" << endl;
      cout << "  AVL (ID): " << hMinArvore << endl;
      cout << "  ABB (ID): " << hMinArvore << endl;
      cout << "  AVL (Nome): " << hMinArvore << endl;
      cout << "  ABB (Nome): " << hMinArvore << endl;
      cout << "  AVL (Data Nascimento): " << hMinArvore << endl;
      cout << "  ABB (Data Nascimento): " << hMinArvore << endl << endl;

      cout << "C) Tamanho da AVL" << endl;
      cout << "  AVL (ID): " << AVLById.height() << endl;
      cout << "  AVL (Nome): " << AVLByName.height() << endl;
      cout << "  AVL (Data Nascimento): " << AVLByBirthday.height() << endl << endl;

      cout << "D) Folhas na AVL" << endl;
      cout << "  AVL (ID): " << AVLById.leaves() << endl;
      cout << "  AVL (Nome): " << AVLByName.leaves() << endl;
      cout << "  AVL (Data Nascimento): " << AVLByBirthday.leaves() << endl << endl;

      cout << "E) Tamanho da ABB" << endl;
      cout << "  ABB (ID): " << ABBById.height() << endl;
      cout << "  ABB (Nome): " << ABBByName.height() << endl;
      cout << "  ABB (Data Nascimento): " << ABBByBirthday.height() << endl << endl;

      cout << "F) Folhas na ABB" << endl;
      cout << "  ABB (ID): " << ABBById.leaves() << endl;
      cout << "  ABB (Nome): " << ABBByName.leaves() << endl;
      cout << "  ABB (Data Nascimento): " << ABBByBirthday.leaves() << endl << endl;

      cout << "G) Rotações na inserção da AVL" << endl;
      cout << "  AVL (ID): " << AVLById.rotations() << endl;
      cout << "  AVL (Nome): " << AVLByName.rotations() << endl;
      cout << "  AVL (Data Nascimento): " << AVLByBirthday.rotations() << endl << endl;

      cout << "H) Comparações na inserção ABB" << endl;
      cout << "  ABB (ID): " << ABBById.comparisons() << endl;
      cout << "  ABB (Nome): " << ABBByName.comparisons() << endl;
      cout << "  ABB (Data Nascimento): " << ABBByBirthday.comparisons() << endl << endl;

      cout << "I) Comparações na inserção AVL" << endl;
      cout << "  AVL (ID): " << AVLById.comparisons() << endl;
      cout << "  AVL (Nome): " << AVLByName.comparisons() << endl;
      cout << "  AVL (Data Nascimento): " << AVLByBirthday.comparisons() << endl << endl;
    }
    else if(opt == "0") {
      cout << "Encerrando..." << endl;
    }
    else {
      cout << "Comando não reconhecido!" << endl;
    }
  } while(opt != "0");

  return 0;
}
