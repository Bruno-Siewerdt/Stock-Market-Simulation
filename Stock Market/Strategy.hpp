/*
 *  Decides witch stock to buy, based on the prices of Market
 *  It's a Interface, there will be many different strategies
 */

#pragma once

#include "Wallet.hpp"

enum StrategyType {
	BUY_MONTHLY
};

class Strategy {
private:

public:
	virtual void buyStocks(Wallet& wallet) {}; // Runs the strategy to decide with Stock to buy and runs it
};