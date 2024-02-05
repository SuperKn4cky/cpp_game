#ifndef IPLAYER_HPP_
#define IPLAYER_HPP_

#include <tuple>
#include "IDisplay.hpp"

class IPlayer : public IDisplay {
public:
    virtual ~IPlayer()                  = default;
    virtual std::tuple<int, int> play() = 0;
};

#endif
