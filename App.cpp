// Trabalho 2 - Tree
// AED1 - Prof. José Augusto Baranauskas
// Alexandre Santato    | 14555162
// Leonardo Rizzo Costa | 14756204
#include <iostream>
#include "ABBTree.cpp"
using namespace std;

// Programa principal
int main() {

  ABBTree<int> tree;

  tree.insert(1);
  tree.insert(2);
  tree.insert(3);

  cout << tree.search(3) << endl;
  cout << tree.search(5) << endl;
  
  tree.remove(3);
  tree.insert(5);

  cout << tree.search(3) << endl;
  cout << tree.search(5) << endl;

  tree.remove(1);
  cout << tree.min() << endl;

  return 0;
}
