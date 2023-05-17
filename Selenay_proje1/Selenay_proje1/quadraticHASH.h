
#include <iostream>
#include <string>
#include <vector>


using namespace std;

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

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}
int nextPrime(int n)
{
    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}


// Most of the member functions, HashTable function and their design are taken from "8-Hashtables.pptx" and changed


template <class HashedObj>
class HashTable
{
public:
    explicit HashTable(const HashedObj& notFound, int size = 101);
    HashTable(const HashTable& rhs)
        : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
        array(rhs.array), currentSize(rhs.currentSize) { }

    HashedObj* find( HashedObj& x) const;
    //int hash(const HashedObj& x, int rt);
    void writeStu();
    void makeEmpty();
    void insert( HashedObj& x);
    void remove( HashedObj& x);
    const HashTable& operator=(const HashTable& rhs);
    enum EntryType { ACTIVE, EMPTY, DELETED };
    void printLoadFt();
private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj(),
            EntryType i = EMPTY)
            : element(e), info(i) { }
    };

    vector<HashEntry> array;
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;

    bool isActive(int currentPos) const;
    int findPos( HashedObj& x) const;
    void rehash();

  
};



int hashX(PhoneInfo & key, int tableSize)
{
    int hashVal = 0;
    string keyE = key.name + key.surname;
    for (int i = 0; i < keyE.size(); i++)
        hashVal = 37 * hashVal + keyE[i];

    hashVal = hashVal % tableSize;
    if (hashVal < 0){
        hashVal = hashVal + tableSize;
        }
    return hashVal;
}

/**
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound,
    int size)
    : ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
     currentSize = 0;
}

/**
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
template <class HashedObj>
int HashTable<HashedObj>::findPos( HashedObj& x) const
{
    int collisionNum = 0;
    int currentPos = hashX(x, array.size());
    //cout << "allah allah" << endl;
    //cout << currentPos << endl << array.size() << endl;
    while (array[currentPos].info != EMPTY && x != 
        array[currentPos].element )
    {
        currentPos += pow(++collisionNum, 2);  //add the difference
        if (currentPos >= array.size())              // perform the mod
        {
            currentPos = currentPos - array.size();
        }               // if necessary
        //cout << currentPos << endl;
    }
    return currentPos;
}

/**
  * Return true if currentPos exists and is active.
  */
template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

/**
 * Remove item x from the hash table.
 *  x has to be in the table
 */
template <class HashedObj>
void HashTable<HashedObj>::remove( HashedObj& x)
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
        array[currentPos].info = DELETED;
    //else { cout << "not found" << endl; }
}

/**
 * Find item x in the hash table.
 * Return the matching item, or ITEM_NOT_FOUND, if not found.
 */
template <class HashedObj>
 HashedObj* HashTable<HashedObj>::find( HashedObj& x)
const
{
     
    HashedObj *temp = new HashedObj;
    int currentPos = findPos(x);
    //cout << array[currentPos].element;
    if (isActive(currentPos)) {
        *temp = (array[currentPos].element);
        return temp;
    }
    *temp = ITEM_NOT_FOUND;
    return temp;
}


/**
 * Expand the hash table.
 */
template <class HashedObj>
void HashTable<HashedObj>::rehash()
{
    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize(nextPrime(2 * oldArray.size()));
    for (int j = 0; j < array.size(); j++)
        array[j].info = EMPTY;

    // Copy table over
    currentSize = 0;
    for (int i = 0; i < oldArray.size(); i++)
        if (oldArray[i].info == ACTIVE)
            insert(oldArray[i].element);

    cout << "rehashed..." << endl;
    cout << "previous table size:" << oldArray.size() << ", new table size: " << array.size() << ", current unique word count: " << currentSize << ", current load factor: " << double(currentSize) / array.size() << endl;
}


/**
  * Insert item x into the hash table. If the item is
  * already present, then do nothing.
  */
template <class HashedObj>
void HashTable<HashedObj>::insert( HashedObj& x)
{
    // Insert x as active

    int currentPos = findPos(x);
    if (isActive(currentPos))
        return;
    array[currentPos] = HashEntry(x, ACTIVE);

    // enlarge the hash table if necessary 
    if (++currentSize >= array.size() / 2)
    {
        rehash();
    }
}

template <class HashedObj>
void HashTable<HashedObj>::writeStu()  // I wrote this member function to debug my code
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << "stu of " << i << " is: " << array[i].info <<endl;
    }
}

template <class HashedObj>
void HashTable<HashedObj>::printLoadFt() // it is built to write the result after all hashes are done
{
    cout << "After preprocessing, the unique word count is " << currentSize << ". current load ratio is " << double(currentSize) / array.size() << endl;
}


