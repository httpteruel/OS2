#include "lib.h"
#include <fstream>
#include <stdexcept>

namespace Lib {
    uint32_t get_file_size_words(const std::string_view fname) {
        std::ifstream file(fname.data(), std::ios::binary);
        if (!file) throw std::runtime_error("Cannot open file");
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        return (size + 1) / 2; // Tamanho em palavras (16 bits)
    }

    std::vector<uint16_t> load_from_disk_to_16bit_buffer(const std::string_view fname) {
        std::ifstream file(fname.data(), std::ios::binary);
        if (!file) throw std::runtime_error("Cannot open file");
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<uint16_t> buffer((size + 1) / 2);
        file.read(reinterpret_cast<char*>(buffer.data()), size);
        return buffer;
    }
}