#ifndef AATREE_H
#define AATREE_H

template <class T>
class AATree;

template <class T>
class BinTreeNode{
    friend AATree<T>;
private:
    T data;
    int level;
    BinTreeNode<T> *left, *right;
public:
    BinTreeNode(const T& x);
};

template <class T>
class AATree{
private:
    BinTreeNode<T> *root; // pointer to root node
    int numOfNodes;
    bool allowDuplicates;
    void skew(BinTreeNode<T> *&node);
    void split(BinTreeNode<T> *&node);
    void insert(BinTreeNode<T> *&currentNode, BinTreeNode<T> *&newNode);
    void remove(BinTreeNode<T> *&currentNode, BinTreeNode<T> *&last, BinTreeNode<T> *&deleted, const T& x);
    void inorder(BinTreeNode<T> *node) const;
    void preorder(BinTreeNode<T> *node) const;
    void postorder(BinTreeNode<T> *node) const;
    void printFormattedTree(BinTreeNode<T> *node, BinTreeNode<T> *parent, int indent) const;
    void destroyTree(BinTreeNode<T> *node);
public:
    AATree(bool allowDuplicates = false);
    bool search(const T& x) const;
    void insert(const T& x);
    void remove(const T& x);
    void inorder() const;
    void preorder() const;
    void postorder() const;
    void printFormattedTree() const;
    int getNumOfNodes() const;
    ~AATree();
};

class Exception{
public: 
    void printErrorMessage(std::string msg = "Exception");
};

class DuplicateElementsException : public Exception{
public:
    std::string msg;
    DuplicateElementsException(std::string msg = "DuplicateElementsException");
};

class ElementNotFoundException : public Exception{
public:
    std::string msg;
    ElementNotFoundException(std::string msg = "ElementNotFoundException");
};

#endif
