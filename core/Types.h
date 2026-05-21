#pragma once

enum Side {
    BUY,
    SELL
};

// every order has a side, price and size
struct Order {
    Side side;
    double price;
    int size;
};

struct Fill {
    Side side;
    double price;
    int tick;
};
