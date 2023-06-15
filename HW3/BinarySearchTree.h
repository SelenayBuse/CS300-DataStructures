#ifndef	BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE
#include <iostream>
using namespace std;


template<typename T>
struct BinaryTreeNode {
    T FullName;
    T phoneNumber;
    T city;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

		BinaryTreeNode(const T& theFullName, const T& thephoneNumber, const T& thecity, BinaryTreeNode* lt, BinaryTreeNode* rt)
        : FullName(theFullName), phoneNumber(thephoneNumber), city(thecity), left(lt), right(rt) {}
};


template <class T>
class BinarySearchTree
{
public:

	BinarySearchTree( const BinarySearchTree & root );
	~BinarySearchTree( );
	BinaryTreeNode<T>* createBinaryNode( T FullName, T phoneNumber, T city);
	bool searchContact(BinaryTreeNode<T>* root, T FullName);
	BinaryTreeNode<T>* AddContactToBST( T FullName, T phoneNumber, T city);
	BinaryTreeNode<T>* DeleteContact(BinaryTreeNode<T>*& root, T FullName, T phoneNumber, T city);
	SearchAContact(BinaryTreeNode<T>*& root, const string& name);
	void InOrderPrintToFile();
	void PreOrderPrintToFile();
	void DrawTreeToFile();
	void destroyTree(BinaryTreeNode<T>*& node);
	
private:
	BinaryTreeNode<T>* root;
};

#endif