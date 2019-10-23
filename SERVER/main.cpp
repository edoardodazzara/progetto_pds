#include <iostream>
#include "Char.h"

int main() {
    std::vector<int> v1;
    v1.push_back(0);
    Char *c1 = new Char(0,0,v1,'c');
    std::vector<int> v2;
    v2.push_back(1);
    Char *c2 = new Char(1,0,v2,'i');
    int i=c1->compareTo(*c2);
    std::cout<<i;
    return 0;
}