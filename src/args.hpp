/**
 * @file args.hpp
 * @author Albert Uchytil
 * @brief Argparser
 */

using namespace std;

class ArgParser {
private:
  vector<string> args;
public:
  ArgParser (int argc, char* argv[]);
  virtual ~ArgParser ();
};
