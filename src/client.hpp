/**
 * @file client.hpp
 * @author Albert Uchytil
 * @brief SMTP client
 */
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "env.hpp"

class Client {
private:
  Envelope *env;
public:
  Client (Envelope *env);
  virtual ~Client ();
  void SendMails();
};

#endif //CLIENT_HPP
