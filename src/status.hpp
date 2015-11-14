/**
 * @file status.hpp
 * @author Albert Uchytil (xuchyt03)
 * @brief ApplicationStatus
 */
#ifndef STATUS_HPP
#define STATUS_HPP

enum class State { STARTED = 0, INIT, SENDING, FINISHED };

class ApplicationStatus {
protected:
  static State currentState;
public:
  static State GetCurrent();
  static void SetCurrent(State state);
};

#endif // STATUS_HPP
