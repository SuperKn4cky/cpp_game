#include "../include/TermDisplay.hpp"
#include "../include/TermPlayer.hpp"
#include <iostream>


/*int main()
{
    TermPlayer TermPlayer(1);
    std::tuple<int, int> position = TermPlayer.play();
    std::cout << "Position choisie : (" << std::get<0>(position) << ", " << std::get<1>(position) << ")" << std::endl;

    return 1;
}*/

/*int main()
{
    TermDisplay TermDisplay;
    int p1board[100] = {0, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 3, 1, 1, 3, 3, 3, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0};
                                
    int p2board[100] = {3, 0, 0, 3, 3, 0, 0, 0, 3,0,
                        2, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        2, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        2, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        2, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        2, 0, 3, 1, 1, 3, 3, 3, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0};
    Status state = Status::PREGAME;

    TermDisplay.display(p1board, p2board, state);
    TermDisplay.display(p1board, p2board, state);

    return 1;
}*/

int main()
{
    TermPlayer TermPlayer(2);
    int p1board[100] = {0, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 3, 1, 1, 3, 3, 3, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0};
                                
    int p2board[100] = {3, 0, 0, 3, 3, 0, 0, 0, 3,0,
                        2, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        2, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        2, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        2, 0, 0, 2, 2, 0, 0, 0, 2,0,
                        2, 0, 3, 1, 1, 3, 3, 3, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0,
                        1, 0, 0, 1, 1, 0, 0, 0, 1,0};
    Status state = Status::PREGAME;

    TermPlayer.display(p1board, p2board, state);
    TermPlayer.display(p1board, p2board, state);

    return 1;
}