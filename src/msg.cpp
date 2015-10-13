/**
 * @file msg.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief Message model
 */

#include "msg.hpp"

/**
 * Creates new instance of Message.
 *
 * @param msg_line String defining the message.
 * @throw string When message is invalid.
 */
Message::Message(string msg_line)
{
  auto index = msg_line.find(" ", 0);
  if (index != string::npos) {
    auto mails = msg_line.substr(0, index);
    this->content = msg_line.substr(index + 1);

    stringstream ss(mails);
    string address;
    while (getline(ss, address, ',')) {
      if (isAddrValid(address))
        this->AddRecipient(address);
      else
        throw "Error: Wrong E-Mail address format.";
    }
    if (this->recipients.size() == 0)
      throw "Error: Missing E-Mail address.";
  } else {
    throw "Error: Wrong Message format.";
  }
}

/**
 * Checks wheter the email address is valid.
 *
 * @param mail E-mail address.
 */
bool Message::isAddrValid(string mail)
{
  return true;
  //TODO:
  //return regex_match(mail, regex("[A-Z0-9._+-]+@[A-Z0-9.-]+\\.[A-Z]"));
}

/**
 * Add new recipient to receive a message.
 *
 * @param addr E-mail address
 */
void Message::AddRecipient(string addr)
{
  this->recipients.push_back(addr);
}
