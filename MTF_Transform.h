#ifndef MTF_TRANSFORM_H
#define MTF_TRANSFORM_H

#include <string>



// using the Move To Front Transformation to convert to integers
//   the integers will be space delimited
//   starting with the 256 (8 bit) ASCII table
std::string MTFencode(std::string &s);
// std::string MTFdecode(std::string &s);

#endif
