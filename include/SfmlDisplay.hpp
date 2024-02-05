#ifndef SFMLDISPLAY_HPP_
#define SFMLDISPLAY_HPP_

#include "IDisplay.hpp"

class SfmlDisplay : public IDisplay {
public:
    SfmlDisplay();
    ~SfmlDisplay();
    void display(int *p1board, int *p2board, Status state);

private:
};

#endif
