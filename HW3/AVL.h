#ifndef	AVL_H
#define AVL
#include <iostream>
using namespace std;

// CODES ARE TAKEN FROM LECTURE SLIDES

template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
	Comparable 	element;
	AvlNode   		*left;
	AvlNode   		*right;
	int        		height;

	AvlNode( const Comparable & theElement, 
		AvlNode *lt, AvlNode *rt, int h = 0 )
		: element( theElement ), left( lt ), right( rt ), height( h ) { }

	friend class AvlTree<Comparable>;
};



template <class Comparable>
class AvlTree
{

	public:

		AvlTree( const AvlTree & root );
		~AvlTree( );
		AvlNode<Comparable>* createAVLNode( Comparable FirstName, Comparable SurName, Comparable phoneNumber, Comparable city);
		bool searchAVLContact(AvlNode<T>* root, Comparable FirstName, Comparable SurName);
		AvlNode<Comparable>* AddContactToAVL( Comparable FirstName, Comparable SurName, Comparable phoneNumber, Comparable city);
		AvlNode<Comparable>* DeleteContactFromAVL(AvlNode<Comparable>*& root, Comparable FirstName, Comparable SurName, Comparable phoneNumber, Comparable city);
		void InOrderPrintToFileAVL();
		void PreOrderPrintToFileAVL();
		void DrawTreeToFileAVL();
		void destroyAVLTree(AvlNode<Comparable>*& node);
	

		// Avl manipulations
		int height( AvlNode<Comparable> *t ) const;
		void makeEmpty();
		int max( int lhs, int rhs ) const;
		void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
		void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
		void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
		void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;


	private:

		AvlNode<Comparable> *root;

};



#endif