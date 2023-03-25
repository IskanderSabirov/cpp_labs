#ifndef LAB10_MANIP_H_INCLUDED
#define LAB10_MANIP_H_INCLUDED

#include <fstream>
#include <cstring>
#include <iostream>

struct write_le_int32 {
    explicit write_le_int32(int32_t val);
    friend std::ofstream &operator<<(std::ofstream &ofstream, const write_le_int32 &d);
private:
    int32_t val_;
};

struct write_bool {
    explicit write_bool(bool val);
    friend std::ofstream &operator<<(std::ofstream &ofstream, const write_bool &d);
private:
    bool val_;
};

struct write_string {
    explicit write_string(std::string val);
    friend std::ofstream &operator<<(std::ofstream &ofstream, const write_string &d);
private:
    std::string val_;
};

struct read_le_int32 {
    explicit read_le_int32(int32_t *val);
    friend std::ifstream &operator>>(std::ifstream &ifstream, read_le_int32 d);
private:
    int32_t *data_;
};

struct read_bool {
    explicit read_bool(bool *val);
    friend std::ifstream &operator>>(std::ifstream &ifstream, read_bool d);
private:
    bool *data_;
};

struct read_string{
    explicit read_string(std::string *val);
    friend std::ifstream &operator>>(std::ifstream& ifstream, read_string d);
private:
    std::string* data_;
};



///
std::ofstream &operator<<(std::ofstream &ofstream, const write_le_int32 &d);

std::ofstream &operator<<(std::ofstream &ofstream, const write_bool &d);

std::ofstream &operator<<(std::ofstream &ofstream, const write_string &d);

std::ifstream &operator>>(std::ifstream &ifstream, read_le_int32 d);

std::ifstream &operator>>(std::ifstream &ifstream, read_bool d);

std::ifstream &operator>>(std::ifstream& ifstream, read_string d);

#endif
