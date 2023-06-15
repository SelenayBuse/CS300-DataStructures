#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

template<typename T>
struct BinaryTreeNode {
    string FullName;
    string phoneNumber;
    string city;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

	BinaryTreeNode(const T& theFullName, const T& thephoneNumber, const T& thecity, BinaryTreeNode* lt, BinaryTreeNode* rt)
        : FullName(theFullName), phoneNumber(thephoneNumber), city(thecity), left(lt), right(rt) {}

};


template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree & root) { //const
    root = nullptr;
	cout << " Binary Tree is constructed...\n";
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() { //dest
    destroyTree(root);
	cout << " Binary Tree is destructed...\n";
}

template<typename T>
void BinarySearchTree<T>::destroyTree(BinaryTreeNode<T>*& node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
        node = nullptr;
    }
}

template<typename T>
BinaryTreeNode<T>* createBinaryNode( T FullName, T phoneNumber, T city) {
    
	BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>;
	newNode->FullName = FullName;
	newNode->phoneNumber = phoneNumber;
	newNode->city = city;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;

}

template<typename T>
bool searchContact(BinaryTreeNode<T>* root, T FullName) {
    BinaryTreeNode<T>* current = root;
    while (current != nullptr) {
        if (FullName == current->FullName) {
            return true;  // returns true if there is already in BST

        } else if (FullName < current->FullName) {
            current = current->left;

        } else {
            current = current->right;
        }
    }

    return false;
}


template<typename T>
BinaryTreeNode<T>* AddContactToBST(BinaryTreeNode<T>*& root, T FullName, T phoneNumber, T city) {
    // FIRST THING TO DO
    if (root == nullptr) {             
        return createBinaryNode(FullName, phoneNumber, city);
    }
    // IF A ROOT EXISTS
    else {
        if (searchContact(root, FullName)) {
            cout << "The given contact full name already exists in the database.\n";
        }
        else {
            if (FullName < root->FullName) {
                root->left = createBinaryNode(root->left, FullName, phoneNumber, city);
            }
            else {
                root->right = createBinaryNode(root->right, FullName, phoneNumber, city);
            }
            return root;
        }
    }
}


template<typename T>
BinaryTreeNode<T>* DeleteContact(BinaryTreeNode<T>*& root, T FullName, T phoneNumber, T city) {



}


template<typename T>
BinaryTreeNode<T>* SearchAContact(BinaryTreeNode<T>*& root, const string& name) {

	if (root == nullptr) {    //IS THIS EVEN NECESSARY?
        cout << "There is not a such contact.\n";
    }

	else{

		if ((root->FullName) == name) {
			cout << root->FullName << ", " << root->phoneNumber << ", " << root->city << endl;
		}

		SearchAContact(root->left, name);
		SearchAContact(root->right, name);
	}

}


