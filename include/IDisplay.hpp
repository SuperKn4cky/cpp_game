#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include "Status.hpp"

class IDisplay {
public:
    virtual ~IDisplay()                                            = default;
    virtual void display(int *p1board, int *p2board, Status state) = 0;
};

#endif
