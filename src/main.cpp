/**
 * @file main.cpp
 * @author Albert Uchytil
 * @brief Entry point
 */

#include <iostream>

#include "args.hpp"
#include "client.hpp"
#include "env.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  ArgParser argparser = ArgParser(argc, argv);
  Envelope *env = argparser.GetEnvelope();
  Client client = Client(env);
  client.SendMails();

  return 0;
}
