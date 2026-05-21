#pragma once
#include<string>
#include "../core/Types.h"
#include "../core/OrderBook.h"

class BaseStrategy{
    public:
        //Virtual functions help calling the right functions during polymorphism
        virtual void onTick(const OrderBook& book, int tick) = 0;
        virtual std::string name() const = 0; // this function never modifies anything but just returns the name
        virtual ~BaseStrategy() = default; // Virtual destructor
};
