//
// Created by Lorenzo Del Sordo on 2020-01-13.
//

#ifndef PROGETTO_IDENTIFIER_H
#define PROGETTO_IDENTIFIER_H


class Identifier {
    int digit;
    int siteId;

public:
    Identifier(int digit, int siteId);
    int compareTo(Identifier other);
    int getDigit();
};


#endif //PROGETTO_IDENTIFIER_H
