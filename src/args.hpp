/**
 * @file args.hpp
 * @author Albert Uchytil
 * @brief ArgParser
 */
#ifndef ARGS_HPP
#define ARGS_HPP

#include "env.hpp"

#include <string>
#include <vector>

using namespace std;

class ArgParser {
private:
  vector<string> args;
  string ip = "127.0.0.1";
  string port = "25";
  enum ip_type type = IPv4;
  string filename = "";
  int delay = 0;
  void setDelay(string delay);
  void setIP(string ip);
  bool parseArgs();
public:
  ArgParser (int argc, char* argv[]);
  Envelope* GetEnvelope();
};

#endif // ARGS_HPP
