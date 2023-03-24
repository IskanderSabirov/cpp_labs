#include "bin_manip.h"

write_le_int32::write_le_int32(int32_t val) {
    val_ = val;
}

write_bool::write_bool(bool val) {
    val_ = val;
}

write_string::write_string(std::string val) {
    val_ = val;
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

std::ofstream &operator <<(std::ofstream &ofstream, const write_string &d) {
    ofstream.write((char *) d.val_.c_str(), (unsigned long) d.val_.size() + 1);
    return ofstream;
}



