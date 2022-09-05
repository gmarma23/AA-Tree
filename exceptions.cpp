#include <iostream>
#include "exceptions.h"

using std::cerr;
using std::endl;
using std::string;

void Exception::printErrorMessage(string msg){ 
    cerr << msg << endl; 
}

DuplicateElementsException::DuplicateElementsException(string msg){ 
    this->msg = msg; 
}

ElementNotFoundException::ElementNotFoundException(string msg){ 
    this->msg = msg; 
}