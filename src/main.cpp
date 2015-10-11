/**
 * @file main.cpp
 * @author Albert Uchytil
 * @brief Entry point
 */

#include <iostream>

#include "args.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  ArgParser argparser = ArgParser(argc, argv);
  cout << "#yolo" << endl;

  return 1;
}
