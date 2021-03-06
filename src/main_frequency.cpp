/*******************************************************************************
 * src/main_frequency.cpp
 *
 * Copyright (c) 2018 Florian Gauger
 *
 * All rights reserved. Published under the MIT License in the LICENSE file.
 ******************************************************************************/

#include <cobs/frequency.hpp>

int main(int argc, char** argv) {
    if (argc == 5) {
        char* pEnd;
        std::string type = argv[1];
        std::string in_dir = argv[2];
        std::string out_dir = argv[3];
        size_t batch_size = std::strtoul(argv[4], &pEnd, 10);
        if (type == "bin") {
            cobs::frequency::process_all_in_directory<cobs::file::document_header>(in_dir, out_dir, batch_size);
        }
        else if (type == "fre") {
            cobs::frequency::process_all_in_directory<cobs::file::frequency_header>(in_dir, out_dir, batch_size);
        }
        else {
            std::cout << "wrong type: use 'bin' or 'fre'" << std::endl;
        }
    }
    else if (argc == 4) {
        std::string type = argv[1];
        std::string in_file = argv[2];
        std::string out_file = argv[3];
        if (type == "com") {
            cobs::frequency::combine(in_file, out_file);
        }
        else {
            std::cout << "wrong type: use 'com'" << std::endl;
        }
    }
    else {
        std::cout << "wrong number of args:\n\ttype[bin/fre] in_dir out_dir batch_size\n\ttype[com] in_file out_file" << std::endl;
    }
}

/******************************************************************************/
