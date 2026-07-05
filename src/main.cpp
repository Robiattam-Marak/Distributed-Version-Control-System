#include <iostream>
#include <string>
#include "../include/git_commands.hpp"

int main(int argc, char *argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 2) {
        std::cerr << "No command provided.\n";
        return EXIT_FAILURE;
    }

    std::string command = argv[1];

    if (command == "init") {
        cmd_init();
    }
    else if (command == "cat-file" && argc >= 4 && std::string(argv[2]) == "-p") {
        cmd_cat_file(argv[3]);
    }
    else if (command == "hash-object" && argc >= 4 && std::string(argv[2]) == "-w") {
        cmd_hash_object(argv[3]);
    }
    else if (command == "ls-tree" && argc >= 4 && std::string(argv[2]) == "--name-only") {
        cmd_ls_tree(argv[3]);
    }
    else if (command == "write-tree") {
        cmd_write_tree();
    }
    else if (command == "commit-tree") {
        std::string tree_sha = argv[2];
        std::string parent_sha = "";
        std::string message = "";

        for (int i = 3; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-p" && i + 1 < argc) parent_sha = argv[++i];
            else if (arg == "-m" && i + 1 < argc) message = argv[++i];
        }
        cmd_commit_tree(tree_sha, parent_sha, message);
    }
    else {
        std::cerr << "Unknown command: " << command << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
