/**
 * @file client.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SMTP client
 */

 #include "client.hpp"

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
 * Sends E-Mails.
 */
void Client::SendMails()
{
  this->openConnection();
  this->initConnection();
  int sent = 0;
  for (unsigned i = 0; i < this->env->msgs.size(); i++) {
    try {
      auto msg = this->env->msgs[i];
      this->sendMessage(msg);
      sent++;
    } catch (char const *err) {
      std::cerr << "Error: Was not able to send email no.";
      std::cerr << i << "." << std::endl;
    }
  }
  this->closeConnection();

  if (sent == 0)
    throw "Error: Client was not able to send any E-Mails.";
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
  return code;
}

/**
 * Initializes SMTP connection.
 */
void Client::initConnection()
{
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
  this->setSender();
  for (unsigned i = 0; i < msg.recipients.size(); i++) {
    auto rcpt = msg.recipients[i];
    int code = this->sendCommand("RCPT TO: <" + rcpt + ">");
    if (code != 250) {
      std::cerr << "Error: There was problem with sending mail to ";
      std::cerr << rcpt << "." << std::endl;
    }
  }
  int code = this->sendCommand("DATA");
  if (code != 354)
    throw "Error: Unable to send email.";

  string data = msg.content + "\r\n.";
  code = this->sendCommand(data);
  if (code != 250)
    throw "Error: Unable to send email.";
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
  this->sendCommand("QUIT");
}
