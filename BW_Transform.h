#ifndef BW_TRANSFORM_H
#define BW_TRANSFORM_H

#include <string>

// Encodes a string using the Burrows-Wheeler Transform.
// The input string will be modified to include a '\0' terminator at the end.
// Returns the encoded string.
std::string BWencode(std::string &s);

// Decodes a Burrows-Wheeler encoded string.
// The string must contain exactly one '\0' character.
// Throws if '\0' is missing.
// Returns the decoded string.
std::string BWdecode(std::string &s);

#endif
