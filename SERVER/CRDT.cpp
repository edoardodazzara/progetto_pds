//
// Created by Lorenzo Del Sordo on 2019-10-02.
//

#include <iostream>
#include "CRDT.h"

CRDT::CRDT(int id): siteID(id), strategy(RANDOM_STRATEGY),counter(0),boundary(10),base(32),text("") {
    this->listChar.clear();
}

std::vector<Identifier*> CRDT::findPosBefore(int index){
    std::vector<Identifier*> pos;
    if (index != 0){
        pos = this->listChar[index-1]->getPos();
    }else{
        pos.clear();
    }
    return pos;
}

std::vector<Identifier*> CRDT::findPosAfter(int index) {
    std::vector<Identifier*> pos;
    auto len = this->listChar.size();
    if (len < index){
        std::cout<< "Index error";
    }else{
        if (len==index){
            pos.clear();
        }else {
            pos = this->listChar[index]->getPos();
        }
    }
    return pos;
}

int CRDT::retrieveStrategy(int level) {
    int returnStrategy;
    switch (this->strategy){
        case RANDOM_STRATEGY:
            returnStrategy = round(random())==0 ? PLUS_STRATEGY : MINUS_STRATEGY;
            break;
        default:
            returnStrategy = this->strategy;
            break;
    }
    return returnStrategy;
}

int CRDT::generateIdBetween(int id1, int id2, int strategy) {
    if ((id2 - id1) < this->boundary) {
        id1 = id1 + 1;
    } else {
        if (strategy == MINUS_STRATEGY) {
            id1 = id2 - this->boundary;
        } else {
            id1 = id1 + 1;
            id2 = id1 + this->boundary;
        }
    }
    return floor(random()%(id2-id1))+id1;
}


std::vector<Identifier*> CRDT::generatePosBetween(std::vector<Identifier*> pos1, std::vector<Identifier*> pos2, std::vector<Identifier*>& newPos,int level) {
    int strategy = retrieveStrategy(level);
    Identifier* id1;
    Identifier* id2;
    auto base = pow(2, level)*this->base;

    if (pos1.size()!=0) {
        id1 = pos1[0];
    }else{
        id1 = new Identifier(0,this->siteID);
    }
    if (pos2.size()!=0) {
        id2 = pos2[0];
    }else{
        id2 = new Identifier(base,this->siteID);
    }
    auto difference = id2->getDigit() - id1->getDigit();

    if (difference > 1){
        int newDigit = generateIdBetween(id1->getDigit(),id2->getDigit(),strategy);
        newPos.push_back(new Identifier(newDigit,this->siteID));
        return newPos;
    } else if (difference == 1){
        newPos.push_back(id1);
        pos1.erase(pos1.cbegin());
        pos2.clear();
        return this->generatePosBetween(pos1, pos2, newPos,level+1);
    }else if(difference == 0){
        newPos.push_back(id1);
        pos1.erase(pos1.cbegin());
        pos2.erase(pos2.cbegin());
        return this->generatePosBetween(pos1, pos2, newPos,level+1);
    }
}

Char* CRDT::generateChar(char value,int index){
    std::vector<Identifier*> pos1 = findPosBefore(index);
    std::vector<Identifier*> pos2 = findPosAfter(index);
    std::vector<Identifier*> newPos;
    newPos.clear();
    std::vector<Identifier*> newPos1 = generatePosBetween(pos1,pos2,newPos,0);

    return new Char(this->siteID,this->counter++,newPos1,value);
}

int CRDT::findInsertIndex(Char ch) {
    int left = 0;
    int right = this->listChar.size()-1;
    int mid;
    int compareNum;

    if((this->listChar.size()==0) || (ch.compareTo(*this->listChar[left])) < 0){
        return left;
    }else if(ch.compareTo(*this->listChar[right])>0){
        return right+1;
    }

    while (left + 1 < right) {
        mid = floor(left + (right - left) / 2);
        compareNum = ch.compareTo(*this->listChar[mid]);

        if (compareNum == 0) {
            return mid;
        } else if (compareNum > 0) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return ch.compareTo(*this->listChar[left]) == 0 ? left : right;
}

int CRDT::findIndexByPosition(Char ch) {
    int left = 0;
    int right = this->listChar.size() - 1;
    int mid, compareNum;

    if (this->listChar.size()==0) {
        std::cout<<"Character does not exist in CRDT";
    }

    while (left + 1 < right) {
        mid = floor(left + (right - left) / 2);
        compareNum = ch.compareTo(*this->listChar[mid]);

        if (compareNum == 0) {
            return mid;
        } else if (compareNum > 0) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (ch.compareTo(*this->listChar[left]) == 0) {
        return left;
    } else if (ch.compareTo(*this->listChar[right]) == 0) {
        return right;
    } else {
        std::cout<<"Character does not exist in CRDT.";
    }
}


void CRDT::localInsert(char value, int index) {
    Char* character = generateChar(value,index);
    this->listChar.insert(listChar.cbegin()+index,character);
    this->text.insert(text.cbegin()+index, character->getValue());
}

void CRDT::localErase(int index) {
    this->listChar.erase(listChar.cbegin()+index);
    this->text.erase(text.cbegin()+index);
}

void CRDT::remoteInsert(Char* value) {
    int index = findInsertIndex(*value);
    this->listChar.insert(listChar.cbegin()+index,value);
    this->text.insert(text.cbegin()+index, value->getValue());
}

void CRDT::remoteDelete(Char* value) {
    int index = findIndexByPosition(*value);
    this->listChar.erase(this->listChar.cbegin()+index);
    this->text.erase(this->text.cbegin()+index);
}





