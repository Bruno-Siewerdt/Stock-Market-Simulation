/*
 *  Saves the stocks already purchased
 *  Has a certain amout of assets (stocks)
 */

#pragma once

#include "Market.hpp"

class Wallet {
private:
	 

public:
	void buyStock(std::string ticker, int quantity); // buys a quantity of a specific stock
	double getWalletValue(); // return the sum of the prices of all stocks of wallet
};