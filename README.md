A tool for making stock market historical analysis, simulation how different strategies would perform in the last years.

In development

Structure:
- main.cpp: main file, calls python files that integrates with Yahoo Finances and creates CSV files with Stocks historical prices and dividends.
- data/integrator.py: Uses yfinance library to create the CSV files.
- Class Market: Simulates the market each month, with some stocks options and its current prices.
- Class BacktestSimulator: runs the simulation, contains and process the Wallet, Market and Strategy objects. Also saves the results (income, yield...) of this simulation.
- Class Wallet: Contains a list of purchased stocks, can return the portifolio current value and is the one who really execute the purchases.
- Class Strategy: it's an interface for different investments Strategies.


Types of Strategies:
- BuyMonthly: It has a certain amount of money to spend monthly and tries to always balance it equally among a list of predefined stocks.
