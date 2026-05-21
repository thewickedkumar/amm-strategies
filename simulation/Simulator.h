#pragma once
#include "../core/PriceFeed.h"
#include "../core/OrderBook.h"
#include "../strategies/BaseStrategy.h"

class Simulator {
private:
    BaseStrategy* _strategy;    
    PriceFeed&    _feed;
    OrderBook&    _book;
    int           _numTicks;

public:
    Simulator(BaseStrategy* strategy, PriceFeed& feed, OrderBook& book, int numTicks)
        : _strategy(strategy)
        , _feed(feed)
        , _book(book)
        , _numTicks(numTicks)
    {}
    void run();

};
