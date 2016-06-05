#include "paintview.h"
#include "../gfx/colorpicker.h"
#include "../gfx/renderer.h"
#include "../gfx/rect.h"
#include "../gfx/spritepicker.h"
#include "../gfx/pos.h"
#include "../engine/engine.h"
#include "../events/eventlistener.h"
#include "../core/rom.h"
#include "../core/chr.h"

PaintView::PaintView(Engine &engine, Rom &rom) : View(engine),
  rom_(rom),
  sprites_(rom_.chr().sprites()),
  sprite_editor_(engine, palette_, sprites_[0]),
  color_picker_(engine, palette_)
{
  sprite_editor_.setGlobalPos(Pos(16, 16));
  color_picker_.setGlobalPos(Pos(16, 400));
  color_picker_.initPalette();

  sprite_picker_.reset(new SpritePicker(engine, sprites_, palette_));
}

PaintView::~PaintView(){}

View::Action PaintView::render() {
  if(engine().eventsListener().quit()){
    return View::Action(View::Action::QUIT);
  }
  if(engine().eventsListener().keyboardEvent(SDLK_s).pressed){
    rom_.save();
  }

  if(sprite_picker_){
    sprite_picker_->handleEvents();
    sprite_editor_.setSprite(sprite_picker_->currentSprite());
  }

  auto color = palette_[color_picker_.selectedPaletteColorIndex()];
  color_picker_.handleEvents();
  if(color != palette_[color_picker_.selectedPaletteColorIndex()]){
    sprite_editor_.setCurrentColorIndex(color_picker_.selectedPaletteColorIndex());
    if(sprite_picker_){
      sprite_picker_->refresh();
    }
  }
  sprite_editor_.handleEvents();


  if(sprite_picker_){
    sprite_picker_->render();
  }
  sprite_editor_.render();
  color_picker_.render();

  return View::Action(View::Action::NONE);
}
