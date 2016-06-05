#include "sprite.h"
#include <string.h>

Sprite::Sprite(){}

Sprite::Sprite(uint32_t width, uint32_t height, const uint8_t *raw_chr_data) :
  width_(width), height_(height)
{
  pixels_.resize(width * height);
  uint64_t first_line = 0;
  uint64_t second_line = 0;

  memcpy(&first_line, raw_chr_data, 8);
  memcpy(&second_line, raw_chr_data + 8, 8);

  for (auto y = 0; y < 8; y++){
    for (auto x = 0; x < 8; x++){
      uint8_t first_bit = (first_line & (static_cast<uint64_t>(1) << (y * 8 + (7 - x)))) ? 1 : 0;
      uint8_t second_bit = (second_line & (static_cast<uint64_t>(1) << (y * 8 + (7 - x)))) ? 2 : 0;
      pixels_[y * 8 + x] = first_bit + second_bit;
    }
  }
}

Sprite::Sprite(uint32_t width, uint32_t height, std::vector<uint8_t> &&pixels) :
width_(width), height_(height), pixels_(std::move(pixels))
{

}

uint32_t Sprite::width() const {
  return width_;
}

uint32_t Sprite::height() const {
  return height_;
}

uint8_t* Sprite::data(){
  return pixels_.data();
}

std::vector<uint8_t> Sprite::toChrData() const {
  std::vector<uint8_t> chr_data(16, 0);

  uint64_t first_line = 0;
  uint64_t second_line = 0;

  for (auto y = 0; y < 8; y++){
    for (auto x = 0; x < 8; x++){
      if(pixels_[y * 8 + x] & 1){
        first_line |= static_cast<uint64_t>(1) << (y * 8 + (7 - x));
      }
      if(pixels_[y * 8 + x] & 2){
        second_line |= static_cast<uint64_t>(1) << (y * 8 + (7 - x));
      }
    }
  }

  memcpy(chr_data.data(), &first_line, 8);
  memcpy(chr_data.data() + 8, &second_line, 8);
  return chr_data;
}
