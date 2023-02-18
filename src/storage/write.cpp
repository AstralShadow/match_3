#include "utils.hpp"
#include <memory>


namespace storage
{


void write8(ostream& dest, u8 data)
{
    char input = static_cast<char>(data);
    dest.write(&input, 1);
}

void write16(ostream& dest, u16 data)
{
    char input[] {
        static_cast<char>(data >> 8),
        static_cast<char>(data),
    };
    dest.write(&input[0], 2);
}

void write32(ostream& dest, u32 data)
{
    char input[] {
        static_cast<char>(data >> 24),
        static_cast<char>(data >> 16),
        static_cast<char>(data >> 8),
        static_cast<char>(data),
    };
    dest.write(&input[0], 4);
}

void write64(ostream& dest, u64 data)
{
    char input[] {
        static_cast<char>(data >> 56),
        static_cast<char>(data >> 48),
        static_cast<char>(data >> 40),
        static_cast<char>(data >> 32),
        static_cast<char>(data >> 24),
        static_cast<char>(data >> 16),
        static_cast<char>(data >> 8),
        static_cast<char>(data),
    };
    dest.write(&input[0], 8);
}


void write(ostream& dest, string data)
{
    write32(dest, data.size());
    dest << data;
}


void writef(ostream& dest, float data)
{
    const auto size = sizeof(float);

    char input[size];
    std::copy(&data, &data + 1, input);

    dest.write(&input[0], size);
}


} // namespace storage

