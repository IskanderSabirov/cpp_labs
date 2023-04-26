#include "binary_io.hpp"

namespace BinaryIO {

    ///writer

    writer::writer(std::ostream *file) {
        file_ = file;
    }

    void writer::write_buffer() {
        if (buffer_size_ == 0)
            return;
        *file_ << buffer_;
        buffer_size_ = 0;
        buffer_ = 0;
    }

    void writer::write(bool bit) {
        if (buffer_size_ == 8)
            write_buffer();
        buffer_ |= (bit << (7 - buffer_size_));
        buffer_size_++;
    }

    void writer::write(std::vector<bool> &bools) {
        for (auto bit: bools)
            write(bit);
    }

    void writer::write(char symbol) {
        *file_ << symbol;
    }

    void writer::write(unsigned char symbol) {
        *file_ << symbol;
    }


    void writer::write(uint64_t number, int byte_count) {
        std::vector<bool> bin_symbols;
        for (int64_t i = byte_count * 8 - 1; i >= 0; i--)
            bin_symbols.push_back((number >> i) & 1);
        write(bin_symbols);
    }


    /// reader


    reader::reader(std::istream *file) {
        file_ = file;
    }

    bool reader::read_bit() {
        if (buffer_index_ == -1)
            read_buffer();

        bool bit = (buffer_ >> buffer_index_) & 1;
        buffer_index_--;
        return bit;
    }

    void reader::read_buffer() {

        int symbol = file_->get();
        if (symbol == EOF)
            throw MyException::my_exception("Error: can`t read new byte");

        buffer_ = static_cast<unsigned char>(symbol);
        buffer_index_ = 7;
    }

    std::vector<bool> reader::read_bits(uint32_t count) {
        std::vector<bool> answer{};
        answer.reserve(count);
        for (uint32_t i = 0; i < count; ++i)
            answer.push_back(read_bit());

        return answer;
    }


}