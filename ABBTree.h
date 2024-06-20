// ABBTree.h
// Declaração/interface para árvore binária de busca genérica
using namespace std;

#ifndef ABBTREE_H
#define ABBTREE_H

template <typename TreeEntry>
class ABBTree {
  public:
    ABBTree();
    ~ABBTree();
    bool empty();
    void clear();
    void preOrder();
    void inOrder();
    void postOrder();
    int nodes();
    int leaves();
    int height();
    TreeEntry min();
    TreeEntry max();
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
