import yfinance as yf

# Exemplo com uma ação brasileira e uma americana
tickers = ["PETR4.SA", "BBAS3.SA"]

for t in tickers:
    ticker_obj = yf.Ticker(t)
    print(f"Processing {t}...")
    
    # Salva o histórico de preços em CSV
    precos = ticker_obj.history(period="max", interval="1mo")
    precos.to_csv(f"data/{t}_precos.csv")
    
    # Salva o histórico de dividendos em CSV
    # dividendos = ticker_obj.dividends
    # sdividendos.to_csv(f"data/{t}_dividendos.csv")