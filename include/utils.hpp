#pragma once
#include <string>

// I/O and Formatting helpers
std::string readFile(const std::string& path);
std::string toHex(const unsigned char* hash);
std::string decompressZlib(const std::string& compressedData);
