#include "tree.h"
class AVL: public Tree {
    public:
        ~AVL();
        bool insert(int i);
        Node* insert(int i, Node *n);
        bool access(int i); 
        bool deleteN(int i);
        Node* deleteNHelper(int i, Node* n);
        void print();
        void printbfs();
        void clear(Node *n);
        bool contains(int i) const;
        void preorder(); 
        void inorder(); 
        void postorder();
        int getHeight(Node *n) const;
        int maxHeight(int l, int r);
        int balance(Node *n);
        Node* rightRotate(Node *n);
        Node* leftRotate(Node *n);


    private:
        Node* root; 
        Node* getNodeFor(int i, Node* n) const; 
        Node* getSuccessorNode(int i);
};