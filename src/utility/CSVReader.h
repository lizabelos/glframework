//
// Created by thomas on 16/11/18.
//

#ifndef SOLAR_SYSTEM_CSVREADER_H
#define SOLAR_SYSTEM_CSVREADER_H

#include <string>
#include <vector>

namespace CSVReader {

    std::vector<std::vector<std::string>> read(const std::string &path);

};


#endif //SOLAR_SYSTEM_CSVREADER_H
