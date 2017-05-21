#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <string>
#include "Node.h"

class BSTree {

private:
  Node *root;

private:
  Node * search(const std::string &, Node *) const;
  void inOrder(Node *) const;
  void postOrder(Node *) const;
  void preOrder(Node *) const;
  void remove(Node *);
public:
  BSTree();
  void insert(const std::string &);
  bool search(const std::string &) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void preOrder( ) const;
  std::string largest( ) const;
  std::string smallest( ) const;
  int height(const std::string &) const;
  void remove(const std::string &);
};

#endif