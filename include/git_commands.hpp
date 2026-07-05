#pragma once
#include <string>

// The individual git commands
void cmd_init();
void cmd_cat_file(const std::string& hexHash);
void cmd_hash_object(const std::string& filePath);
void cmd_ls_tree(const std::string& hexHash);
void cmd_write_tree();
void cmd_commit_tree(const std::string& tree_sha, const std::string& parent_sha, const std::string& message);
