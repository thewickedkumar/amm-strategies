#pragma once
#include <random>

// Generates a synthetic mid-price using a simple random walk.
// At each tick, price moves up or down by a small random amount.
// This is the simplest realistic model of short-term price movement.
class PriceFeed {
public:
    PriceFeed(double startPrice, double volatility, unsigned int seed = 42);

    double nextPrice();

    double currentPrice() const;

    int tickCount() const;

private:
    double _price;
    double _volatility;
    int _tick;

    std::mt19937 _rng;                       // Mersenne Twister RNG
    std::normal_distribution<double> _dist;  // N(0, volatility)
};
