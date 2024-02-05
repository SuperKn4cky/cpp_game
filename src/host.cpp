#include <iostream>
#include <tuple>
#include "../include/Game.hpp"
#include "../include/NetworkPlayer.hpp"
#include "../include/SfmlPlayer.hpp"
#include "../include/TermPlayer.hpp"

int *fill_table()
{
    int b[100] = {0,1,1,0,0,0,0,0,0,1,
                  0,0,0,0,0,0,0,0,0,1,
                  1,0,0,0,0,0,0,0,0,1,
                  1,0,0,0,0,0,0,0,0,1,
                  1,0,0,0,0,0,0,0,0,1,
                  1,0,0,0,0,0,0,0,0,0,
                  0,0,0,1,1,1,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,1,1,1,0,0,
                  0,0,0,0,0,0,0,0,0,0};
    int *a      = new int[100];
    int  i      = 0;
    for (int x : b) {
        a[i] = x;
        i++;
    }
    return a;
}

void host(int port)
{
    std::tuple<int, int> i;
    Game                 game(port);

    std::cout << "Your local IP address : " << sf::IpAddress::getLocalAddress()
              << std::endl;
    std::cout << "Your public IP address : "
              << sf::IpAddress::getPublicAddress() << std::endl;
    // while (aswr != 0 && aswr != 1) {
    //     std::cout << "On which support will you play ? Terminal (0) / Graphic
    //     "
    //                  "window (1)"
    //               << std::endl;
    //     std::cin >> aswr;
    // }
    // if (aswr == 0) {
    TermPlayer p1(std::cin, std::cout, 1);
    game.set_player1(&p1);
    // }
    // } else {
    //     SfmlPlayer p1(1);
    //     game.set_player1(&p1);
    // }
    NetworkPlayer p2(2, game.get_lstnr());
    game.set_player2(&p2);
    game.set_p1board(fill_table());
    game.set_p2board(fill_table());
    game.set_status(Status::P1TURN);
    while (game.get_status() != Status::P1WIN &&
           game.get_status() != Status::P2WIN) {
        game.display_all();
        if (game.currentPlayer() == 1) {
            i = game.get_player1()->play();
        } else {
            i = game.get_player2()->play();
        }
        game.play(std::get<0>(i), std::get<1>(i));
        if (game.get_status() == Status::P1WIN || game.get_status() == Status::P2WIN) {
            game.display_all();
        }
    }
}
