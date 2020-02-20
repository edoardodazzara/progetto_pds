//
// Created by Lorenzo Del Sordo on 2020-01-13.
//

#include "Identifier.h"

Identifier::Identifier(int digit, int siteId): digit(digit), siteId(siteId) {}

int Identifier::compareTo(Identifier otherId) {
        if (this->digit < otherId.digit) {
            return -1;
        } else if (this->digit > otherId.digit) {
            return 1;
        } else {
            if (this->siteId < otherId.siteId) {
                return -1;
            } else if (this->siteId > otherId.siteId) {
                return 1;
            } else {
                return 0;
            }
        }

}

int Identifier::getDigit() {return this->digit;}