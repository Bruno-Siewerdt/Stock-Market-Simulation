#pragma once

#include "Strategy.hpp"
#include <vector>

class StrategyBuyMonthly : public Strategy {
private:
	int monthlyInput;
	double money = 0;

	const std::vector<std::string> STOCKS_TO_BUY = {"BBAS3.SA", "PETR4.SA"};

public:
	StrategyBuyMonthly(int monthlyInput);
	void buyStocks(Wallet& wallet) override;
};

