#include <iostream>
#include <iomanip>
#include <climits>
#include "AVL.h"

using namespace std;

// Construtor
template <typename TreeEntry>
AVL<TreeEntry>::AVL() {
// pre: Nenhuma
// pos: A AVL eh criada vazia (sem elementos)
  root = NULL;
}

// Finalizador
template <typename TreeEntry>
AVL<TreeEntry>::~AVL() {
// pre: Nenhuma
// pos: A AVL eh finalizada deixando de ocupar
//      espaco em memoria e seus nos deletados
  clear();
}

// Status
template <typename TreeEntry>
bool AVL<TreeEntry>::empty() {
// pre: Nenhuma
// pos: Retorna true se a arvore esta vazia;
//      false caso contrario
  return (root == NULL);
}

// Verificar se a arvore esta cheia
template <typename TreeEntry>
bool AVL<TreeEntry>::full() {
// pre: nenhuma
// pos: retorna true se a arvore binária esta cheia;
//      false caso contrario
  return false;
}

// Imprimir a arvore
template <typename TreeEntry>
void AVL<TreeEntry>::print() {
// pre: nenhuma
// pos: imprime a arvore na ordem DRE
  print(root, 0);
}

template <typename TreeEntry>
void AVL<TreeEntry>::print(TreePointer &t, int s) {
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
void AVL<TreeEntry>::clear() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao descartados
//      e ela se torna uma arvore vazia
  clear(root);
  root = NULL;
}

template <typename TreeEntry>
void AVL<TreeEntry>::clear(TreePointer &t) {
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
void AVL<TreeEntry>::preOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso pre-ordem (RED)
  preOrder(root);
}

template <typename TreeEntry>
void AVL<TreeEntry>::preOrder(TreePointer &t) {
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
void AVL<TreeEntry>::inOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso em-ordem (ERD)
  inOrder(root);
}

template <typename TreeEntry>
void AVL<TreeEntry>::inOrder(TreePointer &t) {
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
void AVL<TreeEntry>::postOrder() {
// pre: Nenhuma
// pos: Todos os itens da arvore sao percorridos
//      pelo percurso pós-ordem (EDR)
  postOrder(root);
}

template <typename TreeEntry>
void AVL<TreeEntry>::postOrder(TreePointer &t) {
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
int AVL<TreeEntry>::nodes() {
// pre: Nenhuma
// pos: Retorna o numero de nos na arvore
  return nodes(root);
}

template <typename TreeEntry>
int AVL<TreeEntry>::nodes(TreePointer &t) {
// pre: Nenhuma
// pos: Retorna o numero de nos na arvore
  if(t == NULL)
    return 0;

  return 1 + nodes(t->leftNode) + nodes(t->rightNode);
}

// Numero de folhas
template <typename TreeEntry>
int AVL<TreeEntry>::leaves() {
// pre: Nenhuma
// pos: Retorna o numero de folhas na arvore
  return leaves(root);
}

template <typename TreeEntry>
int AVL<TreeEntry>::leaves(TreePointer &t) {
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
int AVL<TreeEntry>::height() {
// pre: Nenhuma
// pos: Retorna a altura da arvore
  return height(root);
}

template <typename TreeEntry>
int AVL<TreeEntry>::height(TreePointer &t) {
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
template <typename TreeEntry>
void AVL<TreeEntry>::insert(TreeEntry x) {
// pre: Nenhuma
// pos: O elemento x eh inserido na arvore
  bool h = false;
  insert(x, root, h);
}

template <typename TreeEntry>
void AVL<TreeEntry>::insert(TreeEntry x, TreePointer &pA, bool &h) {
// pre: Nenhuma
// pos: O elemento x eh inserido na arvore
  TreePointer pB, pC;

  if(pA == NULL) {  // inserir
    pA = new TreeNode;
    h = true;
    pA -> entry = x;
    pA->leftNode = pA->rightNode = NULL;
    pA->bal = 0;
  } else {
    if(x < pA->entry) {
      insert(x, pA->leftNode, h);
      if(h) {                                         // subarvore esquerda cresceu
        switch(pA->bal) {
          case -1: pA->bal = 0; h = false; break;
          case  0: pA->bal = +1;           break;
          case +1: pB = pA->leftNode;
                   if(pB->bal == +1) {                // LL
                     pA->leftNode = pB->leftNode;
                     pB->rightNode = pA;
                     pA->bal = 0;
                     pA = pB;
                   } else {                           // LR
                     pC = pB->rightNode;
                     pB->rightNode = pC->leftNode;
                     pC->leftNode = pB;
                     pA->leftNode = pC->rightNode;
                     pC->rightNode = pA;
                     if(pC->bal == +1) pA->bal = -1; else pA->bal = 0;
                     if(pC->bal == -1) pB->bal = +1; else pB->bal = 0;
                     pA = pC;
                   }
                   pA->bal = 0;
                   h = false;
        }
      }
    } else {
      insert(x, pA->rightNode, h);
      if(h) {                                         // subarvore direita cresceu
        switch(pA->bal) {
          case +1: pA->bal = 0; h = false; break;
          case  0: pA->bal = -1;           break;
          case -1: pB = pA->rightNode;
                   if(pB->bal == -1) {                // RR
                     pA->rightNode = pB->leftNode;
                     pB->leftNode = pA;
                     pA->bal = 0;
                     pA = pB;
                   } else {                           // RL
                     pC = pB->leftNode;
                     pB->leftNode = pC->rightNode;
                     pC->rightNode = pB;
                     pA->rightNode = pC->leftNode;
                     pC->leftNode = pA;
                     if(pC->bal == -1) pA->bal = +1; else pA->bal = 0;
                     if(pC->bal == +1) pB->bal = -1; else pB->bal = 0;
                     pA = pC;
                   }
                   pA->bal = 0;
                   h = false;
        }
      }
    }
  }
}

// Remoção
template <typename TreeEntry>
bool AVL<TreeEntry>::remove(TreeEntry x) {
// pre: Nenhuma
// pos: Retorna true se o elemento x foi encontrado
//      e removido da arvore; false, caso contrario
  bool h = false;
  return remove(x, root, h);
}

template <typename TreeEntry>
bool AVL<TreeEntry>::remove(TreeEntry x, TreePointer &p, bool &h) {
// pre: Nenhuma
// pos: Retorna true se o elemento x foi encontrado
//      e removido da arvore; false, caso contrario
  TreePointer q;
  bool removed;

  if(p == NULL)           // x não encontrado
    return false;

  if(x < p->entry) { 
    removed = remove(x,p->leftNode,h);
    if(h)
      balanceL(p,h);
    return removed;

  } else if(x > p->entry) { 
    removed = remove(x,p->rightNode,h);
    if(h)
      balanceR(p,h);
    return removed;

  } else {                // remover p->
    q = p;
    if(q->rightNode == NULL) { 
      p = q->leftNode;
      h = true;
    } else if(q->leftNode == NULL) { 
      p = q->rightNode;
      h = true;
    } else { 
      removeMin(q,q->rightNode,h);
      if(h)
        balanceR(p,h);
    }
    
    delete q;
    return true;            // x removido
  }
}

template <typename TreeEntry>
void AVL<TreeEntry>::removeMin(TreePointer &q, TreePointer &r, bool &h) {
  if(r->leftNode != NULL) {
    removeMin(q, r->leftNode, h);
    if(h)
      balanceL(r,h);
  } else { 
    q->entry = r->entry;
    q = r;
    r = r->rightNode;
    h = true;
  }
}

template <typename TreeEntry>
void AVL<TreeEntry>::balanceL(TreePointer &pA, bool &h) { 
  // subarvore esquerda encolheu
  TreePointer pB, pC;
  int balB, balC;
  switch(pA->bal) { 
    case +1: pA->bal = 0;             break;
    case  0: pA->bal = -1; h = false; break;
    case -1:
      pB = pA->rightNode; 
      balB = pB->bal;
      if(balB <= 0) {                         // RR
        pA->rightNode = pB->leftNode;
        pB->leftNode = pA;
        if(balB == 0) { 
          pA->bal = -1; 
          pB->bal = +1; 
          h = false; 
        } else { 
          pA->bal = 0; 
          pB->bal = 0; 
        }
        pA = pB;
      } else {                                // RL
        pC = pB->leftNode; 
        balC = pC->bal;
        pB->leftNode = pC->rightNode;
        pC->rightNode = pB;
        pA->rightNode = pC->leftNode;
        pC->leftNode = pA;
        if(balC == -1) pA->bal = +1; else pA->bal = 0;
        if(balC == +1) pB->bal = -1; else pB->bal = 0;
        pA = pC; 
        pC->bal = 0;
      }
  }
}

template <typename TreeEntry>
void AVL<TreeEntry>::balanceR(TreePointer &pA, bool &h) { 
  // subarvore direita encolheu
  TreePointer pB, pC;
  int balB, balC;
  switch(pA->bal) { 
    case -1: pA->bal = 0;             break;
    case  0: pA->bal = +1; h = false; break;
    case +1:
      pB = pA->leftNode; 
      balB = pB->bal;
      if(balB >= 0) {                         // LL
        pA->leftNode = pB->rightNode;
        pB->rightNode = pA;
        if(balB == 0) { 
          pA->bal = +1; 
          pB->bal = -1; 
          h = false; 
        } else { 
          pA->bal = 0; 
          pB->bal = 0; 
        }
        pA = pB;
      } else {                                // LR
        pC = pB->rightNode; 
        balC = pC->bal;
        pB->rightNode = pC->leftNode;
        pC->leftNode = pB;
        pA->leftNode = pC->rightNode;
        pC->rightNode = pA;
        if(balC == +1) pA->bal = -1; else pA->bal = 0;
        if(balC == -1) pB->bal= +1 ; else pB->bal = 0;
        pA = pC; 
        pC->bal = 0;
      }
  }
}

// Busca
template <typename TreeEntry>
bool AVL<TreeEntry>::search(TreeEntry x) {
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
