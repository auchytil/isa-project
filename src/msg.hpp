/**
 * @file msg.hpp
 * @author Albert Uchytil (xuchyt03)
 * @brief Message model
 */
#ifndef MSG_HPP
#define MSG_HPP

#include <string>
#include <vector>

using namespace std;

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
