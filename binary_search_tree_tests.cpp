#include <iostream>
#include "binary_search_tree.h"

using std::cout;
using std::endl;

int main() {
    std::cout << "BST TESTS" << std::endl;
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(100);
    bst.insert(1);
    bst.insert(50);

    bst.print_tree();


    std::cout << "Min: " <<bst.find_min() << std::endl;
    std::cout << "Max: " <<bst.find_max() << std::endl;

    BinarySearchTree<int> copy = bst;
    BinarySearchTree<int> copy2 = BinarySearchTree<int>(bst);
    bst.make_empty();
    bst.print_tree();
    std::cout<< "Empty: " << bst.is_empty() << std::endl;
    //BinarySearchTree<int> copy = BinarySearchTree<int>(bst);

    copy.print_tree();

    std::cout << "\n";
   
    copy.remove(5);
    copy.remove(100);

    copy.print_tree();
    std::cout << "11?: " << copy.contains(11) << std::endl;
    std::cout << "50?: " << copy.contains(50) << std::endl;
    std::cout << "1?: " << copy.contains(1) << std::endl;

    std::cout << "\n";

    copy2.insert(111);
    copy2.insert(4);
    copy2.insert(77);
    copy2.print_tree();
    


   

    std::cout<<"END" << std::endl;

}
