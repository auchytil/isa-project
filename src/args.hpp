/**
 * @file args.hpp
 * @author Albert Uchytil
 * @brief ArgParser
 */
#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>
#include <vector>

using namespace std;

class ArgParser {
private:
  vector<string> args;
  string ip = "127.0.0.1";
  string port = "25";
  string filename;
  int delay = 0;
public:
  ArgParser (int argc, char* argv[]);
};

#endif // ARGS_HPP
