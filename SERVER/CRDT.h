//
// Created by Lorenzo Del Sordo on 2019-10-02.
//

#ifndef PROGETTO_CRDT_H
#define PROGETTO_CRDT_H

#include <vector>
#include "Char.h"

class CRDT {

private:
    int siteID;
    std::vector<Char> listChar;

public:
    CRDT(int id);
    void localInsert(char value, int index);
    void localErase(int index);
    void remoteInsert(char value);
    void remoteDelete(char value);

    
};


#endif //PROGETTO_CRDT_H
