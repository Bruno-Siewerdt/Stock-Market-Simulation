#include "Market.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

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
	const std::string path = "./data";
	try {
		if (fs::exists(path) && fs::is_directory(path)) {
			for (const auto& entry : fs::directory_iterator(path)) {
				std::string fileName = entry.path().filename().string();
				if (fileName.find("_precos") != -1) {
					Stock stock;
					stock.ticker = fileName.substr(0, fileName.find('_'));
					std::string line = CsvReader::readCsvLine(stock.ticker, 1);
					fillMetrics(line, stock);
					stocks.insert(std::pair<std::string, Stock>(stock.ticker, stock));
				}
			}
		}
		else {
			std::cerr << "Error: Data Folder not found\n";
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

void Market::updatePrices() {
	date++;
	for (auto& stock : stocks) {
		std::string line = CsvReader::readCsvLine(stock.first, date+1); // first line is header, date = 0 must read second line
		fillMetrics(line, stock.second);
	}
}

void Market::fillMetrics(std::string line, Stock& stock) {
	// CSV header:
	// Date,Open,High,Low,Close,Volume,Dividends,Stock Splits
	for (int i = 0; i < 8; i++) {
		double metric = CsvReader::getMetric(line);
		switch (i) {
		case 1:
			stock.openPrice = metric;
			break;
		case 2:
			stock.highPrice = metric;
			break;
		case 3:
			stock.lowPrice = metric;
			break;
		case 4:
			stock.closePrice = metric;
			break;
		case 6:
			stock.dividends = metric;
			break;
		default:
			break;
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