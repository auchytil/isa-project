/**
 * @file msg.hpp
 * @author Albert Uchytil (xuchyt03)
 * @brief Message model
 */
#ifndef MSG_HPP
#define MSG_HPP

#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

class Message
{
private:
  static bool isAddrValid(string mail);
public:
  Message(string msg_line);
  vector<string> recipients;
  string content;
  void AddRecipient(string addr);
};

#endif //MSG_HPP
