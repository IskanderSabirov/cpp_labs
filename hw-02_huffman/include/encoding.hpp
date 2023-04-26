#ifndef HW_02_HUFFMAN_ENCODING_HPP
#define HW_02_HUFFMAN_ENCODING_HPP

#include "tree.hpp"
#include "binary_io.hpp"


namespace MyEncoder {

    class encoder {
    private:

        std::istream *from_;

        BinaryIO::writer *writer_;

        uint64_t read_text_length_{};

        uint64_t code_text_length_{};

        MyNodeTree::tree *tree_;


    public:

        explicit encoder(std::istream *from, std::ostream *to);

        ~encoder();

        void write_text();

        void write_header();

        void write();

        [[nodiscard]] uint64_t get_encoded_text_length() const;

        [[nodiscard]] uint64_t get_read_text_length() const;

        [[nodiscard]] uint64_t get_header_length() const;

        friend std::ostream &operator<<(std::ostream &ostream, const encoder &e);

    private:

        std::map<char, uint64_t> get_symbols_count(std::istream *file);

    };

    std::ostream &operator<<(std::ostream &ostream, const encoder &e);
}

#endif //HW_02_HUFFMAN_ENCODING_HPP
