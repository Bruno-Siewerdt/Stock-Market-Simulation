/*
 *  Simulates Market
 *  Contains a list of Stocks and its prices
 *  The Strategy can buy any of these Stocks
 */ 

#pragma once

#include <string>
#include <map>

#include "CsvReader.hpp"

struct Stock {
	std::string ticker;
	double highPrice;
	double lowPrice;
	double openPrice;
	double closePrice;
	double dividends;
};

class Market {
private:
	int date; // months since Jan 2000
	std::map<std::string, Stock> stocks; // optimize?
	
	
	void createStocks(); // Read all the existing CSV files and creates structs based on them
	bool fillMetrics(std::string line, Stock& stock); // Read the line and complete the metrics (prices and dividends)

public:
	Market();
	~Market();

	void printStocks(); // Prints a table with all the stocks and metrics, used for testing
	bool updatePrices(); // advance one month and update the prices

	double getHighPrice(std::string ticker) const;
	double getLowPrice(std::string ticker) const;
	double getOpenPrice(std::string ticker) const;
	double getClosePrice(std::string ticker) const;
	double getDividends(std::string ticker) const;
};