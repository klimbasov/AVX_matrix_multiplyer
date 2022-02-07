#include "IlligalArgumentException.h"

IlligalArgumentException::IlligalArgumentException(const char* message) : exception(message){}

const char* IlligalArgumentException::what() const throw()
{
    return exception::what();
}
