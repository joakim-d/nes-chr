#ifndef id637FF18A74694DDCBA44F4397542CEBB_H
#define id637FF18A74694DDCBA44F4397542CEBB_H

#include <memory>
#include "../core/sprite.h"
#include "pos.h"

class Engine;
class Palette;
class Texture;
/*!
 * \brief The SpriteEditor class
 */
//! TODO DOCUMENTING!!!

class SpriteEditor {
public:
  SpriteEditor(Engine &engine, Palette &palette);

  void setSprite(Sprite &sprite);
  void handleEvents();
  void render();
  void setGlobalPos(const Pos &pos);
  void setGlobalPos(Pos &&pos);
  void setCurrentColorIndex(uint32_t index);

private:
  Engine &engine_;
  Sprite sprite_;
  std::unique_ptr<Texture> sprite_texture_;
  Pos pos_;
  int32_t hovered_pixel_idx_{-1};
  uint32_t current_color_idx_{0};
  Palette &palette_;
};

#endif // id637FF18A74694DDCBA44F4397542CEBB_H
