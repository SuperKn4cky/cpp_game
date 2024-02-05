#include "../include/SfmlPlayer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "../include/SfmlDisplay.hpp"

SfmlPlayer::SfmlPlayer(int id, sf::RenderWindow &window)
    : id_(id), window_(window)
{}

std::tuple<int, int> SfmlPlayer::play()
{
    return std::make_tuple(-1, -1);
}

void SfmlPlayer::display(int *p1board, int *p2board, Status state)
{
    window_.clear(sf::Color::Black);
    drawGrid(50, 100, p1board);
    drawGrid(450, 100, p2board);
    displayGameState(state);
    displayPlayerInfo();
    window_.display();
}

static void playerGrid(int startX, int startY, sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur de chargement de la police" << std::endl;
        return;
    }

    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(24);
    playerText.setFillColor(sf::Color::White);

    if (startX == 50)
        playerText.setString("Joueur 1");
    else if (startX == 450)
        playerText.setString("Joueur 2");
    else
        playerText.setString("Joueur inconnu");

    sf::FloatRect textBounds = playerText.getLocalBounds();
    playerText.setPosition(startX + 30, startY + 10 * 30 + 10);
    window.draw(playerText);
}

void SfmlPlayer::drawGrid(int startX, int startY, int *board)
{
    for (int i = 0; i < 10; i += 1) {
        for (int j = 0; j < 10; j += 1) {
            sf::RectangleShape cell(sf::Vector2f(30, 30));
            cell.setPosition(startX + i * 30, startY + j * 30);
            cell.setOutlineColor(sf::Color::White);
            cell.setOutlineThickness(1);

            switch (board[i * 10 + j]) {
            case 0:
                cell.setFillColor(sf::Color::Blue);
                break;
            case 1:
                cell.setFillColor(sf::Color::Green);
                break;
            case 2:
                cell.setFillColor(sf::Color::Cyan);
                break;
            case 3:
                cell.setFillColor(sf::Color::Red);
                break;
            }
            window_.draw(cell);
        }
    }
    playerGrid(startX, startY, window_);
}

static void getStatusString(sf::Text &text, Status state)
{
    switch (state) {
    case Status::PREGAME:
        text.setString(L"Préparation du jeu");
        break;
    case Status::P1TURN:
        text.setString("Tour du Joueur 1");
        break;
    case Status::P2TURN:
        text.setString("Tour du Joueur 2");
        break;
    case Status::P1REPLAY:
        text.setString("Joueur 1, rejouez");
        break;
    case Status::P2REPLAY:
        text.setString("Joueur 2, rejouez");
        break;
    case Status::P1WIN:
        text.setString(L"Joueur 1 a gagné!");
        break;
    case Status::P2WIN:
        text.setString(L"Joueur 2 a gagné!");
        break;
    }
}

void SfmlPlayer::displayGameState(Status state)
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur de chargement de la police" << std::endl;
        return;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    getStatusString(text, state);
    text.setPosition(window_.getSize().x / 2 - text.getLocalBounds().width / 2,
                     window_.getSize().y - 50);
    window_.draw(text);
}

void SfmlPlayer::displayPlayerInfo()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur de chargement de la police" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    std::string playerName = "Fenetre joueur " + std::to_string(id_);
    text.setString(playerName);
    text.setPosition(10, 10);

    window_.draw(text);
}
