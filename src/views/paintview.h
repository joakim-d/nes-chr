#ifndef id75221EC6877A410DA87FEF48B7A8AE47_H
#define id75221EC6877A410DA87FEF48B7A8AE47_H

#include "view.h"
#include "../core/sprite.h"
#include "../gfx/texture.h"

#include <vector>
/*!
 * \brief The PaintView class
 */
//! TODO DOCUMENTING!!!

class PaintView : public View {
public:
  //PaintView();
  void setNesSprites(const std::vector<Sprite> &sprites);
  virtual View::Action render() override;

private:
  std::vector<Sprite> sprites_;
  std::vector<Texture> textures_;
};

#endif // id75221EC6877A410DA87FEF48B7A8AE47_H
