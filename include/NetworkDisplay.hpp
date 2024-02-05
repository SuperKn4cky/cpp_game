#ifndef NETWORKDISPLAY_HPP_
#define NETWORKDISPLAY_HPP_

#include <SFML/Network.hpp>
#include "IDisplay.hpp"

class NetworkDisplay : public IDisplay {
public:
    NetworkDisplay(sf::TcpListener lstnr);
    ~NetworkDisplay();
    void display(int *p1board, int *p2board, Status state);

private:
    sf::Socket         sock;
    sf::SocketSelector stor_;
};

#endif
