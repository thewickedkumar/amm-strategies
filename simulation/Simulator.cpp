#include "Simulator.h"
#include <iostream>
#include <iomanip>
#include "../strategies/fixed_offset/FixedOffset.h"

void Simulator::run() {
    FixedOffset* fo = dynamic_cast<FixedOffset*>(_strategy);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n=== " << _strategy->name() << " ===\n\n";

    std::cout << std::setw(6)  << "Tick"
        << std::setw(10) << "Mid"
        << std::setw(10) << "BestBid"
        << std::setw(10) << "BestAsk"
        << std::setw(10) << "OurBid"
        << std::setw(10) << "OurAsk"
        << std::setw(6)  << "Inv"
        << std::setw(12) << "RealPnL"
        << "\n";

    std::cout << std::string(84, '-') << "\n";

    for (int i = 0; i < _numTicks; ++i) {
        double mid = _feed.nextPrice();
        _book.update(mid);
        _strategy->onTick(_book, i);

        if (fo && i % 10 == 0) {
            std::cout << std::setw(6)  << i
                << std::setw(10) << mid
                << std::setw(10) << _book.bestBid()
                << std::setw(10) << _book.bestAsk()
                << std::setw(10) << fo->ourBid()
                << std::setw(10) << fo->ourAsk()
                << std::setw(6)  << fo->inventory()
                << std::setw(12) << fo->realizedPnl()
                << "\n";
        }
    }

    if (fo) {
        double finalMid = _feed.currentPrice();
        double unrealized = fo->unrealizedPnl(finalMid);
        double total = fo->realizedPnl() + unrealized;
        int fillCount = (int)fo->fills().size();

        std::cout << "\n=== Summary ===\n";
        std::cout << "Strategy         : " << _strategy->name()  << "\n";
        std::cout << "Total fills      : " << fillCount           << "\n";
        std::cout << "Final inventory  : " << fo->inventory()     << " shares\n";
        std::cout << "Realized P&L     : " << fo->realizedPnl()   << "\n";
        std::cout << "Unrealized P&L   : " << unrealized          << "\n";
        std::cout << "Total P&L        : " << total               << "\n";
    }
}
