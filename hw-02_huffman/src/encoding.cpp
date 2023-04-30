#include <queue>
#include "encoding.hpp"

namespace MyEncoder {

    encoder::encoder(std::istream *from, std::ostream *to) {

        if (!from || !to)
            throw MyException::my_exception("Error: given invalid istream or ostream to encoder");

        try {
            writer_ = new BinaryIO::writer(to);

            from_ = from;

            auto data = get_symbols_count(from);

            tree_ = new MyNodeTree::tree(data);

            code_text_length_ = 0;
            for (auto [symbol, _]: data)
                code_text_length_ += tree_->get_code_of_symbol(symbol).size() * data[symbol];

            code_text_length_ = (code_text_length_ + 7) / 8;
        } catch (...) {
            delete writer_;
            delete tree_;
            throw MyException::my_exception("Error: error in encoder constructor");
        }

    }

    encoder::~encoder() {
        delete writer_;
        delete tree_;
    }

    void encoder::write_text() {

        from_->clear();
        from_->seekg(0, std::ios::beg);
        int symbol = from_->get();
        while (symbol != EOF) {
            writer_->write(tree_->get_code_of_symbol(static_cast<char>(symbol)));

            symbol = from_->get();
        }
        writer_->write_buffer();
    }

    void encoder::write_header() {

        writer_->write(get_read_text_length(), 8);
        writer_->write_buffer();

        writer_->write(get_encoded_text_length(), 8);
        writer_->write_buffer();

        auto symbol_count = static_cast<char>(tree_->get_symbol_count());
        writer_->write(symbol_count - 1, 1);
        writer_->write_buffer();

        for (auto [symbol, code]: tree_->get_symbol_code_map()) {
            writer_->write(symbol);
            auto n = static_cast<unsigned char>(tree_->get_code_of_symbol(symbol).size());
            writer_->write(n);
            writer_->write(tree_->get_code_of_symbol(symbol));
            writer_->write_buffer();
        }
    }

    uint64_t encoder::get_read_text_length() const {
        return read_text_length_;
    }

    uint64_t encoder::get_encoded_text_length() const {
        return code_text_length_;
    }

    uint64_t encoder::get_header_length() const {
        uint64_t header_length = 2 * sizeof(uint64_t) + sizeof(char);
        for (auto [_, code]: tree_->get_symbol_code_map()) {
            header_length += sizeof(char) + sizeof(char) + (code.size() + 7) / 8;
        }
        return header_length;
    }

    std::map<char, uint64_t> encoder::get_symbols_count(std::istream *file) {

        file->clear();
        file->seekg(0, std::ios::beg);
        int symbol = from_->get();
        auto data = std::map<char, uint64_t>{};

        while (symbol != EOF) {
            data[static_cast<char>(symbol)]++;
            read_text_length_++;

            symbol = from_->get();
        }

        return data;
    }

    std::ostream &operator<<(std::ostream &ostream, const encoder &encoder) {
        ostream << encoder.get_read_text_length() << std::endl << encoder.get_encoded_text_length() << std::endl
                << encoder.get_header_length() << std::endl;
        return ostream;
    }

    void encoder::write() {
        write_header();
        write_text();
    }
}