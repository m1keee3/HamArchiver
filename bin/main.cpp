#include <iostream>
#include <fstream>
#include <string>
#include "filework.h"
#include "Pars.h"

using namespace std;

int main(int argc, char** argv) {
    Pars arguments;
    arguments.Parse(argc, argv);
    string arc_path = arguments.arc_name + ".haf";
    string file_path;
    if (arguments.to_create) {
        ofstream archieve(arc_path, ios::binary);
        archieve.close();
        for (string &i : arguments.file_names) {
            file_path = i + ".txt";
            HammingFile(i , file_path, arc_path);
        }
    }
    if (arguments.to_list) {
        List(arc_path);
    }
    if (arguments.to_extract) {
        if (arguments.file_names.empty()) {
            GetAllFiles(arc_path);
        } else {
            for (string &i :arguments.file_names) {
                DecodeFile(i, arc_path);
            }
        }
    }
    if (arguments.to_append) {
        for (string &i : arguments.file_names) {
            file_path = i + ".txt";
            HammingFile(i , file_path, arc_path);
        }
    }
    if (arguments.to_delete) {
        for (string &i : arguments.file_names) {
            DeleteFile(i, arc_path);
        }
    }
    string arc_merge_path_1 = arguments.arc_to_merge_1 + "haf";
    string arc_merge_path_2 = arguments.arc_to_merge_2 + "haf";
    if (arguments.to_concatenate) {
        Merge(arc_path, arc_merge_path_1, arc_merge_path_2);
    }
}