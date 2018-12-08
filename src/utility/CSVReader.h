// Copyright (C) BELOS Thomas. All Rights Reserved.

#ifndef SOLAR_SYSTEM_CSVREADER_H
#define SOLAR_SYSTEM_CSVREADER_H

#include <string>
#include <vector>

namespace CSVReader {

    std::vector<std::vector<std::string>> read(const std::string &path);

};


#endif //SOLAR_SYSTEM_CSVREADER_H
