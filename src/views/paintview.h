#ifndef id75221EC6877A410DA87FEF48B7A8AE47_H
#define id75221EC6877A410DA87FEF48B7A8AE47_H

#include "view.h"
#include "../core/sprite.h"

#include <vector>
#include "../gfx/spriteeditor.h"

class SpritePicker;

/*!
 * \brief The PaintView class
 */
//! TODO DOCUMENTING!!!

class PaintView : public View {
public:
  PaintView(Engine &engine);
  ~PaintView();
  void setNesSprites(const std::vector<Sprite> &sprites);
  virtual View::Action render() override;

private:
  SpriteEditor sprite_editor_;
  std::unique_ptr<SpritePicker> sprite_picker_;
  std::vector<Sprite> sprites_;
  uint32_t current_texture_index_{};
  uint32_t current_color_{};
};

#endif // id75221EC6877A410DA87FEF48B7A8AE47_H
