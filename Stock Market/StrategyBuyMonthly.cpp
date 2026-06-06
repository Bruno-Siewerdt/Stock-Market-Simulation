#include "StrategyBuyMonthly.h"

#include <iostream>

StrategyBuyMonthly::StrategyBuyMonthly(int monthlyInput, std::vector<std::string> stocksToBuy): 
	monthlyInput(monthlyInput), stocksToBuy(stocksToBuy) {
}

void StrategyBuyMonthly::buyStocks(Wallet& wallet) {
	money += (double)monthlyInput;
	std::cout << monthlyInput << std::endl;
	double monthlyDividend = 0;
	double moneyEachStock = money / Market::getInstance().getAvailableStocksCount(stocksToBuy);

	for (std::string ticker : stocksToBuy) {
		if (Market::getInstance().isStockAvailable(ticker)) {
			monthlyDividend += addDividends(wallet, Market::getInstance().getDividends(ticker) * (double)wallet.getStockQuantity(ticker));
			double price = Market::getInstance().getOpenPrice(ticker);
			int quantity = floor(moneyEachStock / price);
			money -= quantity * price;
			wallet.buyStock(ticker, quantity, price);
		}
	}

	walletValue.push_back(wallet.getWalletValue());
	investedMoney.push_back(wallet.getInvestedMoney());
	totalDividends.push_back(wallet.getTotalDividends());
	monthlyDividends.push_back(monthlyDividend);
}

void StrategyBuyMonthly::applyInflation(double inflationRate) {
	monthlyInput = (double)monthlyInput * (1 + inflationRate);
}

double StrategyBuyMonthly::addDividends(Wallet& wallet, double dividends) {
	money += dividends;
	wallet.addDividends(dividends);
	return dividends;
}