#include "CsvReader.hpp"


std::string CsvReader::readCsvLine(const std::string& file, int line) {
	 // ler linha específica do CSV
	return "";
}

double CsvReader::getMetric(std::string& line) {
	size_t index = line.find(',');
	std::string metric = line.substr(0, index);
	line = line.substr(index + 1);
	return std::stod(metric);
}