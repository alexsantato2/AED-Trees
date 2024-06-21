#include <iostream>
#include <iomanip>
#include <climits>

using namespace std;

#ifndef ABB_CPP
#define ABB_CPP

template <typename TreeEntry, typename Compare = less<TreeEntry>>
class ABB {
  public:
    ABB();
    ~ABB();
    bool empty();
    bool full();
    void print();
    void clear();
    void preOrder();
    void inOrder();
    void postOrder();
    int nodes();
    int leaves();
    int height();
    void insert(TreeEntry x);
    bool remove(TreeEntry x);
    bool search(TreeEntry x);

  private:
    struct TreeNode;
    typedef TreeNode (* TreePointer);

    struct TreeNode {
      TreeEntry entry;
      TreePointer leftNode, rightNode;
    };
    TreePointer root;
    Compare compare;

    void print(TreePointer &t, int s);
    void clear(TreePointer &t);
    void preOrder(TreePointer &t);
    void inOrder(TreePointer &t);
    void postOrder(TreePointer &t);
    int nodes(TreePointer &t);
    int leaves(TreePointer &t);
    int height(TreePointer &t);
    bool remove(TreeEntry x, TreePointer &t);
    void removeMin(TreePointer &q, TreePointer &r);
};

#endif

// Construtor
template <typename TreeEntry, typename Compare>
ABB<TreeEntry, Compare>::ABB() {
// pre: Nenhuma
// pos: A ABB eh criada vazia (sem elementos)
  root = NULL;
}

// Finalizador
template <typename TreeEntry, typename Compare>
ABB<TreeEntry, Compare>::~ABB() {
// pre: Nenhuma
// pos: A ABB eh finalizada deixando de ocupar
//      espaco em memoria e seus nos deletados
  clear();
}

// Status
template <typename TreeEntry, typename Compare>
bool ABB<TreeEntry, Compare>::empty() {
// pre: Nenhuma
// pos: Retorna true se a arvore esta vazia;
//      false caso contrario
  return (root == NULL);
}

// Verificar se a arvore esta cheia
template <typename TreeEntry, typename Compare>
bool ABB<TreeEntry, Compare>::full() {
// pre: nenhuma
// pos: retorna true se a arvore binária esta cheia;
//      false caso contrario
  return false;
}

// Imprimir a arvore
template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::print() {
// pre: nenhuma
// pos: imprime a arvore na ordem DRE
  print(root, 0);
}

template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::print(TreePointer &t, int s) {
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
template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::clear() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao descartados
//      e ela se torna uma arvore vazia
  clear(root);
  root = NULL;
}

template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::clear(TreePointer &t) {
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
template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::preOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso pre-ordem (RED)
  preOrder(root);
}

template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::preOrder(TreePointer &t) {
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
template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::inOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso em-ordem (ERD)
  inOrder(root);
}

template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::inOrder(TreePointer &t) {
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
template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::postOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso pós-ordem (EDR)
  postOrder(root);
}

template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::postOrder(TreePointer &t) {
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
template <typename TreeEntry, typename Compare>
int ABB<TreeEntry, Compare>::nodes() {
// pre: Nenhuma
// pos: Retorna o numero de nos na arvore
  return nodes(root);
}

template <typename TreeEntry, typename Compare>
int ABB<TreeEntry, Compare>::nodes(TreePointer &t) {
// pre: Nenhuma
// pos: Retorna o numero de nos na arvore
  if(t == NULL)
    return 0;

  return 1 + nodes(t->leftNode) + nodes(t->rightNode);
}

// Numero de folhas
template <typename TreeEntry, typename Compare>
int ABB<TreeEntry, Compare>::leaves() {
// pre: Nenhuma
// pos: Retorna o numero de folhas na arvore
  return leaves(root);
}

template <typename TreeEntry, typename Compare>
int ABB<TreeEntry, Compare>::leaves(TreePointer &t) {
// pre: Nenhuma
// pos: Retorna o numero de folhas na arvore
  if(t == NULL)
   return 0;

  if(t->leftNode == NULL && t->rightNode == NULL)
    return 1;

  return leaves(t->leftNode) + leaves(t->rightNode);
}

// Altura
template <typename TreeEntry, typename Compare>
int ABB<TreeEntry, Compare>::height() {
// pre: Nenhuma
// pos: Retorna a altura da arvore
  return height(root);
}

template <typename TreeEntry, typename Compare>
int ABB<TreeEntry, Compare>::height(TreePointer &t) {
// pre: Nenhuma
// pos: Retorna a altura da arvore
  if(t == NULL)
    return -1;

  int L, R;
  L = height(t->leftNode);
  R = height(t->rightNode);
  return (L>R) ? L+1 : R+1;
}

// Inserção
template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::insert(TreeEntry x) {
// pre: Nenhuma
// pos: O elemento x eh inserido na arvore
  TreePointer p = NULL, q = root, r;

  while(q != NULL) {
    p = q;

    if(compare(x, q->entry))
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
    if(compare(x, p->entry))
      p->leftNode = r;
    else
      p->rightNode = r;
}

// Remoção
template <typename TreeEntry, typename Compare>
bool ABB<TreeEntry, Compare>::remove(TreeEntry x) {
// pre: Nenhuma
// pos: Retorna true se o elemento x foi encontrado
//      e removido da arvore; false, caso contrario
  return remove(x, root);
}

template <typename TreeEntry, typename Compare>
bool ABB<TreeEntry, Compare>::remove(TreeEntry x, TreePointer &t) {
// pre: Nenhuma
// pos: Retorna true se o elemento x foi encontrado
//      e removido da arvore; false, caso contrario
  if(t == NULL)
    return false; // elemento inexistente

  if(compare(x, t->entry))
    return remove(x, t->leftNode);

  if(compare(t->entry, x))
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

template <typename TreeEntry, typename Compare>
void ABB<TreeEntry, Compare>::removeMin(TreePointer &q, TreePointer &r) {
  if(r->leftNode != NULL)
    removeMin(q, r->leftNode);
  else {
    q->entry = r->entry;
    q = r;
    r = r->rightNode;
  }
}

// Busca
template <typename TreeEntry, typename Compare>
bool ABB<TreeEntry, Compare>::search(TreeEntry x) {
// pre: Nenhuma
// pos: Retorna true se x esta na arvore;
//      caso contrario, retorna false
  TreePointer t = root;

  while(t != NULL && t->entry != x) {
    if(compare(x, t->entry))
      t = t->leftNode;
    else
      t = t->rightNode;
  }

  return (t != NULL);
}