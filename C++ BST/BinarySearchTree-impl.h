
#ifndef APR20_BINARY_SEARCH_TREE_BINARYSEARCHTREE_IMPL_H_H
#define APR20_BINARY_SEARCH_TREE_BINARYSEARCHTREE_IMPL_H_H

#include "BinarySearchTree.h"

template <typename T>
TreeNode<T>::TreeNode(const T &value) :
    left(nullptr),
    right(nullptr),
    value(value)
{}

template <typename T>
void TreeNode<T>::print(std::ostream &out, int depth) const
{
    auto printBars = [&](int count)
    {
        for (int i = 0; i < count - 1; ++i)
            out << "   ";
        if (count > 0)
            out << "-> ";
    };

    auto printChild = [&](const TreeNode *child)
    {
        if (child == nullptr)
        {
            printBars(depth + 1);
            out << std::endl;
        }
        else
            child->print(out, depth + 1);
    };

    printBars(depth);
    out << value << std::endl;

    if (left != nullptr || right != nullptr)
    {
        // This is an internal node
        printChild(left);
        printChild(right);
    }
}

template <typename T>
TreeNode<T> *& BinarySearchTree<T>::locate(TreeNode<T> *&base, const T &value)
{
    if (base == nullptr
            || base->value == value)
        return base;
    else if (value < base->value)
        return locate(base->left, value);
    else // value > base->value
        return locate(base->right, value);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree() :
    nodeCount(0),
    root(nullptr)
{}

template <typename T>
int BinarySearchTree<T>::size() const
{
    return nodeCount;
}

template <typename T>
T & BinarySearchTree<T>::add(const T &value)
{
    TreeNode<T> *&nodePointer = locate(root, value);
    if (nodePointer == nullptr)
    {
        // It's not presently in the tree - add it
        nodePointer = new TreeNode<T>(value);
        ++nodeCount;
    }

    return nodePointer->value;
}

template <typename T>
bool BinarySearchTree<T>::find(const T &value)
{
    return (locate(root, value) != nullptr);
}

template <typename T>
BinarySearchTreeIterator<T> BinarySearchTree<T>::begin()
{
    return BinarySearchTreeIterator<T>(root);
}

template <typename T>
BinarySearchTreeIterator<T> BinarySearchTree<T>::end()
{
    return BinarySearchTreeIterator<T>(nullptr);
}

template <typename T>
std::ostream & operator<<(std::ostream &out, BinarySearchTree<T> &tree)
{
    if (tree.root == nullptr)
        return out;
    else
    {
        tree.root->print(out);
        return out;
    }
}

#endif //APR20_BINARY_SEARCH_TREE_BINARYSEARCHTREE_IMPL_H_H
