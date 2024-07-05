// CSCI2100B Programming Assignment 1 Red Black Tree
#pragma once
#include <iostream>
// Assume all user inputs are valid

template<class T>
class RedBlackTree
{
private:
    enum ColorSet { black, red };   // The color of the node

    struct Node
    {
        Node* left;                     // The pointer pointing to the left child
        Node* right;                    // The pointer pointing to the right child
        Node* parent;                   // The pointer pointing to the parent node
        T data;                       // The storing data
        ColorSet color;
    };

    Node* root;
    Node* NIL;

    void leftRotation(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            this->root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotation(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL)
            y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            this->root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insertFixUp(Node* z)
    {
        // Case 0: Special Cases
        // When z is a root node
        if (!z->parent)
        {
            z->color = ColorSet::black;
            return;
        }
        // When z->grandparent is null
        if (!z->parent->parent)
            return;

        Node* y;

        while (z->parent->color == ColorSet::red)
        {
            if (z->parent == z->parent->parent->right)
            {
                y = z->parent->parent->left;
                // Case 1: when z has uncle and it is red
                if (y->color == ColorSet::red)
                {
                    z->parent->color = ColorSet::black;
                    y->color = ColorSet::black;
                    z->parent->parent->color = ColorSet::red;
                    z = z->parent->parent;
                }
                // Case 2 and 3
                else
                {
                    // Case 2: when uncle of z is black and form a triangle, make it to Case 3
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotation(z);
                    }
                    // Case 3:
                    z->parent->color = ColorSet::black;
                    z->parent->parent->color = ColorSet::red;
                    leftRotation(z->parent->parent);
                }
            }
            else // it means: if (z->parent == z->parent->parent->left)
            {
                y = z->parent->parent->right;
                // Case 1: when z has uncle and it is red
                if (y->color == ColorSet::red)
                {
                    z->parent->color = ColorSet::black;
                    y->color = ColorSet::black;
                    z->parent->parent->color = ColorSet::red;
                    z = z->parent->parent;
                }
                // Case 2 and 3
                else
                {
                    // Case 2: when uncle of z is black and form a triangle, make it to Case 3
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotation(z);
                    }
                    // Case 3:
                    z->parent->color = ColorSet::black;
                    z->parent->parent->color = ColorSet::red;
                    rightRotation(z->parent->parent);
                }

            }
            if (z == root)
                break;
        }
        root->color = ColorSet::black;
    }

    void removeFixUp(Node* x)
    {
        Node* w;
        while (x != root && x->color == ColorSet::black)
        {
            if (x == x->parent->left)
            {
                w = x->parent->right;
                // Case 1
                if (w->color == ColorSet::red)
                {
                    w->color = ColorSet::black;
                    x->parent->color = ColorSet::red;
                    leftRotation(x->parent);
                    w = x->parent->right;
                }
                // Case 2
                if (w->left->color == ColorSet::black && w->right->color == ColorSet::black)
                {
                    w->color = ColorSet::red;
                    x = x->parent;
                }
                // Case 3 and 4
                else
                {
                    // Case 3£º turn it to Case 4
                    if (w->right->color == ColorSet::black)
                    {
                        w->left->color = ColorSet::black;
                        w->color = ColorSet::red;
                        rightRotation(w);
                        w = x->parent->right;
                    }
                    // Case 4
                    w->color = x->parent->color;
                    x->parent->color = ColorSet::black;
                    w->right->color = ColorSet::black;
                    leftRotation(x->parent);
                    x = root;
                }

            }
            else // it means  if (x == x->parent->right)
            {
                w = x->parent->left;
                // Case 1
                if (w->color == ColorSet::red)
                {
                    w->color = ColorSet::black;
                    x->parent->color = ColorSet::red;
                    rightRotation(x->parent);
                    w = x->parent->left;
                }
                // Case 2
                if (w->right->color == ColorSet::black && w->left->color == ColorSet::black)
                {
                    w->color = ColorSet::red;
                    x = x->parent;
                }
                // Case 3 and 4
                else
                {
                    // Case 3: turn it to Case 4
                    if (w->left->color == ColorSet::black)
                    {
                        w->right->color = ColorSet::black;
                        w->color = ColorSet::red;
                        leftRotation(w);
                        w = x->parent->left;
                    }
                    // Case 4
                    w->color = x->parent->color;
                    x->parent->color = ColorSet::black;
                    w->left->color = ColorSet::black;
                    rightRotation(x->parent);
                    x = root;
                }
            }
        }
        x->color = ColorSet::black;
    }

    void transplant(Node* u, Node* v)
    {
        if (!u->parent)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v)
            v->parent = u->parent;
    }

public:
    RedBlackTree()                              // Constructor of RedBlackTree
    {
        NIL = new Node();                       // NIL is an empty node
        NIL->color = ColorSet::black;     // NIL is black in color
        NIL->left = nullptr;                    // NIL does not have children
        NIL->right = nullptr;
        root = NIL;                             // When the instance of RedBlackTree is created, set root to NIL first
    }

    Node* search(T key)
    {
        Node* x = this->root;

        while (x != NIL && x->data != key)
        {
            if (key < x->data)
                x = x->left;
            else
                x = x->right;
        }
        return x;
    }

    Node* successor(Node* x)
    {
        if (x->right != NIL)
            return treeMin(x->right);       // Case 1: If x has right child, find the leftmost node in right subtree
        else
        {
            Node* y = x->parent;            // Case 2: If x right child is empty, find the lowest ancestor of x whose left child is an ancestor of x
            while (y != NIL && x == y->right)
            {
                x = y;
                y = y->parent;
            }
            return y;
        }
    }

    Node* treeMin(Node* temp)
    {
        while (temp->left != NIL)
            temp = temp->left;
        return temp;
    }

    void insert(T key)
    {
        Node* z = new Node();
        z->parent = nullptr;
        z->data = key;
        z->left = NIL;
        z->right = NIL;
        z->color = ColorSet::red;

        Node* y = nullptr;
        Node* x = this->root;

        // finding a suitable position for the new node to be inserted
        while (x != NIL)
        {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        // inserting the new node into the tree
        z->parent = y;
        if (!y)
            this->root = z;
        else if (z->data < y->data)
            y->left = z;
        else
            y->right = z;

        // Fix the tree
        insertFixUp(z);
    }

    void remove(T key)
    {
        Node* z = NIL;
        Node* x;
        Node* y;

        z = search(key);

        y = z;

        ColorSet y_original_color = y->color;

        // Case 1: Only 1 child
        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == NIL)
        {
            x = z->left;
            transplant(z, z->left);
        }
        // Case 2: 2 child 
        else
        {
            y = treeMin(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y != z->right)
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            else
            {
                x->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        free(z);

        if (y_original_color == ColorSet::black)
            removeFixUp(x);

    }

    void searchTiming(T num)
    {
        Node* temp;
        for (int i = 0; i < num * 0.1 - 1; i++)
            temp = search(i);
    }
};