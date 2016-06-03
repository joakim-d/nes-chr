#include "spritepicker.h"
#include "renderer.h"

#include "../core/sprite.h"
#include "../gfx/rect.h"
#include "../engine/engine.h"
#include "../events/eventlistener.h"
#include <SDL2/SDL_render.h>

SpritePicker::SpritePicker(Engine &engine, std::vector<Sprite> &sprites) : engine_(engine), sprites_(sprites){
  refresh();
}

void SpritePicker::setSprites(std::vector<Sprite> &sprites) {
  sprites_ = sprites;
  refresh();
}

void SpritePicker::handleEvents() {
  auto &events_listener = engine_.eventsListener();
  if(events_listener.keyboardEvent(SDLK_UP).released){
    if(index_ - 16 >= 0){
      index_ -= 16;
    }
  }
  else if (events_listener.keyboardEvent(SDLK_DOWN).released){
    if(index_ + 16 < sprites_.size()){
      index_ += 16;
    }
  }
  else if (events_listener.keyboardEvent(SDLK_LEFT).released){
    index_--;
  }
  else if (events_listener.keyboardEvent(SDLK_RIGHT).released){
    index_++;
  }

  if(index_ < 0){
    index_ = 0;
  }
  else if (index_ >= sprites_.size()){
    index_ = sprites_.size() - 1;
  }
}

void SpritePicker::render() {
  const int x_margin = 256 + 64;
  const int step_margin = 8;

  int x = x_margin;
  int y = 0;

  int index = 0;
  for(auto &texture : textures_){
    if(index == index_){
      engine_.renderer().setDrawColor(0, 255, 0, 255);
      engine_.renderer().drawFillRect(Rect(x - 2, y - 2, 20, 20));
    }

    texture.setDstRect(Rect (x, y, 16, 16));
    engine_.renderer().renderTexture(texture);

    index++;
    x += 16 + step_margin;
    if(index % 16 == 0){
      y += 16 + step_margin;
      x = x_margin;
    }
  }
}

void SpritePicker::refresh(){
  textures_.clear();
  for(auto &sprite : sprites_){
    textures_.push_back(Texture(engine_.renderer(), sprite));
  }
}

Sprite& SpritePicker::currentSprite() {
  return sprites_[index_];
}
