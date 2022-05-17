#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cstddef>
#include <iostream>
//NOTES!
//If height dif (balance) positive - left skewed(bigger)
//if balance factor negative - right skewed(bigger) 
//Balances (-1,0,1)

//If not balanced -> rotation. When rotate left, use right child at imbalance
//given 15->r20->r25, single rotate l 20->l15->25r

//Rotate right, with left child

//Double left rotation. rotate child right, then rotate entire left
//Balance factor at node we are rotating (if left skewed - double rotate) (if right skewed- single rotate)
//balance factor created from heights each node

//After insert, update heights.
//Find possible imbalance
//if (< -1) -> rotate left
// 
// if( > 1) -> rotate right
//
//Only touch 3 pointers in rotation
//Left skew of right child, double rotate 


template <typename Comparable>
class AVLTree {
private:
    struct Node{
        Comparable data;
        Node* lPtr;
        Node* rPtr;
        int height;

        Node(Comparable val, Node* lt, Node* rt, int h = 0):data(val),lPtr(lt),rPtr(rt),height(h){};
        //Node(Comparable val, Node* lt, Node* rt):data(val),lPtr(lt),rPtr(rt){};
    };

    Node* root;

        //depth is default 0(root position)
    void print_tree(std::ostream& os, Node* p, unsigned int depth = 0) const { 
        if(p == nullptr){
            return;
        }
       //Reverse in order for print format

        //For each recursive call, increment the depth. This indicates a traversal to a deeper level
        print_tree(os,p->rPtr,depth+1);
        //After all of the right elements have been traversed, insert depth amount of double spaces into the stream
        for(unsigned int i = 0; i < depth; i++)
            os << "  ";
        os << p->data << std::endl; //output data
        print_tree(os,p->lPtr,depth+1)   ; //traverse left side of tree, incrementing depth
    }
    Node* find_min(Node* p) const{ //recursive function to find minimum
        if(p == nullptr)
            return nullptr;
        if(p->lPtr == nullptr)
            return p;
        return find_min(p->lPtr); //recurse to left most node
    }

    int height(Node* p) const{
        return p == nullptr ? -1 : p->height; //Ternary that returns -1 if nullptr, otherwise member height (states that height scale of 1 node beneath current = 0 NOT 1)
    }

    void insert(const Comparable& value, Node*& p){ //SAME AS BST!
        if(p == nullptr)
            p = new Node(value, nullptr,nullptr);
        else if(value < p->data)
            insert(value,p->lPtr);
        else if (p->data < value)
            insert(value, p->rPtr);

        balance(p); //Added balance check at the end of insert!
    }

    void remove(const Comparable& val, Node*& p){ //SAME AS BST!
        if(p == nullptr)
            return;
        if(val < p->data)
            remove(val, p->lPtr);
        else if(p->data < val)
            remove(val, p->rPtr);
        else if(p->lPtr != nullptr && p->rPtr != nullptr){
            p->data = find_min(p->rPtr)->data;
            remove(p->data,p->rPtr);
        } else{
            Node* old = p;
            p = (p->lPtr != nullptr) ? p->lPtr : p->rPtr;
            delete old;
        }

        balance(p); //Added balance check at the end of removal!
    }

    Node* copyTree(Node* toCopy) const{
        if(toCopy == nullptr){
            return nullptr;
        } else{
            return new Node(toCopy->data,copyTree(toCopy->lPtr),copyTree(toCopy->rPtr),toCopy->height); //utilizes Node constructor that defines data, left tree, right tree, and height
        }
    }

    void make_empty(Node* p){ //SAME AS BST!
        if(p != nullptr){
            make_empty(p->lPtr);
            make_empty(p->rPtr);
            delete p;
        }
        p = nullptr;
    }

    void singleLeft(Node*& parent){//Left rotation! occurs during RIGHT skew!!
        Node* child = parent->rPtr; //Child defined in terms of the parent node (rPtr because right skew!)
        parent->rPtr = child->lPtr; //Redefine the right pointer of the parent to the left pointer of the child to maintain balance
        child->lPtr = parent; //Child now puts parent at lPtr, Parent will ALWAYS be less than child in this case
        parent->height = max(height(parent->lPtr),height(parent->rPtr)) +1; //recalc heights
        child->height = max(parent->height,height(child->rPtr)) +1; 
        parent = child; //The child is now in the parent position
    }

    void singleRight(Node*& parent){//Occurs during LEFT SKEW!
        Node* child = parent->lPtr; //imbalance
        parent->lPtr = child->rPtr; // make parents left childs left
        child->rPtr = parent; // child right becomes the parent(parent is always greater than child)
        parent->height = max(height(parent->lPtr),height(parent->rPtr)) +1; //recalc heights
        child->height = max(height(child->lPtr),parent->height) +1;
        parent = child; // child is now the parent node
    }

    void doubleLeft(Node*& parent){
        singleRight(parent->rPtr); //Rotate elbow out into straight
        singleLeft(parent); //Rotate the straight into balance
    }
    void doubleRight(Node*& parent){ //Symmetrical!
        singleLeft(parent->lPtr); //Rotate elbow out into straight
        singleRight(parent); //Rotate the straight into balance
    }

    int max(int a, int b){ //helper
        return a >= b ? a : b; //Ternary to return the max of two ints
    }

    const int BAL_FACT = 1; //Parameterized balance factor
    void balance(Node*& p){
        if(p == nullptr)
            return;

        if(std::abs(height(p->lPtr) - height(p->rPtr)) > BAL_FACT){ // Determine imbalance!
             if(height(p->lPtr) - height(p->rPtr) > 0) {//Left Heavy
                if(height(p->lPtr->lPtr) >= height(p->lPtr->rPtr)) //Determine children skewedness to perform appropriate rotation
                    singleRight(p);
                else
                    doubleRight(p);
            }else if(height(p->lPtr) - height(p->rPtr) < 0){ //Right heavy
            if(height(p->rPtr->rPtr) >= height(p->rPtr->lPtr)) //Determine children skewedness to perform appropriate rotation
                singleLeft(p);
            else
                doubleLeft(p);
            }
        }
        p->height = max(height(p->lPtr),height(p->rPtr)) + 1; //Recalculate height
    }

public:
    AVLTree():root(nullptr){};
    AVLTree(const AVLTree& other){
        root = copyTree(other.root);
    }
    ~AVLTree(){ make_empty(); };
    AVLTree& operator=(const AVLTree& other){ //Same as BST
        if(&other != this){
            make_empty();
            root = copyTree(other.root);
        }
        return *this;
    }
    bool contains(const Comparable& value) const{ //Same as BST
        if(is_empty()){
            std::cout << "Empty" << std::endl;
            return false;
        }
        Node* cur = root;

        while(cur != nullptr){
            if(cur->data == value){ //Target hit, return true
                return true;
            } else if (cur->data > value){ //Target is less than current, move left
                cur = cur->lPtr;
            } else{ //Alternatively move right
                cur = cur->rPtr;
            }
        }
        return false; //Tree is not empty, but value DNE
    }
    void insert(const Comparable& value){
        insert(value,root);
    }
    void remove(const Comparable& value){
        remove(value,root);
    }
    const Comparable& find_min() const{ //Same as BST Iterative traversal to left most node
        if(is_empty()){
            std::cout << "Empty" << std::endl;
        }
        Node* cur = root;
        Node* prev;
        while(cur != nullptr){
            prev = cur;
            cur = cur->lPtr;
        }
        return prev->data;
    }
    const Comparable& find_max() const{//Same as BST Iterative traversal to right most node
        if(is_empty()){
            std::cout << "Empty" << std::endl;
        }
        Node* cur = root;
        Node* prev;
        while(cur != nullptr){
            prev = cur;
            cur = cur->rPtr;
        }
        return prev->data;
    }
    void print_tree(std::ostream& os=std::cout) const{ //Same as BST
        if(is_empty())
            os << "<empty>\n";
        print_tree(os,root);
    };
    bool is_empty() const{return root == nullptr;};
    void make_empty(){ //Same as BST
        if(!is_empty()){
            make_empty(root);
            root = nullptr;
        }
    };

    // optional
    // AVLTree(AVLTree&& other);
    // AVLTree& operator=(AVLTree&& other);
    // void insert(Comparable&& value);
};

#endif
