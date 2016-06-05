#include "spriteeditor.h"
#include "texture.h"
#include "rect.h"
#include "renderer.h"
#include "palette.h"
#include "../core/sprite.h"
#include "../engine/engine.h"
#include "../events/eventlistener.h"

#include <iostream>


const int BORDER_SIZE = 16;
const int FRAME_SIZE = 256;
const int PIXEL_SIZE = 32;

SpriteEditor::SpriteEditor(Engine &engine, Palette& palette, Sprite &sprite) : engine_(engine), palette_(palette), sprite_(&sprite){}

void SpriteEditor::handleEvents(){
  auto mouse_event(engine_.eventsListener().mouseEvent());

  mouse_event.pos -= pos_;
  mouse_event.pos -= Pos(BORDER_SIZE / 2, BORDER_SIZE / 2);

  if(Rect(0, 0, 256, 256).contains(mouse_event.pos)){
    auto rects(Rect(0,0,256,256).split(8, 8));
    hovered_pixel_idx_ = 0;
    for(const auto &rect : rects){
      if(rect.contains(mouse_event.pos)){
        break;
      }
      hovered_pixel_idx_++;
    }
    if(mouse_event.left_click){
      *(sprite_->data() + hovered_pixel_idx_) = current_color_idx_;
    }
  }
  else{
    hovered_pixel_idx_ = -1;
  }
}

void SpriteEditor::render(){
  if(sprite_texture_){
    engine_.renderer().setDrawColor(0, 255, 0, 0);
    engine_.renderer().drawFillRect(Rect(pos_.x, pos_.y, FRAME_SIZE + BORDER_SIZE, FRAME_SIZE + BORDER_SIZE));
    engine_.renderer().renderTexture(*sprite_texture_);
  }

  if(hovered_pixel_idx_ != -1){
    auto x = hovered_pixel_idx_ % 8;
    auto y = hovered_pixel_idx_ / 8;
    engine_.renderer().setDrawColor(palette_[current_color_idx_]);
    engine_.renderer().drawFillRect(Rect(pos_.x + x * 32 + BORDER_SIZE / 2, pos_.y + BORDER_SIZE / 2 + y * 32, PIXEL_SIZE, PIXEL_SIZE));
  }
}

void SpriteEditor::setSprite(Sprite &sprite) {
  sprite_ = &sprite;
  sprite_texture_.reset(new Texture(engine_.renderer(), *sprite_, palette_));
  sprite_texture_->setDstRect(Rect(pos_.x + BORDER_SIZE / 2, pos_.y + BORDER_SIZE / 2, FRAME_SIZE, FRAME_SIZE));
}

void SpriteEditor::setGlobalPos(const Pos &pos) {
  pos_ = pos;
}

void SpriteEditor::setGlobalPos(Pos &&pos) {
  pos_ = std::move(pos);
}

void SpriteEditor::setCurrentColorIndex(uint32_t index) {
  current_color_idx_ = index;
}

