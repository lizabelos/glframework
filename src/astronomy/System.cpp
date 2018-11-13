//
// Created by thomas on 13/11/18.
//

#include "System.h"

Astronomy::System::System(std::shared_ptr<Astronomy::Star> star) : mStar(star) {

}

std::shared_ptr<Astronomy::Star> Astronomy::System::getStar() {
    return mStar;
}

void Astronomy::System::add(std::shared_ptr<Astronomy::Astre> &mAstre) {
    mAstres.push_back(mAstre);
}
