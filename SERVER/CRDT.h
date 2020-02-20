//
// Created by Lorenzo Del Sordo on 2019-10-02.
//

#ifndef PROGETTO_CRDT_H
#define PROGETTO_CRDT_H

#define RANDOM_STRATEGY 0
#define PLUS_STRATEGY 1
#define MINUS_STRATEGY 2

#include <vector>
#include "Char.h"
#include <math.h>


class CRDT {

private:
    int siteID;
    std::vector<Char*> listChar;

    int strategy;
    int boundary;
    //int counter;
    int base;

public:
    std::string text;
    int counter;
    CRDT(int id);
    void localInsert(char value, int index);
    void localErase(int index);
    void remoteInsert(Char* value);
    void remoteDelete(Char* value);

protected:
    Char* generateChar(char value, int index);
    std::vector<Identifier*> findPosBefore(int index);
    std::vector<Identifier*> findPosAfter(int index);
    std::vector<Identifier*> generatePosBetween(std::vector<Identifier*> pos1, std::vector<Identifier*> pos2,std::vector<Identifier*>& newPos,int level);
    int generateIdBetween(int id1, int id2, int strategy);
    int retrieveStrategy(int level);
    int findInsertIndex(Char ch);
    int findIndexByPosition(Char ch);
};


#endif //PROGETTO_CRDT_H
