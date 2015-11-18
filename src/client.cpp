/**
 * @file client.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SMTP client
 */

 #include "client.hpp"
 #include "signal.hpp"
 #include "status.hpp"

Client::Client(Envelope *env)
{
  if (env == NULL)
    throw "Error: Envelope cannot be NULL.";
  this->env = env;
}

Client::~Client ()
{
  delete this->env;
}

/**
 * Checks whether program was interrupted.
 */
void Client::checkInterrupt()
{
  if (SignalHandler::GetExitStatus()) {
    this->closeConnection();
    std::cerr << "Error: Interrupted" << std::endl;
    exit(1);
  }
}

/**
 * Sends E-Mails.
 */
void Client::SendMails()
{
  ApplicationStatus::SetCurrent(State::INIT);
  this->openConnection();
  this->initConnection();
  this->checkInterrupt();
  int sent = 0;
  ApplicationStatus::SetCurrent(State::SENDING);
  for (unsigned i = 0; i < this->env->msgs.size(); i++) {
    try {
      auto msg = this->env->msgs[i];
      this->sendMessage(msg);
      sent++;
    } catch (char const *err) {
      std::cerr << "Error: Was not able to send email no.";
      std::cerr << i << "." << std::endl;
    }
    this->checkInterrupt();
  }
  this->closeConnection();
  ApplicationStatus::SetCurrent(State::FINISHED);

  if (sent == 0)
    throw "Error: Client was not able to send any E-Mails.";
}

/**
 * Opens connection to SMTP server.
 */
void Client::openConnection()
{
  struct sockaddr_in socket_in;
  struct timeval timeout;
  fd_set fdset;

  if ((this->sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    throw "Error: Unable to create socket.";

  fcntl(this->sock, F_SETFL, O_NONBLOCK);

  socket_in.sin_family = this->env->type;
  socket_in.sin_addr.s_addr = inet_addr(this->env->ip.c_str());
  socket_in.sin_port = htons(this->env->port);

  /*if (*/connect(this->sock, (struct sockaddr *) &socket_in, sizeof(socket_in));/* < 0)
    throw "Error: Unable to connect to SMTP server.";*/

  FD_ZERO(&fdset);
  FD_SET(this->sock, &fdset);
  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = 0;

  if (select(this->sock + 1, NULL, &fdset, NULL, &timeout) == 1) {
    int err;
    socklen_t len = sizeof(err);
    if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len) != 0)
      throw "Error: Problem with connection to the socket.";
  } else
    throw "Error: Timeout.";

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
  return code;
}

/**
 * Initializes SMTP connection.
 */
void Client::initConnection()
{
  log("Initializing connection");
  string host = "isa.local";
  int code = this->sendCommand("EHLO " + host);
  if (code != 250)
    throw "Error: Invalid SMTP host.";
}

/**
 * Send particular Message.
 *
 * @param msg Message data.
 */
void Client::sendMessage(Message msg)
{
  log("Setting MAIL FROM");
  this->setSender();
  this->checkInterrupt();
  for (unsigned i = 0; i < msg.recipients.size(); i++) {
    log("Setting RCPT TO");
    auto rcpt = msg.recipients[i];
    int code = this->sendCommand("RCPT TO: <" + rcpt + ">");
    if (code != 250) {
      std::cerr << "Error: There was problem with sending mail to ";
      std::cerr << rcpt << "." << std::endl;
    }
    this->checkInterrupt();
  }
  log("Setting DATA");
  int code = this->sendCommand("DATA");
  if (code != 354)
    throw "Error: Unable to send email.";

  log("Sending mail content");
  string data = msg.content + "\r\n.";
  code = this->sendCommand(data);
  if (code != 250)
    throw "Error: Unable to send email.";
  this->checkInterrupt();
}

/**
 * Sets SMTP
 */
void Client::setSender()
{
  string mail = "xuchyt03@isa.local";
  this->sendCommand("MAIL FROM: <" + mail + ">");
}

/**
 * Closes SMTP connection
 */
void Client::closeConnection()
{
  if (!SignalHandler::GetExitStatus())
    sleep(this->env->delay);
  log("Closing connection");
  this->sendCommand("QUIT");
  if (close(this->sock) != 0)
    throw "Error: Unable to close socket";
}
