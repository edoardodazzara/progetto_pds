//
// Created by Lorenzo Del Sordo on 2019-10-02.
//

#ifndef PROGETTO_CHAR_H
#define PROGETTO_CHAR_H


#include <vector>

class Char {

private:
    int siteId;
    int counter;
    std::vector<int> position;
    char value;

public:
    Char(int siteId, int counter, std::vector<int> position, char value);
    int compareTo(Char other);
};


#endif //PROGETTO_CHAR_H
