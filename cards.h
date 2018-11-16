//cards.h
//Authors:Yi Xiao Yue
//All class declarations go here

#ifndef CARDS_H
#define CARDS_H
#include <iostream>



class Card{

 public:
  Card(char s = 's',char v = '0');
  void setSuit(char s);//set the value of suit
  void setValue(char v);//set the value of value
  char getSuit()const;//return the suit character of the calling card
  char getValue()const;//return the value character of the calling card
  friend std::ostream& operator <<(std::ostream& out, const Card& c);

 private:
  char suit;
  char value;

};

struct Node{
  Card card;
  Node* link;
  
};

class Linkedlist{

 public:
  Linkedlist(Node* head_init = 0,Node* tail_init = 0);//Parameterized constructor
  ~Linkedlist();//overload deconstructor
  void insert(const Card& c);//insert the suit and value of a card into the end of the linkedlist, will work for empty linkedlist
  int length()const;//return the number of Cards in the linkedlist
  bool found(const Card& c1)const;//search the object that calls the function and return true if c1 is in the list
  Card card_at(int index)const;//return the Card at certain index of the linkedlist, index count starts at 0
  void delete_card(const Card& c);//delete the card in the linked list
  friend std::ostream& operator<< (std::ostream& out, const Linkedlist& list);

 private:
  Node* head;
  Node* tail;
};

std::ostream& operator <<(std::ostream& out, const Card& c);//overload << for card
std::ostream& operator<< (std::ostream& out, const Linkedlist& list);//overload << for linkedlist
#endif
