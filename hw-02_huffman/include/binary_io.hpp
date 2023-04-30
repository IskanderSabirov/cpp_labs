#ifndef HW_02_HUFFMAN_BINARY_IO_HPP
#define HW_02_HUFFMAN_BINARY_IO_HPP

#include <iostream>
#include <vector>
#include "my_exception.hpp"

namespace BinaryIO {

    class writer {
    private:
        std::ostream *file_;
        unsigned char buffer_size_{};
        unsigned char buffer_{};

    public:

        explicit writer(std::ostream *file_);

        ~writer() = default;

        void write_buffer();

        void write(bool bit);

        void write(std::vector<bool> &bools);

        void write(uint64_t number, int byte_count);

        void write(char symbol);

        void write(unsigned char symbol);

    };


    class reader {
    private:
        std::istream *file_;
        int buffer_index_{-1};
        unsigned char buffer_{};

    public:

        explicit reader(std::istream *file);

        bool read_bit();

        std::vector<bool> read_bits(uint32_t count);

        void read_buffer();
    };

}

#endif //HW_02_HUFFMAN_BINARY_IO_HPP
