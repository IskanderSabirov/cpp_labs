#include "bin_manip.h"
#include <utility>

write_le_int32::write_le_int32(int32_t val) {
    val_ = val;
}

write_bool::write_bool(bool val) {
    val_ = val;
}

write_string::write_string(std::string val) {
    val_ = std::move(val);
}

read_le_int32::read_le_int32(int32_t *val) {
    data_ = val;
}

read_bool::read_bool(bool *val) {
    data_ = val;
}

/// functions

std::ofstream &operator<<(std::ofstream &ofstream, const write_le_int32 &d) {
    ofstream.write((char *) &d.val_, sizeof(int32_t));
    return ofstream;
}

std::ofstream &operator<<(std::ofstream &ofstream, const write_bool &d) {
    ofstream.write((char *) &d.val_, sizeof(bool));
    return ofstream;
}

std::ofstream &operator<<(std::ofstream &ofstream, const write_string &d) {
    ofstream.write((char *) d.val_.c_str(), (unsigned long) d.val_.size() + 1);
    return ofstream;
}

std::ifstream &operator>>(std::ifstream &ifstream, read_le_int32 &d) {
    ifstream.read((char *) d.data_, sizeof(int32_t));
    return ifstream;
}

std::ifstream &operator>>(std::ifstream &ifstream, read_bool &d) {
    ifstream.read((char *) d.data_, sizeof(bool));
    return ifstream;
}
