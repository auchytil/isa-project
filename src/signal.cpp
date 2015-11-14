/**
 * @file signal.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SignalHandler
 */

#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include "signal.hpp"
#include "status.hpp"
/**
 * A flag that shows whether a signal was received.
 */
bool SignalHandler::signalReceived = false;

/**
 * Handles received signals.
 */
void SignalHandler::handler(int signum)
{
  SignalHandler::signalReceived = true;
  auto currState = ApplicationStatus::GetCurrent();
  if (currState == State::STARTED || currState == State::FINISHED) {
    std::cerr << "Interrupt: program interupted" << std::endl;
    SignalHandler::Exit();
  } else {
    std::cerr << "Interrupt: Closing connection with remote server" << std::endl;
  }
}

/**
 * Sets up signal handling.
 */
void SignalHandler::SetupHandlers()
{
  if (signal((int)SIGTERM, SignalHandler::handler) == SIG_ERR ||
      signal((int)SIGQUIT, SignalHandler::handler) == SIG_ERR ||
      signal((int)SIGINT, SignalHandler::handler) == SIG_ERR)
    throw "Error: Unable to register signal handler";
}

/**
 * Returns signal status, that shows whether the program should exit.
 */
bool SignalHandler::GetExitStatus()
{
  return SignalHandler::signalReceived;
}

/**
 * Exits in case of receiving a signal.
 */
void SignalHandler::Exit()
{
  if (SignalHandler::signalReceived) {
    exit(1);
  }
}
