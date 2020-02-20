//
// Created by Lorenzo Del Sordo on 2019-10-02.
//

#ifndef PROGETTO_CHAR_H
#define PROGETTO_CHAR_H


#include <vector>
#include "Identifier.h"

class Char {

private:
    int siteId;
    int counter;
    std::vector<Identifier*> position;
    char value;

public:
    Char(int siteId, int counter, std::vector<Identifier*> position, char value);
    int compareTo(Char other);
    std::vector<Identifier*> getPos();
    char getValue();
};


#endif //PROGETTO_CHAR_H
