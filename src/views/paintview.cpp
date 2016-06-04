#include "paintview.h"
#include "../gfx/colorpicker.h"
#include "../gfx/renderer.h"
#include "../gfx/rect.h"
#include "../gfx/spritepicker.h"
#include "../gfx/pos.h"
#include "../engine/engine.h"
#include "../events/eventlistener.h"

PaintView::PaintView(Engine &engine) : View(engine),
  sprite_editor_(engine, palette_),
  color_picker_(engine, palette_)
{
  sprite_editor_.setGlobalPos(Pos(16, 16));
  color_picker_.setGlobalPos(Pos(16, 400));
  color_picker_.initPalette();
}

PaintView::~PaintView(){}

void PaintView::setNesSprites(const std::vector<Sprite> &sprites){
  sprites_ = sprites;

  if(sprites.size() == 0){
    throw std::runtime_error("Sprite list empty");
  }
  sprite_picker_.reset(new SpritePicker(engine(), sprites_, palette_));

  sprite_editor_.setSprite(sprites_[0]);
  current_texture_index_ = 0;
}

View::Action PaintView::render() {
  if(engine().eventsListener().quit()){
    return View::Action(View::Action::QUIT);
  }

  if(sprite_picker_){
    sprite_picker_->handleEvents();
    sprite_editor_.setSprite(sprite_picker_->currentSprite());
  }


  color_picker_.handleEvents();
  sprite_editor_.setCurrentColorIndex(color_picker_.selectedPaletteColorIndex());
  sprite_editor_.handleEvents();


  if(sprite_picker_){
    sprite_picker_->render();
  }
  sprite_editor_.render();
  color_picker_.render();

  return View::Action(View::Action::NONE);
}
