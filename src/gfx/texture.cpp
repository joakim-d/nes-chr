#include "texture.h"
#include "renderer.h"

#include "../core/sprite.h"
#include <SDL2/SDL.h>

class Texture::TexturePrivate {
public:
  TexturePrivate(Renderer &renderer, Sprite &sprite){
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(sprite.data(), sprite.width(), sprite.height(), 8, sprite.width(), 0, 0, 0, 0);

    SDL_Color colours[4];
    for(int i = 0; i < 4; i++){
      colours[i].a = 255;
      colours[i].r = i * 85;
      colours[i].g = i * 85;
      colours[i].b = i * 85;
    }

    SDL_SetPaletteColors(surface->format->palette, colours, 0, 4);
    texture_ = SDL_CreateTextureFromSurface(renderer.rawRenderer(), surface);
    if(texture_ == nullptr){
      throw std::runtime_error("SDL_CreateTextureFromSurface failed: " + std::string(SDL_GetError()));
    }
    SDL_FreeSurface(surface);
  }

  ~TexturePrivate(){
    SDL_DestroyTexture(texture_);
  }

  SDL_Texture *texture_{};
};

Texture::Texture(Renderer &renderer, Sprite &sprite) : d_(new TexturePrivate(renderer, sprite)){}

Texture::Texture(Texture &&rhs) : d_(std::move(rhs.d_)){}

Texture& Texture::operator =(Texture &&rhs) {
  d_ = std::move(rhs.d_);
  return *this;
}

Texture::~Texture() = default;

SDL_Texture* Texture::rawTexture() const {
  return d_->texture_;
}
