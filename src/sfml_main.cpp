#include <SFML/Graphics.hpp>
#include "../include/SfmlPlayer.hpp"
#include "../include/Status.hpp"

int *fill_table()
{
    int b[100] = {1,1,1,0,0,0,0,0,0,1,
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

int main()
{
    int *p1board;
    int *p2board;

    p1board = fill_table();
    p2board = fill_table();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bataille Navale");
    sf::RenderWindow window2(sf::VideoMode(800, 600), "Bataille Navale");

    SfmlPlayer player1(1, window);
    SfmlPlayer player2(2, window2);

    while (window.isOpen() || window2.isOpen()) {
        sf::Event event;
        sf::Event event2;
        while (window.pollEvent(event) || window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event2.type == sf::Event::Closed)
                window2.close();
        }
        player1.display(p1board, p2board, Status::PREGAME);
        player2.display(p1board, p2board, Status::P1WIN);
    }
    return 0;
}
