/**
 * @file msg.hpp
 * @author Albert Uchytil (xuchyt03)
 * @brief Message model
 */
#ifndef MSG_HPP
#define MSG_HPP

#include <vector>

class Message
{
private:
  vector<string> recipients;
  string content;
public:
  Message();
  void addRecipient(string addr);
  void setContent();
};

#endif //MSG_HPP
