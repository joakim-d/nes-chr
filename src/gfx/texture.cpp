#include "texture.h"
#include "renderer.h"
#include "rect.h"

#include "../core/sprite.h"
#include "palette.h"
#include <SDL2/SDL.h>

class Texture::TexturePrivate {
public:
  TexturePrivate(Renderer &renderer, Sprite &sprite, Palette &palette) : src_rect_(0,0,8,8), dst_rect_(0,0,8,8){
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(sprite.data(), sprite.width(), sprite.height(), 8, sprite.width(), 0, 0, 0, 0);

    SDL_Color colours[4];
    for(int i = 0; i < 4; i++){
      colours[i].a = palette[i].a;
      colours[i].r = palette[i].r;
      colours[i].g = palette[i].g;
      colours[i].b = palette[i].b;
    }

    SDL_SetPaletteColors(surface->format->palette, colours, 0, 4);
    texture_ = SDL_CreateTextureFromSurface(renderer.rawRenderer(), surface);
    if(texture_ == nullptr){
      throw std::runtime_error("SDL_CreateTextureFromSurface failed: " + std::string(SDL_GetError()));
    }
    SDL_FreeSurface(surface);
  }

  TexturePrivate(SDL_Texture *texture) : texture_(texture){
    int32_t w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    src_rect_ = Rect(0,0,w,h);
  }

  ~TexturePrivate(){
    SDL_DestroyTexture(texture_);
  }

  SDL_Texture *texture_{};
  Rect src_rect_;
  Rect dst_rect_;
};

Texture::Texture(Renderer &renderer, Sprite &sprite, Palette& palette) : d_(new TexturePrivate(renderer, sprite, palette)){}

Texture::Texture(SDL_Texture *texture) : d_(new TexturePrivate(texture)){}

Texture::Texture(Texture &&rhs) : d_(std::move(rhs.d_)){}

Texture& Texture::operator =(Texture &&rhs) {
  d_ = std::move(rhs.d_);
  return *this;
}

Texture::~Texture() = default;

SDL_Texture* Texture::rawTexture() const {
  return d_->texture_;
}

const Rect & Texture::srcRect() const {
  return d_->src_rect_;
}

const Rect & Texture::dstRect() const {
  return d_->dst_rect_;
}

void Texture::setDstRect(Rect &&dst_rect) {
  d_->dst_rect_ = std::move(dst_rect);
}
