#include "../include/TermDisplay.hpp"

TermDisplay::TermDisplay() {}
TermDisplay::TermDisplay(std::istream &i, std::ostream &o): _i{i}, _o{o} {}

void printBoard(int *board,std::ostream &o, int width)
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
            o << 'o';
        else if (board[i] == 3 && i < 100)
            o << 'x';
        else if (board[i] == 0 && i < 100)
            o << '.';

        o << ' ';
    }
    o << '\n';
}

void printStatus(std::ostream &o,Status state)
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

void TermDisplay::display(int *p1board, int *p2board, Status state)
{
    int width = 10;

    system("clear");
    _o << "\n Tableau P1 : \n\n";
    char top = 'A';
    _o << "     ";
    for (size_t i = 0; i < width; i++) {
        _o << (top) << " ";
        top += 1;
    }
    printBoard(p1board,_o, width);

    _o << "\n Tableau P2 : \n\n";
    top = 'A';
    _o << "     ";
    for (size_t i = 0; i < width; i++) {
        _o << (top) << " ";
        top += 1;
    }
    printBoard(p2board,_o, width);

    printStatus(_o,state);
}
