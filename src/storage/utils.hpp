#ifndef INCLUDE_STORAGE_UTILS_HPP
#define INCLUDE_STORAGE_UTILS_HPP

#include <iostream>
#include <string>
#include "utils/types.hpp"

using std::istream;
using std::ostream;
using std::string;


namespace storage
{
    void write8(ostream&, u8);
    void write16(ostream&, u16);
    void write32(ostream&, u32);
    void write64(ostream&, u64);

    u8 read8(istream&);
    u16 read16(istream&);
    u32 read32(istream&);
    u64 read64(istream&);

    void write(ostream&, string);
    string read(istream&);

    // Raw copy of floats. System specific
    void writef(ostream&, float);
    float readf(istream&);

    // Not tested. Use at your own risk
    u32 mapf(float value, float min, float max);
    float unmapf(u32 value, float min, float max);
}

#endif // INCLUDE_STORAGE_UTILS_HPP
