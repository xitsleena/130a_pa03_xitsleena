#include "tree.h"
class BST : public Tree{
    public:
        ~BST();
        bool insert(int i);
        bool insert(int i, Node *n);
        bool access(int i); 
        bool deleteN(int i);
        void print();
        void clear(Node *n);
        bool contains(int i) const;
        void preorder(); 
        void inorder(); 
        void postorder();

    private:
        Node* root; 
        Node* getNodeFor(int i, Node* n) const; 
        Node* getPredecessorNode(int i) const;
};