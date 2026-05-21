#pragma once
#include <string>
#include <vector>
#include "../../core/OrderBook.h"
#include "../../core/Types.h"
#include "../BaseStrategy.h"

class FixedOffset : public BaseStrategy {
public:
    FixedOffset(int offsetTicks, int maxInventory = 10);

    void        onTick(const OrderBook& book, int tick) override;
    std::string name() const override;

    double ourBid()      const;
    double ourAsk()      const;
    int    inventory()   const;
    double realizedPnl() const;
    double unrealizedPnl(double midPrice) const;

    const std::vector<Fill>& fills() const;

private:
    int    _offsetTicks;
    int    _maxInventory;
    double _ourBid;
    double _ourAsk;
    int    _inventory;
    double _realizedPnl;
    std::vector<Fill> _fills;

    bool _checkBuyFill (const OrderBook& book, int tick);
    bool _checkSellFill(const OrderBook& book, int tick);
};
