/*
 *  Decides witch stock to buy, based on the prices of Market
 *  It's a Interface, there will be many different strategies
 */

#pragma once

#include "Wallet.hpp"

class Strategy {
private:

public:
	virtual void buyStocks(Wallet& wallet) {}; // Runs the strategy to decide with Stock to buy and runs it
	virtual void applyInflation(double inflationRate) {};

	std::vector<double> walletValue;
	std::vector<double> investedMoney;
	std::vector<double> totalDividends;
	std::vector<double> monthlyDividends;
};