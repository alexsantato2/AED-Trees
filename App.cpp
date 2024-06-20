// Trabalho 2 - Trees
// AED1 - Prof. José Augusto Baranauskas
// Alexandre Santato    | 14555162
// Leonardo Rizzo Costa | 14756204
#include <iostream>
#include "AVL.cpp"
#include "ABB.cpp"

using namespace std;

int main() {
    AVL<int> tree1;
    ABB<int> tree2;

    cout << "TESTANDO AVL: " << endl;
    // Inserção inicial
    cout << "Inserindo valores iniciais: 10, 20, 30, 40, 50, 25, 10" << endl;
    tree1.insert(10);
    tree1.insert(20);
    tree1.insert(30);
    tree1.insert(40);
    tree1.insert(50);
    tree1.insert(25);
    tree1.insert(10);
    tree1.print();
    cout << endl;

    // Busca
    cout << "Buscando valores 30 e 60:" << endl;
    cout << "30 encontrado: " << tree1.search(30) << endl;
    cout << "60 encontrado: " << tree1.search(60) << endl;

    // Remoção e novas inserções
    cout << "Removendo o valor 30 e inserindo 60 e 70:" << endl;
    tree1.remove(30);
    tree1.insert(60);
    tree1.insert(70);
    tree1.print();
    cout << endl;

    // Mais inserções para testar o balanceamento
    cout << "Inserindo mais valores: 15, 5, 35, 45" << endl;
    tree1.insert(15);
    tree1.insert(5);
    tree1.insert(35);
    tree1.insert(45);
    tree1.print();
    cout << endl;

    // Verificando altura da árvore
    cout << "Altura da árvore: " << tree1.height() << endl;

    // Verificando número de nós e folhas
    cout << "Número de nós: " << tree1.nodes() << endl;
    cout << "Número de folhas: " << tree1.leaves() << endl;

    // Testando mais remoções
    cout << "Removendo valores 10 e 25:" << endl;
    tree1.remove(10);
    tree1.remove(25);
    tree1.print();
    cout << endl;

    // Busca após remoções
    cout << "Buscando valores 10 e 25 após remoção:" << endl;
    cout << "10 encontrado: " << tree1.search(10) << endl;
    cout << "25 encontrado: " << tree1.search(25) << endl;




    cout << endl << endl << endl << endl << endl << endl << endl;



    cout << "TESTANDO ABB: " << endl;
    // Inserção inicial
    cout << "Inserindo valores iniciais: 10, 20, 30, 40, 50, 25, 10" << endl;
    tree2.insert(10);
    tree2.insert(20);
    tree2.insert(30);
    tree2.insert(40);
    tree2.insert(50);
    tree2.insert(25);
    tree2.insert(10);
    tree2.print();
    cout << endl;

    // Busca
    cout << "Buscando valores 30 e 60:" << endl;
    cout << "30 encontrado: " << tree2.search(30) << endl;
    cout << "60 encontrado: " << tree2.search(60) << endl;

    // Remoção e novas inserções
    cout << "Removendo o valor 30 e inserindo 60 e 70:" << endl;
    tree2.remove(30);
    tree2.insert(60);
    tree2.insert(70);
    tree2.print();
    cout << endl;

    // Mais inserções para testar o balanceamento
    cout << "Inserindo mais valores: 15, 5, 35, 45" << endl;
    tree2.insert(15);
    tree2.insert(5);
    tree2.insert(35);
    tree2.insert(45);
    tree2.print();
    cout << endl;

    // Verificando altura da árvore
    cout << "Altura da árvore: " << tree2.height() << endl;

    // Verificando número de nós e folhas
    cout << "Número de nós: " << tree2.nodes() << endl;
    cout << "Número de folhas: " << tree2.leaves() << endl;

    // Testando mais remoções
    cout << "Removendo valores 10 e 25:" << endl;
    tree2.remove(10);
    tree2.remove(25);
    tree2.print();
    cout << endl;

    // Busca após remoções
    cout << "Buscando valores 10 e 25 após remoção:" << endl;
    cout << "10 encontrado: " << tree2.search(10) << endl;
    cout << "25 encontrado: " << tree2.search(25) << endl;

    return 0;
}
