class Tree{
    public:
        struct Node{
            Node(int v):value(v),height(0),left(nullptr),right(nullptr),parent(nullptr){}
            int height;
            int value; 
            Node* left; 
            Node* right; 
            Node* parent;
        };
        virtual bool insert(int i) = 0;
        virtual bool access(int i) = 0; 
        virtual bool deleteN(int i) = 0;
        virtual void print() = 0;
        virtual void printbfs() = 0;

};