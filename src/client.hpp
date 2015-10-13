/**
 * @file client.hpp
 * @author Albert Uchytil
 * @brief SMTP client
 */
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "env.hpp"

#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <unistd.h>

class Client {
private:
  Envelope *env;
  int sock;
  void openConnection();
public:
  Client (Envelope *env);
  virtual ~Client ();
  void SendMails();
};

#endif //CLIENT_HPP
