/**
 * @file signal.hpp
 * @author Albert Uchytil (xuchyt03)
 * @brief SignalHandler
 */
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

class SignalHandler {
private:
  static bool signalReceived;
  static void handler(int signum);
public:
  static void SetupHandlers();
  static bool GetExitStatus();
  static void Exit();
};

#endif // SIGNAL_HPP
