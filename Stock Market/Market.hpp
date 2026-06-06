/*
 *  Simulates Market
 *  Contains a list of Stocks and its prices
 *  The Strategy can buy any of these Stocks
 */ 

#pragma once

#include <string>
#include <unordered_map>

#include "CsvReader.hpp"

#define MEAN_INFLATION 0.08

struct MarketStock {
	double highPrice = 0;
	double lowPrice = 0;
	double openPrice = 0;
	double closePrice = 0;
	double dividends = 0;
	int delayDate = 0; // months since April 1993 until the stock release in the market

	void findDelayDate(std::string strDate);
};

class Market {
private:
	Market();
	~Market();

	int date; // months since Jan 2000
	std::unordered_map<std::string, MarketStock> stocks; // optimize?
	
	void createStocks(); // Read all the existing CSV files and creates structs based on them
	void fillMetrics(std::string line, MarketStock& stock); // Read the line and complete the metrics (prices and dividends)

public:
	static Market& getInstance();

	// avoid cloning
	Market(const Market&) = delete;
	Market& operator=(const Market&) = delete;
	Market(Market&&) = delete;
	Market& operator=(Market&&) = delete;

	void printStocks(); // Prints a table with all the stocks and metrics, used for testing
	bool updatePrices(); // advance one month and update the prices
	bool isStockAvailable(std::string ticker);
	int getAvailableStocksCount(std::vector<std::string> stockList);
	std::string getFormatedDate();
	int getDate();

	double getHighPrice(std::string ticker) const;
	double getLowPrice(std::string ticker) const;
	double getOpenPrice(std::string ticker) const;
	double getClosePrice(std::string ticker) const;
	double getDividends(std::string ticker) const;
};