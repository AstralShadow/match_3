#include "utils.hpp"


namespace storage
{


u8 read8(istream& src)
{
    char input;
    src.read(&input, 1);
    return static_cast<u8>(input);
}

u16 read16(istream& src)
{
    char input[2];
    src.read(&input[0], 2);

    u16 data = 0;
    for(int i = 0; i < 2; i++) {
        data = data << 8;
        data += static_cast<u8>(input[i]);
    }

    return data;
}

u32 read32(istream& src)
{
    char input[4];
    src.read(&input[0], 4);

    u32 data = 0;
    for(int i = 0; i < 4; i++) {
        data = data << 8;
        data += static_cast<u8>(input[i]);
    }

    return data;
}

u64 read64(istream& src)
{
    char input[8];
    src.read(&input[0], 8);

    u64 data = 0;
    for(int i = 0; i < 8; i++) {
        data = data << 8;
        data += static_cast<u8>(input[i]);
    }

    return data;
}


string read(istream& src)
{
    u32 size = read32(src);

    string input(size, '?');
    src.read(&input[0], input.size());

    return input;
}


float readf(istream& src)
{
    const auto size = sizeof(float);

    char input[size];
    src.read(&input[0], size);

    float data;
    std::copy(&input[0], &input[0] + size, &data);
    return data;
}


} // namespace storage

