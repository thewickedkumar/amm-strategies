#pragma once

// In a real exchange, the order book has many levels of bids and asks.
// For our simulation, we only need the best bid and best ask (top of book),
// because that's what determines limit order execution (from Chapter 10).
class OrderBook {
public:
    // tickSize : smallest price increment (e.g. 0.01 for 1 cent)
    // spread   : gap between best bid and best ask in ticks (e.g. 1 tick)
    OrderBook(double tickSize, int spreadTicks = 1);

    // Update the book around a new mid price from the feed.
    // best ask = mid + half spread
    // best bid = mid - half spread
    void update(double midPrice);

    double bestBid() const;
    double bestAsk() const;
    double tickSize() const;

private:
    double _bestBid;
    double _bestAsk;
    double _tickSize;
    int _spreadTicks;
};
