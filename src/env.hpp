/**
 * @file env.hpp
 * @author Albert Uchytil (xuchyt03)
 * @brief Envelope model containing instructions for Client
 */
 #ifndef ENV_HPP
 #define ENV_HPP

#include "msg.hpp"

#include <string>
#include <vector>

using namespace std;

enum ip_type { IPv4, IPv6 };

class Envelope
{
public:
  vector<Message> msgs;
  string ip;
  enum ip_type type;
  string port;
  int delay;
};

 #endif //ENV_HPP
