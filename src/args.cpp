/**
 * @file args.hpp
 * @author Albert Uchytil
 * @brief Argparser
 */

#include "args.hpp"

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
}

Envelope* ArgParser::GetEnvelope()
{
  return new Envelope;
}
