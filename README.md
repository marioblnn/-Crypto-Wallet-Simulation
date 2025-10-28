# -Crypto-Wallet-Simulation
📊 Pure C++ cryptocurrency and precious metals portfolio management system with real-time price tracking, transaction history, and CSV export capabilities

📚 This is a project that my partner and I created during our first year at university.

🚀 Technologies Used:

-🔥Purely C++
## Project Structure

```
/CryptoWallet/
├── shared/                 # Common code and resources used by both applications
│   ├── classes/            # C++ classes organized by files
│   │   ├── Moneda.cpp      # Coin class implementation
│   │   ├── Moneda.h        # Coin class declaration
│   │   ├── Api.cpp         # API class implementation (interface to real CoinGecko API)
│   │   ├── Api.h           # API class declaration
│   │   ├── Tranzactie.cpp  # Transaction class implementation
│   │   ├── Tranzactie.h    # Transaction class declaration
│   │   ├── Portofoliu.cpp  # Portfolio class implementation
│   │   ├── Portofoliu.h    # Portfolio class declaration
│   │   ├── Utils.cpp       # Helper functions (e.g., createMarket)
│   │   └── Utils.h         # Helper functions header
│   └── files/              # Shared data files (coins, wallet, transactions)
│       ├── monede.txt      # Allowed coins list
│       ├── monede_live.csv # Live coin price export (CSV)
│       ├── portofel.txt    # Wallet – symbols and amounts
│       ├── tranzactii.txt  # Transaction history
│       ├── portofel.csv    # Wallet CSV export
│       └── fonduri.txt     # Available funds
├── app1.cpp                # Executable 1 – coin/material management (uses Moneda, Api)
├── app2.cpp                # Executable 2 – wallet & transactions (uses Tranzactie, Portofoliu, Moneda, Api)
└── README.md               # Project documentation
```

## 🧱 Main Classes

### Market (abstract)
Base class for any tradable asset (cryptocurrencies or materials).

### Coin and Material
Represents a cryptocurrency or material by its symbol (e.g., BTC, ETH).

### Api (live)
Provides static methods to fetch prices:
- `getPriceFromApi(symbol, fiat="ron")` – fetches the current price of a cryptocurrency
- `getMetalPrice(symbol)` – fetches the price of a precious metal
- Sends real HTTP requests to the CoinGecko API and parses JSON responses
- **Dependencies:** libcurl and jsoncpp

### Transaction
Represents a purchase: symbol, amount, purchase price

### Portfolio
Manages assets, available funds, and transaction history. Supports local file storage and CSV export.

### Utils
- `createMarketFromSymbol()` – distinguishes between coins and materials
- Generic template function `load_items<T>` – loads items of type T from a text file into a vector

## 🧑‍💼 Application 1: Coin & Material Management (app1.cpp)

### Command-Line Commands

```bash
./app1 add_coin <symbol>        # Adds a cryptocurrency to monede.txt
./app1 remove_coin <symbol>     # Removes a cryptocurrency from monede.txt

./app1 add_material <symbol>    # Adds a precious material (gold, silver, etc.) to monede.txt
./app1 remove_material <symbol> # Removes a material from monede.txt

./app1 init         # Resets the list of coins and materials
./app1 view         # Displays all coins and materials with current live prices
./app1 export       # Exports the asset list to monede_live.csv
```

### Example Usage

```bash
./app1 init
./app1 add_coin bitcoin
./app1 add_material gold
./app1 remove_material silver
./app1 view
./app1 export
```

### Compilation

```bash
g++ -std=c++17 app1.cpp shared/classes/Moneda.cpp shared/classes/Api.cpp shared/classes/Market.cpp shared/classes/Materiale.cpp -o app1.exe -lcurl -ljsoncpp
```

## 👨‍💻 Application 2: Wallet & Transactions (app2.cpp)

### Command-Line Commands

```bash
./app2 buy <symbol> <amountRON>       # Calculates amount purchased & updates wallet
./app2 view_wallet                    # Displays symbols, amounts, and current value
./app2 view_transactions              # Shows transaction history
./app2 export                          # Exports wallet to portofel.csv
./app2 init <amount>                  # Resets wallet, transactions, and funds to initial amount
```

### Example Usage

```bash
./app2 init 10000
./app2 buy bitcoin 1500
./app2 buy gold 700
./app2 view_wallet
./app2 view_transactions
./app2 export
```

### Compilation

```bash
g++ app2.cpp shared/classes/Tranzactie.cpp shared/classes/Portofoliu.cpp shared/classes/Moneda.cpp shared/classes/Api.cpp shared/classes/Market.cpp shared/classes/Materiale.cpp shared/classes/Utils.cpp -o app2.exe -lcurl -ljsoncpp
```

## ✅ Notes

Prices are fetched live from CoinGecko. HTTP requests via libcurl, JSON parsing via jsoncpp.

## 👥 Authors

Andrei Chindriș & Mario Bălan
