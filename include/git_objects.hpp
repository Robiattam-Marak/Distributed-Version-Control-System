#pragma once
#include <string>
#include <filesystem>

struct TreeEntry {
    std::string mode;
    std::string name;
    std::string raw_sha;

    bool operator<(const TreeEntry& other) const {
        return name < other.name;
    }
};

// Core object creation
std::string writeGitObject(const std::string& type, const std::string& content);
std::string recursiveWriteTree(const std::filesystem::path& dirPath);
