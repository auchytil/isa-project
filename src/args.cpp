/**
 * @file args.hpp
 * @author Albert Uchytil
 * @brief Argparser
 */

#include "args.hpp"

#include <iostream>

using namespace std;

/**
 * ArgParser constructor.
 *
 * @param argc Argument count
 * @param argv Arguments
 */
ArgParser::ArgParser(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++) {
    this->args.push_back(string(argv[i]));
  }
  if (this->parseArgs()) {
    if (filename == "") {
      std::cerr << "Required '-i' argument." << std::endl;
      exit(1);
    }
  } else {
    cerr << "Invalid arguments." << endl;
    exit(1);
  }
}

/**
 * Creates envelope for Client.
 *
 * @return Envelope* New instance of Envelope.
 */
Envelope* ArgParser::GetEnvelope()
{
  Envelope* env = new Envelope;
  env->ip = this->ip;
  env->port = this->port;
  env->delay = this->delay;
  env->type = this->type;

  return env;
}

/**
 * Sets SMTP client delay.
 *
 * @param delay Delay in seconds.
 */
void ArgParser::setDelay(string delay)
{

}

/**
 * Sets SMTP server IP.
 *
 * @param ip IP of SMTP server to connect.
 */
void ArgParser::setIP(string ip)
{

}

/**
 * Parses arguments and checks if they're valid.
 *
 * @return bool Valid args.
 */
bool ArgParser::parseArgs()
{
  unsigned arg_count = this->args.size();
  for (unsigned i = 0; i < arg_count; i++) {
    auto current_value = this->args[i];
    unsigned next_index = i + 1;

    if (current_value == "-a") { //IP
      if (next_index < arg_count)
        this->setIP(this->args[i+1]);
      else
        return false;
    }

    if (current_value == "-p") { //port
      if (next_index < arg_count)
        this->port = this->args[i+1];
      else
        return false;
    }

    if (current_value == "-i") { //file
      if (next_index < arg_count)
        this->filename = this->args[i+1];
      else
        return false;
    }

    if (current_value == "-w") { //delay
      if (next_index < arg_count)
        this->setDelay(this->args[i+1]);
      else
        return false;
    }
  }
  return true;
}
