#include "exception.h"

//конструктор по умолчанию!

MException::MException()
{
    message = "error.";
}

MException::MException(std::string str){
    message = str;
}

std::ostream& operator <<(std::ostream &os, MException &exc){
    os << "exception: " << exc.message << std::endl;
    return os;
}
