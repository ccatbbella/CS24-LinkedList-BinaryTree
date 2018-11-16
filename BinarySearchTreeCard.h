//Yixiao Yue 
//All class declarations go here

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
template <class item>

class BST {
  
 public:
    BST();                   // constructor
    ~BST();                  // destructor
    bool insert(item value);     // insert value; return false if duplicate
    void printInOrder() const;       // print tree data in-order to cout
    int count() const;               // count of values
    bool contains(item value) const;  // true if value is in tree
    item Item_at(int index) const;    //return the item stored in a specific index. Index is assigned based on in-order traversal, starting from 0.
    bool remove(item value);                    // deletes the Node containing the given value from the tree

 private:

    struct Node {
	item info;
	Node *left, *right, * parent;
	// useful constructor:
    Node(item v=0) : info(v), left(0), right(0), parent(0) { }
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(item value, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(item value, Node *n); // note overloading names for simplicity
    void printInOrder(Node *n) const;
    int count(Node *n) const;
    Node* max(Node* n) const;
    Node* min(Node* n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(item value) const;   // returns the Node containing the successor of the given value

};

#endif
