#include <iostream>

class LiquidityPool {
private:
    double reserve1; // Reserve of asset 1
    double reserve2; // Reserve of asset 2
    double totalFees; // Total fees collected

public:
    // Constructor
    LiquidityPool(double r1, double r2) : reserve1(r1), reserve2(r2), totalFees(0.0) {}

    // Function to add liquidity to the pool
    void addLiquidity(double amount1, double amount2) {
        reserve1 += amount1;
        reserve2 += amount2;
    }

    // Function to remove liquidity from the pool
    void removeLiquidity(double share) {
        double fraction1 = share * reserve1 / (reserve1 + reserve2);
        double fraction2 = share * reserve2 / (reserve1 + reserve2);

        reserve1 -= fraction1;
        reserve2 -= fraction2;
    }

    // Function to process a trade and collect fees
    void processTrade(double amount1, double amount2) {
        double fee = (amount1 + amount2) * 0.003; // 0.3% fee
        totalFees += fee;

        // Distribute 50% of the fee to each reserve
        double reserveFee = fee / 2.0;
        reserve1 += reserveFee;
        reserve2 += reserveFee;
    }

    // Function to get current reserves
    void getReserves(double& r1, double& r2) {
        r1 = reserve1;
        r2 = reserve2;
    }

    // Function to get total fees collected
    double getTotalFees() {
        return totalFees;
    }
};

int main() {
    // Initial reserves
    double initialReserve1 = 1000.0;
    double initialReserve2 = 2000.0;

    // Create liquidity pool with initial reserves
    LiquidityPool pool(initialReserve1, initialReserve2);

    // Add liquidity to the pool
    double addedAmount1 = 500.0;
    double addedAmount2 = 1000.0;
    pool.addLiquidity(addedAmount1, addedAmount2);
    std::cout << "Added liquidity: Asset 1 = " << addedAmount1 << ", Asset 2 = " << addedAmount2 << std::endl;

    // Process a trade
    double tradeAmount1 = 200.0;
    double tradeAmount2 = 400.0;
    pool.processTrade(tradeAmount1, tradeAmount2);
    std::cout << "Processed trade: Asset 1 = " << tradeAmount1 << ", Asset 2 = " << tradeAmount2 << std::endl;

    // Get current reserves and total fees
    double currentReserve1, currentReserve2;
    pool.getReserves(currentReserve1, currentReserve2);
    std::cout << "Current reserves: Asset 1 = " << currentReserve1 << ", Asset 2 = " << currentReserve2 << std::endl;
    std::cout << "Total fees collected: " << pool.getTotalFees() << std::endl;

    return 0;
}
