# High Frequency Market Making Strategies
## Implemented Each Strategy from Irene Aldrige's HFT Book in C++17

This repository contains each market making strategy carefully written in C++ 17 from Irene Aldrige's *High Frequency Trading* Textbook, specifically from Chapter 17: Automated Market Making 1 and Chapter 18: Automated Market Making 2.

## Repository Structure

```
amm-strategies/
├── core/
│   ├── PriceFeed.h / .cpp
│   ├── OrderBook.h / .cpp
│   └── Types.h
├── strategies/
│   ├── BaseStrategy.h
│   └── fixed\_offset/
│       ├── FixedOffset.h
│       └── FixedOffset.cpp
├── simulation/
│   ├── Simulator.h / .cpp
│   └── main.cpp
└── Makefile
```

`Pricefeed` implements a random walk which uses a pseudo random generator to sample from a normal distribution of mean 0.0 and standard deviation of `VOLATILITY`. Then, Orderbook, takes this Pricefeed and considers a spread around the price value to synthetically obtain best bid and ask offers. Together they simulate an L1 Orderbook.

In strategies, BaseStrategy is a parent class which implements all the strategies in the repo. It has several virtual functions such as onTick which implement the market making strategy.

In the simulation folder, `Simulation` implements the loop `MAX_TICKS` amount of times and prints onto the screen different stats such as MID\_PRICE, BEST\_BID, etc. The main file creates the objects and builds the simulator to run a specific strategy.

## Fixed Offset Strategy

A fixed offset is considered and passed on as an argument. This market making strategy quotes its bid and ask based on the offset_ticks. More specifically, quoted_bid = best_bid - offset_ticks * tick_size and similarly for ask with the change of quoting above the best ASK.
