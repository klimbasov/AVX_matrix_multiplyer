#pragma once
#include <exception>
class IlligalArgumentException :
    public std::exception
{
private:
    const char* message;

public:
    IlligalArgumentException(const char* message);
    const char* what() const throw();
};

