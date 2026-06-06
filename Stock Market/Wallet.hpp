/*
 *  Saves the stocks already purchased
 *  Has a certain amout of assets (stocks)
 */

#pragma once

#include "Market.hpp"

struct WalletStock {
	int quantity = 0;
	double meanPrice = 0;
};

class Wallet {
private:
	std::unordered_map<std::string, WalletStock> stocks;
	double investedMoney = 0;
	double totalDividends = 0;

public:
	Wallet();
	void buyStock(const std::string& ticker, const int quantity, const double price); // buys a quantity of a specific stock
	double getWalletValue(); // return the sum of the prices of all stocks of wallet
	int getStockQuantity(std::string ticker);
	void printStocks();

	void addDividends(double dividends);
	double getTotalDividends();
	double getInvestedMoney();
};