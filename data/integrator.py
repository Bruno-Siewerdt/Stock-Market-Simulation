import yfinance as yf

# Exemplo com uma ação brasileira e uma americana
tickers = ["BBAS3.SA", "PETR4.SA", "IVVB11.SA", "CMIG4.SA", "ITSA4.SA", 
           "PSSA3.SA", "BBSE3.SA", "ITUB4.SA", "SAPR11.SA", "BBDC3.SA",
           "^BVSP"]

for t in tickers:
    ticker_obj = yf.Ticker(t)
    print(f"Processing {t}...")
    
    # Salva o histórico de preços em CSV
    precos = ticker_obj.history(period="max", interval="1mo")
    precos.to_csv(f"data/{t}_precos.csv")
    
    # Salva o histórico de dividendos em CSV
    # dividendos = ticker_obj.dividends
    # dividendos.to_csv(f"data/{t}_dividendos.csv")