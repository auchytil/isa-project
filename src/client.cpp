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

/**
 * Sends E-Mails.
 */
void Client::SendMails()
{
  this->openConnection();
  this->initConnection();

  this->closeConnection();
}

/**
 * Opens connection to SMTP server.
 */
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

  this->readResponse();
}

/**
 * Sends command to SMTP client and returns Status Code.
 *
 * @return int Status of message.
 */
int Client::sendCommand(string cmd)
{
  if (write(this->sock, (cmd + "\r\n").c_str(), cmd.length() + 2) < 0)
    throw "Error: Unable to write to socket.";

  return this->readResponse();
}

/**
 * Read SMTP response.
 *
 * @return int Status Code of the message.
 */
int Client::readResponse()
{
  int len = 0;
  int counter = TIMEOUT;
  while (!len && counter > 0 && ioctl(this->sock, FIONREAD, &len) >= 0) {
    counter--;
    sleep(1);
  }

  if (len <= 0)
    throw "Error: No data received.";

  if (read(this->sock, this->buffer, len) < 0)
    throw "Error: Unable to read from socket";

  stringstream ss(this->buffer);
  int code;
  ss >> code;
  std::cout << code << std::endl;
  return code;
}

/**
 * Initializes SMTP connection.
 */
void Client::initConnection()
{
  string host = "isa.local";
  int code = this->sendCommand("EHLO " + host);
  if (code == 0)
    code++;
}

/**
 * Closes SMTP connection
 */
void Client::closeConnection()
{
  this->sendCommand("QUIT");
}
