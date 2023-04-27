#include "decoding.hpp"

namespace MyDecoder {

    namespace {
        uint64_t bool_vector_to_uint64t(std::vector<bool> &data) {
            uint64_t answer = 0;
            for (auto &&i: data) {
                answer *= 2;
                answer += (i ? 1 : 0);
            }
            return answer;
        }

    }

    decoder::decoder(std::istream *from, std::ostream *to) {
        try {
            reader_ = new BinaryIO::reader(from);
            to_ = to;
            decode_header();
        } catch (...) {
            delete reader_;
            throw MyException::my_exception("Error: error in decoder constructor");
        }
    }

    decoder::~decoder() {
        delete reader_;
    }

    void decoder::decode_header() {

        auto v1 = reader_->read_bits(64);
        read_text_length_ = bool_vector_to_uint64t(v1);

        auto v2 = reader_->read_bits(64);
        code_text_length_ = bool_vector_to_uint64t(v2);

        auto v3 = reader_->read_bits(8);
        symbols_count_ = static_cast<uint32_t>( bool_vector_to_uint64t(v3)) + 1;

        if (read_text_length_ == 0)
            symbols_count_ = 0;

        header_text_length_ = 2 * 8 + 1;

        decode_symbols();
    }

    void decoder::decode_symbols() {

        max_code_length = 0;

        for (uint32_t i = 0; i < symbols_count_; ++i) {

            auto v_symbol = reader_->read_bits(8);
            char symbol = static_cast<char>(bool_vector_to_uint64t(v_symbol));

            auto v_code_length = reader_->read_bits(8);
            uint32_t length_in_bits = static_cast<int>(bool_vector_to_uint64t(v_code_length));

            if (length_in_bits == 0)
                throw MyException::my_exception("Error: incorrect length of symbol code");

            uint32_t length_in_bytes = (length_in_bits + 7) / 8;

            auto symbol_code = reader_->read_bits(length_in_bytes * 8);
            symbol_code.resize(length_in_bits);

//            for (auto [_, exist_symbol]: decode_data_)
//                if (exist_symbol == symbol)
//                    throw MyException::my_exception("Error: there are two equal symbols in given text");

            if (max_code_length < length_in_bits)
                max_code_length = length_in_bits;

            header_text_length_ += 2 + length_in_bytes;
            decode_data_[symbol_code] = symbol;
        }

    }

    char decoder::decode_symbol() {
        std::vector<bool> current_code{};
        current_code.push_back(reader_->read_bit());
        while (current_code.size() <= max_code_length) {
            if (decode_data_.find(current_code) != decode_data_.end())
                return decode_data_[current_code];
            current_code.push_back(reader_->read_bit());
        }
        throw MyException::my_exception("Error: wrong symbols`s code in text");
    }

    void decoder::write_text() {
        uint64_t was_symbols = 0;
        while (was_symbols < read_text_length_) {
            *to_ << decode_symbol();
            was_symbols++;
        }
    }

    uint64_t decoder::get_not_codded_text_length() const noexcept {
        return read_text_length_;
    }

    uint64_t decoder::get_header_length() const noexcept {
        return header_text_length_;
    }

    uint64_t decoder::get_codded_length() const noexcept {
        return code_text_length_;
    }

    std::ostream &operator<<(std::ostream &ostream, const decoder &decoder) {
        ostream << decoder.get_codded_length() << std::endl << decoder.get_not_codded_text_length() << std::endl
                << decoder.get_header_length() << std::endl;
        return ostream;
    }

}

