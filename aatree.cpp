#include <iostream>
#include "aatree.h"
#include "exceptions.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

template <class T>
BinTreeNode<T>::BinTreeNode(const T& x){ 
    data = x; 
    level = 1; 
    left = right = nullptr;
}  

template <class T>
AATree<T>::AATree(bool allowDuplicates){ 
    root = nullptr; 
    numOfNodes = 0;
    this->allowDuplicates = allowDuplicates;
}

template <class T>
void AATree<T>::skew(BinTreeNode<T> *&node){
    // fix case: left child of node is horizontal (same level as parent)
    if(node->left && (node->left->level == node->level)){
        BinTreeNode<T> *newChild = node->left; // left child of node becomes the new child 
        node->left = newChild->right;          // new child's right child becomes node's left child
        newChild->right = node;                // node becomes new child's right child
        node = newChild;
    }
}

template <class T>
void AATree<T>::split(BinTreeNode<T> *&node){
    // fix case: consecutive right horizontal nodes
    if(node->right && node->right->right && (node->right->right->level == node->level)){
        BinTreeNode<T> *newChild = node->right; // right child of node becomes the new child
        node->right = newChild->left;           // new child's left child becomes node's right child
        newChild->left = node;                  // node becomes new child's left child
        newChild->level++;
        node = newChild;
    }
}

template <class T>
bool AATree<T>::search(const T& x) const{
    // search for x in tree
    BinTreeNode<T> *n = root;
    while(n)
        if(x < n->data) n = n->left;
        else if(x > n->data) n = n->right;
        else return true; // found match
    return false;
}

template<class T>
void AATree<T>::insert(BinTreeNode<T> *&currentNode, BinTreeNode<T> *&newNode){
    if (!currentNode){ 
        // found place to insert 
        currentNode = newNode;
        numOfNodes++;
    } 
    else if (newNode->data <= currentNode->data){
        if((newNode->data == currentNode->data) && !allowDuplicates)
            throw DuplicateElementsException("Element " + std::to_string(newNode->data) + " already exists in tree");
        insert(currentNode->left, newNode);
    }
    else insert(currentNode->right, newNode);

    // rebalance the tree
    // perform skew and split at each level from inserted node up to root
    skew(currentNode); 
    split(currentNode);

    //printFormattedTree();
    //std::cout << std::endl;
}

template<class T>
void AATree<T>::insert(const T& x){ 
    BinTreeNode<T> *newNode = new BinTreeNode<T>(x);
    try{
        insert(root, newNode);
    }
    catch(DuplicateElementsException e){
        e.printErrorMessage(e.msg);
        delete newNode;
    }
}

template<class T>
void AATree<T>::remove(BinTreeNode<T> *&currentNode, BinTreeNode<T> *&last, BinTreeNode<T> *&deleted, const T& x){
    if(!currentNode) return;
    last = currentNode;
    // find node to delete
    if(x < currentNode->data){
        remove(currentNode->left, last, deleted, x);
    }
    else{
        deleted = currentNode;
        remove(currentNode->right, last, deleted, x);
    }

    if(currentNode == last && deleted && x == deleted->data){
        // found match...delete node
        deleted->data = currentNode->data;
        deleted = nullptr;
        currentNode = currentNode->right;
        delete last;
        numOfNodes--;
    }
    else if(currentNode->left && currentNode->right && (currentNode->left->level < currentNode->level-1 || currentNode->right->level < currentNode->level-1)){
        // rebalance the tree
        currentNode->level--;
        if(currentNode->level < currentNode->right->level) currentNode->right->level = currentNode->level;
        skew(currentNode);
        skew(currentNode->right);
        skew(currentNode->right->right);
        split(currentNode);
        split(currentNode->right);
    }
}

template<class T>
void AATree<T>::remove(const T& x){
    BinTreeNode<T> *last, *deleted;
    last = deleted = nullptr;
    try{
        if(!search(x)) throw ElementNotFoundException("Can not delete " + std::to_string(x) + "\nIt's not an element of the tree");
        remove(root, last, deleted, x);
    }
    catch(ElementNotFoundException e){
        e.printErrorMessage(e.msg);
    }

    //printFormattedTree();
    //std::cout << std::endl;
}

template<class T>
void AATree<T>::printFormattedTree(BinTreeNode<T> *node, BinTreeNode<T> *parent, int indent) const{
    // output is rotated 90 degrees to the left
    if(!node) return;
    printFormattedTree(node->right, node, indent + 4);
    for(int i=0; i < indent; i++) std::cout << " ";
    if(parent && (node->level == parent->level)) 
        std::cout << ANSI_COLOR_RED << node->data << ANSI_COLOR_RESET << std::endl;
    else
        std::cout << node->data << std::endl;
    printFormattedTree(node->left, node, indent + 4);
}

template<class T>
void AATree<T>::printFormattedTree() const{ 
    std::cout << std::endl;
    printFormattedTree(root, nullptr, 6); 
    std::cout << std::endl;
}

template <class T>
void AATree<T>::postorder(BinTreeNode<T> *node) const{
    if(!node) return;
    postorder(node->left);          // recur on left subtree
    postorder(node->right);         // recur on right subtree
    std::cout << node->data << " "; // print node's data
}

template <class T>
void AATree<T>::postorder() const{
    std::cout << "Postorder: ";
    postorder(root);
    std::cout << std::endl;
}

template <class T>
void AATree<T>::inorder(BinTreeNode<T> *node) const{
    if(!node) return;
    inorder(node->left);            // recur on left subtree
    std::cout << node->data << " "; // print node's data
    inorder(node->right);           // recur on right subtree
}

template <class T>
void AATree<T>::inorder() const{
    std::cout << "Inorder: ";
    inorder(root);
    std::cout << std::endl;
}

template <class T>
void AATree<T>::preorder(BinTreeNode<T> *node) const{
    if(!node) return;
    std::cout << node->data << " "; // print node's data
    preorder(node->left);           // recur on left subtree
    preorder(node->right);          // recur on right subtree
}

template <class T>
void AATree<T>::preorder() const{
    std::cout << "Preorder: ";
    preorder(root);
    std::cout << std::endl;
}

template<class T>
int AATree<T>::getNumOfNodes() const{ return numOfNodes; }

template <class T>
void AATree<T>::destroyTree(BinTreeNode<T> *node){ 
    if(!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

template <class T>
AATree<T>::~AATree(){ destroyTree(root); }
