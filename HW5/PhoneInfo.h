#include <iostream>
#include <string>

using namespace std;


template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
    Comparable element;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode(const Comparable& theElement,
        BinaryNode* lt, BinaryNode* rt)
        : element(theElement), left(lt), right(rt) { }

    friend class BinarySearchTree<Comparable>;
};


struct PhoneInfo // struct to keep the datas from the files
{
    string name;
    string surname;
    string phoneNum;
    string city;
    PhoneInfo(string n = "", string sn = "", string pn = "", string c = "") { // constructor
        name = n;
        surname = sn;
        phoneNum = pn;
        city = c;
    }
    bool operator <(const PhoneInfo& PI)  // operotar functions are created to use this struct in equations
    {
        if (PI.surname == "")
        {
            return name < PI.name;
        }
        return (name + surname) < (PI.name + PI.surname);
    }
    bool operator >(const PhoneInfo& PI)
    {
        if (PI.surname == "")
        {
            return name > PI.name;
        }
        return (name + surname) > (PI.name + PI.surname);
    }
    bool operator ==(const PhoneInfo& PI)
    {
        if (PI.surname == "")
        {
            return name == PI.name;
        }
        return (PI.name + PI.surname) == (name + surname);
    }
    bool operator >=(const PhoneInfo& PI)
    {
        if (PI.surname == "")
        {
            return name >= PI.name;
        }
        return (name + surname) >= (PI.name + PI.surname);
    }
    bool operator <=(const PhoneInfo& PI)
    {
        if (PI.surname == "")
        {
            return name <= PI.name;
        }
        return (name + surname) <= (PI.name + PI.surname);
    }
    bool operator !=(const PhoneInfo& PI)
    {
        if (PI.surname == "")
        {
            return name != PI.name;
        }
        return (name + surname) != (PI.name + PI.surname);
    }
    PhoneInfo operator =(const PhoneInfo& PI)
    {
        name = PI.name;
        surname = PI.surname;
        phoneNum = PI.phoneNum;
        city = PI.city;
        return *this;
    }
    bool findPartialIdx(PhoneInfo PI) // to find partial names is in the name or not
    {
        return name.find(PI.name) == 0;
    }
    friend ostream& operator<<(ostream& os, const PhoneInfo& obj) {
        os << "x: " << obj.name << ", y: " << obj.surname << ", z: " << obj.phoneNum << ", t: " << obj.city << endl;
        return os;
    }
    int getLength() const {
        string temp = (name + surname);
        return temp.size();
    }
};


template <class Comparable>
class BinarySearchTree
{
public:
    explicit BinarySearchTree(const Comparable& notFound);
    BinarySearchTree(const BinarySearchTree& rhs);
    ~BinarySearchTree();

    const Comparable& findMin(BinaryNode<Comparable>* t) const;
    const Comparable& findMax() const;
    const Comparable& find(const Comparable& x) const;
    bool isEmpty() const;
    void printTree() const;
    Comparable* findElement(const Comparable& x) const;
    void makeEmpty();
    void insert(Comparable& x);
    void remove(Comparable& x);
    const BinarySearchTree& operator=(const BinarySearchTree& rhs);
private:
    BinaryNode<Comparable>* root;
    const Comparable ITEM_NOT_FOUND;

    const Comparable& elementAt(BinaryNode<Comparable>* t) const;

    void privInsert(Comparable& x, BinaryNode<Comparable>*& t) const;
    void privRemove(Comparable& x, BinaryNode<Comparable>*& t) const;
    BinaryNode<Comparable>* privFindMin(BinaryNode<Comparable>* t) const;
    BinaryNode<Comparable>* privFindMax(BinaryNode<Comparable>* t) const;
    BinaryNode<Comparable>* privFind(const Comparable& x,
        BinaryNode<Comparable>* t) const;
    void privMakeEmpty(BinaryNode<Comparable>*& t) const;
    void privPrintTree(BinaryNode<Comparable>* t) const;
    BinaryNode<Comparable>* clone(BinaryNode<Comparable>* t) const;
};


/**
  * Construct the tree.
  */
template <class Comparable>
BinarySearchTree<Comparable>::
BinarySearchTree(const Comparable& notFound) :
    ITEM_NOT_FOUND(notFound), root(NULL)
{
}


/**
  * Internal method to get element field in node t.
  * Return the element field or ITEM_NOT_FOUND if t is NULL.
  */
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::
elementAt(BinaryNode<Comparable>* t) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
  * Find item x in the tree.
  * Return the matching item or ITEM_NOT_FOUND if not found.
  */
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::
find(const Comparable& x) const
{
    return elementAt(privFind(x, root));
}


template <class Comparable>
Comparable* BinarySearchTree<Comparable>::
findElement(const Comparable& x) const    // It is built to searching anf finding the element and returning it 
{

    BinaryNode<Comparable>* tmp = privFind(x, root);
    Comparable* mTemp = new Comparable;
    *mTemp = tmp->element;
    return mTemp;
}

/**
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */
template <class Comparable>
BinaryNode<Comparable>*
BinarySearchTree<Comparable>::
privFind(const Comparable& x, BinaryNode<Comparable>* t) const
{
    if (t == NULL)
        return NULL;
    else if (t->element > x)
        return privFind(x, t->left);
    else if (t->element < x)
        return privFind(x, t->right);
    else
        return t;    // Match
}

/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>* t) const
{
    return elementAt(privFindMin(t));
}


/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <class Comparable>
BinaryNode<Comparable>*
BinarySearchTree<Comparable>::privFindMin(BinaryNode<Comparable>* t)
const
{
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return privFindMin(t->left);
}

/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::findMax() const
{
    return elementAt(privFindMax(root));
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <class Comparable>
BinaryNode<Comparable>*
BinarySearchTree<Comparable>::privFindMax(BinaryNode<Comparable>* t)
const
{
    if (t != NULL)
        while (t->right != NULL)
            t = t->right;
    return t;
}

/**
  * Insert x into the tree; duplicates are ignored.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::insert(Comparable& x)
{
    privInsert(x, root);
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::
privInsert(Comparable& x, BinaryNode<Comparable>*& t) const
{
    if (t == NULL) //  create a new node at the right place
        t = new BinaryNode<Comparable>(x, NULL, NULL);
    else if (x < t->element)
        privInsert(x, t->left);  // insert at the left or 
    else if (t->element < x)
        privInsert(x, t->right);  // right subtree
    else
        ;  // Duplicate; do nothing
}

/**
  * Remove x from the tree. Nothing is done if x is not found.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::remove
(Comparable& x)
{
    privRemove(x, root);
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::
privRemove(Comparable& x, BinaryNode<Comparable>*& t)
const
{
    if (t == NULL)

    {
        //cout << "the element that you want to delete is not found" << endl;
        return;
    }   // Item not found; do nothing
    if (x < t->element)
        privRemove(x, t->left);
    else if (t->element < x)
        privRemove(x, t->right);
    else if (t->left != NULL && t->right != NULL) // Two children
    {
        //cout << "buldum " << t->element;
        t->element = findMin(t->right);
        privRemove(t->element, t->right);
    }
    else // one or no children
    {
        BinaryNode<Comparable>* oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}

/**
  * Make the tree logically empty.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
    privMakeEmpty(root);
}

/**
 * Internal method to make subtree empty.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::
privMakeEmpty(BinaryNode<Comparable>*& t) const
{
    if (t != NULL)
    {
        privMakeEmpty(t->left);
        privMakeEmpty(t->right);
        delete t;
    }
    t = NULL;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::
isEmpty() const
{
    return root == NULL;
}




/**
  * Print the tree contents in sorted order.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        privPrintTree(root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::privPrintTree(BinaryNode<Comparable>* t) const
{
    if (t != NULL)
    {

        privPrintTree(t->left);
        cout << t->element << endl;
        privPrintTree(t->right);
    }
}

/**
  * Destructor for the tree.
  */
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    makeEmpty();
}



