#include "BinaryTree.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

#include <iostream>
#include <fstream>

BinaryTree::BinaryTree()
// Descrição: construtor da classe BinaryTree, define a raiz como nula
// Entrada: -
// Saída: -
{
  root = nullptr;
}
BinaryTree::~BinaryTree()
// Descrição: destrutor da classe BinaryTree, faz a chamada da função CleanTree
// Entrada: -
// Saída: -
{
  //CleanTree(root);
  root = nullptr;
}
void BinaryTree::CleanTree(node* p)
// Descrição: limpa os elementos da árvore binária recursivamente
// Entrada: nó a ser deletado
// Saída: -
{
  if(p != nullptr){
    CleanTree(p->left);
    CleanTree(p->right);
    free(p);
  }
}
void BinaryTree::AccessTree(node* p)
// Descrição: realiza o acesso recursivo em ordem da árvore binária para
//            mapear os endereços de memória
// Entrada: nó a ser mapeado
// Saída: -
{
  if(p != nullptr){
    AccessTree(p->left);
    LEMEMLOG((long int)(&(*p)),sizeof(int),0);
    AccessTree(p->right);
  }

}

void BinaryTree::Insert(std::string &message,
                        int ID,
                        int IB)
// Descrição: Insere um elemento na árvore binária de pesquisa
// Entrada: messagem, ID da mensagem e código da caixa de entrada
// Saída: -
{

  // caso não esteja inicializada
  if(root == nullptr){
    root = new node(message, ID, IB, nullptr, nullptr);
    ESCREVEMEMLOG((long int)(&(*root)),sizeof(int),0);
  }

  // caso já tenha sido inicializada
  else{
    RecursiveInsert(root, message, ID, IB);
  }
}
void BinaryTree::Search(int ID,
                        int IB,
                        std::ofstream &FileOut)
// Descrição: realiza a busca de determinada mensagem na árvore
// Entrada: ID da mensagem, código da caixa de entrada e arquivo de saída
// Saída: -
{
  
  Email e;
  e = RecursiveSearch(root, ID, IB);
  // caso a mensagem não exista
  if(e.ID == EOF)
    FileOut << "MENSAGEM INEXISTENTE" << std::endl;
  // caso a mensagem seja encontrada
  else
    FileOut << e.message << std::endl;

}
void BinaryTree::Erase(int ID,
                       int IB,
                       std::ofstream &FileOut)
// Descrição: exclui o elemento desejado da caixa de entrada caso ele exista
// Entrada: ID da mensagem, código da caixa de entrada e arquivo de saída
// Saída: -
{
  // caso a mensagem seja apagada
  if(RecursiveErase(root, ID, IB))
    FileOut << "OK: MENSAGEM APAGADA" << std::endl;
  // caso a mensagem não exista
  else
    FileOut << "ERRO: MENSAGEM INEXISTENTE" << std::endl;
}

void BinaryTree::RecursiveInsert(node* &p,
                                 std::string& m,
                                 int ID,
                                 int IB)
// Descrição: faz a busca recursivamente da posição e insere o elemento desejado da caixa
//            de entrada caso ele já não tenha sido adicionado
// Entrada: nó a ser analisado, mensagem, ID da mensagem e código da caixa de entrada
// Saída: -
{
  // caso a posição seja nula a mensagem é inserida
  if(p == nullptr){
    p = new node(m, ID, IB, nullptr, nullptr);
    ESCREVEMEMLOG((long int)(&(*p)),sizeof(int),0);
  }

  // procura a posição onde a mensagem vai ser inserida na árvore
  else{
    // caso o ID seja menor que o ID do nó corrente
    if(ID < p->email.ID)
      RecursiveInsert(p->left, m, ID, IB);
    // caso o ID seja maior que o ID do nó corrente
    else if(ID > p->email.ID)
      RecursiveInsert(p->right, m, ID, IB);
    // caso a mensagem com mesmo ID para o mesmo código da caixa de entrada já tenha
    // sido inserido 
    else if((ID == p->email.ID) && (p->InBox == IB)){
      std::cout << "Um email com o ID " << ID << " para " << IB << " já foi adicionado" << std::endl;
      return ;
    }
  } 
}
Email BinaryTree::RecursiveSearch(node* p,
                                  int ID,
                                  int IB)
// Descrição: faz a busca recursivamente e exclui o elemento desejado da caixa
//            de entrada caso ele exista
// Entrada: nó a ser analisado, ID da mensagem e código da caixa de entrada
// Saída: -
{
  Email email_aux;

  // caso não exista o elemento na lista
  if(p == nullptr){
    // flags para item não presente
    email_aux.ID = -1;
    email_aux.message = "";

    return email_aux;
  }

  // caso a chave seja menor que a chave corrente
  if(ID < p->email.ID)
    return RecursiveSearch(p->left, ID, IB);
  // caso a chave seja maior que a chave corrente
  else if(ID > p->email.ID)
    return RecursiveSearch(p->right, ID, IB);
  // caso seja o elemento procurado
  else if((ID == p->email.ID) && (IB == p->InBox))
    return p->email;
  else
    return RecursiveSearch(p->right, ID, IB);
}
void BinaryTree::Predecessor(node* remove,
                             node* predecessor)
// Descrição: faz a busca recursiva do antecessor do nó a ser removido
// Entrada: nó a ser removido e nó a substituí-lo
// Saída: -
{
  if(predecessor->right != nullptr){
    Predecessor(remove, predecessor->right);
    return ;
  }

  remove->email.message = predecessor->email.message;
  remove->email.ID = predecessor->email.ID;
  remove = predecessor;
  predecessor = predecessor->left;
  remove = nullptr;
  delete remove;
}
bool BinaryTree::RecursiveErase(node* &p,
                                int ID,
                                int IB)
// Descrição: faz a busca recursivamente e exclui o elemento desejado da caixa
//            de entrada caso ele exista
// Entrada: nó a ser analisado, ID da mensagem e código da caixa de entrada
// Saída: false caso não esteja presente e true caso esteja
{

  // caso o nó não esteja presente
  if(p == nullptr)
    return false;

  // caso o ID seja maior que o ID corrente
  if(ID > p->email.ID)
    return RecursiveErase(p->right, ID, IB);
  //caso o ID seja menor que o ID corrente
  else if(ID < p->email.ID)
    return RecursiveErase(p->left, ID, IB);
  // caso o ID seja igual ao ID corrente
  else if((ID == p->email.ID) && (IB == p->InBox)){
    node* node_aux;
    // se o nó não tiver o filho da direita
    if(p->right == nullptr){
      node_aux = p;
      p = p->left;
      node_aux = nullptr;
      delete node_aux;
    }
    // se possuir apenas o filho da direita
    else if(p->left == nullptr){
      node_aux = p;
      p = p->right;
      node_aux = nullptr;
      delete node_aux;
    }
    // se possuir dois filhos é substituído pelo antecessor
    else
      Predecessor(p, p->left);

    return true;
  }
  // caso seja o mesmo ID mas com o código da caixa de entrada diferente
  else
    return false;
}