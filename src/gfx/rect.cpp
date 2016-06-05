#include "rect.h"
#include "pos.h"

#include <SDL2/SDL_rect.h>

class Rect::RectPrivate {
public:
  RectPrivate(){}
  RectPrivate(int32_t x, int32_t y, int32_t w, int32_t h){
    rect_.x = x;
    rect_.y = y;
    rect_.w = w;
    rect_.h = h;
  }

  bool contains(const Pos &pos){
    return pos.x >= rect_.x && pos.x < rect_.x + rect_.w &&
        pos.y >= rect_.y && pos.y < rect_.y + rect_.h;
  }

  std::vector<Rect> split(uint32_t cols, uint32_t rows){
    std::vector<Rect> res;
    auto splitted_width = rect_.w / static_cast<int32_t>(cols);
    auto splitted_heigth = rect_.h / static_cast<int32_t>(rows);
    for(unsigned y = 0; y < rows; y++){
      for(unsigned x = 0; x < cols; x++){
        res.push_back(Rect(x * splitted_width + rect_.x, y * splitted_heigth + rect_.y, splitted_width, splitted_heigth));
      }
    }
    return res;
  }

  SDL_Rect rect_{};
};

Rect::Rect() : d_(new RectPrivate()){}

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

bool Rect::contains(const Pos &pos) const {
  return d_->contains(pos);
}

std::vector<Rect> Rect::split(uint32_t cols, uint32_t rows) const {
  if(cols == 0 || rows == 0){
    throw std::runtime_error("Bad rect split");
  }
  return d_->split(cols, rows);
}

void Rect::adjust(int32_t pixels) {
  d_->rect_.x -= pixels;
  d_->rect_.y -= pixels;
  d_->rect_.w += 2 * pixels;
  d_->rect_.h += 2 * pixels;
}
