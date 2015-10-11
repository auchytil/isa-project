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
public:
  Message();
  Message(string line);
  vector<string> recipients;
  string content;
  void addRecipient(string addr);
};

#endif //MSG_HPP
