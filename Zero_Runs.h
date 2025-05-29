#ifndef ZERO_RUNS_H
#define ZERO_RUNS_H

#include <string>

// Takes in a string of integers separated by whitespace, runs of 0's are replaced by "0 [count]" in encoding
//   ie: "0 0 0 1 2 0" <-> "0 3 1 2 0 1"
std::string ZRencode(const std::string &s);
std::string ZRdecode(const std::string &s);

#endif
