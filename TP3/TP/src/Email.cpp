#include "Email.hpp"

Email::Email(std::string &message,
              int ID)
// Descrição: construtor da classe Email
// Entrada: mensagem enviada e ID da mensagem
// Saída: -
{
  this->message = message;
  this->ID = ID;
}