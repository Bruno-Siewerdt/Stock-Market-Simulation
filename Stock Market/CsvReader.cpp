#include "CsvReader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> // C++17 necessary

namespace fs = std::filesystem;

std::string CsvReader::readCsvLine(const std::string& ticker, int line) {
    std::ifstream file("./data/" + ticker + "_precos.csv");
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << ticker << "" << "\n";
        return "";
    }

    std::string res = "";
    int currentLine = 0;

    while (std::getline(file, res) && line > currentLine) {
        currentLine++;
    }

    file.close();
	return res;
}

double CsvReader::getMetric(std::string& line) {
	size_t index = line.find(',');
	std::string metric = line.substr(0, index);
	line = line.substr(index + 1);
	return std::stod(metric);
}