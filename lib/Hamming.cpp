#include "Hamming.h"

using namespace std;

bool PowOfTwo(int value) {
    while (value > 1) {
        if (value % 2 > 0) {
            return false;
        }
        value /= 2;
    }
    return true;
}

vector<bool>& HammingCode(vector<bool>& input_data) {
    int original_size = input_data.size();
    int parity_bits = 0;
    while ((original_size + parity_bits + 1) > (1 << parity_bits)) {
        parity_bits++;
    }

    std::vector<bool> output_data(original_size + parity_bits);
    int data_index = 0;

    for (int i = 0; i < original_size + parity_bits; i++) {
        if (PowOfTwo(i + 1)) {
            output_data[i] = false;
        } else {
            output_data[i] = input_data[data_index];
            data_index++;
        }
    }

    CalculateParityBits(output_data);
    return *new vector<bool>(output_data);
}

void CalculateParityBits(vector<bool>& data) {
    int n = data.size();
    for (int i = 0; i < n; i++) {
        if (PowOfTwo(i + 1)) {
            bool parity = false;
            for (int j = i; j < n; j += (i + 1) * 2) {
                for (int k = 0; k < i + 1 && j + k < n; k++) {
                    if (j != i || k != 0) {
                        parity ^= data[j + k];
                    }
                }
            }
            data[i] = parity;
        }
    }
}

vector<bool>& DecodeHammingCode(vector<bool>& input_data, size_t& error_ctr) {

    int original_size = input_data.size();
    if (original_size == CHAR_BIT) {
        input_data.pop_back();
        original_size--;
    }
    int parity_bits = 1;
    while ((1 << parity_bits) < original_size) {
        parity_bits++;
    }

    std::vector<bool> output_data(original_size - parity_bits);

    int error_bit = CalculateErrorBit(input_data);
    if (error_bit > -1) {
        input_data[error_bit - 1] = !input_data[error_bit - 1];
        error_ctr++;
    }

    int j = 0;
    for (int i = 0; i < original_size; i++) {
        if (!PowOfTwo(i + 1)) {
            output_data[j] = input_data[i];
            j++;
        }
    }

    return *new vector<bool>(output_data);
}

int CalculateErrorBit(std::vector<bool>& data) {
    int errorBit = -1;
    int n = data.size();
    for (int i = 0; i < n; i++) {
        if (PowOfTwo(i + 1)) {
            bool parity = false;
            for (int j = i; j < n; j += (i + 1) * 2) {
                for (int k = 0; k < i + 1 && j + k < n; k++) {
                    if (j != i || k != 0) {
                        parity ^= data[j + k];
                    }
                }
            }
            if (data[i] != parity) {
                errorBit += i + 1;
            }
        }
    }
    return (errorBit > -1 ? errorBit + 1 : errorBit);
}