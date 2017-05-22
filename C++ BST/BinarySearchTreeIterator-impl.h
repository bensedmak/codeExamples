
#ifndef APR20_BINARY_SEARCH_TREE_BINARYSEARCHTREEITERATOR_IMPL_H
#define APR20_BINARY_SEARCH_TREE_BINARYSEARCHTREEITERATOR_IMPL_H

#include "BinarySearchTree.h"

template <typename T>
BinarySearchTreeIterator<T>::BinarySearchTreeIterator(const TreeNode<T> *node)
{
    if (node)
    {
        if (node->left)
            state.push(TraversalPoint(node, Direction::Left));
        else
            state.push(TraversalPoint(node, Direction::Mid));
        ++*this;
    }
}

template <typename T>
BinarySearchTreeIterator<T> & BinarySearchTreeIterator<T>::operator++()
{
    while (state.size())
    {
        auto &top = state.top();
        auto node = top.node;

        if (top.direction == Direction::Left)
        {
            top.direction = Direction::Mid;
            if (node->left)
                state.push(TraversalPoint(node->left, Direction::Left));
        }
        else if (top.direction == Direction::Mid)
        {
            top.direction = Direction::Right;
            break;
        }
        else if (top.direction == Direction::Right)
        {
            top.direction = Direction::Up;
            if (node->right)
                state.push(TraversalPoint(node->right, Direction::Left));
        }
        else if (top.direction == Direction::Up)
            state.pop();
    }

    return *this;
}

template <typename T>
BinarySearchTreeIterator<T> BinarySearchTreeIterator<T>::operator++(int)
{
    auto copy = *this;
    ++*this;
    return copy;
}

template <typename T>
const T & BinarySearchTreeIterator<T>::operator*() const
{
    return state.top().node->value;
}

template <typename T>
const T * BinarySearchTreeIterator<T>::operator->() const
{
    return &(state.top().node->value);
}

template <typename T>
bool BinarySearchTreeIterator<T>::operator==(const BinarySearchTreeIterator &other) const
{
    return state == other.state;
}

template <typename T>
bool BinarySearchTreeIterator<T>::operator!=(const BinarySearchTreeIterator &other) const
{
    return !(*this == other);
}

#endif
