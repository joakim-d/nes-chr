#include "chr.h"
#include "header.h"
#include <stdexcept>
#include <string.h>
#include <iostream>

Chr::Chr(const std::vector<uint8_t> &data, const Header &header) {
  data_.resize(header.chr_size(), 0);

  uint32_t offset = header.trainer() ? 16 + 512 + header.prg_size() : 16 + header.prg_size();

  if(header.chr_size() + offset > data.size()){
    throw std::runtime_error("File corrupted, chr size too big.");
  }

  memcpy(data_.data(), data.data() + offset, header.chr_size());
}

std::vector<Sprite> Chr::sprites() const {
  std::vector<Sprite> sprites;
  for (auto i = 0; i < data_.size() / 16; i++){
    std::vector<uint8_t> pixels(64, 0);
    uint64_t first_line = 0;
    uint64_t second_line = 0;

    for(int j = 0; j < 8; j++){
      memcpy(&first_line, (data_.data() + i * 16 + j), 8);
      memcpy(&second_line, (data_.data() + i * 16 + 8 + j), 8);
    }
    for (auto j = 0; j < 64; j++){
      uint8_t first_bit = (first_line & (static_cast<uint64_t>(1) << (j))) ? 1 : 0;
      uint8_t second_bit = (second_line & (static_cast<uint64_t>(1) << (j))) ? 2 : 0;
      pixels[j] = first_bit + second_bit;
    }
    Sprite sprite(8, 8, std::move(pixels));
    sprites.push_back(sprite);
  }

  return sprites;
}
