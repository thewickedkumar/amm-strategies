#include "OrderBook.h"
#include <cmath>

OrderBook::OrderBook(double tickSize, int spreadTicks)
    : _bestBid(0.0)
    , _bestAsk(0.0)
    , _tickSize(tickSize)
    , _spreadTicks(spreadTicks)
{}

void OrderBook::update(double midPrice) {
    double snapped = std::round(midPrice / _tickSize) * _tickSize;
    double halfSpread = (_spreadTicks * _tickSize) / 2.0;

    _bestBid = snapped - halfSpread;
    _bestAsk = snapped + halfSpread;
}

double OrderBook::bestBid() const { return _bestBid; }
double OrderBook::bestAsk() const { return _bestAsk; }
double OrderBook::tickSize() const { return _tickSize; }
