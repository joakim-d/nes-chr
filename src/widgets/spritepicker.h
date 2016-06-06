#ifndef idE64112F9834946D0AB6270D44BBF1A52_H
#define idE64112F9834946D0AB6270D44BBF1A52_H

#include <vector>
#include "../gfx/texture.h"
#include "../gfx/pos.h"
#include "../gfx/textgenerator.h"

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
  void setGlobalPos(const Pos& pos);

private:
  Engine &engine_;
  std::vector<Sprite> &sprites_;
  std::vector<Texture> textures_;
  int32_t index_{};
  Palette &palette_;
  Pos pos_{};
  TextGenerator text_generator_;
  int32_t page_index_{};
  uint32_t page_size_{};
  std::unique_ptr<Texture> prev_page_texture_;
  std::unique_ptr<Texture> next_page_texture_;
  std::unique_ptr<Texture> page_texture_;
};

#endif // idE64112F9834946D0AB6270D44BBF1A52_H
