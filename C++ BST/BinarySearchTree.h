

#ifndef APR20_BINARY_SEARCH_TREE_BINARYSEARCHTREE_H
#define APR20_BINARY_SEARCH_TREE_BINARYSEARCHTREE_H

#include <iostream>
#include <stack>

// Forward declaration: warn the compiler that there will be a class template
// called BinarySearchTree that we just haven't seen yet. (Basically a function
// prototype for classes.)
// This is needed so that TreeNode can name BinarySearchTree as a friend.
template <typename T>
class BinarySearchTree;

template <typename T>
class BinarySearchTreeIterator;

template <typename T>
class TreeNode
{
private:
    TreeNode<T> *left, *right;
    T value;

    TreeNode(const T &value);

    void print(std::ostream &out, int depth=0) const;

    friend class BinarySearchTree<T>;
    friend class BinarySearchTreeIterator<T>;

    template <typename T2>
    friend std::ostream & operator<<(std::ostream &, BinarySearchTree<T2> &);
};

template <typename T>
class BinarySearchTree
{
private:
    int nodeCount;
    TreeNode<T> *root; // null when the tree is empty

    TreeNode<T> *& locate(TreeNode<T> *&base, const T &value);

public:
    BinarySearchTree();

    int size() const;
    T & add(const T &value); // add() does nothing if the value is already present
                             // (i.e. the tree holds no duplicates)
    bool find(const T &value);
    // void remove(const T &value); // won't do in this class (complicated!)

    BinarySearchTreeIterator<T> begin();
    BinarySearchTreeIterator<T> end();

    friend class BinarySearchTreeIterator<T>;

    template <typename T2>
    friend std::ostream & operator<<(std::ostream &, BinarySearchTree<T2> &);
};

template <typename T>
class BinarySearchTreeIterator
{
private:
    using Iterator = BinarySearchTreeIterator;

    enum class Direction { Left, Mid, Right, Up };
    class TraversalPoint
    {
        TraversalPoint(const TreeNode<T> *n, Direction d) :
            node(n), direction(d)
        {}

        const TreeNode<T> *node;
        Direction direction;

    public:
        bool operator==(const TraversalPoint &other) const
        {
            return node == other.node && direction == other.direction;
        }

        friend class BinarySearchTreeIterator;
    };

    std::stack<TraversalPoint> state;

    BinarySearchTreeIterator(const TreeNode<T> *node);

public:
    Iterator & operator++(); // prefix
    Iterator operator++(int); // postfix
    const T & operator*() const;
    const T * operator->() const;

    bool operator==(const BinarySearchTreeIterator &other) const;
    bool operator!=(const BinarySearchTreeIterator &other) const;

    friend class BinarySearchTree<T>;
};

template <typename T>
std::ostream & operator<<(std::ostream &, BinarySearchTree<T> &);

#include "BinarySearchTree-impl.h"
#include "BinarySearchTreeIterator-impl.h"

#endif //APR20_BINARY_SEARCH_TREE_BINARYSEARCHTREE_H
