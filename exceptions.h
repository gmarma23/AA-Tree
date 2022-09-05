#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class Exception{
public: 
    void printErrorMessage(std::string msg = "Exception");
};

class DuplicateElementsException : public Exception{
public:
    std::string msg;
    DuplicateElementsException(std::string msg = "DuplicateElementsException");
};

class ElementNotFoundException : public Exception{
public:
    std::string msg;
    ElementNotFoundException(std::string msg = "ElementNotFoundException");
};

#endif