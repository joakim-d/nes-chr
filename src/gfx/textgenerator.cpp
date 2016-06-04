#include "textgenerator.h"
#include "color.h"
#include "renderer.h"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

TextGenerator::TextGenerator(Renderer &renderer, const std::string &ttf_path, int32_t point_size)
  : renderer_(renderer){
  font_ = TTF_OpenFont(ttf_path.data(), point_size);
  if(font_ == nullptr){
    throw std::runtime_error("Error while opening font.");
  }
}

TextGenerator::~TextGenerator(){
  TTF_CloseFont(font_);
}

Texture TextGenerator::textureFromText(const std::string &text, const Color &color){
  SDL_Surface *surface = TTF_RenderText_Blended(font_, text.data(), color.toSDLColor());
  if(surface == nullptr){
    throw std::runtime_error("Failed to render text.");
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_.rawRenderer(), surface);
  if(texture == nullptr){
    throw std::runtime_error("Failed to create texture from surface.");
  }
  SDL_FreeSurface(surface);
  return Texture(texture);
}
