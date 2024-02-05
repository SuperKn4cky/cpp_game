#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "../include/Status.hpp"
#include "../include/TermPlayer.hpp"

using namespace std::literals;

struct Order {
    std::string func_name{"play"};
    int        *p1board{NULL};
    int        *p2board{NULL};
    Status      state{Status::PREGAME};
};

int *turn_into_int(char *str)
{
    int  i;
    int *table;

    i     = 0;
    table = new int[100];
    while (i <= 99) {
        table[i] = str[i] - 48;
        i += 1;
    }
    return table;
}

// Fonction pour déserialiser un paquet côté client
void deserialize(std::stringstream &ss, Order *order)
{
    int   a;
    char *p1;
    char *p2;

    ss >> a;
    if (a == 1) {
        order->func_name = "display";
    } else {
        order->func_name = "play";
        return;
    }
    ss.get();
    p1 = new char[101];
    ss.get(p1, 101);
    order->p1board = turn_into_int(p1);
    delete []p1;
    ss.get();
    p2 = new char[101];
    ss.get(p2, 101);
    order->p2board = turn_into_int(p2);
    delete []p2;
    ss >> a;
    order->state = static_cast<Status>(a);
}

//     // Utilisation des données extraites
//     std::cout << "Function : " << order->func_name << std::endl;
//     std::cout << "Player 1 Value: " << order->p1board << std::endl;
//     std::cout << "Player 2 Value: " << order->p2board << std::endl;
//     std::cout << "Status Value: " << static_cast<int>(order->state) << std::endl;
// }

// void ask_platform(int &aswr)
// {
//     while (aswr < 0 || aswr > 1) {
//         std::cout << "On which support will you play ? Terminal (0) / Graphic
//         "
//                      "window (1)"
//                   << std::endl;
//         std::cin >> aswr;
//     }
// }

Order *receive_order(sf::TcpSocket &sock)
{
    char       *str;
    std::size_t bytes_read = 1;
    Order      *order      = new Order;

    str = new char[207];
    sock.receive(str, 206, bytes_read);
    str[bytes_read] = '\0';
    // std::cout << "str: "<< str << " bytes read: "<< bytes_read << '\n';
    std::stringstream ss(str);
    delete []str;
    deserialize(ss, order);

    return order;
}

void exec_order(Order *order, IPlayer *p, sf::TcpSocket &sock, Status &state)
{
    std::stringstream ss;
    state = order->state;
    if ("display"sv == order->func_name) {
        p->display(order->p1board, order->p2board, order->state);
    } else {
        std::tuple<int, int> i = p->play();
        ss << ' ' << std::get<0>(i) << ' ' << std::get<1>(i);
        if (sock.send(ss.str().c_str(), ss.str().size()) != sf::TcpSocket::Done) {
            throw std::runtime_error("exec_order : can't send the move");
        }
    }
}

void client(int port, char *ip)
{
    Status        state = Status::PREGAME;
    sf::TcpSocket sock;
    IPlayer      *p1;

    if (sock.connect(ip, port) != sf::Socket::Done)
        throw std::runtime_error("Client: Socket Connection went Wrong");
    p1 = new TermPlayer(std::cin, std::cout, 2);
    // } else {
    //     SfmlPlayer p(2);
    //     p1 = &p;
    // }
    while (state != Status::P1WIN && state != Status::P2WIN) {
        exec_order(receive_order(sock), p1, sock, state);
    }
    sock.disconnect();
}
