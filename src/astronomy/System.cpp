//
// Created by thomas on 13/11/18.
//

#include "System.h"

#include <iostream>

Astronomy::System::System(std::shared_ptr<Astronomy::Star> star) : mStar(star) {

}

std::shared_ptr<Astronomy::Star> Astronomy::System::getStar() {
    return mStar;
}

void Astronomy::System::add(std::shared_ptr<Astronomy::Astre> astre) {
    mAstres.push_back(astre);
}

std::vector<std::shared_ptr<Astronomy::Astre>> Astronomy::System::getAstres() {
    return mAstres;
}

std::vector<std::shared_ptr<Astronomy::Astre>> Astronomy::System::getAll() {
    std::vector<std::shared_ptr<Astronomy::Astre>> result = std::vector<std::shared_ptr<Astronomy::Astre>>(mAstres);
    result.emplace_back(mStar);
    return result;
}
