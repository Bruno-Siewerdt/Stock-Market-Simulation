#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem> // C++17 necessary

#include "Market.hpp"

namespace fs = std::filesystem;

static void print(const std::string& content) {
	std::cout << content << std::endl;
}

static void printError(const std::string& content) {
	std::cerr << content << std::endl;
}

static bool integrateData() { // Downloads online data about selected stocks
	print("Integrating historical data");
	try {
		fs::current_path("../");
	}
	catch (const fs::filesystem_error& e) {
		printError("Critical Error: it was not possible to achieve integrator on filesystem");
		return false;
	}
	std::string command = ".venv\\Scripts\\python.exe data/integrator.py";
	int result = std::system(command.c_str());
	if (result != 0) {
		printError("Critical Error: it was not possible to download the historical data"); 
		return false;
	}
	return true;
}

int main() {
	print("Initializing Analysis");
	if (!integrateData()) {
		printError("Execution Stopped");
		return 1;
	}
	print("Historical data successfully integrated");

	Market market = Market();

	return 0;
}