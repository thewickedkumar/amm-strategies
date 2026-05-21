#include "PriceFeed.h"

PriceFeed::PriceFeed(double startPrice, double volatility, unsigned int seed)
    : _price(startPrice)
    , _volatility(volatility)
    , _tick(0)
    , _rng(seed)
    , _dist(0.0, volatility)   // norm dist with 0 mean and vol std dev
{}

double PriceFeed::nextPrice() { // Being more explicit about which class the function belongs to
    _price += _dist(_rng);   // random step up or down
    if (_price < 0.01) _price = 0.01;  // price can't go negative
    _tick++;  // You increment the tick counter
    return _price;  // Return the new price !
}

double PriceFeed::currentPrice() const {
    return _price;  // The current price
}

int PriceFeed::tickCount() const {
    return _tick;
}
