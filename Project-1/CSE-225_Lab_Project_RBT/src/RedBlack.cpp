#include <bits/stdc++.h>
#include "RedBlack.h"

using namespace std;


Node::Node(int data) {
    this->data = data;
    color = RED;
    left = right = parent = NULL;
}


RedBlack::RedBlack() {
    root = NULL;
}


int RedBlack::getColor(Node *&node) {
    if (node == NULL)
        return BLACK;

    return node->color;
}


void RedBlack::setColor(Node *&node, int color) {
    if (node == NULL)
        return;

    node->color = color;
}


Node* RedBlack::insertBST(Node *&root, Node *&ptr) {
    if (root == NULL)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}


void RedBlack::insertValue(int n) {
    Node *node = new Node(n);
    root = insertBST(root, node);
    fixInsertRedBlack(node);
}


void RedBlack::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != NULL)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == NULL)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}


void RedBlack::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != NULL)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == NULL)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}


void RedBlack::fixInsertRedBlack(Node *&ptr) {
    Node *parent = NULL;
    Node *grandparent = NULL;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}


void RedBlack::fixDeleteRedBlack(Node *&node) {
    if (node == NULL)
        return;

    if (node == root) {
        root = NULL;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != NULL ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != NULL)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != NULL)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = NULL;
        Node *parent = NULL;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
        delete(node);
        setColor(root, BLACK);
    }
}


Node* RedBlack::deleteBST(Node *&root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == NULL || root->right == NULL)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}


void RedBlack::deleteValue(int data) {
    Node *node = deleteBST(root, data);
    fixDeleteRedBlack(node);
}

void RedBlack::searchValue()
{
     if(root==NULL)
     {
           cout<<"Empty Tree" ;
           return  ;
     }
     int x;
     cout<<" Enter key of the node to be searched: ";
     cin>>x;

     Node *p=root;
     int found=0;

     while(p!=NULL&& found==0)
     {
            if(p->data==x)
                found=1;
            if(found==0)
            {
                 if(p->data < x)
		      p=p->right;
                 else
                      p=p->left;
            }
     }

     if(found==1)
          cout<<"Value Found.";
     else
     	  cout<<"Value not found";
}

void RedBlack::inorderBST(Node *&ptr) {
    if (ptr == NULL)
        return;

    inorderBST(ptr->left);
    cout << ptr->data << " " << ptr->color << endl;
    inorderBST(ptr->right);
}


void RedBlack::inorder() {
    inorderBST(root);
}


void RedBlack::preorderBST(Node *&ptr) {
    if (ptr == NULL)
        return;

    cout << ptr->data << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}


void RedBlack::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}


Node *RedBlack::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != NULL)
        ptr = ptr->left;

    return ptr;
}


Node* RedBlack::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != NULL)
        ptr = ptr->right;

    return ptr;
}


int RedBlack::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != NULL) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}



