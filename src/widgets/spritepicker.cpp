#include "spritepicker.h"

#include "../core/sprite.h"
#include "../gfx/color.h"
#include "../gfx/rect.h"
#include "../gfx/renderer.h"
#include "../engine/engine.h"
#include "../events/eventlistener.h"

#include <sstream>
#include <SDL2/SDL_render.h>

const int SPRITE_SPACE = 8;

SpritePicker::SpritePicker(Engine &engine, std::vector<Sprite> &sprites, Palette &palette) :
  engine_(engine), sprites_(sprites), palette_(palette), text_generator_(engine.renderer(), "resources/PressStart2P.ttf", 24){
  prev_page_texture_.reset(new Texture(text_generator_.textureFromText("<<", Color(220,220,220))));
  next_page_texture_.reset(new Texture(text_generator_.textureFromText(">>", Color(220,220,220))));
  page_size_ = sprites_.size() / (16 * 16);
  if(sprites_.size() % (16 * 16) != 0){
    page_size_++;
  }
  refresh();
}

void SpritePicker::setSprites(std::vector<Sprite> &sprites) {
  sprites_ = sprites;
  refresh();
}

void SpritePicker::handleEvents() {
  auto &events_listener = engine_.eventsListener();
  if(events_listener.keyboardEvent(SDLK_UP).pressed){
    if(index_ - 16 >= 0){
      index_ -= 16;
    }
  }
  if (events_listener.keyboardEvent(SDLK_DOWN).pressed){
    if(index_ + 16 < textures_.size()){
      index_ += 16;
    }
  }
  if (events_listener.keyboardEvent(SDLK_LEFT).pressed){
    index_--;
  }
  if (events_listener.keyboardEvent(SDLK_RIGHT).pressed){
    index_++;
  }

  auto mouse_event(events_listener.mouseEvent());

  int index = 0;
  if(mouse_event.left_click){
    for(auto &texture : textures_){
      auto rect(texture.dstRect());
      rect.adjust(SPRITE_SPACE / 2);
      if(rect.contains(mouse_event.pos)){
        index_ = index;
        break;
      }
      index++;
    }
    if(prev_page_texture_->dstRect().contains(mouse_event.pos)){
      page_index_--;
      if(page_index_ < 0){
        page_index_ = 0;
      }
      refresh();
    }
    else if(next_page_texture_->dstRect().contains(mouse_event.pos)){
      page_index_++;
      if(page_index_ == page_size_){
        page_index_--;
      }
      refresh();
    }
  }

  if(index_ < 0){
    index_ = 0;
  }
  else if (index_ >= textures_.size()){
    index_ = textures_.size() - 1;
  }
}

void SpritePicker::render() {
  int index = 0;

  auto rect(textures_[index_].dstRect());
  textures_[index_] = Texture(engine_.renderer(), sprites_[index_ + page_index_ * 256], palette_);
  textures_[index_].setDstRect(std::move(rect));

  for(auto &texture : textures_){
    if(index == index_){
      engine_.renderer().setDrawColor(0, 255, 0, 255);
      auto rect(textures_[index_].dstRect());
      rect.adjust(2);
      engine_.renderer().drawFillRect(std::move(rect));
    }

    engine_.renderer().renderTexture(texture);

    index++;
  }

  if(page_index_ != 0){
    engine_.renderer().renderTexture(*prev_page_texture_);
  }

  engine_.renderer().renderTexture(*page_texture_);

  if(page_index_ != page_size_ - 1){
    engine_.renderer().renderTexture(*next_page_texture_);
  }
}

void SpritePicker::refresh(){
  textures_.clear();

  int x = pos_.x;
  int y = pos_.y;

  int32_t index = page_index_ * (256);
  int32_t end = (page_index_ + 1) * (256);

  for(; index < sprites_.size() && index != end; ){
    auto &sprite = sprites_[index];
    auto tex = Texture(engine_.renderer(), sprite, palette_);
    tex.setDstRect(Rect (x, y, 16, 16));
    textures_.push_back(std::move(tex));

    index++;
    x += 16 + SPRITE_SPACE;
    if(index % 16 == 0){
      y += 16 + SPRITE_SPACE;
      x = pos_.x;
    }
  }

  y += 16;
  std::stringstream ss;
  ss << page_index_ + 1 << "/" << page_size_;

  page_texture_.reset(new Texture(text_generator_.textureFromText(ss.str(), Color(220,220,220))));
  prev_page_texture_->setDstRect(Rect(pos_.x + 112, y, 32, 32));
  next_page_texture_->setDstRect(Rect(pos_.x + 240, y, 32, 32));
  page_texture_->setDstRect(Rect(pos_.x + 160, y, 64, 32));

}

Sprite& SpritePicker::currentSprite() {
  return sprites_[index_ + page_index_ * 256];
}

void SpritePicker::setGlobalPos(const Pos &pos){
  pos_ = pos;
  refresh();
}
