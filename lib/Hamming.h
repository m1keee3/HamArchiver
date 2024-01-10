#pragma once
#include <vector>
#include <iostream>

using namespace std;

bool PowOfTwo(int value);

vector<bool>& HammingCode(vector<bool>& input_data);

void CalculateParityBits(vector<bool>& data);

vector<bool>& DecodeHammingCode(vector<bool>& input_data, size_t& error_ctr);

int CalculateErrorBit(std::vector<bool>& data);
