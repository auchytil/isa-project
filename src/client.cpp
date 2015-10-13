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
  this->openConnection();
}

void Client::openConnection()
{
  struct sockaddr_in socket_in;

  if ((this->sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    throw "Error: Unable to create socket.";

  //TODO: PF_INET6
  socket_in.sin_family = PF_INET;
  socket_in.sin_addr.s_addr = inet_addr(this->env->ip.c_str());
  socket_in.sin_port = htons(this->env->port);

  if (connect(this->sock, (struct sockaddr *) &socket_in, sizeof(socket_in)) < 0)
    throw "Error: Unable to connect to SMTP server.";
}
