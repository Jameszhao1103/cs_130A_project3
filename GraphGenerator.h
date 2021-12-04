#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <iostream>
#include <vector>

//Reference: Section of the AVL tree implementation

class GraphGenerator
{
public:
    struct adjlist
    {
    public:
        int vertex_connected;
        adjlist *next;
        int size = 0;
        void addSize() { size += 1; }
        int getSize() { return size; }
        adjlist(int el)
        {
            vertex_connected = el;
            next = NULL;
        };
    };

    struct leaf
    {
    public:
        int vertex;
        int height;
        leaf *left;
        leaf *right;
        adjlist *list;
        leaf(int k)
        {
            height = 0;
            vertex = k;
            left = NULL;
            right = NULL;
            list = NULL;
        };
    };

    leaf *root = nullptr;
    int size = 0;

    void InsertVertex(int vertex)
    {
        size += 1;
        InsertVertex_helper(vertex, root);
    }

    void InsertEdge(int vertex1, int vertex2)
    {
        if (LookUp(vertex1) == nullptr)
        {
            InsertVertex(vertex1);
        }
        if (LookUp(vertex2) == nullptr)
        {
            InsertVertex(vertex2);
        }
        InsertEdge_helper(vertex1, vertex2, root);
        InsertEdge_helper(vertex2, vertex1, root);
    }

    leaf *LookUp(int vertex)
    {
        return find(root, vertex);
    }

    void InOrder()
    {
        std::cout << "The in order traversal:\n";
        InOrder_helper(root);
        std::cout << "\n";
    }

    void PreOrder()
    {
        std::cout << "The pre order traversal:\n";
        PreOrder_helper(root);
        std::cout << "\n";
    }

private:
    int height(leaf *t) const
    {
        return t == nullptr ? -1 : t->height;
    };

    int max(int a, int b)
    {
        return a > b ? a : b;
    };

    void rightRotation(leaf *&t)
    {
        leaf *t_left = t->left;
        t->left = t_left->right;
        t_left->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        t_left->height = max(height(t_left->left), t->height) + 1;
        t = t_left;
    };

    void leftRotation(leaf *&t)
    {
        leaf *t_right = t->right;
        t->right = t_right->left;
        t_right->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        t_right->height = max(height(t_right->left), t->height) + 1;
        t = t_right;
    };

    void leftRightDoubleRotation(leaf *&t)
    {
        leftRotation(t->left);
        rightRotation(t);
    };

    void rightLeftDoubleRotation(leaf *&t)
    {
        rightRotation(t->right);
        leftRotation(t);
    };

    void balance(leaf *&t)
    {
        if (t == nullptr)
        {
            return;
        }
        if (height(t->left) - height(t->right) > 1)
        {
            if (height(t->left->left) >= height(t->left->right))
            {
                rightRotation(t);
            }
            else
            {
                leftRightDoubleRotation(t);
            }
        }
        else if (height(t->right) - height(t->left) > 1)
        {
            if (height(t->right->right) >= height(t->right->left))
            {
                leftRotation(t);
            }
            else
            {
                rightLeftDoubleRotation(t);
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    };

    void InsertVertex_helper(int k, leaf *&t)
    {
        if (t == nullptr)
        {
            t = new leaf(k);
        }
        else if (k < t->vertex)
        {
            InsertVertex_helper(k, t->left);
        }
        else if (k > t->vertex)
        {
            InsertVertex_helper(k, t->right);
        }
        balance(t);
    }

    void append(adjlist *&list, int new_edge)
    {
        adjlist *new_node = new adjlist(new_edge);
        adjlist *last = list;
        if (list == nullptr)
        {
            list = new_node;
            return;
        }
        while (last->next != nullptr)
        {
            last = last->next;
        }
        last->next = new_node;
        return;
    }

    leaf *find(leaf *t, int el)
    {
        if (t == nullptr)
        {
            return NULL;
        }
        int k = t->vertex;
        if (k == el)
            return t;
        if (k > el)
            return find(t->left, el);
        if (k < el)
            return find(t->right, el);
    };

    void InsertEdge_helper(int k1, int k2, leaf *&t)
    {
        if (k1 == t->vertex)
        {
            append(t->list, k2);
            t->list->addSize();
            return;
        }
        else if (k1 < t->vertex)
        {
            InsertEdge_helper(k1, k2, t->left);
        }
        else if (k1 > t->vertex)
        {
            InsertEdge_helper(k1, k2, t->right);
        }
    }

    void InOrder_helper(leaf *root)
    {
        if (root == NULL)
            return;
        InOrder_helper(root->left);
        std::cout << root->vertex << " ";
        InOrder_helper(root->right);
    }

    void PreOrder_helper(leaf *root)
    {
        if (root == NULL)
            return;
        std::cout << root->vertex << " ";
        PreOrder_helper(root->left);
        PreOrder_helper(root->right);
    }
};
#endif