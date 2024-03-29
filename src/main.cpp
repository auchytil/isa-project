/**
 * @file main.cpp
 * @author Albert Uchytil
 * @brief Entry point
 */

#include <iostream>

#include "args.hpp"
#include "client.hpp"
#include "env.hpp"
#include "signal.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  try {
    SignalHandler::SetupHandlers();
    ArgParser argparser = ArgParser(argc, argv);
    Envelope *env = argparser.GetEnvelope();
    Client client = Client(env);
    client.SendMails();
    return 0;
  } catch (char const* err) {
    std::cerr << err << std::endl;
    return 1;
  }
}
