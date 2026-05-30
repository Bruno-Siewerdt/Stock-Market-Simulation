#include "BacktestSimulator.hpp"

#include <iomanip>

BacktestSimulator::BacktestSimulator(StrategyType type) {
	date = 0;
	earnedDividends = 0;
	wallet = Wallet();
	strategy = new StrategyBuyMonthly(100);
	/*if (type == StrategyType::BUY_MONTHLY) {
		strategy = new StrategyBuyMonthly(500);
	}*/
}

BacktestSimulator::~BacktestSimulator() {
	delete strategy;
	strategy = nullptr;
}

bool BacktestSimulator::simulate() {
	strategy->buyStocks(wallet);
	printMoney(wallet.getWalletValue());
	wallet.printStocks();
	return Market::getInstance().updatePrices();
}

void BacktestSimulator::printMoney(double value) {
	std::cout << "R$";
	if (value > 1000000000) {
		int aux = (int)value / 1000000000;
		std::cout << aux << ",";
		value -= (double)aux * 1000000000;
	}
	if (value > 1000000) {
		int aux = (int)value / 1000000;
		std::cout << aux << ",";
		value -= (double)aux * 1000000;
	}
	if (value > 1000) {
		int aux = (int)value / 1000;
		std::cout << aux << ",";
		value -= (double)aux * 1000;
	}
	std::cout << std::fixed << std::setprecision(2);
	std::cout << value << std::endl;
}