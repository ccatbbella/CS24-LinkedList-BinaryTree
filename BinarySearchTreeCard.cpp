//Authors: Yixiao Yue
//Implementation of the classes defined in BinarySearchTreeCard.h

#include <iostream>
using namespace std;

// constructor sets up empty tree
template <class item>
BST<item>::BST() : root(0) { }

// destructor deletes all nodes
template <class item>
BST<item>::~BST() {
    clear(root);
}

//return item stored at certain index using in-order traversal
template <class item>
item BST<item>::Item_at(int index) const {
  Node* n = min(root);
  item target = n->info; //target initially set to equal to the minimum value
  for(int i = 0; i < index; i++){
    n = getSuccessorNode(target);
    target = n->info;
  }
  return target;
}


// recursive helper for destructor
template <class item>
void BST<item>::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
template <class item>
bool BST<item>::insert(item value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
template <class item>
bool BST<item>::insert(item value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}



// print tree data in-order, with helper
template <class item>
void BST<item>::printInOrder() const {
    printInOrder(root);
}
template <class item>
void BST<item>::printInOrder(Node *n) const {
  
   if (n) {
  	printInOrder(n->left);
	if(n->info.getValue() == 0)
	  cout << n->info.getSuit() << " a" << endl;
	else if(n->info.getValue() == 11)
	  cout << n->info.getSuit() << " j" << endl;
	else if(n->info.getValue() == 12)
	  cout << n->info.getSuit() << " q" << endl;
	else if(n->info.getValue() == 13)
	  cout << n->info.getSuit() << " k" << endl;
	else
          cout << n->info << endl;
  	printInOrder(n->right);
   }
}



// return count of values
template <class item>
int BST<item>::count() const {
    return count(root);
}

// recursive helper for count
template <class item>
int BST<item>::count(Node *n) const {
  int lresult = 0,rresult = 0;
  if(!n)
    return 0;
  if(n->left == 0 && n->right == 0)
    return 1;
  if(n->left)
    lresult = count(n->left);
  if(n->right)
    rresult = count(n->right);
  return 1 + lresult + rresult;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
template <class item>
typename BST<item>::Node* BST<item>::getNodeFor(item value,Node* n) const{
  if(!n)
    return NULL;
  if(n->info == value){
    return n;
  }
  else if(n->info < value){
    return getNodeFor(value, n->right);
  }
  else{
    return getNodeFor(value, n->left);
  }
}

// returns true if value is in the tree; false if not
template <class item>
bool BST<item>::contains(item value) const {
  if(getNodeFor(value, root) == NULL)
    return false;
  else
    return true;
}

// returns the Node containing the predecessor of the given value


// returns the Node containing the successor of the given value
template <class item>
typename BST<item>::Node* BST<item>::getSuccessorNode(item value) const{
  if(!contains(value))
    return 0;
  Node* n = getNodeFor(value,root);
  if(n == max(root))
    return 0;
  if(n->right)
    return min(n->right);
  while(n->parent && n->parent->right == n)
    n = n->parent;
  return n->parent;
}



// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
template <class item>
bool BST<item>::remove(item value){
  Node* n = getNodeFor(value,root);
  //value is not in the BST
  if(!n)
    return false;
  //case leaf node with 2 subcases
  if(!n->left && !n->right){
    if(!n->parent){    //n is the root
      root = 0;
    }
    else if(n->parent->left == n) //left leaf node
      n->parent->left = 0;
    else
      n->parent->right = 0; //right leaf node
    n->parent = 0;
    delete n;
    return true;
  }

  //one child case with 4 subcases
  if(n->left && !n->right){ //n has a left child
    if(!n->parent){    //n is the root
      root = n->left;
      n->left->parent = 0;
      n->left = 0;
      
    }
    if(n->info < n->parent->info){  //n is a left child
      n->parent->left = n->left;
      n->left->parent = n->parent;
      n->parent = 0;
      n->left = 0;
    }
    else{                         //n is a right child
      n->parent->right = n->left;
      n->left->parent = n->parent;
      n->parent = 0;
      n->left = 0;
    }
    delete n;
    return true;
  }

  if(n->right && !n->left){  //n has a right child
    if(!n->parent){    //n is the root
      root = n->right;
      n->right->parent = 0;
      n->right = 0;
      
    }
    else if(n->info < n->parent->info){  //n is a left child
      n->parent->left = n->right;
      n->right->parent = n->parent;
      n->parent = 0;
      n->right = 0;
    }
    else{                          //n is a right child
      n->parent->right = n->right;
      n->right->parent = n->parent;
      n->parent = 0;
      n->right = 0;
    }
    delete n;
    return true;
  }

  
  //two children case
  if(n->left && n->right){
    Node* s = getSuccessorNode(value);
    if(!s->right){   //successor is a leaf node
      //swap n with its successor
      if(n->right == s){   //s is n's direct right child
        s->left = n->left;
        s->right = 0;
	s->parent = n->parent;
	if(n->parent){
	  if(n->parent->info > n->info) // n is a left child
	    n->parent->left = s;
	  else
	    n->parent->right = s;
	}
	else{
	  root = s;
	}
	s->left->parent = s;
	n->parent = 0;
	n->left = 0;
	n->right = 0;
	delete n;
	return true;
      }
      else{   //s is not a direct child of n
	s->left = n->left;
	s->right = n->right;
	Node* p = s->parent;
	p->left = 0;
	s->parent = n->parent;
	if(n->parent){
	  if(n->parent->info > n->info) // n is a left child
	    n->parent->left = s;
	  else
	    n->parent->right = s;
	}
	else{
	  root = s;
	}
	s->left->parent = s;
	s->right->parent = s;
	n->parent = 0;
	n->left = 0;
	n->right = 0;
	delete n;
	return true;
      }
    }
    else{                 //suscessor has one right child
      if(s == n-> right){    //if successor is the direct right child of n
	s->left = n->left;
	s->parent = n->parent;
	if(n->parent){
	  if(n->parent->info > n->info) // n is a left child
	    n->parent->left = s;
	  else
	    n->parent->right = s;
	}
	else{
	  root = s;
	}
	s->left->parent = s;
	n->left = 0;
	n->right = 0;
	n->parent = 0;
	delete n;
	return true;
      }
      else {               //if the successor is not the direct right child of n
	s->left = n->left;
	Node* p = s->parent;
	s->parent = n-> parent;
	if(n->parent){
	  if(n->parent->info > n->info) // n is a left child
	    n->parent->left = s;
	  else
	    n->parent->right = s;
	}
	else{
	  root = s;
	}
        Node* r = s-> right;
	s-> right = n-> right;
	s->right->parent = s;
	s->left->parent = s;
	p->left = r;
	r->parent = p;
	n->right = NULL;
	n->left = NULL;
	n->parent = NULL;
	delete n;
	return true;
      }
    }
  }
}    
    
template <class item>
typename BST<item>::Node* BST<item>::max(Node* n) const{
  while(n->right)
    n = n-> right;
  return n;
}

template <class item>
typename BST<item>::Node* BST<item>::min(Node* n) const{
  while(n->left)
    n = n->left;
  return n;
}

