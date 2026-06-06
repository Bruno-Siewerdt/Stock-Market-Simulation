#include "Wallet.hpp"

#include <iostream>

Wallet::Wallet() {

}

void Wallet::buyStock(const std::string& ticker, const int quantity, const double price) {
	if (quantity == 0) return;
	if (stocks.count(ticker) == 0) { // doesn't exist
		WalletStock stock;
		stocks.insert(std::pair<std::string, WalletStock>(ticker, stock));
	}
	investedMoney += (double)quantity * price;
	stocks[ticker].meanPrice = (stocks[ticker].meanPrice * (double)stocks[ticker].quantity + price * (double)quantity) / (double)(stocks[ticker].quantity + quantity);
	stocks[ticker].quantity += quantity;
}

int Wallet::getStockQuantity(std::string ticker) {
	return stocks[ticker].quantity;
}

double Wallet::getWalletValue() {
	double sum = 0;
	for (auto& stock : stocks) {
		sum += Market::getInstance().getClosePrice(stock.first) * (double)stock.second.quantity;
	}
	return sum;
}

void Wallet::printStocks() {
	for (auto& stock : stocks) {
		std::cout << stock.first << " | " << Market::getInstance().getClosePrice(stock.first) << " | " << stock.second.quantity  << " | ";
		std::cout << Market::getInstance().getClosePrice(stock.first) * (double)stock.second.quantity << " | " << stock.second.meanPrice << " | ";
		std::cout << stock.second.meanPrice * (double)stock.second.quantity << std::endl;
	}
	std::cout << "-------------------------------------------------------------------------" << std::endl;
}

void Wallet::addDividends(double dividends) {
	totalDividends += dividends;
}

double Wallet::getTotalDividends() {
	return totalDividends;
}
double Wallet::getInvestedMoney() {
	return investedMoney;
}