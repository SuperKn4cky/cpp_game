#pragma once

#include <SFML/Network.hpp>
#include <vector>
#include "IDisplay.hpp"
#include "IPlayer.hpp"
#include "Status.hpp"

class Game {
public:
    // enum class PlayResult {
    //     OK,
    //     OutsideBoard,
    //     InvalidMove,
    //     Victory,
    //     GameEnded,
    //     Miss,
    //     Replay,
    // };

    Game(int port);
    ~Game();

    const int *get_p1board() const;
    void       set_p1board(int value, int index);
    void       set_p1board(int *i);

    const int *get_p2board() const;
    void       set_p2board(int value, int index);
    void       set_p2board(int *i);

    Status get_status() const;
    void   set_status(Status state);

    sf::TcpListener       &get_lstnr();
    std::vector<IDisplay> &get_specs();
    IPlayer               *get_player1() const;
    IPlayer               *get_player2() const;
    void                   set_player1(IPlayer *p);
    void                   set_player2(IPlayer *p);
    int                    currentPlayer();

    Status play(unsigned int x, unsigned int y);
    void   dump(std::ostream &) const;
    void   display_all();

private:
    Status _play(unsigned int x, unsigned int y);
    void   _set_current_player_replay();
    void   _set_current_player_win();
    void   _set_current_player_turn();
    void   _swap_turn();
    bool   _isGameOver() const;
    void   _placeBoats(int *board);
    bool   _isValidPlacement(const int *board, unsigned int x, unsigned int y,
                             unsigned int size, unsigned int direction) const;
    void   _updateStatus();
    bool   _isBoardEmpty(const int *board) const;

    int                   currentPlayer_;
    int                  *p1board_;
    int                  *p2board_;
    Status                status_{Status::PREGAME};
    IPlayer              *player1_;
    IPlayer              *player2_;
    std::vector<IDisplay> specs_;
    sf::TcpListener       lstnr_;
};
