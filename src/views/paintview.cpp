#include "paintview.h"
#include "../gfx/renderer.h"
#include "../gfx/rect.h"

void PaintView::setNesSprites(const std::vector<Sprite> &sprites){
  sprites_ = sprites;
  //textures_.resize(sprites_.size());

  for(auto &sprite : sprites_){
    textures_.push_back(Texture(*renderer(), sprite));
  }
}

View::Action PaintView::render() {

  auto r = renderer();
  int x = 0;
  int y = 0;

  Rect src_rect(0, 0, 8, 8);
  for(const auto &texture : textures_){
    Rect dst_rect(x, y, 8, 8);

    r->renderTexture(texture, src_rect, dst_rect);

    x += 8;
    if(x == 160){
      y += 8;
      x = 0;
    }


  }

  return View::Action(View::Action::NONE);
}
