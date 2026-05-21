#include <iostream>
#include <iomanip>
#include "../core/PriceFeed.h"
#include "../core/OrderBook.h"
#include "Simulator.h"
#include "../strategies/fixed_offset/FixedOffset.h"

int main() {

    const double START_PRICE   = 100.0;
    const double VOLATILITY    = 0.05;
    const unsigned int SEED    = 42;
    const double TICK_SIZE     = 0.01;
    const int    SPREAD_TICKS  = 1;
    const int    OFFSET_TICKS  = 2;
    const int    MAX_INVENTORY = 10;
    const int    NUM_TICKS     = 500;

    PriceFeed feed(START_PRICE, VOLATILITY, SEED);
    OrderBook book(TICK_SIZE, SPREAD_TICKS);
    FixedOffset strategy(OFFSET_TICKS, MAX_INVENTORY);

    Simulator sim(&strategy, feed, book, NUM_TICKS);

    sim.run();

    return 0;
}
