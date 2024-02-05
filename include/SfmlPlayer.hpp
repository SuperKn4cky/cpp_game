#ifndef SFMLPLAYER_HPP_
#define SFMLPLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <tuple>
#include "IPlayer.hpp"
#include "Status.hpp"

class SfmlPlayer : public IPlayer {
public:
    SfmlPlayer(int id, sf::RenderWindow &window);
    ~SfmlPlayer() = default;
    void display(int *p1board, int *p2board, Status state) override;
    std::tuple<int, int> play() override;

private:
    int               id_;
    sf::RenderWindow &window_;
    void              drawGrid(int startX, int startY, int *board);
    void              displayGameState(Status state);
    void              displayPlayerInfo();
};

#endif
