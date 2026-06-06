#include "BacktestSimulator.hpp"

#include <matplot/matplot.h>
#include <iomanip>

Simulator::Simulator(double monthlyInput, std::vector<std::string> stocks) {
	wallet = Wallet();
	strategy = new StrategyBuyMonthly(monthlyInput, stocks);
}

BacktestSimulator::BacktestSimulator() {

	simulators.emplace_back(new Simulator(100, { "BBAS3.SA", "PETR4.SA", "IVVB11.SA", "CMIG4.SA", "ITSA4.SA", "PSSA3.SA", "BBSE3.SA", "ITUB4.SA", "SAPR11.SA", "BBDC3.SA" }));
	simulators.emplace_back(new Simulator(100, { "^BVSP" }));

}

BacktestSimulator::~BacktestSimulator() {
	simulators.clear();
}

bool BacktestSimulator::simulate() { // simulation loop
	int cont = 1;
	std::cout << simulators.size() << std::endl;
	for (auto simulator : simulators) {
		std::cout << "Carteira " << cont << std::endl;
		cont++;

 		simulator->strategy->buyStocks(simulator->wallet);
		if (Market::getInstance().getDate() % 12 == 11) {
			simulator->strategy->applyInflation(MEAN_INFLATION);
		}

		std::cout << "                   " << Market::getInstance().getFormatedDate() << std::endl;
		std::cout << "Total Money: ";
		printMoney(simulator->wallet.getWalletValue());
		std::cout << " | Money Invested: ";
		printMoney(simulator->wallet.getInvestedMoney());
		std::cout << " | Month Dividends: ";
		printMoney(simulator->strategy->monthlyDividends.back());
		std::cout << " | Total Dividends: ";
		printMoney(simulator->wallet.getTotalDividends());
		std::cout << std::endl;
		simulator->wallet.printStocks();
	}

	return Market::getInstance().updatePrices();
}

void BacktestSimulator::printResults() { // once at the end of simulation
	using namespace matplot;

	for (auto& simulator : simulators) {
		figure_handle f = figure(true);
		f->size(900, 600);

		subplot(2, 2, 0);
		auto p1 = plot(simulator->strategy->walletValue, "b-");
		p1->line_width(2.5);
		title("Total Wallet Value");
		xlabel("Operation Months");
		ylabel("Value (R$)");
		grid(on);

		subplot(2, 2, 1);
		auto p2 = plot(simulator->strategy->investedMoney, "g--");
		p2->line_width(2.5);
		title("Invested Money");
		xlabel("Operation Months");
		ylabel("Invested Value (R$)");
		grid(on);

		subplot(2, 2, 2);
		auto p3 = bar(simulator->strategy->totalDividends);
		p3->face_color("green");
		title("Total Dividends Received");
		xlabel("Operation Months");
		ylabel("Dividends (R$)");
		grid(on);

		subplot(2, 2, 3);
		auto p4 = bar(simulator->strategy->monthlyDividends);
		p4->face_color("green");
		title("Monthly Dividends");
		xlabel("Operation Months");
		ylabel("Dividends (R$)");
		grid(on);

		show();
	}
}

void BacktestSimulator::printMoney(double value) {
	std::cout << "R$";
	bool zerosFlag = false;
	if (value > 1000000000) {
		int aux = (int)value / 1000000000;
		std::cout << aux << ",";
		value -= (double)aux * 1000000000;
		zerosFlag = true;
	}
	if (value > 1000000) {
		int aux = (int)value / 1000000;
		std::cout << ((zerosFlag && aux < 100) ? "0" : "") << ((zerosFlag && aux < 10) ? "0" : "") << aux << ",";
		value -= (double)aux * 1000000;
		zerosFlag = true;
	}
	if (value > 1000) {
		int aux = (int)value / 1000;
		std::cout << ((zerosFlag && aux < 100) ? "0" : "") << ((zerosFlag && aux < 10) ? "0" : "") << aux << ",";
		value -= (double)aux * 1000;
		zerosFlag = true;
	}
	std::cout << std::fixed << std::setprecision(2);
	std::cout << ((zerosFlag && value < 100) ? "0" : "") << ((zerosFlag && value < 10) ? "0" : "") << value;
}