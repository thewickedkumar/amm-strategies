CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

SRCS = core/Pricefeed.cpp \
       core/Orderbook.cpp \
       strategies/fixed_offset/FixedOffset.cpp \
       simulation/Simulator.cpp \
       simulation/main.cpp

OBJS = $(SRCS:.cpp=.o)

all: market_maker

market_maker: $(OBJS)
	$(CXX) $(OBJS) -o market_maker

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) market_maker
