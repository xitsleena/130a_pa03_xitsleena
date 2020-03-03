#include "avl.h"
#include <string>
#include <stack> 
#include <queue>
#include <sstream>
#include <iostream> 

using namespace std; 

int AVL::getHeight(Node *n) const{
    if (n == NULL){
		return -1;
	}
	return n->height;
}

int AVL::maxHeight(int l, int r){
	if (l > r){
		return l;
	}
	return r;
}

int AVL::balance(Node *n){
	if (n == NULL){
		return 0;
	}
	return getHeight(n->left) - getHeight(n->right);
}

AVL::~AVL(){
	clear(root);
}

void AVL::clear(Node *n){
	if (n) {
		clear(n->left);
		clear(n->right);
		delete n;
	}
}

bool AVL::contains(int i) const{
	return getNodeFor(i, root);
}

AVL::Node* AVL::getNodeFor(int i, Node* n) const{
	if (!n){
		return NULL;
	}
	if (n->value == i){
		return n; 
	}
	if (n->value < i){
		return getNodeFor(i, n->right);
	}
	if (n->value > i){
		return getNodeFor(i, n->left);
	}
	return NULL;
}

bool AVL::insert(int i){
    if (root == NULL){
		root = new Node(i);
		cout << "Element inserted" << endl;
		return true;
	}	

	return insert(i, root);
}

bool AVL::insert(int i, Node *n){
	if (i == n->value){
		cout << "Element already present" << endl;
		return false;
	}
	if (i < n->value) {
		if (n->left){
			return insert(i, n->left);
		}else {
			n->left = new Node(i);
			n->left->parent = n;
            n->height = maxHeight(n->left->height,n->right->height) + 1;
			cout << "Element inserted" << endl;
		}
	}
	else {
		if (n->right){
			return insert(i, n->right);
		}
		else {
			n->right = new Node(i);
			n->right->parent = n;
            n->height = maxHeight(n->left->height,n->right->height) + 1;
			cout << "Element inserted" << endl;	
		}
	}

	// check balance 
	// does this work using n?
	Node *inserted = getNodeFor(i,n);
	int b = balance(inserted);

	// left-left 
	if (b > 1 && i < inserted->left->value){
		rightRotate(inserted);
	}

	// right-right
	if (b < -1 && i > inserted->right->value){
		leftRotate(inserted);
	}

	// left-right
	if (b > 1 && i > inserted->left->value){
		inserted->left = leftRotate(inserted->left);
		rightRotate(inserted);
	}

	// right-left 
	if (b < -1 && i < inserted->right->value){
		inserted->right = rightRotate(inserted->right);
		leftRotate(inserted);

	}

	return true;
}

bool AVL::access(int i){
	Node* n = this->root; 

	while(n){
		if (i > n->value){
			n = n->right;
		}
		else if(i < n->value){
			n = n->left;
		}
		else{
			cout << "Element accessed" << endl;
			return true;
		}
	}
	cout << "Element not found" << endl;
	return false;
}

AVL::Node* AVL::getPredecessorNode(int i) const{
	if (!contains(i)){
		return NULL; // node for value does not exist
	}

	Node* min = root; 
	while (min && min->left){
		min = min->left; // check if value at min 
	}
	if (min->value == i){
		return NULL; // a predecessor will not exist at min
	} 
	Node* n = getNodeFor(i, root); 
	if (n->left){
		n = n->left; // if left subtree exists, find right-most child
		while(n && n->right){
			n = n->right;
		}
		return n; 
	}
	n = n->parent; // look for smaller value from parent 
	while (n && n->parent){ 
		if (n->value < i){
			return n; 
		}
		n = n->parent;
	}
	return NULL;
}

bool AVL::deleteN(int i){
	if (!contains(i)){
		cout << "Element not found" << endl;
		return false; 
	}

	Node *n = getNodeFor(i,root);

	// leaf node case 
	if (!(n->left) && !(n->right)){
		if (n==root){  
			root = NULL;
			delete n;
			cout << "Element deleted" << endl;
			return true;
		}
		else{
			Node *par = n->parent; 
			if (par->left && par->left->value==i){
				par->left = NULL;
			}
			else{
				par->right = NULL;
			}
			delete n; 
			cout << "Element deleted" << endl;
			return true; 
		}
	}
	// if deleted node only has left child
	if (!(n->right)){
		// if n is root
		if (n == root){  
			root = n->left; 
			root->parent = NULL; 
			delete n; 
			cout << "Element deleted" << endl;
			return true; 
		}
		Node *mom = n->parent;
		if (mom->left && mom->left->value == i){
			mom->left = n->left; // if deleted node is the left child
		}
		else{
			mom->right = n->left; // if deleted node is the right child
		}
		n->left->parent = mom; 
		delete n; 
		cout << "Element deleted" << endl;
		return true; 
	}
	//1 child case: only has right child
	if (!(n->left)){ 
		//if n is root then set root to its right child, update relations, and delete n
		if (n==root){ 
			root = n->right;
			n->right->parent = NULL;
			delete n;
			cout << "Element deleted" << endl;
			return true; 
		}
		//otherwise, find parent, if node is left child, then set parents child to n->right, if node is right child, then set parents child to right child
		Node *dad = n->parent;
		if (dad->left && dad->left->value == i){
			dad->left = n->right;
		}
		else{
			dad->right = n->right;
		}
		//update relationship
		n->right->parent = dad;
		delete n;
		cout << "Element deleted" << endl;
		return true;
	} 
	//two child case
	Node *pre = getPredecessorNode(i); 
	int toAdd = pre->value; 
	deleteN(toAdd);
	n->value = toAdd;
	cout << "Element deleted" << endl;
	return true; 
}

AVL::Node* AVL::rightRotate(Node *n){
	Node *l = n->left; 
	Node *lrsubtree = l->right; 

	l->right = n; 
	n->left = lrsubtree;

	// did i set maxHeight correctly when inserting
	n->height = maxHeight(getHeight(n->left),getHeight(n->right)) + 1;
	l->height = maxHeight(getHeight(l->left),getHeight(l->right)) + 1;

	return l;
}

AVL::Node* AVL::leftRotate(Node *n){
	Node *r = n->right; 
	Node *rlsubtree = r->right; 

	r->right = n; 
	n->right = rlsubtree;

	// did i set maxHeight correctly when inserting
	n->height = maxHeight(getHeight(n->left),getHeight(n->right)) + 1;
	r->height = maxHeight(getHeight(r->left),getHeight(r->right)) + 1;
	
	return r;
}

void AVL::print(){
	if (root == NULL){
		cout << "Empty tree" << endl;
		return;
	}
	// pre-order 
	preorder();
	cout << "\n";
	// in-order 
	inorder();
	cout << "\n";
	// post-order 
	postorder();
	cout << "\n";
}

void AVL::preorder(){
	stack<Node *> nodeTracker; 
	nodeTracker.push(root); 

	while (nodeTracker.empty() == false){
		Node *add = nodeTracker.top();
		cout << add->value << " "; 
		nodeTracker.pop();

		if (add->right){
			nodeTracker.push(add->right);
		}
		if (add->left){
			nodeTracker.push(add->left);
		}
	}
}

void AVL::inorder(){
	stack<Node *> nodeTracker; 
	Node *curr = root; 

	while (curr != NULL || nodeTracker.empty() != true){
		while (curr != NULL){
			nodeTracker.push(curr);
			curr = curr->left;
		}

		curr = nodeTracker.top();
		nodeTracker.pop(); 

		cout << curr->value << " "; 

		curr = curr->right;
	}
	
}

void AVL::postorder(){
	stack<Node *> nodeTracker; 
	stack<Node *> nodeStorage;
    Node *curr = root; 
    nodeTracker.push(curr);

    while(nodeTracker.empty()!=true){
        curr = nodeTracker.top();
        nodeTracker.pop();

        nodeStorage.push(curr);

        if (curr->left){
            nodeTracker.push(curr->left);
        }
        if (curr->right){
            nodeTracker.push(curr->right);
        }
    }

     while (nodeStorage.empty()!=true){
         cout << nodeStorage.top()->value << " ";
         nodeStorage.pop();
     }


}

void AVL::printbfs(){
	if (root == NULL){
		cout << "Empty tree" << endl;
		return;
	}
	queue<Node *> nodeTracker;
	nodeTracker.push(root);

	while (nodeTracker.empty() == false){
		Node *add = nodeTracker.front();
		cout << add->value << " ";
		nodeTracker.pop();

		if (add->left){
			nodeTracker.push(add->left);
		}

		if (add->right){
			nodeTracker.push(add->right);
		}
	}
	cout << "\n";
}

int main(int arc, char* argv[]){

    string str = argv[1];
    
    istringstream iss(str);
	string i;
	string tt;

    int num; 

	AVL *avl = new AVL();

    while(iss >> i){
		
		if (i == "insert"){
		    // cout << i << endl;
		    iss >> tt;  
		    if (tt.back() == ','){
		       tt.pop_back();
		    }
            num = stoi(tt);
            avl->insert(num);
		    // cout << tt << endl; 
		}
		else if (i == "access"){
		    // cout << i << endl;
		    iss >> tt; 
		    if (tt.back() == ','){
		       tt.pop_back();
		    }
            num = stoi(tt);
            avl->access(num);
		    // cout << tt << endl; 
		}
		else if (i == "delete") {
		    // cout << i << endl;
		    iss >> tt; 
		    if (tt.back() == ','){
		       tt.pop_back();
		    }
            num = stoi(tt);
			avl->deleteN(num);
		    // cout << tt << endl; 
		}
		else if (i == "print"){
			iss >> tt;
			if (tt.back() == ','){
				tt.pop_back();
			}
			avl->printbfs();
		}
		else {
		    if (i.back() == ','){
		       i.pop_back();
		    }
           
            if (i == "print"){
                avl->print();
            }
		   // cout << i << endl;
		}
		
	}

    return 0; 


}


