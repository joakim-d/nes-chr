#ifndef idE64112F9834946D0AB6270D44BBF1A52_H
#define idE64112F9834946D0AB6270D44BBF1A52_H

#include <vector>
#include "texture.h"

class Engine;
class Sprite;

/*!
 * \brief The SpritePicker class
 */
//! TODO DOCUMENTING!!!

class SpritePicker {
public:
  SpritePicker(Engine &engine, std::vector<Sprite> &sprites, Palette &palette);

  void setSprites(std::vector<Sprite> &sprites);
  Sprite& currentSprite();
  void handleEvents();
  void render();
  void refresh();

private:
  Engine &engine_;
  std::vector<Sprite> &sprites_;
  std::vector<Texture> textures_;
  int32_t index_{};
  Palette &palette_;
};

#endif // idE64112F9834946D0AB6270D44BBF1A52_H
