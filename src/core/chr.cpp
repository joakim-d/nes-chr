#include "chr.h"
#include "header.h"
#include <stdexcept>
#include <string.h>

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
    for (auto j = 0; j < 16; j++){
      auto sprite_offset = i * 16 + j;
      pixels[j * 4] = (data_[sprite_offset] & 0x01) + (data_[sprite_offset] & 0x02);
      pixels[j * 4 + 1] = ((data_[sprite_offset] & 0x04) + (data_[sprite_offset] & 0x08)) >> 2;
      pixels[j * 4 + 2] = ((data_[sprite_offset] & 0x10) + (data_[sprite_offset] & 0x20)) >> 4;
      pixels[j * 4 + 3] = ((data_[sprite_offset] & 0x40) + (data_[sprite_offset] & 0x80)) >> 6;
    }
    Sprite sprite(8, 8, std::move(pixels));
    sprites.push_back(sprite);
  }

  return sprites;
}
