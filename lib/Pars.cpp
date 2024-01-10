#include "Pars.h"
#include <cstring>

void Pars::Parse(int argc, char **argv) {
    for (size_t i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if ((strcmp(argv[i], "--create") == 0) || (strcmp(argv[i], "-c") == 0)) {
                to_create = true;
            } else if ((strcmp(argv[i], "--list") == 0) || (strcmp(argv[i], "-l") == 0)) {
                to_list = true;
            } else if ((strcmp(argv[i], "--extract") == 0) || (strcmp(argv[i], "-x") == 0)) {
                to_extract = true;
            } else if ((strcmp(argv[i], "--append") == 0) || (strcmp(argv[i], "-a") == 0)) {
                to_append = true;
            } else if ((strcmp(argv[i], "--delete") == 0) || (strcmp(argv[i], "-d") == 0)) {
                to_delete = true;
            } else if ((strcmp(argv[i], "--concatenate") == 0) || (strcmp(argv[i], "-A") == 0)) {
                to_concatenate = true;
                arc_to_merge_1 = argv[++i];
                arc_to_merge_2 = argv[++i];
            } else if (strcmp(argv[i], "-f") == 0) {
                i++;
                arc_name = argv[i];
            } else {
                std::string arg = argv[i];
                std::string new_arg = arg.substr(0, 7);
                if (new_arg == "--file=") {
                    arc_name = arg.substr(7, arg.size() - 7);
                }
            }
        } else {
            file_names.emplace_back(argv[i]);
        }
    }
}