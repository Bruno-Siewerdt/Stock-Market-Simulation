#include "StrategyBuyMonthly.h"

#include <iostream>

StrategyBuyMonthly::StrategyBuyMonthly(int monthlyInput): 
	monthlyInput(monthlyInput) {
}

void StrategyBuyMonthly::buyStocks(Wallet& wallet) {
	money += (double)monthlyInput;
	double moneyEachStock = money / STOCKS_TO_BUY.size();
	for (std::string ticker : STOCKS_TO_BUY) {
		double dividends = Market::getInstance().getDividends(ticker) * (double)wallet.getStockQuantity(ticker);
		money += dividends;
		double price = Market::getInstance().getOpenPrice(ticker);
		int quantity = moneyEachStock / price;
		money -= quantity * price;
		wallet.buyStock(ticker, quantity, price);
	}
}