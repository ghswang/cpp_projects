//
// binary search tree practice
//

#include <iostream> // std::cout, std::cin, std::endl
using namespace std;

template <typename T>
class Node {
	public:
		Node(T i) : data(i), left(0), right(0) { count++; }
		~Node(void) { count--; }
		T data;
		Node<T>* left;
		Node<T>* right;
		static int getCount(void) { return count; }
	private:
		static int count;
};

template <typename T>
int Node<T>::count = 0;

template <typename T>
class Tree {
	public:
		Tree(void) : root(0) { }
		void insertNode(T i);
		void deleteNode(T i);
		void preorderTraversal(void) const;
		void inorderTraversal(void) const;
		void postorderTraversal(void) const;
	private:
		void insertNodeAt(Node<T>*& p, T i);
		void deleteNodeAt(Node<T>*& p, T i);
		void preorderTraversalAt(const Node<T>* p) const;
		void inorderTraversalAt(const Node<T>* p) const;
		void postorderTraversalAt(const Node<T>* p) const;
		void findInorderSuccAt(Node<T>*& start, Node<T>*& succ);
 		Node<T>* root;
};

template <typename T>
void Tree<T>::insertNode(T i) {
	if (root) { // COMMENTS
		cout << "Starting at ROOT: " << root->data << endl; // COMMENTS
	} // COMMENTS
	
	insertNodeAt(root, i);
}

template <typename T>
void Tree<T>::insertNodeAt(Node<T>*& p, T i) {
	if (!p) { // found empty root/node
		cout << "Inserting " << i << endl << endl; // COMMENTS
		
		p = new Node<T>(i);
	}
	else {
		if (p->data > i) {
			if (p->left) { // COMMENTS
				cout << "Going LEFT to " << p->left->data << endl; // COMMENTS
			} // COMMENTS
			else if (!p->left) { // COMMENTS
				cout << "Going LEFT to nothing" << endl; // COMMENTS
			} // COMMENTS

			insertNodeAt(p->left, i);
		}
		else if (p->data < i) {
			if (p->right) { // COMMENTS
				cout << "Going RIGHT to " << p->right->data << endl; // COMMENTS
			} // COMMENTS
			else if (!p->right) { // COMMENTS
				cout << "Going RIGHT to nothing" << endl; // COMMENTS
			} // COMMENTS

			insertNodeAt(p->right, i);
		}
		else {
			// i == p->data (duplicate), so do nothing
			cout << i << " cannot be inserted because it already exists" << endl << endl;
		}
	}
}

template <typename T>
void Tree<T>::deleteNode(T i) {
	if (root) { // COMMENTS
		cout << "Starting at ROOT: " << root->data << endl; // COMMENTS
	} // COMMENTS
	
	deleteNodeAt(root, i);
}

template <typename T>
void Tree<T>::deleteNodeAt(Node<T>*& p, T i) {
	if (!p) { // could not find node (i.e. DNE)
		cout << i << " cannot be deleted because it does not exist" << endl;
	}
	else if (p->data == i) { // found desired node to delete
		cout << "Successfully found " << i << endl; // COMMENTS
		
		if (!p->left && !p->right) { // if leaf node
			cout << i << " is a leaf node" << endl; // COMMENTS

			delete p;
			p = 0; // set to nullptr

			cout << "Successfully deleted " << i << endl; // COMMENTS
		}
		else if (p->left && !p->right) { // if desired node has only one left child node
			cout << i << " has only one LEFT child node, that being " << p->left->data << endl; // COMMENTS

			Node<T>* temp = p->left;
			delete p;
			p = temp; // links left child node to grandparent node (and hence, to rest of tree)

			cout << "Successfully deleted " << i << endl; // COMMENTS
		}
		else if (!p->left && p->right) { // if desired node has only on right child node
			cout << i << " has only one RIGHT child node, that being " << p->right->data << endl; // COMMENTS
			
			Node<T>* temp = p->right;
			delete p;
			p = temp; // links right child node to grandparent node (and hence, to rest of tree)

			cout << "Successfully deleted " << i << endl; // COMMENTS
		}
		else { // if desired node has both a left and right child node
			cout << i << " has BOTH a left and right child node, those being " << p->left->data << " and " << p->right->data; // COMMENTS
			cout << ", respectively" << endl; // COMMENTS
			cout << "Beginning search for an inorder successor" << endl; // COMMENTS
			cout << "Starting from RIGHT child node of " << p->data << ", which is " << p->right->data << endl; // COMMENTS
			
			findInorderSuccAt(p, p->right);

			cout << "Successfully deleted " << i << endl; // COMMENTS
		}
	}
	else if (p->data > i) {
		if (p->left) { // COMMENTS
			cout << "Going LEFT to " << p->left->data << endl; // COMMENTS
		} // COMMENTS

		deleteNodeAt(p->left, i);
	}
	else if (p->data < i) {
		if (p->right) { // COMMENTS
			cout << "Going RIGHT to " << p->right->data << endl; // COMMENTS
		} // COMMENTS

		deleteNodeAt(p->right, i);
	}
}

template <typename T>
void Tree<T>::findInorderSuccAt(Node<T>*& start, Node<T>*& succ) {
	if (succ->left) {
		cout << "Going LEFT to " << succ->left->data << endl; // COMMENTS

		findInorderSuccAt(start, succ->left);
	}
	else {
		if (succ == start->right) {
			cout << "No inorder successor found" << endl; // COMMENTS
			cout << start->data << " has NO inorder successor"; // COMMENTS
			cout << " so the \"inorder successor\" will be its RIGHT child node, which is "; // COMMENTS
			cout << succ->data << endl; // COMMENTS
			
			cout << "Setting LEFT child node of \"inorder successor\" (\"inorder successor\" is " << succ->data; // COMMENTS
			cout << ") to be LEFT child node of "; // COMMENTS
			cout << start->data << ", which is " << start->left->data << endl; // COMMENTS
			succ->left = start->left;

			cout << "Deleting " << start->data << endl; // COMMENTS
			delete start;

			cout << "Setting the now-deleted node to be the \"inorder successor\", which is " << succ->data << endl; // COMMENTS
			start = succ;
		}
		else if (succ->right) {
			cout << "Successfully found inorder successor" << endl; // COMMENTS
			cout << start->data << " has an inorder successor, " << succ->data << ", WITH a RIGHT child node, which is "; // COMMENTS
			cout << succ->right->data << endl; // COMMENTS

			// SOLUTION

			cout << "\"Swapping\" " << start->data << " and the inorder successor, which is " << succ->data << endl; // COMMENTS
			start->data = succ->data;

			cout << "Storing RIGHT child node of " << succ->data << ", which is " << succ->right->data; // COMMENTS
			cout << ", in a temporary place" << endl; // COMMENTS
			Node<T>* temp = succ->right;

			cout << "Deleting the previously designated inorder successor (i.e. before the \"swapping\" occurred)" << endl; // COMMENTS 
			delete succ;

			cout << "Setting the now-deleted node to be the node stored in the temporary place"; // COMMENTS
			cout << " [i.e. RIGHT child node of the inorder successor (" <<  start->data << "), which is "; // COMMENTS
			cout << temp->data << "]" << endl; // COMMENTS
			succ = temp;

			// // ALTERNATIVE SOLUTION

			// cout << "Setting LEFT child node of inorder successor (inorder successor is " << succ->data << ") to be "; // COMMENTS
			// cout << "LEFT child node of " << start->data << ", which is " << start->left->data << endl; // COMMENTS
			// succ->left = start->left;

			// cout << "Storing RIGHT child node of " << start->data << ", which is " << start->right->data; // COMMENTS
			// cout << ", in a temporary place" << endl; // COMMENTS
			// Node<T>* temp = start->right;

			// cout << "Deleting " << start->data << endl; // COMMENTS
			// delete start;

			// cout << "Setting the now-deleted node to be the node stored in the temporary place"; // COMMENTS
			// cout << " (i.e. RIGHT child node of the now-deleted node)" << endl; // COMMENTS
			// start = temp;
		}
		else {
			cout << "Successfully found inorder successor" << endl; // COMMENTS
			cout << start->data << " has an inorder successor WITHOUT a RIGHT child node, which is " << succ->data << endl; // COMMENTS

			cout << "Setting " << start->data << " to now be the inorder successor, which is " << succ->data; // COMMENTS
			cout << " (This effectively \"swaps\" the places of " << start->data << " and " << succ->data << ")" << endl; // COMMENTS
			start->data = succ->data;

			cout << "Deleting the previously designated inorder successor "; // COMMENTS
			cout << "(i.e. inorder successor before the \"swapping\")" << endl; // COMMENTS
			delete succ;

			cout << "Setting the newly-deleted node to be NULL (\"nothing\")" << endl; // COMMENTS
			succ = 0; // set to nullptr
		}
	}
}

template <typename T>
void Tree<T>::preorderTraversal(void) const {
	preorderTraversalAt(root);
}

template <typename T>
void Tree<T>::preorderTraversalAt(const Node<T>* p) const {
	if (!p) { // found empty root/node
		return;
	}
	else {
		cout << p->data << " ";
		preorderTraversalAt(p->left);
		preorderTraversalAt(p->right);
	}
}

template <typename T>
void Tree<T>::inorderTraversal(void) const {
	inorderTraversalAt(root);
}

template <typename T>
void Tree<T>::inorderTraversalAt(const Node<T>* p) const {
	if (!p) { // found empty root/node
		return;
	}
	else {
		inorderTraversalAt(p->left);
		cout << p->data << " ";
		inorderTraversalAt(p->right);
	}
}

template <typename T>
void Tree<T>::postorderTraversal(void) const {
	postorderTraversalAt(root);
}

template <typename T>
void Tree<T>::postorderTraversalAt(const Node<T>* p) const {
	if (!p) { // found empty root/node
		return;
	}
	else {
		postorderTraversalAt(p->left);
		postorderTraversalAt(p->right);
		cout << p->data << " ";
	}
}

int main() {
	Tree<int> t;
	int i;

	cout << "\nNumber of nodes in tree: " << Node<int>::getCount() << endl << endl;

	cin >> i;
	while (cin) {
		t.insertNode(i);
		cin >> i;
	}

	cout << "Number of nodes in tree: " << Node<int>::getCount() << endl;

	/*
	***********************************************************************
					47
				       /  \
				     40    60
				    /        \
			          23	      77
		                 /  \        /  \
		               11    34    69    86
                              /     /  \    \    / \
	                     9    30    38   72 81  90
		            / \  / \   /           /  \
                           3 10 25 32 36         87    95
	                         \                \    / \
			          26	           88 92  96
			            \		    \      \
				     27		     89     98
				      \		           /  \
				       28	         97    99
								\
								105
								/ \
							     103   112
								   / \
								110   115
								/     / \
							      109  114   120
							      /
							    108
							    /
							  107
	***********************************************************************
	*/

	cout << "\nPreorder Traversal:\n";
	t.preorderTraversal();
	cout << endl;

	cout << "Inorder Traversal:\n";
	t.inorderTraversal();
	cout << endl;

	cout << "Postorder Traversal:\n";
	t.postorderTraversal();
	cout << endl << endl;

	i = 23; // data to be deleted
	cout << "Attempting to delete " << i << endl;
	t.deleteNode(i);

	cout << "\nNumber of nodes in tree: " << Node<int>::getCount() << endl;

	cout << "\nPreorder Traversal:\n";
	t.preorderTraversal();
	cout << endl;

	cout << "Inorder Traversal:\n";
	t.inorderTraversal();
	cout << endl;

	cout << "Postorder Traversal:\n";
	t.postorderTraversal();
	cout << endl << endl;
}
