/*
 *  Decides witch stock to buy, based on the prices of Market
 *  It's a Interface, there will be many different strategies
 */

#pragma once

#include "Wallet.hpp"
#include "Market.hpp"

enum StrategyType {
	BUY_MONTHLY
};

class Strategy {
private:
	

public:
	virtual void buyStocks(Wallet& wallet, Market& market); // Runs the strategy to decide with Stock to buy and runs it
};