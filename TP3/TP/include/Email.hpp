#ifndef EMAIL
#define EMAIL

#include <string>

class Email{
  public:
    Email(){}
    Email(std::string &message,
          int ID);
          
    std::string message;
    int ID; 
};

#endif