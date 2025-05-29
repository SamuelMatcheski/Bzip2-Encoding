#ifndef HUFFMAN_ENDCODING_H
#define HUFFMAN_ENCODING_H

#include <string>
#include <vector>

std::string HUFFencode(const std::string &s, std::vector<int> &vec);
std::string HUFFdecode(const std::string &s, std::vector<int> &serializedTrie);


#endif
