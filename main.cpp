#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "There is no path to a config file. Use the command like this:\n\t\t authority <PATH TO CONFIG>" << std::endl;
        exit(1);
    } else if (argc > 2) {
        std::cout << "More than the expected amount of arguments given. Taking " << argv[1] << "as the config path" << std::endl;
    }

    std::string configFile = argv[1];
    std::vector<std::string> lines;

    std::ifstream reader;
    reader.open(configFile, std::ios_base::in);
    if (reader.rdstate() == std::fstream::failbit) {
        std::cerr << "Encountered an error when attempting to read the file. Is the path correct?" << std::endl;
        exit(1);
    }

    uint32_t lineCounter = 0;
    std::string tmp;
    while(getline(reader, tmp)) {
        lines.push_back(tmp);
        tmp = "";
        lineCounter++;
    }

    reader.close();
    if (reader.rdstate() == std::fstream::failbit) {
        std::cerr << "Encountered an error when attempting to close the file." << std::endl;
        exit(1);
    }

    std::cout << "Read " << lineCounter << " lines" << std::endl;

    if (lineCounter > 0) {
        std::mt19937 rng(std::hash<uint32_t>{}(clock()));
        uint32_t r = rng();
        auto selected = static_cast<uint32_t>((static_cast<uint64_t>(r) * static_cast<uint64_t>(lineCounter)) >> 32);

        std::ranges::transform(lines[selected], lines[selected].begin(), [](auto c) {return std::toupper(c);});
        std::cout << "YOU SHOULD DO: \n\n\t\t" << lines[selected] << std::endl << std::endl;
    }
}