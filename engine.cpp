#include <iostream>
#include <map>

class OrderBook {
private:
    std::map<double, int> bids; // map to store bid prices and quantities
    std::map<double, int> asks; // map to store ask prices and quantities

public:
    // Add a market bid order
    void addMarketBid(int quantity) {
        if (!asks.empty()) {
            auto bestAsk = asks.begin(); // Get the best ask price
            int filledQuantity = std::min(quantity, bestAsk->second); // Fill as much as possible
            bestAsk->second -= filledQuantity; // Reduce the quantity at the best ask price
            if (bestAsk->second == 0) // If the ask is fully filled, remove it from the order book
                asks.erase(bestAsk);
            std::cout << "Market bid filled for " << filledQuantity << " at price " << bestAsk->first << std::endl;
        } else {
            std::cout << "No asks available to fill market bid." << std::endl;
        }
    }

    // Add a market ask order
    void addMarketAsk(int quantity) {
        if (!bids.empty()) {
            auto bestBid = bids.rbegin(); // Get the best bid price
            int filledQuantity = std::min(quantity, bestBid->second); // Fill as much as possible
            bestBid->second -= filledQuantity; // Reduce the quantity at the best bid price
            if (bestBid->second == 0) // If the bid is fully filled, remove it from the order book
                bids.erase(bestBid->first);
            std::cout << "Market ask filled for " << filledQuantity << " at price " << bestBid->first << std::endl;
        } else {
            std::cout << "No bids available to fill market ask." << std::endl;
        }
    }

    // Add a limit bid order
    void addBid(double price, int quantity) {
        bids[price] += quantity;
    }

    // Add a limit ask order
    void addAsk(double price, int quantity) {
        asks[price] += quantity;
    }

    // Display the order book
    void display() {
        std::cout << "Bids:\n";
        for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
            std::cout << "Price: " << it->first << " Quantity: " << it->second << "\n";
        }

        std::cout << "\nAsks:\n";
        for (auto it = asks.begin(); it != asks.end(); ++it) {
            std::cout << "Price: " << it->first << " Quantity: " << it->second << "\n";
        }
    }
};

int main() {
    OrderBook orderBook;

    // Adding some bids and asks
    orderBook.addBid(100, 5);
    orderBook.addBid(99.5, 10);
    orderBook.addAsk(101, 8);
    orderBook.addAsk(102, 15);

    // Adding market orders
    orderBook.addMarketBid(7); // Market bid to buy 7 units
    orderBook.addMarketAsk(12); // Market ask to sell 12 units

    // Displaying the order book
    orderBook.display();

    return 0;
}
