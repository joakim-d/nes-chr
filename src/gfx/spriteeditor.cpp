#include "spriteeditor.h"
#include "renderer.h"
#include "texture.h"
#include "rect.h"
#include "../core/sprite.h"

const int BORDER_SIZE = 16;
const int FRAME_SIZE = 256;

SpriteEditor::SpriteEditor(Renderer &renderer) : renderer_(renderer){

}

void SpriteEditor::render(){
  if(sprite_texture_){
    renderer_.setDrawColor(0, 255, 0, 0);
    renderer_.drawFillRect(Rect(pos_.x, pos_.y, FRAME_SIZE + BORDER_SIZE, FRAME_SIZE + BORDER_SIZE));
    renderer_.renderTexture(*sprite_texture_);
  }
}

void SpriteEditor::setSprite(Sprite &sprite) {
  sprite_ = sprite;
  sprite_texture_.reset(new Texture(renderer_, sprite_));
  sprite_texture_->setDstRect(Rect(pos_.x + BORDER_SIZE / 2, pos_.y + BORDER_SIZE / 2, FRAME_SIZE, FRAME_SIZE));
}

void SpriteEditor::setGlobalPos(const Pos &pos) {
  pos_ = pos;
}

void SpriteEditor::setGlobalPos(Pos &&pos) {
  pos_ = std::move(pos);
}
