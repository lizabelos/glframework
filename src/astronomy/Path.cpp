//
// Created by thomas on 10/01/19.
//

#include "Path.h"

Astronomy::TimePath::TimePath() {
    time = Maths::make_SVariable();
}

Astronomy::AnglePath::AnglePath() {
    angle = Maths::make_SVariable();
}

Astronomy::PathScale::PathScale() {
    param = Maths::make_SVariable();
}
