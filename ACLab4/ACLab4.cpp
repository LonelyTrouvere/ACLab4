#include <iostream>
#include"BTree.h"

int main()
{
    BTree t(3); // A B-Tree with minimum degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
    t.insert(100);


    int k = 6;
    (t.search(k) != NULL) ? std::cout << "\nPresent" : std::cout << "\nNot Present";

    k = 15;
    (t.search(k) != NULL) ? std::cout << "\nPresent" : std::cout << "\nNot Present";

    k = 17;
    (t.search(k) != NULL) ? std::cout << "\nPresent" : std::cout << "\nNot Present";

    k = 100;
    (t.search(k) != NULL) ? std::cout << "\nPresent" : std::cout << "\nNot Present";

    return 0;
}
