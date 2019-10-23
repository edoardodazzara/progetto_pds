//
// Created by Lorenzo Del Sordo on 2019-10-02.
//

#include "Char.h"


Char::Char(int siteId, int counter, std::vector<int> position, char value):
siteId(siteId), counter(counter),position(position),value(value) {}

/*METHOD compareTo: prende i due Char e confronta le due posizioni
 * Return values: -1 se this<other
 *                0  se this=other
 *                1  se this>other*/
int Char::compareTo(Char other) {
    auto const pos1=this->position;
    auto const pos2=other.position;

    for (int i=0; i<std::min(pos1.size(),pos2.size());i++){
        auto id1=pos1[i];
        auto id2=pos2[i];

        if (id1<id2)
            return -1;
        else if (id1>id2)
            return 1;
    }

    if (pos1.size()<pos2.size()){
        return -1;
    }else {
        if (pos1.size()>pos2.size())
            return 1;
        else
            return 0;
    }
}

