/**
 * @file client.hpp
 * @author Albert Uchytil
 * @brief SMTP client
 */
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "env.hpp"

#include <cstring>
#include <sstream>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define TIMEOUT 10
#define DEBUG 1
#if DEBUG
  #define log(x) std::cerr << "Log: " << (x) << std::endl
#else
  #define log(x)
#endif

class Client {
private:
  Envelope *env;
  int sock;
  char buffer[BUFFER_SIZE];
  void openConnection();

  int sendCommand(string cmd);
  int readResponse();

  void initConnection();
  void sendMessage(Message msg);
  void setSender();
  void setRecipients();
  void closeConnection();

  void checkInterrupt();
public:
  Client (Envelope *env);
  virtual ~Client ();
  void SendMails();
};

#endif //CLIENT_HPP
