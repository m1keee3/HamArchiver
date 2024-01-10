#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include "Hamming.h"

using namespace std;

const int CHAR_SIZE = 128;
const int HAM_BITS = 7;
const int MAX_FILE_NAME_SIZE = 255;

size_t GetFileSize(string& file_path);

void HammingFile(string& file_name, string& file_path, string& arc_path);

void DecodeFile(string& file_name, string& output_path, string& arc_path);

void DecodeFile(string& file_name, string& arc_path);

void GetAllFiles(string& arc_path);

void List(string& arc_path);

void Merge(string& arc_path_1, string& arc_path_2, string& arc_path_3);

void DeleteFile(string& file_name, string& arc_path);