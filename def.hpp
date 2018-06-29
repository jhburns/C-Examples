#ifndef DEF_HPP
#define DEF_HPP

#include <string>

using namespace std;


//// EmptyException (when a data structure  tries to remove nothing)

class EmptyException {
  public:
    EmptyException();
    string what() const;
  protected:
    string msg;
};


//// NotFoundException (when a element is not found in a structure)

class NotFoundException {
  public:
    NotFoundException();
    string what() const;
  protected:
    string msg;
};


////  ListNode (Used by Structures)

//error handling and data protection should be handled by classes that use this object
template <typename T> class ListNode {
  public:
    ListNode();
    ListNode(T d);
    ~ListNode();

    T data;

    //links to nodes around current
    ListNode * next;
    ListNode * prev;
};

// implementation

template <typename T> ListNode<T>::ListNode() {
  //NULL should prevent data mistyping
  data = NULL;
  next = NULL;
  prev = NULL;
}

template <typename T> ListNode<T>::ListNode(T d) {
  data = d;
  next = NULL;
  prev = NULL;
}

template <typename T> ListNode<T>::~ListNode() {
  next = NULL;
  prev = NULL;
  delete prev;
  delete next;
}


//// BSTNode (Node for trees)

template <typename T> class BSTNode {
  public:
    BSTNode();
    BSTNode(T d);
    ~BSTNode();

    T data;

    BSTNode *left;
    BSTNode *right;
};

// implementation

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


////  List (template for any list)

template <typename T> class List {
  public:

    //insertFront
      //param: data - is inserted at the front
    virtual void insertFront(T data)=0;

    //insertBack
      //param: data - inserted in the back
    virtual void insertBack(T data)=0;

    //removeThat
      //param: key - the data being removed, assumed to exist
      //return: data
    virtual T removeThat(T key)=0;

    //removeFront
      //return: data - delted and returned the front
    virtual T removeFront()=0;

    //removeBack
      //return: data - delted anf returned the back
    virtual T removeBack()=0;

    //deletePos
      //param: pos - index of data, assumed to exist
      //return data at that index and delete it
    virtual T deletePos(int pos)=0;


    //getData
      //param: pos - index of data, assumed to exist
      //return: data at index
    virtual T getData(int pos)=0;

    //print
      //prints each data to a newline
    virtual void print()=0;

    //fint
      //param: data - that need to be found
      //return: index - for that data, -1 if not found
    virtual int find(T data)=0;

    //getSize
      //return: size - total number of list elements
    virtual unsigned int getSize()=0;

    //isEmpty
      //return: true/false - true if empty
    virtual bool isEmpty()=0;
};


//// DoublyLList (template for list implementation)

template <typename T> class DoublyLList : public List<T> {
  private:
    ListNode<T> *front;
    ListNode<T> *back;
    unsigned int size;

  public:
    DoublyLList();
    ~DoublyLList();

    void insertFront(T data);
    void insertBack(T data);

    T removeThat(T key);
    T removeFront();
    T removeBack();
    T deletePos(int pos);

    T getData(int pos);
    void print();
    int find(T data);
    unsigned int getSize();
    bool isEmpty();
};

// implementation

template <typename T> DoublyLList<T>::DoublyLList() {
  size = 0;
  front = NULL;
  back = NULL;
}

template <typename T> DoublyLList<T>::~DoublyLList() {
  //loop through and delete everything
  while (front != NULL) {
    ListNode<T> * temp = front;
    front = front -> next;
    temp = NULL;
    delete temp;
  }
}

template <typename T> unsigned int DoublyLList<T>::getSize() {
  return size;
}

template <typename T> void DoublyLList<T>::print() {
  ListNode<T> * current = front;

  while (current -> next != NULL) {
    std::cout << current -> data << endl;
    current = current -> next;
  }
  std::cout << current -> data << '\n';
}

template <typename T> void DoublyLList<T>::insertFront(T data) {
  ListNode<T> *node = new ListNode<T>(data);

  if (isEmpty()) {
    back = node;
  } else {
    front -> prev = node;
    node -> next = front;
  }

  front = node;
  size++;
}

template <typename T> bool DoublyLList<T>::isEmpty() {
  return (size == 0);
}

template <typename T> void DoublyLList<T>::insertBack(T data) {
  ListNode<T> * node = new ListNode<T>(data);

  if (isEmpty()) {
    front = node;
  } else {
    back -> next = node;
    node -> prev = back;
  }

  back = node;
  size++;
}

template <typename T> T DoublyLList<T>::removeThat(T key) {
  ListNode<T> * curr = front;

  while (curr -> data != key) {
    curr = curr -> next;

    //not found
    if (curr == NULL) {
      throw EmptyException();
    }
  }
  //checks if the node is the front or the back first
  if (curr == front) {
    front = curr -> next;
  } else {
    curr -> prev -> next = curr -> next;
  }

  if (curr == back) {
    back = curr -> prev;
  } else {
    curr -> next -> prev = curr -> prev;
  }

  curr -> next = NULL;
  curr -> prev = NULL;
  size--;

  T tempData = curr -> data;
  delete curr;
  return tempData;
}

template <typename T> T DoublyLList<T>::removeFront() {
  if (isEmpty()) {
    throw EmptyException();
  } else {
    ListNode<T> * tempFront = front;
    front = tempFront -> next;

    tempFront -> next = NULL;
    tempFront -> next = NULL;
    size--;

    T tempData = tempFront -> data;
    delete tempFront;
    return tempData;
  }
}

template <typename T> T DoublyLList<T>::removeBack() {
  if (isEmpty()) {
    throw EmptyException();
  } else {
    ListNode<T> * tempBack = back;
    back = tempBack -> prev;

    tempBack -> next = NULL;
    tempBack -> next = NULL;
    size--;

    T tempData = tempBack -> data;
    delete tempBack;
    return tempData;
  }
}

template <typename T> int DoublyLList<T>::find(T data) {
  int index = -1;
  ListNode<T> * current = front;

  while (current != NULL) {
    ++index;
    if (current -> data == data) {
      break;
    } else {
      current = current -> next;
    }
  }

  if (current == NULL) {
    index = -1;
  }

  return index;
}

template <typename T> T DoublyLList<T>::deletePos(int pos) {
  if (pos < 0) {
    throw NotFoundException();
  }

  unsigned int j = (unsigned) pos;
  if (j - 1 > getSize() || isEmpty()) {
    throw NotFoundException();
  }

  unsigned int i = 0;
  ListNode<T> * current = front;
  ListNode<T> * prev = front;

  while (i != j) { //update pointers
    prev = current;
    current = current -> next;
    i++;
  }

  prev -> next = current -> next;

  current -> next = NULL;
  T temp = current -> data;
  delete current;
  size--;
  return temp;
}

template <typename T> T DoublyLList<T>::getData(int pos) {
  if (pos < 0) {
    throw NotFoundException();
  }

  unsigned int j = (unsigned) pos;
  if (j - 1 > getSize() || isEmpty()) {
    throw NotFoundException();
  }

  unsigned int i = 0;
  ListNode<T> * current = front;

  while (i != j) {
    current = current -> next;
    i++;
  }

  return current -> data;
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

    //getSucc
      //get the successor
      //param d: starting pointer
      //return successor to be swapped out for deleted
    BSTNode<T> * getSucc(BSTNode<T> *d);

    //recDelete
      //param: node - nodes below are opened, then this is deleted
    void recDelete(BSTNode<T> * node);
};

//implementation

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
    BSTNode<T> * succ = getSucc(curr);

    if (curr == root) {
      root = succ;
    } else if (isLeft) {
      parent -> left = succ;
    } else {
      parent -> right = succ;
      //connect succ left child to curret left children

      succ -> left = curr -> left;

    }
  }

  size--;
}


template <typename T> BSTNode<T> * BSTree<T>::getSucc(BSTNode<T> *d) {
  BSTNode<T> *sp = d; //d is deleted
  BSTNode<T> *succ = d;

  BSTNode<T> *curr = new BSTNode<T>();
  curr = curr -> right;
  //loop until we find succ
  while (curr != NULL) {
    sp = succ;
    succ = curr;
    curr = curr -> left;
  }

  if(succ != d -> right) { //check if descdent of right child
    sp -> left = succ -> right;
    succ -> right = d -> right;
  }

  return succ;
}


//// Que (abstract queue class)

template <typename T> class Que {
public:
  Que();
  ~Que();

  //push
    //param: data - added to the end of the queque
  void push(T data);

  //pop
    //return: data - also deleted
  T pop();

  //peek
    //return: first in que
  T peek();

  //isEmpty
    //return: true/false - true if empty
  bool isEmpty();

  //getSize
    //return: size - number of elements
  int getSize();

  private:
    DoublyLList<T> line;
    int size;
};

//implementation

template <typename T> Que<T>::Que() {
  line = DoublyLList<T>();
  size = 0;
}

template <typename T> Que<T>::~Que() {
  //nothing to delete for now
}

template <typename T> void Que<T>::push(T data) {
  line.insertBack(data);
  size++;
}

template <typename T> T Que<T>::peek() {
  return line.getData(0);
}

template <typename T> T Que<T>::pop() {
  std::cout << size << '\n';

  if (isEmpty()) {
    throw EmptyException();
  } else {
    T tempData = line.removeFront();
    size--;
    return tempData;
  }
}

template <typename T> bool Que<T>::isEmpty() {
  return (size == 0);
}

template <typename T> int Que<T>::getSize() {
  return size;
}

#endif
