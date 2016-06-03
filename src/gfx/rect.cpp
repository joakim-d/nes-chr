#include "rect.h"
#include "SDL2/SDL_rect.h"

class Rect::RectPrivate {
public:
  RectPrivate(int32_t x, int32_t y, int32_t w, int32_t h){
    rect_.x = x;
    rect_.y = y;
    rect_.w = w;
    rect_.h = h;
  }

  SDL_Rect rect_;
};

Rect::Rect(int32_t x, int32_t y, int32_t width, int32_t height) : d_(new RectPrivate(x, y, width, height)){}

Rect::~Rect() = default;

SDL_Rect &Rect::rect() const {
  return d_->rect_;
}


Rect::Rect(Rect &&rhs) : d_(std::move(rhs.d_)){}

Rect::Rect(const Rect &c) : d_(new RectPrivate(*c.d_)){}

Rect& Rect::operator =(Rect &&rhs){
  d_ = std::move(rhs.d_);
  return *this;
}

Rect& Rect::operator =(const Rect &c){
  if(&c != this){
    *d_ = *c.d_;
  }
  return *this;
}
