#include "../include/TermPlayer.hpp"
#include <iostream>

TermPlayer::TermPlayer(int id) : _id(id){};

TermPlayer::TermPlayer(std::istream &i, std::ostream &o, int id)
    : _id{id}, _i{i}, _o{o} {};

void printStatus(std::ostream &o, Status state)
{
    if (state == Status::PREGAME)
        o << "\n Mise en place du jeu\n\n";
    else if (state == Status::P1TURN)
        o << "\n Au joueur 1 de jouer !\n\n";
    else if (state == Status::P2TURN)
        o << "\n Au joueur 2 de jouer !\n\n";
    else if (state == Status::P1REPLAY)
        o << "\n Le joueur 1 doit rejouer !\n\n";
    else if (state == Status::P2REPLAY)
        o << "\n Le joueur 2 doit rejouer !\n\n";
    else if (state == Status::P1WIN)
        o << "\n Le joueur 1 a gagné\n\n";
    else if (state == Status::P2WIN)
        o << "\n Le joueur 2 a gagné\n\n";
}

void printRow(int width, std::ostream &o)
{
    char top = 'A';
    o << "     ";
    for (size_t i = 0; i < width; i++) {
        o << (top) << " ";
        top += 1;
    }
}

void printBoard(int *board, std::ostream &o, int width)
{
    o << "\n\n";
    int vertical = 0;
    o << " " << vertical << "   ";
    vertical += 1;
    for (int i = 0; i <= 100; ++i) {
        if (i % width == 0 && i != 0) {
            o << '\n';
            if (vertical < 10) {
                o << " " << vertical << "   ";
                vertical += 1;
            }
        }
        if (board[i] == 1 && i < 100)
            o << '+';
        else if (board[i] == 2 && i < 100)
            o << 'x';
        else if (board[i] == 3 && i < 100)
            o << 'o';
        else if (board[i] == 0 && i < 100)
            o << '.';
        o << ' ';
    }
    o << '\n';
}

void printOppenentBoard(int *board, std::ostream &o, int width)
{
    o << "\n\n";
    int vertical = 0;
    o << " " << vertical << "   ";
    vertical += 1;
    for (int i = 0; i <= 100; ++i) {
        if (i % width == 0 && i != 0) {
            o << '\n';
            if (vertical < 10) {
                o << " " << vertical << "   ";
                vertical += 1;
            }
        }
        if (board[i] == 1 && i < 100)
            o << '.';
        else if (board[i] == 2 && i < 100)
            o << 'x';
        else if (board[i] == 3 && i < 100)
            o << 'o';
        else if (board[i] == 0 && i < 100)
            o << '.';
        o << ' ';
    }
    o << '\n';
}

void TermPlayer::display(int *p1board, int *p2board, Status state)
{
    int width = 10;
    system("clear");
    _o << "\n Votre tableau (P" << _id << "): \n\n";
    printRow(width, _o);
    if (_id == 1) {
        printBoard(p1board, _o, width);
        _o << "\n Tableau P2 : \n\n";
        printRow(width, _o);
        printOppenentBoard(p2board, _o, width);
    } else {
        printBoard(p2board, _o, width);
        _o << "\n Tableau P1 : \n\n";
        printRow(width, _o);
        printOppenentBoard(p1board, _o, width);
    }

    printStatus(_o, state);
}

std::tuple<int, int> TermPlayer::play()
{
start:
    std::string          choice = "";
    std::tuple<int, int> pos;
    _o << "Sur quel case voulez vous tirer ?\n\n";
    _i >> choice;
    char letter = choice[0];
    if (choice.length() != 2 || choice[1] < '0' || choice[1] > '9') {
        _o << "Merci de choisir une case valide !\n\n";
        goto start;
    }
    int y = std::stoi(choice.substr(1));
    if (y < 0 || y > 9 || letter < 'A' || letter > 'J') {
        _o << "Merci de choisir une case valide !\n\n";
        goto start;
    }
    int x = letter - 'A';

    pos = std::make_tuple(x, y);
    return (pos);
}
