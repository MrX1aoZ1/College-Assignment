// CSCI2100B Programming Assignment 1 Doubly Linked List
#pragma once
#include <iostream>
// Assume all user inputs are valid
// Note that x = 1 is the first elements of the linked list 

template<class T>
class DoublyLinkedList
{
private:
    struct Node
    {
        Node* next;    // The pointer pointing to the next node or we say "the node after it" 
        Node* prev;    // The pointer pointing to the previous node or we say "the node in front of it"
        T data;      // The storing data
    };

    Node* head = nullptr; // Creating a empty linked list
    Node* tail = nullptr;

public:
    Node* search(T key)
    {
        Node* x = head;

        while (x && x->data != key)
        {
            x = x->next;
        }

        return x;              // Return the Node consisting the required element
    }

    void insertAfterX(Node* x, T key)
    {
        Node* temp = new Node();            // Create a new node temp
        temp->data = key;
        temp->next = nullptr;
        temp->prev = x;                     // Point the prev pointer of the new node to x

        if (x->next)                        // Case 1: if there is node after x
        {
            x->next->prev = temp;           // Point the prev pointer of the node after x to the new node
            temp->next = x->next;           // Point the next pointer of the new node to the next pointer of node x
        }
        else                                // Case 2: if x is the last node
        {
            tail = temp;                    // Update the tail to the new node
        }
        x->next = temp;                     // Point the next pointer of x to the new node
    }

    void insert(T key)
    {
        append(key);
    }

    void prepand(T key)
    {
        Node* temp = new Node();            // Creating a space for the new Node
        temp->data = key;
        temp->next = head;                  // Point the next pointer of the new node to the original head
        temp->prev = nullptr;               // Set the prev pointer of the new node to nullptr (since it is head)

        if (head)                           // Situation when the list is not empty
            head->prev = temp;              // Pointing the prev-pointer of the original first to the new Node

        if (!tail)
            tail = temp;                    // if it is an empty list, point the tail to the new node

        head = temp;                        // Pointing the head to the 1st Node (new Node) 
    }

    void append(int key)
    {
        Node* temp = new Node();            // Creating a space for the new Node
        temp->data = key;
        temp->prev = tail;                  // Point the prev pointer of the new node to the original tail
        temp->next = nullptr;               // Set the next pointer of the new node to nullptr (since it is tail)

        if (tail)                           // Situation when the list is not empty
            tail->next = temp;              // Pointing the next-pointer of (x-1) Node to the new Node

        if (!head)
            head = temp;                    // if it is an empty list, point the head to the new node

        tail = temp;                        // Pointing the head to the (x)th Node (new Node)
    }

    void removeNodeX(Node* x)                           // Remove node x
    {
        if (!x->next && !x->prev)                       // Case 1: When x do not have next node and previous node(when there is only 1 element in the list)_
        {
            head = nullptr;                             // Update head to nullptr
            tail = nullptr;                             // Update tail to nullptr
        }
        else if (!x->prev)                              // Case 2: When x is head
        {
            head = x->next;                             // Update the head to the next node of x
            x->next->prev = nullptr;                    // Update the prev pointer of the next node of x to nullptr
            x->next = nullptr;                          // Update the next pointer of x to nullptr
        }
        else if (!x->next)                              // Case 3: When x is tail
        {
            tail = x->prev;                             // Update the tail to the prev node of x
            x->prev->next = nullptr;                    // Update the next pointer of the previous node of x to nullptr
            x->prev = nullptr;                          // Update the prev pointer of x to nullptr
        }
        else                                            // Case 4: When x has next node and previous node
        {
            x->prev->next = x->next;                    // Point the next pointer of previous node of x to the next node of x
            x->next->prev = x->prev;                    // Point the prev pointer of next node of x to the previous node of x
            x->next = nullptr;                          // Update the next pointer of x to nullptr
            x->prev = nullptr;                          // Update the prev pointer of x to nullptr
        }

        free(x);                                        // Finally free the space of x
    }

    void remove(T key)
    {
        Node* x = search(key);
        removeNodeX(x);
    }

    void searchTiming(T num)
    {
        Node* temp;
        for (int i = 0; i < num * 0.1 - 1; i++)
            temp = search(i);
    }
};