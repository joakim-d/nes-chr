#include "header.h"
#include <stdexcept>
#include <string.h>

Header::Header(const std::vector<uint8_t> &data) {
  if(data.size() < 16){
    throw std::runtime_error("File too small.");
  }

  memcpy(data_.data(), data.data(), 16);

  if(data_[0] != 0x4E || data_[1] != 0x45 || data_[2] != 0x53 || data_[3] != 0x1A){
    throw std::runtime_error("Corrupted rom file, wrong header.");
  }
}

Header::~Header() = default;

uint32_t Header::prg_size() const {
  return data_[4] * 16384;
}

uint32_t Header::chr_size() const {
  return data_[5] * 8192;
}

bool Header::trainer() const {
  return static_cast<bool>(data_[6] & 0x04);
}
