#include "BacktestSimulator.hpp"

BacktestSimulator::BacktestSimulator() {
	Market market = Market();
	Wallet wallet = Wallet();
	Strategy strategy = Strategy();
}

bool BacktestSimulator::simulate() {
	strategy.buyStocks(wallet, market);
	market.updatePrices();
	return i++ < 10;
}