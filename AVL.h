// AVL.h
// Declaração/interface para AVL genérica
using namespace std;

#ifndef AVL_H
#define AVL_H

template <typename TreeEntry>
class AVL {
  public:
    AVL();
    ~AVL();
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
      int bal;
    };
    TreePointer root;

    void print(TreePointer &t, int s);
    void clear(TreePointer &t);
    void preOrder(TreePointer &t);
    void inOrder(TreePointer &t);
    void postOrder(TreePointer &t);
    int nodes(TreePointer &t);
    int leaves(TreePointer &t);
    int height(TreePointer &t);
    void insert(TreeEntry x, TreePointer &pA, bool &h);
    bool remove(TreeEntry x, TreePointer &p, bool &h);
    void removeMin(TreePointer &q, TreePointer &r, bool &h);
    void balanceL(TreePointer &pA, bool &h);
    void balanceR(TreePointer &pA, bool &h);

};

#endif
