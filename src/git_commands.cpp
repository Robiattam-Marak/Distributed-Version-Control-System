#include "../include/git_commands.hpp"
#include "../include/git_objects.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void cmd_init() {
    fs::create_directory(".git");
    fs::create_directory(".git/objects");
    fs::create_directory(".git/refs");
    std::ofstream headFile(".git/HEAD");
    headFile << "ref: refs/heads/main\n";
    std::cout << "Initialized git directory\n";
}

void cmd_cat_file(const std::string& hexHash) {
    std::string filePath = ".git/objects/" + hexHash.substr(0, 2) + "/" + hexHash.substr(2);
    std::string decompressed = decompressZlib(readFile(filePath));
    size_t nullPos = decompressed.find('\0');
    if (nullPos != std::string::npos) {
        std::cout << decompressed.substr(nullPos + 1);
    }
}

void cmd_hash_object(const std::string& filePath) {
    std::string content = readFile(filePath);
    std::string rawHash = writeGitObject("blob", content);
    std::cout << toHex(reinterpret_cast<const unsigned char*>(rawHash.c_str())) << '\n';
}

void cmd_ls_tree(const std::string& hexHash) {
    std::string filePath = ".git/objects/" + hexHash.substr(0, 2) + "/" + hexHash.substr(2);
    std::string decompressed = decompressZlib(readFile(filePath));
    size_t pos = decompressed.find('\0') + 1;

    while (pos < decompressed.size()) {
        size_t spacePos = decompressed.find(' ', pos);
        size_t nullBytePos = decompressed.find('\0', spacePos);
        std::string name = decompressed.substr(spacePos + 1, nullBytePos - spacePos - 1);
        std::cout << name << '\n';
        pos = nullBytePos + 1 + 20;
    }
}

void cmd_write_tree() {
    std::string rawRootHash = recursiveWriteTree(".");
    std::cout << toHex(reinterpret_cast<const unsigned char*>(rawRootHash.c_str())) << '\n';
}

void cmd_commit_tree(const std::string& tree_sha, const std::string& parent_sha, const std::string& message) {
    std::string content = "tree " + tree_sha + "\n";
    if (!parent_sha.empty()) content += "parent " + parent_sha + "\n";
    content += "author John Doe <john@example.com> 1234567890 +0000\n";
    content += "committer John Doe <john@example.com> 1234567890 +0000\n\n";
    content += message + "\n";

    std::string rawHash = writeGitObject("commit", content);
    std::cout << toHex(reinterpret_cast<const unsigned char*>(rawHash.c_str())) << '\n';
}
