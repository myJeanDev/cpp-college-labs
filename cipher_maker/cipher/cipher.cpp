#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>

#include "cipher.h"

void error_handling(int argc, const char * argv[]){
    if (argc != 5){
        throw std::runtime_error("5 arguments are required");
    }
    std::string cipher_type = argv[0]; // B (block) or S (stream)
    std::string input_file_path = argv[1]; // file_path
    std::string output_file_path = argv[2]; // file_path
    std::string key_file_path = argv[3]; // file_path
    std::string mode_of_operation = argv[4]; // E (encryption) or D (decryption)
    
    if(cipher_type != "B" || cipher_type != "S"){
        throw std::runtime_error("Invalid Function Type");
    }
    
    if(std::filesystem::exists(input_file_path)){
        throw std::runtime_error("Input File Does Not Exist");
    }
    
    if(std::filesystem::exists(key_file_path)){
        throw std::runtime_error("Key File Does Not Exist");
    }
    
    if(mode_of_operation != "E" || mode_of_operation != "D"){
        throw std::runtime_error("Invalid Mode Type");
    }
}

void write_to_file(std::string data, std::string file_path){
    std::cout << "writing to file_path: " << file_path << std::endl;
    std::ofstream outfile;
    outfile.open(file_path, std::ios::out | std::ios::binary);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return;
    }
    outfile << data;
    outfile.close();
}

std::string read_from_file(std::string file_path) {
    std::cout << "reading from file_path: " << file_path << std::endl;
    
    std::ifstream infile(file_path);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return "";
    }
    std::string data;
    std::string line;
    while (std::getline(infile, line)) {
        data += line + "\n";
    }
    infile.close();
    return data;
}

// keySize MUST BE 16 bytes
std::string block_cipher_encryption(std::string data){
    std::cout << "block cipher encryption..." << std::endl;
    std::string encrypted = "";
    encrypted = data;
    return encrypted;
}

std::string block_cipher_decryption(std::string data){
    std::cout << "block cipher decryption..." << std::endl;
    std::string encrypted = "";
    encrypted = data;
    return encrypted;
}

// keySize can be any length
std::string stream_cipher_encryption(std::string data){
    std::cout << "stream cipher encryption..." << std::endl;
    std::string encrypted = "";
    encrypted = data;
    return encrypted;
}

std::string stream_cipher_decryption(std::string data){
    std::cout << "stream cipher decryption..." << std::endl;
    std::string encrypted = "";
    encrypted = data;
    return encrypted;
}
