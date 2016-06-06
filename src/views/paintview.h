#ifndef id75221EC6877A410DA87FEF48B7A8AE47_H
#define id75221EC6877A410DA87FEF48B7A8AE47_H

#include "view.h"
#include "../core/sprite.h"

#include <vector>
#include "../gfx/palette.h"
#include "../widgets/spriteeditor.h"
#include "../widgets/colorpicker.h"

class SpritePicker;
class Rom;

/*!
 * \brief The PaintView class
 */
//! TODO DOCUMENTING!!!

class PaintView : public View {
public:
  PaintView(Engine &engine, Rom& rom);
  ~PaintView();
  virtual View::Action render() override;

private:
  Rom& rom_;
  std::vector<Sprite> &sprites_;
  ColorPicker color_picker_;
  SpriteEditor sprite_editor_;
  std::unique_ptr<SpritePicker> sprite_picker_;
  Palette palette_;
};

#endif // id75221EC6877A410DA87FEF48B7A8AE47_H
