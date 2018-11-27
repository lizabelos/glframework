//
// Created by thomas on 13/11/18.
//

#include "System.h"

#include <iostream>

Astronomy::System::System() {

}

void Astronomy::System::add(std::shared_ptr<Astronomy::Astre> astre) {
    mAstres.push_back(astre);
}

std::vector<std::shared_ptr<Astronomy::Astre>> Astronomy::System::getAstres() {
    return mAstres;
}
