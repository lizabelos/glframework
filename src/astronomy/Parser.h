//
// Created by thomas on 14/01/19.
//

#ifndef SOLAR_SYSTEM_PARSER_H
#define SOLAR_SYSTEM_PARSER_H

#include <memory>
#include <map>

#include "Star"
#include "Planet"

namespace Astronomy {

    namespace Parser {

        void readCSV(const std::string &csvPath, std::shared_ptr<Astronomy::Star> &starSystem, std::map<std::string, std::shared_ptr<Astronomy::Astre>> astres);

    };

}


#endif //SOLAR_SYSTEM_PARSER_H
