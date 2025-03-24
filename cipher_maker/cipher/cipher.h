#ifndef CIPHER_H
#define CIPHER_H
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>

void error_handling(int argc, const char * argv[]);

void write_to_file(std::string data, std::string file_path);

std::string read_from_file(std::string file_path);

std::string block_cipher_encryption(std::string data);

std::string block_cipher_decryption(std::string data);

std::string stream_cipher_encryption(std::string data);

std::string stream_cipher_decryption(std::string data);

#endif // CIPHER_H
