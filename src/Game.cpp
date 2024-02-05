#include "../include/Game.hpp"
#include <SFML/Network.hpp>
#include <iostream>

Game::Game(int port)
{
    if (lstnr_.listen(port) != sf::Socket::Done)
        throw std::runtime_error("ctor:listen");
    status_  = Status::PREGAME;
    // p1board_ = new int[100]{0};
    // p2board_ = new int[100]{0};
    // _placeBoats(p1board_);
    // _placeBoats(p2board_);
    currentPlayer_ = 1;
}

Game::~Game()
{
    if (p1board_ != nullptr) {
        delete[] p1board_;
    }
    if (p2board_ != nullptr) {
        delete[] p2board_;
    }
}

const int *Game::get_p1board() const
{
    return p1board_;
}

void Game::set_p1board(int value, int index)
{
    p1board_[index] = value;
}

void Game::set_p1board(int *i)
{
    p1board_ = i;
}

const int *Game::get_p2board() const
{
    return p2board_;
}

void Game::set_p2board(int value, int index)
{
    p2board_[index] = value;
}

void Game::set_p2board(int * i)
{
    p2board_ = i;
}

Status Game::get_status() const
{
    return status_;
}

void Game::set_status(Status state)
{
    status_ = state;
}

sf::TcpListener &Game::get_lstnr()
{
    return lstnr_;
}

IPlayer *Game::get_player1() const
{
    return player1_;
}

IPlayer *Game::get_player2() const
{
    return player2_;
}

void Game::set_player1(IPlayer *p)
{
    player1_ = p;
}

void Game::set_player2(IPlayer *p)
{
    player2_ = p;
}

int Game::currentPlayer()
{
    return currentPlayer_;
}

Status Game::play(unsigned int x, unsigned int y)
{
    return _play(x, y);
}

void Game::dump(std::ostream &os) const
{
    os << "Game state: ";
    os << "Player 1 Remaining Ships: "
       << (!_isBoardEmpty(p1board_) ? "Yes" : "No")
       << ", Player 2 Remaining Ships: "
       << (!_isBoardEmpty(p2board_) ? "Yes" : "No") << "\n";
    os << "Player 1 Board: ";
    for (int i = 0; i < 100; ++i) {
        os << p1board_[i] << " ";
    }
    os << "\nPlayer 2 Board: ";
    for (int i = 0; i < 100; ++i) {
        os << p2board_[i] << " ";
    }
    os << "\n";
}

void Game::display_all()
{
    player1_->display(p1board_, p2board_, status_);
    player2_->display(p1board_, p2board_, status_);
}

void Game::_set_current_player_win()
{
    if (status_ == Status::P1TURN || status_ == Status::P1REPLAY) {
        status_ = Status::P1WIN;
    } else if (status_ == Status::P2TURN || status_ == Status::P2REPLAY) {
        status_ = Status::P2WIN;
    }
}

void Game::_swap_turn()
{
    currentPlayer_ = (currentPlayer_ == 1) ? 2 : 1;
}

void Game::_set_current_player_replay()
{
    if (currentPlayer_ == 1)
        status_ = Status::P1REPLAY;
    else
        status_ = Status::P2REPLAY;
}

void Game::_set_current_player_turn()
{
    if (currentPlayer_ == 1)
        status_ = Status::P1TURN;
    else
        status_ = Status::P2TURN;
}

Status Game::_play(unsigned int x, unsigned int y)
{
    int         *oppnt_plyr_board;
    unsigned int index = y * 10 + x;

    _set_current_player_turn();
    if (currentPlayer_ == 1)
        oppnt_plyr_board = p2board_;
    else
        oppnt_plyr_board = p1board_;
    if (x >= 10 || y >= 10 || oppnt_plyr_board[index] == 2 || oppnt_plyr_board[index] == 3)
        _set_current_player_replay();
    else if (oppnt_plyr_board[index] == 0)
        oppnt_plyr_board[index] = 3;
    else if (oppnt_plyr_board[index] == 1) {
        oppnt_plyr_board[index] = 2;
        _set_current_player_replay();
    }
    if (_isGameOver()) {
        _set_current_player_win();
        return status_;
    }
    _updateStatus();
    std::cout << static_cast<int>(status_) << ' ' << currentPlayer_ << std::endl;
    return status_;
}

void Game::_placeBoats(int *board)
{
    unsigned int ships[] = {5, 4, 3, 3, 2};
    for (unsigned int i = 0; i < 5; ++i) {
        unsigned int ship_size = ships[i];
        unsigned int start     = rand() % 100;
        unsigned int direction = rand() % 2;
        unsigned int increment = (direction == 0) ? 1 : 10;

        while (!_isValidPlacement(board, start % 10, start / 10, ship_size,
                                  direction)) {
            start     = rand() % 100;
            direction = rand() % 2;
            increment = (direction == 0) ? 1 : 10;
        }

        for (unsigned int j = 0; j < ship_size; ++j) {
            board[(start / 10 + j * increment) * 10 + start % 10 +
                  j * increment] = 1;
        }
    }
}

bool Game::_isValidPlacement(const int *board, unsigned int x, unsigned int y,
                             unsigned int size, unsigned int direction) const
{
    unsigned int increment = (direction == 0) ? 1 : 10;

    if (x + (size - 1) * increment >= 10 || y + (size - 1) * increment >= 10) {
        return false; // ship goes out of bounds
    }

    for (unsigned int i = 0; i < size; ++i) {
        if (board[(y + i * increment) * 10 + x + i * increment] == 1) {
            return false; // ship overlaps with another ship
        }
    }

    return true;
}

void Game::_updateStatus()
{
    if (status_ == Status::P1REPLAY || status_ == Status::P2REPLAY) {
        // If in replay status, continue with the same player's turn
        return;
    }
    _swap_turn();
    if (currentPlayer_ == 1)
        status_ = Status::P1TURN;
    else
        status_ = Status::P2TURN;
}

bool Game::_isBoardEmpty(const int *board) const
{
    // Check if the board has any remaining ship parts
    for (int i = 0; i < 100; ++i) {
        if (board[i] == 1) {
            return false; // Board is not empty
        }
    }
    return true; // Board is empty
}

bool Game::_isGameOver() const
{
    return (_isBoardEmpty(p1board_) || _isBoardEmpty(p2board_));
}
