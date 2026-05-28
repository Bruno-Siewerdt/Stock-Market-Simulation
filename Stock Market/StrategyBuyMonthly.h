#pragma once

#include "Strategy.hpp"

class StrategyBuyMonthly : public Strategy {
private:
	int monthlyInput;

public:
	StrategyBuyMonthly(int monthlyInput);
	void buyStocks(Wallet& wallet, Market& market) override;
};

