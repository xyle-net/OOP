#pragma once

#include <iostream>
#include <string>

class Money
{
public:

    Money();
    Money(const size_t & n, unsigned char t = 0);
    Money(const std::initializer_list< unsigned char> &t);
    Money(const std::string &t);
    Money(const Money& other);
    Money(Money&& other) noexcept;
    
    int get_size();
    unsigned char* get_array();
    std::string get_string_value();

    Money add(const Money& other);
    Money remove(const Money& other);
    bool bigger(const Money& other);
    bool equals(const Money& other);
    void print();

    virtual ~Money() noexcept;

private:
    int _size;
    unsigned char *_array;
};