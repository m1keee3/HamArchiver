#include "filework.h"

size_t GetFileSize(string& file_path) {
    ifstream file(file_path, ios::binary);
    file.seekg(0, ios::end);
    size_t file_size = file.tellg() * 2;
    file.seekg(0, ios::beg);
    file.close();
    return file_size;
}

void HammingFile(string& file_name, string& file_path, string& arc_path) {
    ifstream file(file_path, ios::binary);
    ofstream archieve(arc_path, ios::binary | ios::in | ios::app);

    for (int i = 0; i < file_name.size(); i++) {
        archieve.write(&file_name[i], sizeof(char));
    }
    char zero = 0;
    for (int i = 0; i < MAX_FILE_NAME_SIZE - file_name.size(); i++) {
        archieve.write(&zero, sizeof(char));
    }
    size_t file_size = GetFileSize(file_path);
    archieve.write((char *) &file_size, sizeof(size_t));

    vector<bool> input_data(CHAR_BIT / 2);
    vector<bool> output_data(HAM_BITS);
    char input;
    unsigned char uinput;
    unsigned char output = 0;
    while (file.get(input)) {
        uinput = input;
        for (int i = 0; i < CHAR_BIT / 2; i++) {
            input_data[i] = uinput / CHAR_SIZE;
            cout << input_data[i] << ' ';
            uinput = uinput << 1;
        }
        output_data = HammingCode(input_data);
        output = 0;
        for (int i = 0; i < CHAR_BIT - 1; i++) {
            output += (output_data[i] % 2) << (CHAR_BIT - i - 2);
        }
        output = output << 1; //Незначащий 0;
        archieve.write((char *) &output, sizeof(char));
        for (int i = 0; i < CHAR_BIT / 2; i++) {
            input_data[i] = uinput / CHAR_SIZE;
            uinput = uinput << 1;
        }
        output_data = HammingCode(input_data);
        output = 0;
        for (int i = 0; i < CHAR_BIT - 1; i++) {
            output += (output_data[i] % 2) << (CHAR_BIT - i - 2);
        }
        output = output << 1; //Незначащий 0;
        archieve.write((char *) &output, sizeof(char));
    }
    file.close();
    archieve.close();
}

void DecodeFile(string& file_name, string& output_path, string& arc_path) {
    cout << file_name << '\n';
    ifstream archieve(arc_path, ios::binary);
    string name_to_compare;
    char tmp;
    size_t tmp_file_size;
    while (true) {
        for (int i = 0; i < file_name.size(); i++) {
            archieve.read(&tmp, sizeof(char));
            name_to_compare += tmp;
        }
        if (file_name == name_to_compare) {
            break;
        }
        name_to_compare.clear();
        archieve.seekg(MAX_FILE_NAME_SIZE - file_name.size(), ios::cur);
        archieve.read((char *) &tmp_file_size, sizeof(size_t));
        archieve.seekg(tmp_file_size, ios::cur);
    }
    archieve.seekg(MAX_FILE_NAME_SIZE - file_name.size(), ios::cur);
    archieve.read((char *) &tmp_file_size, sizeof(size_t));
    ofstream outfile(output_path, ios::binary);
    vector<bool> input_data(CHAR_BIT);
    vector<bool> output_data(CHAR_BIT / 2);
    char input;
    unsigned char uinput;
    unsigned char output;
    size_t error_ctr = 0;
    for (int  i = 0; i < tmp_file_size / 2; i++) {
        archieve.get(input);
        uinput = input;
        for (int j = 0; j < CHAR_BIT; j++) {
            input_data[j] = uinput / CHAR_SIZE;
            uinput = uinput << 1;
        }
        output_data = DecodeHammingCode(input_data, error_ctr);
        output = 0;
        for (int j = 0; j < CHAR_BIT / 2; j++) {
            output += (output_data[j] % 2) << (CHAR_BIT - j - 1);
        }
        archieve.get(input);
        uinput = input;

        for (int j = 0; j < CHAR_BIT; j++) {
            input_data[j] = uinput / CHAR_SIZE;
            uinput = uinput << 1;
        }
        output_data = DecodeHammingCode(input_data, error_ctr);
        for (int j = 0; j < CHAR_BIT / 2; j++) {
            output += (output_data[j] % 2) << (CHAR_BIT / 2 - j - 1);
        }
        outfile.write((char *)&output, sizeof(char));
        cout << output;
    }
    cout << '\n' << error_ctr << " errors fixed" << '\n';
    archieve.close();
}

void DecodeFile(string& file_name, string& arc_path) {
    cout << file_name << '\n';
    ifstream archieve(arc_path, ios::binary);
    string name_to_compare;
    char tmp;
    size_t tmp_file_size;
    while (true) {
        for (int i = 0; i < file_name.size(); i++) {
            archieve.read(&tmp, sizeof(char));
            name_to_compare += tmp;
        }
        if (file_name == name_to_compare) {
            break;
        }
        name_to_compare.clear();
        archieve.seekg(MAX_FILE_NAME_SIZE - file_name.size(), ios::cur);
        archieve.read((char *) &tmp_file_size, sizeof(size_t));
        archieve.seekg(tmp_file_size, ios::cur);
    }
    archieve.seekg(MAX_FILE_NAME_SIZE - file_name.size(), ios::cur);
    archieve.read((char *) &tmp_file_size, sizeof(size_t));
    vector<bool> input_data(CHAR_BIT);
    vector<bool> output_data(CHAR_BIT / 2);
    char input;
    unsigned char uinput;
    unsigned char output;
    size_t error_ctr = 0;
    for (int  i = 0; i < tmp_file_size / 2; i++) {
        archieve.get(input);
        uinput = input;
        for (int j = 0; j < CHAR_BIT; j++) {
            input_data[j] = uinput / CHAR_SIZE;
            uinput = uinput << 1;
        }
        output_data = DecodeHammingCode(input_data, error_ctr);
        output = 0;
        for (int j = 0; j < CHAR_BIT / 2; j++) {
            output += (output_data[j] % 2) << (CHAR_BIT - j - 1);
        }
        archieve.get(input);
        uinput = input;

        for (int j = 0; j < CHAR_BIT; j++) {
            input_data[j] = uinput / CHAR_SIZE;
            uinput = uinput << 1;
        }
        output_data = DecodeHammingCode(input_data, error_ctr);
        for (int j = 0; j < CHAR_BIT / 2; j++) {
            output += (output_data[j] % 2) << (CHAR_BIT / 2 - j - 1);
        }
        cout << output;
    }
    cout << '\n' << error_ctr << " errors fixed" << '\n';
    archieve.close();
}

void GetAllFiles(string& arc_path) {
    ifstream archieve(arc_path, ios::binary);
    string file_name;
    size_t file_size;
    vector<bool> input_data(CHAR_BIT);
    vector<bool> output_data(CHAR_BIT / 2);
    char input;
    unsigned char uinput;
    unsigned char output;
    size_t error_ctr = 0;
    char zero = 0;
    while (archieve.get(input)) {
        uinput = uinput;
        if (input != zero) {
            file_name += input;
        } else {
            cout << file_name << '\n';
            archieve.seekg(MAX_FILE_NAME_SIZE - file_name.size() - 1, ios::cur);
            file_name.clear();
            archieve.read((char *) &file_size, sizeof(size_t));
            for (int  i = 0; i < file_size / 2; i++) {
                archieve.get(input);
                uinput = input;
                for (int j = 0; j < CHAR_BIT; j++) {
                    input_data[j] = uinput / CHAR_SIZE;
                    uinput = uinput << 1;
                }
                output_data = DecodeHammingCode(input_data, error_ctr);
                output = 0;
                for (int j = 0; j < CHAR_BIT / 2; j++) {
                    output += (output_data[j] % 2) << (CHAR_BIT - j - 1);
                }
                archieve.get(input);
                uinput = input;

                for (int j = 0; j < CHAR_BIT; j++) {
                    input_data[j] = uinput / CHAR_SIZE;
                    uinput = uinput << 1;
                }
                output_data = DecodeHammingCode(input_data, error_ctr);
                for (int j = 0; j < CHAR_BIT / 2; j++) {
                    output += (output_data[j] % 2) << (CHAR_BIT / 2 - j - 1);
                }
                cout << output;
            }
            cout << '\n' << error_ctr << " errors fixed" << '\n';
        }
    }
    archieve.close();
}

void List(string& arc_path) {
    ifstream archieve(arc_path, ios::binary);
    string cur_file_name;
    size_t file_size = 0;
    char input;
    char zero = 0;
    while (archieve.get(input)) {
        if (input != zero) {
            cur_file_name += input;
        } else {
            archieve.seekg(MAX_FILE_NAME_SIZE - cur_file_name.size() - 1, ios::cur);
            archieve.read((char *) &file_size, sizeof(size_t));
            archieve.seekg((int64_t)file_size, ios::cur);
            cout << cur_file_name << '\n';
            cur_file_name.clear();
        }
    }
}

void Merge(string& arc_path_1, string& arc_path_2, string& arc_path_3) {
    ofstream archieve_1(arc_path_1, ios::binary | ios::in);
    ifstream archieve_2(arc_path_2, ios::binary);
    ifstream archieve_3(arc_path_3, ios::binary);
    char input;
    unsigned char uinput;
    while (archieve_2.get(input)) {
        uinput = input;
        archieve_1 << uinput;
    }
    while (archieve_3.get(input)) {
        uinput = input;
        archieve_1 << uinput;
    }
    archieve_1.close();
    archieve_2.close();
    archieve_3.close();
}

void DeleteFile(string& file_name, string& arc_path) {
    ifstream archieve(arc_path, ios::binary);
    ofstream tmp_arc("tmp_arc.haf", ios::binary);
    string cur_name;
    size_t tmp_file_size;
    size_t ctr = 0;
    char zero = 0;
    char input;
    while (archieve.get(input)) {
        while (input != zero) {
            cur_name += input;
            archieve >> input;
        }
        if (cur_name != file_name) {
            for (char &i : cur_name) {
                tmp_arc << i;
            }
            for (int i = 0; i < MAX_FILE_NAME_SIZE - cur_name.size() - 1; i++) {
                tmp_arc.write((char *) &input, sizeof(char));
                archieve >> input;
            }
            tmp_arc.write((char *) &input, sizeof(char));
            archieve.read((char *) &tmp_file_size, sizeof(size_t));
            for (int i = 0; i < tmp_file_size; i++) {
                archieve >> input;
                tmp_arc.write((char *) &input, sizeof(char));
            }
        } else {
            archieve.seekg(MAX_FILE_NAME_SIZE - file_name.size(), ios::cur);
            archieve.read((char *) &tmp_file_size, sizeof(size_t));
            archieve.seekg((int64_t)tmp_file_size, ios::cur);
        }
    }
    archieve.close();
}
