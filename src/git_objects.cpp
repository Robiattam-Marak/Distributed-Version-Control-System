#include "../include/git_objects.hpp"
#include "../include/utils.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <zlib.h>
#include <openssl/sha.h>

namespace fs = std::filesystem;

std::string writeGitObject(const std::string& type, const std::string& content) {
    std::string store = type + " " + std::to_string(content.size()) + '\0' + content;

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(store.c_str()), store.size(), hash);
    std::string hexHash = toHex(hash);

    uLongf compressedSize = compressBound(store.size());
    std::vector<Bytef> compressedData(compressedSize);
    compress(compressedData.data(), &compressedSize, reinterpret_cast<const Bytef*>(store.c_str()), store.size());

    std::string dirName = hexHash.substr(0, 2);
    std::string fileName = hexHash.substr(2);
    std::string objectDirPath = ".git/objects/" + dirName;

    fs::create_directories(objectDirPath);
    std::ofstream outFile(objectDirPath + "/" + fileName, std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(compressedData.data()), compressedSize);

    return std::string(reinterpret_cast<char*>(hash), SHA_DIGEST_LENGTH);
}

std::string recursiveWriteTree(const fs::path& dirPath) {
    std::vector<TreeEntry> entries;

    for (const auto& entry : fs::directory_iterator(dirPath)) {
        std::string name = entry.path().filename().string();
        if (name == ".git") continue;

        if (entry.is_regular_file()) {
            std::string content = readFile(entry.path().string());
            std::string rawSha = writeGitObject("blob", content);
            entries.push_back({"100644", name, rawSha});
        }
        else if (entry.is_directory()) {
            std::string rawSha = recursiveWriteTree(entry.path());
            entries.push_back({"40000", name, rawSha});
        }
    }

    std::sort(entries.begin(), entries.end());

    std::string treeContent = "";
    for (const auto& e : entries) {
        treeContent += e.mode + " " + e.name + '\0' + e.raw_sha;
    }

    return writeGitObject("tree", treeContent);
}
