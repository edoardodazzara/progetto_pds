#include <iostream>
#include "Char.h"
#include "CRDT.h"
#include "NetworkController.h"


int main() {
    CRDT* alg = new CRDT(1);
    alg->localInsert('a',0);
    std::cout<<alg->text+"\n";
    alg->localInsert('b',1);
    std::cout<<alg->text+"\n";
    alg->localInsert('c',1);
    std::cout<<alg->text+"\n";
    alg->localErase(1);
    std::cout<<alg->text+"\n";
    alg->localErase(0);
    std::cout<<alg->text+"\n";

    Identifier* id1 = new Identifier(3,1);
    std::vector<Identifier*> pos1;
    pos1.push_back(id1);
    Char* ch = new Char(1,alg->counter,pos1,'z');
    alg->remoteInsert(ch);
    std::cout<<alg->text+"\n";

    alg->remoteDelete(ch);
    std::cout<<alg->text+"\n";

    return 0;
}