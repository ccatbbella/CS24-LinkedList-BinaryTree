//cards.cpp
//Authors: Yi Xiao Yue
//Implementation of the classes defined in cards.h
#include "cards.h"
#include <iostream>
#include <string>
using namespace std;

Card::Card(char s,char v){suit = s;value = v;}
void Card::setSuit(char s){suit = s;}
void Card::setValue(char v){value = v;}
char Card::getSuit()const{return suit;}
char Card::getValue()const{return value;}


Linkedlist::Linkedlist(Node* head_init,Node* tail_init){
  head = head_init;
  tail = tail_init;
}

Linkedlist::~Linkedlist(){
  Node* n = head;
  while(n){
    head = n->link;
    delete n;
    n = head;
  }
}

void Linkedlist::insert(const Card& c){
  if(head == 0 && tail == 0){
    Node* n = new Node;
    n -> link = 0;
    n -> card.setSuit(c.getSuit());
    n -> card.setValue(c.getValue());
    head = n;
    tail = n;
  }
  else{
    Node* n = new Node;
    n -> link = 0;
    n -> card.setSuit(c.getSuit());
    n -> card.setValue(c.getValue());
    tail -> link = n;
    tail = n;
  }
}    
    
int Linkedlist::length()const{
  int count = 0;
  Node* n = head;
  while(n){
    count++;
    n = n -> link;
  }
  return count;}

bool Linkedlist::found(const Card& c1)const{
  Node* n = head;
  while(n){
    if(n->card.getSuit() == c1.getSuit() && n->card.getValue() == c1.getValue())
      return true;
    n = n->link;
  }
  return false;
}

Card Linkedlist::card_at(int index)const{
  Card c;
  Node* n = head;
  for(int i = 0; i < index;i++){
    n = n->link;
  }
  c.setSuit(n->card.getSuit());
  c.setValue(n->card.getValue());
  return c;
}
void Linkedlist::delete_card(const Card& c){
  Node*n = head;
  Node*after_me = head;
  int count = 0;
  while((n->card.getSuit() != c.getSuit() || n->card.getValue() != c.getValue()) && n !=0){
      n = n->link;
      count++;
  }
  if(count == 0){
    head = n -> link;
    delete n;
  }
  else{
    for(int i = 1; i < count; i++){
      after_me = after_me -> link;
    }
    after_me -> link = n -> link;
    delete n;
  }
}

ostream& operator<< (ostream& out, const Card& c){
  out << c.suit << " " << c.value;
  return out;
}


ostream& operator<< (ostream& out, const Linkedlist& list){
  out << "'s cards:" << endl;
  Node*n = list.head;
  while(n){
    out << n->card << endl;
    n = n -> link;
    }
  return out;
}
