#include "sprite.h"

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
