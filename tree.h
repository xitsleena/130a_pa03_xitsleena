class Tree{
    
    struct Node{
        int value; 
        Node* left; 
        Node* right; 
        Node* parent;
    };

    virtual void insert(int i);
    virtual bool access(int i); 
    virtual bool deleteN(int i);
    virtual void print();

};