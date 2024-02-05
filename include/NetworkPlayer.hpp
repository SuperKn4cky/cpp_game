#ifndef NETWORKPLAYER_HPP_
#define NETWORKPLAYER_HPP_

#include <SFML/Network.hpp>
#include "IPlayer.hpp"

class NetworkPlayer : public IPlayer {
public:
    NetworkPlayer(int id, sf::TcpListener &lstnr);
    ~NetworkPlayer();
    void display(int *p1board, int *p2board, Status state) override;
    std::tuple<int, int> play() override;

private:
    int           id_;
    sf::TcpSocket sock_;
};

#endif
