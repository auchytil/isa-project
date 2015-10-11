/**
 * @file client.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SMTP client
 */

 #include "client.hpp"

Client::Client(Envelope *env)
{
  this->env = env;
}

Client::~Client ()
{
  delete this->env;
}

void Client::SendMails()
{

}
