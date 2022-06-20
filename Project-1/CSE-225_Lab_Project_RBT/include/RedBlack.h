#ifndef RED_BLACK_TREE_RedBlack_H
#define RED_BLACK_TREE_RedBlack_H

enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};


class RedBlack
{
    private:
        Node *root;
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRedBlack(Node *&);
        void fixDeleteRedBlack(Node *&);
        void inorderBST(Node *&);
        void preorderBST(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* insertBST(Node *&, Node *&);
        Node* deleteBST(Node *&, int);
        int getBlackHeight(Node *);
    public:
        RedBlack();
        void insertValue(int); //Function to insert data
        void deleteValue(int); //Function to delete data
        void searchValue(); //Function to search value
        void inorder();
        void preorder();
};


#endif //RED_BLACK_TREE_RedBlack_H
