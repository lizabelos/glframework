//
// Created by thomas on 16/11/18.
//

#include "CSVReader.h"

#include <fstream>
#include <sstream>

std::vector<std::vector<std::string>> CSVReader::read(const std::string &path) {

    std::vector<std::vector<std::string>> result;

    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Can't open " + path);
    }

    std::string line;

    while (getline(file,line))
    {
        std::stringstream ss(line);
        std::vector<std::string> splitted;

        while( ss.good() )
        {
            std::string substr;
            getline( ss, substr, ',' );
            splitted.push_back( substr );
        }

        result.emplace_back(splitted);

    }

    file.close();

    return result;

}