#include <iostream>
#include <fstream>
#include <filesystem>
#include <string.h>

#include "cipher.h"

int main(int argc, const char * argv[]) {
    try{
        error_handling(argc, argv);
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    std::string cipher_type = argv[0]; // B (block) or S (stream)
    std::string input_file_path = argv[1]; // file_path
    std::string output_file_path = argv[2]; // file_path
    std::string key_file_path = argv[3]; // file_path, will not contain a terminating newline character.
    std::string mode_of_operation = argv[4]; // E (encryption) or D (decryption)
    
    std::cout << cipher_type << std::endl;
    std::cout << input_file_path << std::endl;
    std::cout << output_file_path << std::endl;
    std::cout << key_file_path << std::endl;
    std::cout << mode_of_operation << std::endl;

    std::cout << "input_file_data: " << std::endl;
    std::cout << read_from_file(input_file_path) << std::endl;
    
    std::cout << "key: " << std::endl;
    std::cout << read_from_file(key_file_path) << std::endl;
    
    if(cipher_type == "B"){
        if(mode_of_operation == "E"){
            block_cipher_encryption(read_from_file(input_file_path));
        }else{
            block_cipher_decryption(read_from_file(input_file_path));
        }
    }else{
        if(mode_of_operation == "E"){
            stream_cipher_encryption(read_from_file(input_file_path));
        }else{
            stream_cipher_encryption(read_from_file(input_file_path));
        }
    }
    
    return 0;
}
