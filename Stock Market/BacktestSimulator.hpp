/*
 *  Runs the simulation
 *  Execute all function of the objects
 */

#include <iostream>

#include "Market.hpp"
#include "Wallet.hpp"
#include "Strategy.hpp"
#include "StrategyBuyMonthly.h"

#pragma once

class BacktestSimulator {
private:
	Wallet wallet;
	Strategy *strategy;

	int date; // months since Jan 2000
	double earnedDividends;

public:
	BacktestSimulator(StrategyType type);
	~BacktestSimulator();

	/*Simulates one month of the market, return false if the data ends*/
	bool simulate();

	static void printMoney(double value);
};