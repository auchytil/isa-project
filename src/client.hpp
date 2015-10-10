/**
 * @file client.hpp
 * @author Albert Uchytil
 * @brief SMTP client
 */
#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {
private:
  /* data */
public:
  Client (Message *msg);
  virtual ~Client ();
};

#endif //CLIENT_HPP
