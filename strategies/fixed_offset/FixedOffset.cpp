#include "FixedOffset.h"

FixedOffset::FixedOffset(int offsetTicks, int maxInventory) // classname::constructor/method_name
    : _offsetTicks(offsetTicks)
    , _maxInventory(maxInventory)
    , _ourBid(0.0)
    , _ourAsk(0.0)
    , _inventory(0)
    , _realizedPnl(0.0)
{}

void FixedOffset::onTick(const OrderBook& book, int tick) {
    bool filled = false;

    // If the best bid and offer both cross our quotes, we can fill them immediately
    if (_checkBuyFill(book, tick))  filled = true;
    if (_checkSellFill(book, tick)) filled = true;

    // Only quote a side if inventory limits allow it.
    // If we're already max long, don't post more buys (no point accumulating).
    // If we're already max short, don't post more sells.
    if (_inventory < _maxInventory)
        _ourBid = book.bestBid() - (_offsetTicks * book.tickSize()); // Take the best bid and subtract our offset
    else
        _ourBid = 0.0; //cancelled

    if (_inventory > -_maxInventory)
        _ourAsk = book.bestAsk() + (_offsetTicks * book.tickSize());
    else
        _ourAsk = 0.0; //cancelled
}

std::string FixedOffset::name() const {
    return "FixedOffset";
}

bool FixedOffset::_checkBuyFill(const OrderBook& book, int tick) {
    if (_ourBid <= 0.0) return false;  // no active buy order
    if (_inventory >= _maxInventory) return false;

    if (book.bestAsk() <= _ourBid) { // If the best offer price for us is below what we expect it to be, we obv fill
        _inventory++; //inc. inventory
        _realizedPnl -= _ourBid;  // we spent this money buying
        _fills.push_back({BUY, _ourBid, tick});
        return true;
    }
    return false;
}

bool FixedOffset::_checkSellFill(const OrderBook& book, int tick) {
    if (_ourAsk <= 0.0) return false;  // no active sell order
    if (_inventory <= -_maxInventory) return false;

    if (book.bestBid() >= _ourAsk) {
        _inventory--;
        _realizedPnl += _ourAsk;  // we received this money selling
        _fills.push_back({SELL, _ourAsk, tick});
        return true;
    }
    return false;
}

double FixedOffset::ourBid()        const { return _ourBid; }
double FixedOffset::ourAsk()        const { return _ourAsk; }
int    FixedOffset::inventory()     const { return _inventory; }
double FixedOffset::realizedPnl()   const { return _realizedPnl; }

const std::vector<Fill>& FixedOffset::fills() const {
    return _fills;
}

double FixedOffset::unrealizedPnl(double midPrice) const {
    return _inventory * midPrice;
}
