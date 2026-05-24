#include "Market.hpp"

#include <iostream>


Market::Market() {
	createStocks();
}

Market::~Market() {
	stocks.clear();
}

double Market::getHighPrice(std::string ticker) const {
	return stocks.at(ticker).highPrice;
}

double Market::getLowPrice(std::string ticker) const {
	return stocks.at(ticker).lowPrice;
}

double Market::getClosePrice(std::string ticker) const {
	return stocks.at(ticker).closePrice;
}

double Market::getOpenPrice(std::string ticker) const {
	return stocks.at(ticker).openPrice;
}

double Market::getDividends(std::string ticker) const {
	return stocks.at(ticker).dividends;
}

void Market::createStocks() {
	/*Stock stock;
	stock.ticker = "BBAS3";
	stock.closePrice = 10.0;
	stock.openPrice = 9.5;
	stock.highPrice = 11.2;
	stock.lowPrice = 8.6;
	stock.dividends = 0.1;

	stocks.insert(std::pair<std::string, Stock>("BBAS3", stock));*/
	// open stock files
}

void Market::updatePrices() {
	date++;
	for (auto& stock : stocks) {
		std::string line = CsvReader::readCsvLine(stock.first, date+1); // first line is header, date = 0 must read second line
		// CSV header:
		// Date,Open,High,Low,Close,Volume,Dividends,Stock Splits
		for (int i = 0; i < 8; i++) {
			double metric = CsvReader::getMetric(line);
			switch (i) {
			case 1:
				stock.second.openPrice = metric;
				break;
			case 2:
				stock.second.highPrice = metric;
				break;
			case 3:
				stock.second.lowPrice = metric;
				break;
			case 4:
				stock.second.closePrice = metric;
				break;
			case 6:
				stock.second.dividends = metric;
				break;
			default:
				break;
			}
		}
	}
}


void Market::printStocks() {
	std::cout << "Ticker | LowPrice | HighPrice | OpenPrice | ClosePrice | Dividends" << std::endl;
	for (auto& stock : stocks) {
		std::cout << stock.second.ticker << " | ";
		std::cout << stock.second.lowPrice << " | ";
		std::cout << stock.second.highPrice << " | ";
		std::cout << stock.second.openPrice << " | ";
		std::cout << stock.second.closePrice << " | ";
		std::cout << stock.second.dividends << std::endl;
	}
}