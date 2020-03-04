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
	if (contains(i)){
		cout << "Element already present" << endl;
		return false;
	}

	root = insert(i, root);
	//printbfs();
	return true;

}

AVL::Node* AVL::insert(int i, Node *n){

	// inserting new node
	if (n == NULL){
		n = new Node(i); 
		cout << "Element inserted" << endl;
	}

	if (i < n->value) {
		n->left = insert(i, n->left);
		n->left->parent = n;
	}
	else if (i > n->value){
		n->right = insert(i, n->right);
		n->right->parent = n;
	}
	else {
		return n;
	}

	// fix height
	n->height = maxHeight(getHeight(n->left),getHeight(n->right)) + 1;

	// check balance 
	int b = balance(n);

	// left-left 
	if (b > 1 && i < n->left->value){
//		cout << "ll" << endl;
		return rightRotate(n);
	}

	// right-right
	if (b < -1 && i > n->right->value){
	//	cout << "rr" << endl;
//		printbfs();
		return leftRotate(n);
	}

	// left-right
	if (b > 1 && i > n->left->value){
//		cout << "lr" << endl;
		n->left = leftRotate(n->left);
		return rightRotate(n);
	}

	// right-left 
	if (b < -1 && i < n->right->value){
	//	cout << "rl" << endl;
		n->right = rightRotate(n->right);
		return leftRotate(n);

	}

	// if balanced 
	return n;
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

AVL::Node* AVL::getSuccessorNode(int i){
	if (!contains(i)){
		return NULL; // node for value does not exist
	}

	Node* max = root; 
	while (max && max->right){
		max = max->right; // check if value at min 
	}
	if (max->value == i){
		return NULL; // a predecessor will not exist at min
	} 
	Node* n = getNodeFor(i, root); 
	if (n->right){
		n = n->right; // if right subtree exists, find left-most child
		while(n && n->left){
			n = n->left;
		}
		return n; 
	}
	n = n->parent; // look for larger value from parent 
	while (n && n->parent){ 
		if (n->value > i){
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

	deleteNHelper(i,root);

	cout << "Element deleted" << endl;
	return true;
}

AVL::Node* AVL::deleteNHelper(int i, Node* n){
	if (n == NULL){
		return n;
	}

	if (i < n->value){
		n->left = deleteNHelper(i,n->left);
	}
	else if (i > n->value){
		n->right = deleteNHelper(i,n->right);
	}
	else {
		// not two children 
		if (n->left == NULL || n->right == NULL){
			Node *temp = NULL;
			if (n->left == NULL){
				temp = n->right;
			}
			else if (n->right == NULL){
				temp = n->left;
			}

			if (temp == NULL){
				temp = n;
				n = NULL;
			}
			else{
				*n = *temp;
			}
			delete temp;
		}
		else {
			// two children
			Node* temp = getSuccessorNode(i);
			//cout << temp->value << endl; 
			n->value = temp->value;
			n->right = deleteNHelper(temp->value, n->right);
		}
	}

	// only root 
	if (n == NULL){
		return n;
	}
	//cout << "do i reach after deletion" << endl;
	n->height = maxHeight(getHeight(n->left),getHeight(n->right)) + 1;

	int b = balance(n);

	// left-left
	if (b > 1 && balance(n->left) >= 0){
		return rightRotate(n);
	}

	// right-right
	if (b < -1 && balance(n->right) <= 0){
		return leftRotate(n);
	}

	// left-right
	if (b > 1 && balance(n->left) < 0){
		n->left = leftRotate(n->left);
		return rightRotate(n);
	}

	// right-left
	if (b < -1 && balance(n->right) > 0){
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}
	
//	cout << "reach after balancing" << endl;
	return n;
}

AVL::Node* AVL::rightRotate(Node *n){
	Node *l = n->left; 
	Node *lrsubtree = l->right; 

	l->right = n; 
	n->left = lrsubtree;

	n->height = maxHeight(getHeight(n->left),getHeight(n->right)) + 1;
	l->height = maxHeight(getHeight(l->left),getHeight(l->right)) + 1;

//	cout << "left rotate end" << endl;
	return l;
}

AVL::Node* AVL::leftRotate(Node *n){
	Node *r = n->right; 
	Node *rlsubtree = r->left; 

	r->left = n; 
	n->right = rlsubtree;

	n->height = maxHeight(getHeight(n->left),getHeight(n->right)) + 1;
	r->height = maxHeight(getHeight(r->left),getHeight(r->right)) + 1;
	
//	cout << "right rotate end" << endl;
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

	AVL avl = AVL();

	while(iss >> i){

		if (i == "insert"){
			// cout << i << endl;
			iss >> tt;  
			if (tt.back() == ','){
				tt.pop_back();
			}
			num = stoi(tt);
			avl.insert(num);
			// cout << tt << endl; 
		}
		else if (i == "access"){
			// cout << i << endl;
			iss >> tt; 
			if (tt.back() == ','){
				tt.pop_back();
			}
			num = stoi(tt);
			avl.access(num);
			// cout << tt << endl; 
		}
		else if (i == "delete") {
			// cout << i << endl;
			iss >> tt; 
			if (tt.back() == ','){
				tt.pop_back();
			}
			num = stoi(tt);
			avl.deleteN(num);
			// cout << tt << endl; 
		}
		else if (i == "print"){
			if (i.back() == ','){
				i.pop_back();
				avl.print();
			}

			iss >> tt;
			if (tt.back() == ','){
				tt.pop_back();
			}
			if (tt == "bfs"){
				avl.printbfs();
			} 
			else {
				avl.print();
			}

		}

		else {
			avl.print();
		}

	}

	return 0; 


}


