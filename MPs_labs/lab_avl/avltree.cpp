/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node*& subroot) {
    subroot->height = 1 + max(heightOrNeg1(subroot->left), heightOrNeg1(subroot->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;
    updateHeight(t);
    t = temp;
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;
    updateHeight(t);
    t = temp;
    updateHeight(t);

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }
    if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) > 1) {
        if (heightOrNeg1(subtree->right->right) > heightOrNeg1(subtree->right->left)) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }
    if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) < -1) {
        if (heightOrNeg1(subtree->left->left) > heightOrNeg1(subtree->left->right)) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    }
    updateHeight(subtree);

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (!subtree) {
        subtree = new Node(key,value);
    }
    if (key < subtree->key) {
        insert(subtree->left,key,value);
    }
    if (key > subtree->key) {
        insert(subtree->right,key,value);
    }
    if (key == subtree->key) {
        subtree->value = value;
        return;
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* x = subtree->left;
            while(x->right) {
                x = x->right;
            }
            subtree->key = x->key;
            subtree->value = x->value;
            remove(subtree->left, x->key);
        } else {
            /* one-child remove */
            // your code here
            Node * temp = (subtree->right == NULL) ? subtree->left : subtree->right;
            *subtree = *temp;
            delete temp;
            temp = NULL;
        }
        // your code here
    }
}
