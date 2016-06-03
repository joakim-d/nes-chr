#ifndef id637FF18A74694DDCBA44F4397542CEBB_H
#define id637FF18A74694DDCBA44F4397542CEBB_H

#include <memory>
#include "../core/sprite.h"
#include "pos.h"

class Texture;
class Renderer;
/*!
 * \brief The SpriteEditor class
 */
//! TODO DOCUMENTING!!!

class SpriteEditor {
public:
  SpriteEditor(Renderer &renderer);

  void setSprite(Sprite &sprite);
  void render();
  void setGlobalPos(const Pos &pos);
  void setGlobalPos(Pos &&pos);
private:
  Renderer &renderer_;
  Sprite sprite_;
  std::unique_ptr<Texture> sprite_texture_;
  Pos pos_;
};

#endif // id637FF18A74694DDCBA44F4397542CEBB_H
