// BSTSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"


template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Initializes a new BSTSet whose contents are moved from an
    // expiring one.
    BSTSet(BSTSet&& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);

    // Assigns an expiring BSTSet into another.
    BSTSet& operator=(BSTSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:

    struct TreeNode
    {
        T key;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
    }; 

    TreeNode *root;
    int treeSize;

    void copy(TreeNode &current, TreeNode &other);
    void insert(TreeNode *node, const T& element);
    bool search(TreeNode *node, const T& element) const;
};


template <typename T>
BSTSet<T>::BSTSet() //COMPLETE
    :root(nullptr), treeSize(0)
{
}


template <typename T>
BSTSet<T>::~BSTSet()
{
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
    :root((s.root)), treeSize(s.size()) 
{
}


template <typename T>
BSTSet<T>::BSTSet(BSTSet&& s)
{
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    return *this;
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(BSTSet&& s)
{
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const //COMPLETE
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element) //COMPLETE
{
    if (root == nullptr)
    {
        root = new TreeNode;
        root->key = element;
        treeSize++;
        return;
    }

    insert(root, element);
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const //COMPLETE
{
    return search(root, element);
}


template <typename T>
unsigned int BSTSet<T>::size() const //COMPLETE
{
    return treeSize;
}

//HELPER FUNCTIONS----------------------------------------
template <typename T>
void BSTSet<T>::insert(TreeNode *node, const T& element)
{
    if (element == node->key)
        return;

    if (element < node->key)
    {
        if (node->left != nullptr)
            insert(node->left, element);
        else
        {
            node->left = new TreeNode;
            node->left->key = element;
            treeSize++;
            return;
        }
    }

    else
    {
        if(node->right != nullptr)
            insert(node->right, element);
        else
        {
            node->right = new TreeNode;
            node->right->key = element;
            treeSize++;
            return;
        }
    }
}


template <typename T>
bool BSTSet<T>::search(TreeNode *node, const T& element) const
{
    if (element == node->key)
        return true;

    if (element < node->key)
    {
        if (node->left != nullptr)
            return search(node->left, element);
        else
            return false;
    }

    else 
    {
        if (node->right != nullptr)
            return search(node->right, element);
        else
            return false;
    }
}


template <typename T>
void BSTSet<T>::copy(TreeNode &current, TreeNode &other)
{
    /*if (other == nullptr)
    {
        root = nullptr;
        return;
    }*/    
}


#endif // BSTSET_HPP

