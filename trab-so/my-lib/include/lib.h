#ifndef LIB_H
#define LIB_H

#include <string_view>
#include <vector>
#include <cstdint>

namespace Lib {
    uint32_t get_file_size_words(const std::string_view fname);
    std::vector<uint16_t> load_from_disk_to_16bit_buffer(const std::string_view fname);
}

#endif // LIB_H