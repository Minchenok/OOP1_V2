#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

class MException
{
    std::string message;
public:
    MException();
    MException(std::string str);

    friend std::ostream& operator <<(std::ostream &os, MException &exc);
};
#endif // EXCEPTION_H
