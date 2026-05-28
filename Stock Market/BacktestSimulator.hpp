/*
 *  Runs the simulation
 *  Execute all function of the objects
 */

#include "Market.hpp"
#include "Wallet.hpp"
#include "Strategy.hpp"

#pragma once

class BacktestSimulator {
private:
	Market market;
	Wallet wallet;
	Strategy strategy;
	int i = 0;

public:
	BacktestSimulator();

	/*Simulates one month of the market, return false if the data ends*/
	bool simulate();
};