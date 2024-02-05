#ifndef TERMDISPLAY_HPP_
#define TERMDISPLAY_HPP_

#include "IDisplay.hpp"
#include <iostream>

class TermDisplay : public IDisplay {
public:
    TermDisplay(std::istream &i,std::ostream &o);
    TermDisplay();
    void display(int *p1board,int *p2board, Status state);
    
private:
    std::istream &_i{std::cin};
    std::ostream &_o{std::cout};
};

#endif
