//
// Created by thomas on 14/01/19.
//

#include <iostream>

#include "Parser.h"
#include "../utility/CSVReader.h"

void Astronomy::Parser::readCSV(const std::string &csvPath, std::shared_ptr<Astronomy::Star> &starSystem, std::map<std::string, std::shared_ptr<Astronomy::Astre>> &astres) {

    std::vector<std::vector<std::string>> csv = CSVReader::read(csvPath);

    std::map<std::string, int> entryMap;
    for (int i = 1; i < csv.size(); i++) {
        std::cout << "Property found " << csv[i][0] << std::endl;
        entryMap[csv[i][0]] = i;
    }

    if (entryMap.count("Parent") != 1) throw std::runtime_error("Columns Parent not found");
    if (entryMap.count("Diameter") != 1) throw std::runtime_error("Columns Diameter not found");
    if (entryMap.count("Rotation Period") != 1) throw std::runtime_error("Columns Rotation Period not found");
    if (entryMap.count("Perihelion") != 1) throw std::runtime_error("Columns Perihelion not found");
    if (entryMap.count("Aphelion") != 1) throw std::runtime_error("Columns Aphelion not found");
    if (entryMap.count("Orbital Period") != 1) throw std::runtime_error("Columns Orbital Period not found");
    if (entryMap.count("Orbital Inclination") != 1) throw std::runtime_error("Columns Orbital Inclination not found");
    if (entryMap.count("Orbital Eccentricity") != 1) throw std::runtime_error("Columns Orbital Inclination not found");
    if (entryMap.count("Number of Moons") != 1) throw std::runtime_error("Columns Number of Moons not found");
    if (entryMap.count("Ring System") != 1) throw std::runtime_error("Columns Ring System not found");
    if (entryMap.count("Night Light") != 1) throw std::runtime_error("Columns Night Light not found");
    if (entryMap.count("Texture") != 1) throw std::runtime_error("Columns Texture not found");

    for (int i = 2; i < csv[0].size(); i++) {

        Astronomy::description_t description;

        std::string name = csv[0][i];
        std::cout << "Parsing " << name << std::endl;

        std::string parent = csv[entryMap["Parent"]][i];

        description.diameter = atof(csv[entryMap["Diameter"]][i].c_str());
        description.rotationPeriod = atof(csv[entryMap["Rotation Period"]][i].c_str());
        description.perihelion = atof(csv[entryMap["Perihelion"]][i].c_str()) * 10e6;
        description.aphelion = atof(csv[entryMap["Aphelion"]][i].c_str()) * 10e6;
        description.orbitalPeriod = atof(csv[entryMap["Orbital Period"]][i].c_str());
        description.orbitalInclination = atof(csv[entryMap["Orbital Inclination"]][i].c_str());
        description.orbitalEccentricity = atof(csv[entryMap["Orbital Eccentricity"]][i].c_str());
        description.moonNumber = atoi(csv[entryMap["Number of Moons"]][i].c_str());
        description.ringSystem = csv[entryMap["Ring System"]][i] == "Yes";
        description.nightLight = csv[entryMap["Night Light"]][i] == "Yes";
        description.texture = csv[entryMap["Texture"]][i] == "Yes";

        if (i == 2) {
            starSystem = std::make_shared<Astronomy::Star>(name, description);
            astres[name] = starSystem;
        } else {
            std::shared_ptr<Astronomy::Astre> planet = std::make_shared<Astronomy::Planet>(name, description);
            astres[parent]->getSystem()->add(planet);
            astres[name] = planet;
        }

    }

}