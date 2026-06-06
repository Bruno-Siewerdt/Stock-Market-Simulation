#pragma once

#include "Strategy.hpp"
#include <vector>

class StrategyBuyMonthly : public Strategy {
private:
	int monthlyInput;
	double money = 0;
	
	std::vector<std::string> stocksToBuy;
	double addDividends(Wallet& wallet, double dividends);

public:
	StrategyBuyMonthly(int monthlyInput, std::vector<std::string> stocksToBuy);
	void buyStocks(Wallet& wallet) override;

	void applyInflation(double inflationRate) override;
};

