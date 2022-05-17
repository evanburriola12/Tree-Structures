#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>



template <typename Comparable>
class BinarySearchTree {
private:
    struct Node{
        Comparable data;
        Node* lPtr;
        Node* rPtr;

        Node(Comparable val):data(val),lPtr(nullptr),rPtr(nullptr){};
        Node(Comparable val, Node* lt, Node* rt):data(val),lPtr(lt),rPtr(rt){};
    };
    Node* root;

    void insert(const Comparable& value, Node*& p){//By ref to update data of pointers
        if(p == nullptr){ //base case
            p = new Node(value);
            return;
        }
        //if less than cur node, insert to left
        if(value < p->data){
            insert(value, p->lPtr);
        }else if (value > p->data){ //if greater than cur node, insert to right
            insert(value, p->rPtr);
        }
        //if equal, do nothing - no dupes

        //Do something to height here in AVL
    }

    Node* find_min(Node* p) const{ //recursive version of find min, utility in remove function
        if(p == nullptr)
            return nullptr;
        if(p->lPtr == nullptr)
            return p;
        return find_min(p->lPtr); //navigate to left most node
    }


    //depth is default 0(root position)
    void print_tree(std::ostream& os, Node* p, unsigned int depth = 0) const { 
        if(p == nullptr){
            return;
        }

    //For each recursive call, increment the depth. This indicates a traversal to a deeper level
        print_tree(os,p->rPtr,depth+1);
        //After all of the right elements have been traversed, insert depth amount of double spaces into the stream
        for(unsigned int i = 0; i < depth; i++)
            os << "  ";
        os << p->data << std::endl; //output data
        print_tree(os,p->lPtr,depth+1)   ; //traverse left side of tree, incrementing depth
    }

    void make_empty(Node* p){
        if(p != nullptr){
            make_empty(p->lPtr); //navigate down all left branches
            make_empty(p->rPtr); //navigate down all right branches
            delete p; 
        }
        p = nullptr;
    }

    Node* copyTree(Node* toCopy) const{
        if(toCopy == nullptr){
            return nullptr;
        } else{
            return new Node(toCopy->data,copyTree(toCopy->lPtr),copyTree(toCopy->rPtr)); //utilizes Node constructor that defines data, left tree, and right tree
        }
    }

    void remove(const Comparable& val, Node*& p){
        if(p == nullptr)
            return;
        if(val < p->data) 
            remove(val, p->lPtr); //target value is less than the current nodes data, navigate left
        else if(p->data < val)
            remove(val, p->rPtr); //target value is greater than the current nodes data, navigate right
        else if(p->lPtr != nullptr && p->rPtr != nullptr){ //Both left and right children exist
            p->data = find_min(p->rPtr)->data; //replace data of this node with the smallest data of right subtree 
            remove(p->data,p->rPtr); //delete that node.
        } else{
            Node* old = p;
            p = (p->lPtr != nullptr) ? p->lPtr : p->rPtr; //reassign to the one existing child pointer (slide up into olds position)
            delete old;
        }
    }

public:
    BinarySearchTree():root(nullptr){}
    BinarySearchTree(const BinarySearchTree& other){
        root = copyTree(other.root); //simply call copyTree function with others root. Assign the returned pointer that links the tree to root
    }
    ~BinarySearchTree(){ make_empty(); };
    BinarySearchTree& operator=(const BinarySearchTree& other){
        if(&other != this){ //prevent self-assignment
            make_empty(); //empty any previous data
            root = copyTree(other.root); //same as copy constructor
        }
        return *this;

    }
    bool contains(const Comparable& value) const{ //Iterative function to find if a node is contained 
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

    };
    void insert(const Comparable& value){
        insert(value,root);
    }
    void remove(const Comparable& value){
        remove(value, root);
    }
    const Comparable& find_min() const{ //Iterative function to find the minimum value in a tree
        if(is_empty()){
            std::cout << "Empty" << std::endl;
        }
        Node* cur = root;
        Node* prev;
        while(cur != nullptr){ //Moves to the left until the target node is nullptr
            prev = cur;
            cur = cur->lPtr;
        }
        return prev->data; //Since the target is nullptr, the last leftmost node with data is the smallest
    }
    const Comparable& find_max() const{ //Iterative function to find the max value
        if(is_empty()){
            std::cout << "Empty" << std::endl;
        }
        Node* cur = root;
        Node* prev;
        while(cur != nullptr){ //Move to the right until nullptr
            prev = cur;
            cur = cur->rPtr;
        }
        return prev->data; //previous pointer points to the max node
    }
    void print_tree(std::ostream& os=std::cout) const{
        if(is_empty())
            os << "<empty>\n"; //Empty tree case
        print_tree(os, root); //Even on empty case, doesn't print
    }
    bool is_empty() const{return root == nullptr;};
    void make_empty(){
        if(!is_empty()){ //Check that tree isn't empty
            make_empty(root); //call recursive function
            root = nullptr; //assign root to nullptr
        }
    };
};

#endif
