# C++ Data Structure Examples

Various templates of data structures and abstract data types implimented in C++. Run `make all` to compile.

## Files Overview

*Makefile* - Used to give compiler directions

*def.hpp* - header file that lays out class definitons and has most of the implimentation because template classes would throw errors

*imp.cpp* - implementation for non-template classes, like the Exception classes

*driver.cpp* - the main runner of the program and excpetion catcher

## Instructions

Compile with: `make all` and g++ installed
Run with `./driver.exe`, no parameters
Delete with `make clean`

## Classes overview
**All in order in the def.hpp file**

*EmptyException*  thrown when a structure is empty
*NotFoundException* thrown when a structure is not found

*ListNode* used by the List classes
*BSTNode* used by the BSTree class

*List* super class for any List type Data structure, inherited by the DoublyLList class. Only definitions.

*DoublyLList* Doublely Linked List
*BSTree* Binary Search Tree

*Que* Queue implementation using the DoublyLList


## About

Made by Jonathan Burns and modified from Chapman University Data Structures and Algorithms assignment solutions.

GPL licence 