/**
 * @file msg.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief Message model
 */

#include "msg.hpp"

/**
 * Add new recipient to receive a message.
 *
 * @param addr E-mail address
 */
void Message::addRecipient(string addr)
{
  this->recipients.push_back(addr);
}
