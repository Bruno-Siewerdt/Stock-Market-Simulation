#include "Market.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// ---------------  MarketStock  ----------------

void MarketStock::findDelayDate(std::string strDate) {
	int year = (int)CsvReader::getMetric(strDate, "-");
	int month = (int)CsvReader::getMetric(strDate, "-");
	this->delayDate = (year - 1993) * 12 + (month - 4); // starts on April 1993
}

// ------------------  Market  ------------------

Market::Market() {
	createStocks();
}

Market::~Market() {
	stocks.clear();
}

Market& Market::getInstance() {
	static Market instance;
	return instance;
}

void Market::createStocks() {
	const std::string path = "./data";
	try {
		if (fs::exists(path) && fs::is_directory(path)) {
			for (const auto& entry : fs::directory_iterator(path)) {
				std::string fileName = entry.path().filename().string();
				if (fileName.find("_precos") != -1) {
					MarketStock stock;
					std::string ticker = fileName.substr(0, fileName.find('_'));
					std::string line = CsvReader::readCsvLine(ticker, 1);
					stock.findDelayDate(line.substr(0, line.find(',')));
					fillMetrics(line, stock);
					stocks.insert(std::pair<std::string, MarketStock>(ticker, stock));
				}
			}
		}
		else {
			std::cerr << "Error: Data  Folder not found\n";
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

bool Market::updatePrices() {
	date++;
	bool result = true;
	for (auto& stock : stocks) {
		if (date + 1 - stock.second.delayDate > 0) {
			std::string line = CsvReader::readCsvLine(stock.first, date + 1 - stock.second.delayDate); // first line is header, date = 0 must read second line
			if (line.length() < 2) {
				result = false;
			}
			fillMetrics(line, stock.second);
		}
	}
	return result;
}

void Market::fillMetrics(std::string line, MarketStock& stock) {
	if (line.length() < 2) {
		return;
	}
	// CSV header:
	// Date,Open,High,Low,Close,Volume,Dividends,StockSplits
	for (int i = 0; i < 8; i++) {
		double metric = CsvReader::getMetric(line, ",");
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

bool Market::isStockAvailable(std::string ticker) {
	return date + 1 > stocks[ticker].delayDate;
}

int Market::getAvailableStocksCount(std::vector<std::string> stockList) {
	int res = 0;
	for (std::string ticker : stockList) {
		res += isStockAvailable(ticker);
	}
	return res;
}

std::string Market::getFormatedDate() {
	int month = ((date+3) % 12) + 1;
	return (month < 10 ? "0" : "") + std::to_string(month) + "/" + std::to_string(1993 + date / 12);
}

int Market::getDate() {
	return date;
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

void Market::printStocks() {
	std::cout << "-------------------- " << date%12 << "/" << (2000 + date/12) << " --------------------" << std::endl;
	std::cout << "Ticker | LowPrice | HighPrice | OpenPrice | ClosePrice | Dividends" << std::endl;
	for (auto& stock : stocks) {
		std::cout << stock.first << " | ";
		std::cout << stock.second.lowPrice << " | ";
		std::cout << stock.second.highPrice << " | ";
		std::cout << stock.second.openPrice << " | ";
		std::cout << stock.second.closePrice << " | ";
		std::cout << stock.second.dividends << std::endl;
	}
}