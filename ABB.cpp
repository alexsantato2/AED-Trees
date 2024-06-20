#include <iostream>
#include <climits>
#include "ABB.h"
using namespace std;

// Construtor
template <typename TreeEntry>
ABB<TreeEntry>::ABB() {
// pre: Nenhuma
// pos: A ABB eh criada vazia (sem elementos)
  root = NULL;
}

// Finalizador
template <typename TreeEntry>
ABB<TreeEntry>::~ABB() {
// pre: Nenhuma
// pos: A ABB eh finalizada deixando de ocupar
//      espaco em memoria e seus nos deletados
  clear();
}

// Status
template <typename TreeEntry>
bool ABB<TreeEntry>::empty() {
// pre: Nenhuma
// pos: Retorna true se a arvore esta vazia;
//      false caso contrario
  return (root == NULL);
}

// Verificar se a arvore esta cheia
template <typename TreeEntry>
bool ABB<TreeEntry>::full() {
// pre: nenhuma
// pos: retorna true se a arvore binária esta cheia;
//      false caso contrario
  return false;
}

// Imprimir a arvore
template <typename TreeEntry>
void ABB<TreeEntry>::print() {
// pre: nenhuma
// pos: imprime a arvore na ordem DRE
  print(root, 0);
}

template <typename TreeEntry>
void ABB<TreeEntry>::print(TreePointer &t, int s) {
  // pre: nenhuma
  // pos: imprime a arvore na ordem DRE
  if(t != NULL) {
    print(t->rightNode, s+3);
    for(int i = 1; i < s; i++) {
      cout << " ";
    }
    cout << setw(6) << t->entry << endl;
    print(t->leftNode, s+3);
  }
}

// Clear
template <typename TreeEntry>
void ABB<TreeEntry>::clear() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao descartados
//      e ela se torna uma arvore vazia
  clear(root);
  root = NULL;
}

template <typename TreeEntry>
void ABB<TreeEntry>::clear(TreePointer &t) {
// pre: Nenhuma
// pos: Todos os itens da arvore sao descartados
//      e ela se torna uma arvore vazia
  if(t != NULL) {
    clear(t->leftNode);
    clear(t->rightNode);
    delete t;
  }
}

// Percursos
// Pré-Ordem
template <typename TreeEntry>
void ABB<TreeEntry>::preOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso pre-ordem (RED)
  preOrder(root);
}

template <typename TreeEntry>
void ABB<TreeEntry>::preOrder(TreePointer &t) {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso pre-ordem (RED)
  if(t != NULL) {
    cout << t->entry << " ";
    preOrder(t->leftNode);
    preOrder(t->rightNode);
  }
}

// Em-Ordem
template <typename TreeEntry>
void ABB<TreeEntry>::inOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso em-ordem (ERD)
  inOrder(root);
}

template <typename TreeEntry>
void ABB<TreeEntry>::inOrder(TreePointer &t) {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso em-ordem (ERD)
  if(t != NULL) {
    inOrder(t->leftNode);
    cout << t->entry << " ";
    inOrder(t->rightNode);
  }
}

// Pós-Ordem
template <typename TreeEntry>
void ABB<TreeEntry>::postOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso pós-ordem (EDR)
  postOrder(root);
}

template <typename TreeEntry>
void ABB<TreeEntry>::postOrder(TreePointer &t) {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso pós-ordem (EDR)
  if(t != NULL) {
    postOrder(t->leftNode);
    postOrder(t->rightNode);
    cout << t->entry << " ";
  }
}

// Número de Nós
template <typename TreeEntry>
int ABB<TreeEntry>::nodes() {
// pre: Nenhuma
// pos: Retorna o numero de nos na arvore
  return nodes(root);
}

template <typename TreeEntry>
int ABB<TreeEntry>::nodes(TreePointer &t) {
// pre: Nenhuma
// pos: Retorna o numero de nos na arvore
  if(t == NULL)
    return 0;

  return 1 + nodes(t->leftNode) + nodes(t->rightNode);
}

// Numero de folhas
template <typename TreeEntry>
int ABB<TreeEntry>::leaves() {
// pre: Nenhuma
// pos: Retorna o numero de folhas na arvore
  return leaves(root);
}

template <typename TreeEntry>
int ABB<TreeEntry>::leaves(TreePointer &t) {
// pre: Nenhuma
// pos: Retorna o numero de folhas na arvore
  if(t == NULL)
   return 0;

  if(t->leftNode == NULL && t->rightNode == NULL)
    return 1;

  return leaves(t->leftNode) + leaves(t->rightNode);
}

// Altura
template <typename TreeEntry>
int ABB<TreeEntry>::height() {
// pre: Nenhuma
// pos: Retorna a altura da arvore
  return height(root);
}

template <typename TreeEntry>
int ABB<TreeEntry>::height(TreePointer &t) {
// pre: Nenhuma
// pos: Retorna a altura da arvore
  if(t == NULL)
    return -1;

  int L, R;
  L = height(t->leftNode);
  R = height(t->rightNode);
  return (L>R) ? L+1 : R+1;
}

// Minimo e Maximo
template <typename TreeEntry>
TreeEntry ABB<TreeEntry>::min() {
// pre: Arvore nao esta vazia
// pos: Retorna NULL se a arvore esta vazia;
//      caso contrario, retorna o valor minimo
//      encontrado na arvore
  if(empty()) {
    cout << "Árvore vazia" << endl;
    return NULL;
  }

  TreePointer t = root;
  while(t->leftNode != NULL)
    t = t->leftNode;

  return t->entry;
}

template <typename TreeEntry>
TreeEntry ABB<TreeEntry>::max() {
// pre: Arvore nao esta vazia
// pos: Retorna NULL se a arvore esta vazia;
//      caso contrario, retorna o valor maximo
//      encontrado na arvore
  if(empty()) {
    cout << "Árvore vazia" << endl;
    return NULL;
  }

  TreePointer t = root;
  while(t->rightNode != NULL)
    t = t->rightNode;

  return t->entry;
}

// Inserção
template <typename TreeEntry>
void ABB<TreeEntry>::insert(TreeEntry x) {
// pre: Nenhuma
// pos: O elemento x eh inserido na arvore
  TreePointer p = NULL, q = root, r;

  while(q != NULL) {
    p = q;

    if(x < q->entry)
      q = q->leftNode;
    else
      q = q->rightNode;
  }

  r = new TreeNode;
  if(r == NULL) {
    cout << "Sem memória" << endl;
    abort();
  }

  r->entry = x;
  r->leftNode = NULL;
  r->rightNode = NULL;

  if(p == NULL)
    root = r;
  else
    if(x < p->entry)
      p->leftNode = r;
    else
      p->rightNode = r;
}

// Remoção
template <typename TreeEntry>
bool ABB<TreeEntry>::remove(TreeEntry x) {
// pre: Nenhuma
// pos: Retorna true se o elemento x foi encontrado
//      e removido da arvore; false, caso contrario
  return remove(x, root);
}

template <typename TreeEntry>
bool ABB<TreeEntry>::remove(TreeEntry x, TreePointer &t) {
// pre: Nenhuma
// pos: Retorna true se o elemento x foi encontrado
//      e removido da arvore; false, caso contrario
  if(t == NULL)
    return false; // elemento inexistente

  if(x < t->entry)
    return remove(x, t->leftNode);

  if(x > t->entry)
    return remove(x, t->rightNode);
  else {
    TreePointer q;
    q = t;

    if(q->leftNode == NULL)
      t = q->rightNode;   // Caso A
    else
      if(q->rightNode == NULL)
        t = q->leftNode;  // Caso B
      else
        removeMin(q, q->rightNode); // Caso C (C.1)

    delete q;
    return true;
  }
}

template <typename TreeEntry>
void ABB<TreeEntry>::removeMin(TreePointer &q, TreePointer &r) {
  if(r->leftNode != NULL)
    removeMin(q, r->leftNode);
  else {
    q->entry = r->entry;
    q = r;
    r = r->rightNode;
  }
}

// Busca
template <typename TreeEntry>
bool ABB<TreeEntry>::search(TreeEntry x) {
// pre: Nenhuma
// pos: Retorna true se x esta na arvore;
//      caso contrario, retorna false
  TreePointer t = root;

  while(t != NULL && t->entry != x) {
    if(x < t->entry)
      t = t->leftNode;
    else
      t = t->rightNode;
  }

  return (t != NULL);
}
