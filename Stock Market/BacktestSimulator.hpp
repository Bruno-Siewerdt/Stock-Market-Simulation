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

#include <vector>

struct Simulator {
	Wallet wallet;
	Strategy* strategy;

	Simulator(double monthlyInput, std::vector<std::string> stocks);
	~Simulator() { delete strategy; }
};

class BacktestSimulator {
private:
	std::vector<Simulator*> simulators; // change for smart pointer
	bool considerInflation = true;

public:
	BacktestSimulator();
	~BacktestSimulator();

	/*Simulates one month of the market, return false if the data ends*/
	bool simulate();
	void printResults();

	static void printMoney(double value);
};