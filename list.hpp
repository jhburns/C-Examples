#ifndef LIST_HPP
#define LIST_HPP

#include "exceptions.hpp"

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

template <typename T> class Queue {
public:
  Queue();
  ~Queue();

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

template <typename T> Queue<T>::Queue() {
  line = DoublyLList<T>();
  size = 0;
}

template <typename T> Queue<T>::~Queue() {
  //nothing to delete for now
}

template <typename T> void Queue<T>::push(T data) {
  line.insertBack(data);
  size++;
}

template <typename T> T Queue<T>::peek() {
  return line.getData(0);
}

template <typename T> T Queue<T>::pop() {
  if (isEmpty()) {
    throw EmptyException();
  } else {
    T tempData = line.removeFront();
    size--;
    return tempData;
  }
}

template <typename T> bool Queue<T>::isEmpty() {
  return (size == 0);
}

template <typename T> int Queue<T>::getSize() {
  return size;
}

#endif