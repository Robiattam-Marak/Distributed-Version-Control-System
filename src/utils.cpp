#include "../include/utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <zlib.h>
#include <openssl/sha.h>

std::string readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal: Could not open file " << path << '\n';
        exit(EXIT_FAILURE);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::string toHex(const unsigned char* hash) {
    std::ostringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string decompressZlib(const std::string& compressedData) {
    std::vector<char> decompressed(1024 * 1024);
    z_stream strm = {};
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(compressedData.data()));
    strm.avail_in = compressedData.size();
    strm.next_out = reinterpret_cast<Bytef*>(decompressed.data());
    strm.avail_out = decompressed.size();

    inflateInit(&strm);
    inflate(&strm, Z_NO_FLUSH);
    inflateEnd(&strm);

    return std::string(decompressed.data(), strm.total_out);
}
