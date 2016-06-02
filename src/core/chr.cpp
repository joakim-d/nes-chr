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
    sprites.push_back(Sprite(8, 8, data_.data() + i * 16));
  }

  return sprites;
}
