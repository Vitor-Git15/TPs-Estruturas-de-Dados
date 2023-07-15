#ifndef TREE
#define TREE

#include "Email.hpp"

#include <string>

// definição da estrutura nó da árvore
struct node{

  Email email;
  int InBox;

  node* right;
  node* left;

  node(std::string &m, int ID, int IB, node* r, node* l){
    email.message = m;
    email.ID = ID;
    InBox = IB;
    right = r;
    left = l;
  }
  node(){
    email.message = "";
    email.ID = (-1);
    right = nullptr;
    left = nullptr;
  }
};

class BinaryTree{

  public:

    BinaryTree();
    ~BinaryTree();

    void Insert(std::string &message,
                int ID,
                int IB);
    void Search(int ID,
                int IB,
                std::ofstream &FileOut);
    void Erase(int ID,
               int IB,
               std::ofstream &FileOut);

    void CleanTree(node* p);
    
    void AccessTree(node* p);

  private:

    void RecursiveInsert(node* &current,
                         std::string &m,
                         int ID,
                         int IB);
    Email RecursiveSearch(node* p,
                          int ID,
                          int IB);
    bool RecursiveErase(node* &p,
                        int ID,
                        int IB);
    
    void Predecessor(node* remove,
                     node* predecessor);

    node* root;

    friend class Hash;
};

#endif