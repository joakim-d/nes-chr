#include "sprite.h"

Sprite::Sprite(uint32_t width, uint32_t height, std::vector<uint8_t> &&pixels) :
width_(width), height_(height), pixels_(std::move(pixels))
{

}
