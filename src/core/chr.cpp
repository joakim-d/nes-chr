#include "chr.h"
#include "header.h"
#include <stdexcept>
#include <string.h>
#include <iostream>

Chr::Chr(const std::vector<uint8_t> &data, const Header &header) {
  data_.resize(header.chr_size(), 0);

  uint32_t offset = header.trainer() ? 16 + 512 + header.prg_size() : 16 + header.prg_size();

  if(header.chr_size() == 0){
    throw std::runtime_error("No chr in Rom");
  }

  if(header.chr_size() + offset > data.size()){
    throw std::runtime_error("File corrupted, chr size too big.");
  }

  memcpy(data_.data(), data.data() + offset, header.chr_size());

  for (auto i = 0; i < data_.size() / 16; i++){
    sprites_.push_back(Sprite(8, 8, data_.data() + i * 16));
  }
}

std::vector<Sprite>& Chr::sprites() {
  return sprites_;
}

void Chr::applyChanges() {
  auto index = 0;
  for(auto &sprite : sprites_){
    memcpy(data_.data() + index * 16, sprite.toChrData().data(), 16);
    index++;
  }
}

std::vector<uint8_t>& Chr::data() {
  return data_;
}
