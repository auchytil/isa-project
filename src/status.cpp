/**
 * @file status.cpp
 * @author Albert Uchytil (xuchyt03)
 * @brief ApplicationStatus
 */

#include "status.hpp"

/**
 * Current application state.
 */
State ApplicationStatus::currentState = State::STARTED;

/**
 * Gets current application state.
 */
State ApplicationStatus::GetCurrent()
{
  return ApplicationStatus::currentState;
}

/**
 * Sets current application state.
 */
void ApplicationStatus::SetCurrent(State status)
{
  ApplicationStatus::currentState = status;
}
