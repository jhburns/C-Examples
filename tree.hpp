#ifndef TREE_HPP
#define TREE_HPP

#include "exceptions.hpp"

template <typename T> class BSTNode {
  public:
    BSTNode();
    BSTNode(T d);
    ~BSTNode();

    T data;

    BSTNode *left;
    BSTNode *right;
};

template <typename T> BSTNode<T>::BSTNode() {
  //T() prevents object NULL errors
  T data = T();
  left = NULL;
  right = NULL;
}

template <typename T> BSTNode<T>::BSTNode(T d) {
  data = d;
  left = NULL;
  right = NULL;
}

template <typename T> BSTNode<T>::~BSTNode() {
  left = NULL;
  right = NULL;
  delete left;
  delete right;
}


//// BSTree (A binary search tree)

template <typename T> class BSTree {
  public:
    BSTree();
    ~BSTree();

    //insert
      //param: key - value to be inserted
    void insert(T key);

    //deleteNode
      //param: key - value to be deleted
    void deleteNode(T key);

    //contains
      //param: key - value to be checked is exists
      //return: true/false - whether value is in tree
    bool contains(T key);

    //isEmpty
      //return: true/false - size is zero
    bool isEmpty();

    //getMin
      //return: data pointer - min value node
    BSTNode<T>* getMin();

    //getMax
      //return: data pointer - max value node
    BSTNode<T>* getMax();

    //getSize
      //return: size - number of elements
    int getSize();

    //printTree
      //param: node pointer - starting location
      //return: nothing - print whole tree to cosole in order
    void printTree(BSTNode<T> * node);

    //prTTree
      //print from root, in order traversal
    void printTree();

  private:
    BSTNode<T> * root;
    int size;

    //getSuccessor
      //get the successor
      //param d: starting pointer
      //return successor to be swapped out for deleted
    BSTNode<T> * getSuccessor(BSTNode<T> *d);

    //recDelete
      //param: node - nodes below are opened, then this is deleted
    void recDelete(BSTNode<T> * node);
};

template <typename T> BSTree<T>::BSTree() {
  root = NULL;
  size = 0;
}

template <typename T> BSTree<T>::~BSTree() {
  recDelete(root);
}

template <typename T> void  BSTree<T>::recDelete(BSTNode<T> * node) {
  if (node) {
    recDelete(node -> left);
    recDelete(node -> right);
  }
  delete node;
}

template <typename T> void BSTree<T>::printTree(BSTNode<T> * node) { //in order traversal
  if (node == NULL) {
    return;
  }

  printTree(node -> left);
  std::cout << node -> data << " ";
  printTree(node -> right);
}

template <typename T> void BSTree<T>::printTree() { //in order traversal
  printTree(root);
}

template <typename T> bool BSTree<T>::isEmpty() {
  return (size == 0);
}

template <typename T> int BSTree<T>::getSize() {
  return size;
}

//farthest right is always largest
template <typename T> BSTNode<T> * BSTree<T>::getMax() {
  BSTNode<T> * curr = root;

  if (root == NULL) {
    return NULL;
  }

  while (curr -> right != NULL) {
    curr = curr -> right;
  }

  return curr;
}

template <typename T> void BSTree<T>::insert(T key) {
  BSTNode<T> * node = new BSTNode<T>(key);

  //no duplicate keys allowed
  if (contains(key)) {
    return;
  }

  size++;

  if (root == NULL) { //empty tree
    root = node;
  } else {
    BSTNode<T> * curr = root;
    BSTNode<T> * parent = NULL;

    while (true) {
      parent = curr;

      if (key < curr -> data) {
        curr = curr -> left;

        if (curr == NULL) {
          parent -> left = node;
          break;
        }
      } else  {
        curr = curr -> right;

        if (curr == NULL) {
          parent -> right = node;
          break;
        }
      }

    }
  }
}

template <typename T> bool BSTree<T>::contains(T key) {
  if (root == NULL) {
    throw EmptyException();
  } else {
    BSTNode<T> * curr = root;

    while (curr -> data != key) {
      if (key < curr -> data) {
        curr = curr -> left;
      } else {
        curr = curr -> right;
      }

      if (curr == NULL) {
        return false;
      }
    }

    return true;
  }
}

template <typename T> void BSTree<T>::deleteNode(T key) {
  if (root == NULL) {
    throw EmptyException();
  }

  BSTNode<T> * curr = root;
  BSTNode<T> * parent = root;
  bool isLeft;

  while (curr -> data != key) {
    parent = curr;
    if (key < curr -> data) {
      isLeft = true;
      curr = curr -> left;
    } else {
      isLeft = false;
      curr = curr -> right;
    }
  }

  if (curr == NULL) {
    throw NotFoundException();
  }

    //eval

    //no children

  if (curr -> left == NULL && curr -> right == NULL) {
    if (curr == root) {
      root = NULL;
    } else if (isLeft) {
      parent -> left = NULL;
    } else {
      parent -> right = NULL;
    }
  }

  //one child

  //no right child
  else if (curr -> right == NULL) {
    if (curr == root) {
      root = curr -> left;

    } else if (isLeft) {
      parent -> left = curr -> left;
    } else {
      parent -> right = curr -> left;
    }
  }


  else if (curr -> left == NULL) {
    if (curr == root) {
      root = curr -> right;

    } else if (isLeft) {
      parent -> left = curr -> right;
    } else {
      parent -> right = curr -> right;
    }
  }

  //two children
  else {
    BSTNode<T> * successor = getSuccessor(curr);

    if (curr == root) {
      root = successor;
    } else if (isLeft) {
      parent -> left = successor;
    } else {
      parent -> right = successor;
      //connect successor left child to curret left children

      successor -> left = curr -> left;

    }
  }

  size--;
}


template <typename T> BSTNode<T> * BSTree<T>::getSuccessor(BSTNode<T> *d) {
  BSTNode<T> *sp = d; //d is deleted
  BSTNode<T> *successor = d;

  BSTNode<T> *curr = new BSTNode<T>();
  curr = curr -> right;
  //loop until we find successor
  while (curr != NULL) {
    sp = successor;
    successor = curr;
    curr = curr -> left;
  }

  if(successor != d -> right) { //check if decadent of right child
    sp -> left = successor -> right;
    successor -> right = d -> right;
  }

  return successor;
}

#endif