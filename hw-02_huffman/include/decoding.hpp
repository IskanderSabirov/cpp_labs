#ifndef HW_02_HUFFMAN_DECODING_HPP
#define HW_02_HUFFMAN_DECODING_HPP

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include "binary_io.hpp"
#include "tree.hpp"

namespace MyDecoder {
    class decoder {
    private:

        std::ostream *to_{};

        BinaryIO::reader *reader_;

        uint64_t read_text_length_{};

        uint64_t code_text_length_{};

        uint64_t header_text_length_{};

        uint32_t max_code_length{};

        uint32_t symbols_count_{};

        std::unordered_map<std::vector<bool>, char> decode_data_{};

    public:

        explicit decoder(std::istream *from, std::ostream *to);

        ~decoder();

        void write_text();

        [[nodiscard]] uint64_t get_not_codded_text_length() const noexcept;

        [[nodiscard]] uint64_t get_header_length() const noexcept;

        [[nodiscard]] uint64_t get_codded_length() const noexcept;

        friend std::ostream &operator<<(std::ostream &ostream, const decoder &decoder);

    private:

        void decode_header();

        void decode_symbols();

        char decode_symbol();

    };

    std::ostream &operator<<(std::ostream &ostream, const decoder &decoder);
}

#endif //HW_02_HUFFMAN_DECODING_HPP
