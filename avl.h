#include "tree.h"
class AVL: public Tree {
    public:
        struct Node{
            Node(int v):value(v),depth(0),left(nullptr),right(nullptr),parent(nullptr){}
            int value; 
            int depth;
            Node* left; 
            Node* right; 
            Node* parent;
        };
        ~AVL();
        bool insert(int i);
        bool insert(int i, int d, Node *n);
        bool access(int i); 
        bool deleteN(int i);
        void print();
        void clear(Node *n);
        bool contains(int i) const;
        void preorder(); 
        void inorder(); 
        void postorder();
        int getDepth(int i) const;
        int maxDepth(int l, int r);
        Node* rightRotate(Node *n);
        Node* leftRotate(Node *n);


    private:
        Node* root; 
        Node* getNodeFor(int i, Node* n) const; 
        Node* getPredecessorNode(int i) const;
        int getDepthHelper(Node* n, int i) const;

};