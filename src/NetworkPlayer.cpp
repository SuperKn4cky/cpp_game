#include "../include/NetworkPlayer.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>

using namespace std::literals;

NetworkPlayer::NetworkPlayer(int id, sf::TcpListener &lstnr) : id_(id)
{
    if (lstnr.accept(sock_) != sf::Socket::Done) {
        throw std::runtime_error("NetworkPlayer: Unable to accept client");
    }
}

NetworkPlayer::~NetworkPlayer()
{
    sock_.disconnect();
}

std::string turn_it_to_string(int *pboard)
{
    std::string sstr;
    int         i   = 0;
    char       *str = new char[101];

    while (i <= 99) {
        str[i] = pboard[i] + 48;
        i += 1;
    }
    str[i]     = ' ';
    str[i + 1] = '\0';
    sstr       = str;
    delete[] str;
    return sstr;
}

void NetworkPlayer::display(int *p1board, int *p2board, Status state)
{
    std::stringstream ss;
    ss << 1 << ' ' << turn_it_to_string(p1board) << turn_it_to_string(p2board)
       << static_cast<int>(state) << ' ';

    if (sock_.send(ss.str().c_str(), ss.str().size()) != sf::Socket::Done) {
        throw std::runtime_error(
            "NetworkPlayer: Failed to send data to client");
    }
}

std::tuple<int, int> NetworkPlayer::play()
{
    int               x;
    int               y;
    char             *str;
    std::size_t       bytes_read;
    std::stringstream ss;

    ss << "play ";
    if (sock_.send(ss.str().c_str(), ss.str().size()) != sf::Socket::Done) {
        throw std::runtime_error(
            "NetworkPlayer: Failed to send data to client");
    }
    bytes_read = 0;
    str        = new char[6];
    sock_.receive(str, 5, bytes_read);
    if (bytes_read == 0)
        throw std::runtime_error("play: read 0");
    str[bytes_read] = '\0';
    ss.str(str);
    ss >> x;
    ss >> y;

    return std::tuple(x, y);
}
