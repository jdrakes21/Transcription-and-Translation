/*****************************************
** File:    Strand.cpp
** Project: CMSC 202 Project 3, Spring 2023
** Author:  Jervon Drakes
** Date:    3/31/23
** Section: 44
** E-mail:  jdrakes1@umbc.edu
**
** This file contains the Strand.cpp file for Project 3.
** This program reads the Strand.h file and its functions and
** executes those functions to implement proj2.cpp
**
**
**
***********************************************/

#include "Strand.h"

// Strand
// builds a Strand object
Strand::Strand(){
  
  m_head = nullptr; // sets m_head to nullptr
  m_tail = nullptr; // sets m_tail to nullptr
  m_size = 0;

} 

// Strand(string)
// builds a new empty Strand with a name passed
Strand::Strand(string name){
  
  m_name = name; // sets m_name to name name passed
  m_head = nullptr; // sets m_head to nullptr
  m_tail = nullptr; // sets m_tail to nillptr
  m_size = 0;

}

// ~Strand
// Used to desturct strand and ensure it is deallocated
Strand::~Strand(){
  Node *curr = m_head;

  // loops through node until nullptr is located
  while(curr != nullptr){
    
    m_head = curr; // assigns the node curr to m_head 
    curr = curr->m_next; // points ucrr to the next node in the linked list
    delete m_head; // deallocates the memory within m_head
    
  }
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// InsertEnd
// Takes in a character and creates a new node. Inserts a node at the end of the strand and increased the size
void Strand::InsertEnd(char data){

  
  Node *temp = new Node();

  temp->m_next = nullptr; // point sthe temp node to m_next and assigns to nullptr
  temp->m_data = data; // points the temp node to m_data amd assigns it to the character passed

  // conditional to determine if m_head is nullptr
  if(m_head == nullptr){
    
    m_head = temp;// m_head is assigned to temp once met
    m_tail = temp;// m_tail is assigned to temp once met

    // the following is done otherwise 
  }else{
    
    m_tail->m_next = temp; // m_tail points to m_next and is assigned the temp node
    m_tail = temp; // m_tail assigned to the temp node
   
  }
  m_size++;
} 

// GetName
// returns m_name
string Strand::GetName(){
  
  return m_name;

}

// GetSize
// returns m_size
int Strand::GetSize(){
  
  return m_size;

}

// ReverseSequence
// The strand sequence is reverse in place
void Strand::ReverseSequence(){
  
  Node *curr = m_head; // new node is created and assigned to m_head
  Node *prev = nullptr; // new node is created and assigned to nullptr
  Node *next = nullptr; // new node is created and assigned to nullptr
  
  // loops through the curr node until nullptr is arrived
  while(curr != nullptr){
    next = curr->m_next; // assigns next code to the curr node which points to m_next
    curr->m_next = prev; // points curr node to m_next and assigns it to prev node
    prev = curr; // assigns prev node to curr node 
    curr = next; // assigns curr node to next node
  }
  m_tail = m_head;
  m_head = prev;
}
 // GetData
 // Returns the data at a specific location in the strand  
char Strand::GetData(int nodeNum){
  

  Node *temp = m_head; // new node is created and assigned to m_head

  // loops through the node to retrieve data
  for(int i = 0; i < nodeNum; i++){
    temp = temp->m_next; // temp points to m_next
  }
  return temp->m_data;
  
  
}

// operator << 
// Overloaded << operator to return ostream from strand. Iterates over the entire strand and builds an output stream
ostream &operator<< (ostream &output, Strand &myStrand){

  Node *temp = myStrand.m_head; 

  output << "***" <<  myStrand.m_name << "***" << endl; // the name of the strand is displayed

  // loops through the temp node once it is not nullptr
  while(temp != nullptr){

    output << temp->m_data << "->" ; // the sequence of the strand is outputted 
    temp = temp->m_next; // temp points to m_next to receive the next sequence in the linked list
  }
  
  output << "END";
  return output;
}
