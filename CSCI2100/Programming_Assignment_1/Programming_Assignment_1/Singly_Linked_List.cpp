// CSCI2100B Programming Assignment 1 Singly Linked List
#pragma once
#include <iostream>
// Assume all user inputs are valid
// Note that x = 1 is the first elements of the linked list 

template<class T>
class SinglyLinkedList
{
private:
    struct Node
    {
        Node* next;    // The pointer pointing to the next node or we say "the node after it"
        T data;      // The storing data
    };

    Node* head = nullptr; // Creating a empty linked list

public:
    Node* search(T key)
    {
        Node* x = head;

        while (x->next && x->data != key)
        {
            x = x->next;
        }

        return x;                  // Return the Node consisting the required element
    }

    void insertAfterX(Node* x, T key)
    {
        Node* temp = new Node();
        temp->data = key;
        temp->next = nullptr;

        if (x->next)
        {
            temp->next = x->next;
        }
        x->next = temp;
    }

    void insert(T key)
    {
        append(key);
    }

    void prepand(T key)
    {
        Node* temp = new Node();        // Creating a space for the new Node 
        temp->data = key;
        temp->next = head;              // If head is empty, then temp->next would be empty as well
        head = temp;                    // Pointing the head to the 1st Node (new Node) 
    }

    void append(T key)
    {
        Node* temp1 = new Node();  // Creating a space for the new Node
        temp1->data = key;         // Insearting the value of "key" into the new Node
        temp1->next = nullptr;

        if (head == nullptr)
        {
            head = temp1;          // Point the head to the appended node if the head is NULL
            return;
        }

        Node* temp2 = head;
        while (temp2->next != nullptr)
        {
            temp2 = temp2->next;
        }
        temp2->next = temp1;       // Linking the new Node to last position     
    }

    void remove(T key)
    {
        Node* x = search(key);
        removeNodeX(x);
    }

    void removeNodeX(Node* x)
    {
        if (x == head)                      // Case 1: When x is the head
        {
            head = x->next;                 // Update the head to the next node of x 
            x->next = nullptr;              // Update the next node of x to nullptr
            free(x);                        // free the space of x
            return;
        }

        Node* temp = head;

        while (temp->next != x)
        {
            temp = temp->next;              // Locate temp to the previous node of x
        }


        if (!x->next)                       // Case 2: When x is the last node
        {
            temp->next = nullptr;           // Update the next node of the previous node of x
        }
        else                                // Case 3: When x is not last node and not the head
        {
            temp->next = x->next;           // Link the previous node of x and the next node of x
            x->next = nullptr;              // Update the next node of x to nullptr
        }

        free(x);                            // free the space of x
    }

    void searchTiming(T num)
    {
        Node* temp;
        for (int i = 0; i < num * 0.1 - 1; i++)
            temp = search(i);
    }
};
