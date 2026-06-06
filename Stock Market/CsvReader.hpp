/*
 *  Manages the read of csv files
 */

#pragma once

#include <string>

class CsvReader {
private:


public:
	static std::string readCsvLine(const std::string& ticker, int line);
	static double getMetric(std::string& line, std::string divider);
};