#include <iostream>
#include "avl_tree.h"

using std::cout;
using std::endl;

int main() {
    std::cout << "AVL TESTS" << std::endl;
    AVLTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(100);
    bst.insert(1);
    bst.insert(50);

    bst.print_tree();


    std::cout << "Min: " <<bst.find_min() << std::endl;
    std::cout << "Max: " <<bst.find_max() << std::endl;

    AVLTree<int> copy = bst;
    AVLTree<int> copy2 = AVLTree<int>(bst);
    bst.make_empty();
    bst.print_tree();
    std::cout<< "Empty: " << bst.is_empty() << std::endl;

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
        std::cout << "\n Rotation tests on insert/removal \n";


    AVLTree<int> rotTester;
    rotTester.insert(5);
    rotTester.insert(7);
    rotTester.insert(10);

    rotTester.print_tree();
    std::cout << "\n";

    rotTester.insert(3);
    rotTester.insert(4);
    rotTester.insert(9);

    rotTester.print_tree();
    std::cout << "\n resetting \n";

    rotTester.make_empty();

    rotTester.insert(5);
    rotTester.insert(7);
    rotTester.insert(4);
    rotTester.print_tree();
    std::cout << "\n";
    rotTester.insert(6);
    rotTester.insert(10);
    rotTester.insert(11);
    rotTester.print_tree();
    std::cout << "\n";
    rotTester.insert(20);
    rotTester.insert(19);

    rotTester.print_tree();
    std::cout << "\n";

    rotTester.remove(7);

    rotTester.print_tree();
    std::cout << "\n";

    rotTester.remove(20);
    rotTester.remove(19);
    rotTester.remove(11);

    rotTester.print_tree();
    std::cout << "\n";

    std::cout << "\n resetting \n";

    rotTester.make_empty();

    rotTester.insert(5);
    rotTester.insert(7);
    rotTester.insert(6);
    rotTester.print_tree();
    std::cout << "\n";
    rotTester.remove(6);
    rotTester.print_tree();
    std::cout << "\n";
    rotTester.remove(7);
    rotTester.remove(5);
    rotTester.print_tree();
    std::cout << "\n";



    
    std::cout<<"END" << std::endl;
}
