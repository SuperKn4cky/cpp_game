#ifndef TERMPLAYER_HPP_
#define TERMPLAYER_HPP_

#include <iostream>
#include <tuple>
#include "IPlayer.hpp"

class TermPlayer : public IPlayer {
public:
    TermPlayer(std::istream &i, std::ostream &o, int id);
    TermPlayer(int id);
    ~TermPlayer() = default;
    void display(int *p1board, int *p2board, Status state) override;
    std::tuple<int, int> play() override;

private:
    int           _id;
    std::istream &_i{std::cin};
    std::ostream &_o{std::cout};
};

#endif
