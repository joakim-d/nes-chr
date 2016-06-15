#include "paintview.h"

#include "../core/rom.h"
#include "../core/chr.h"
#include "../engine/engine.h"
#include "../events/eventlistener.h"
#include "../gfx/renderer.h"
#include "../gfx/rect.h"
#include "../gfx/pos.h"
#include "../widgets/spritepicker.h"

PaintView::PaintView(Engine &engine, std::unique_ptr<Rom> &&rom) : View(engine),
  rom_(std::move(rom)),
  sprites_(rom_->chr().sprites()),
  sprite_editor_(engine, palette_, sprites_[0]),
  color_picker_(engine, palette_)
{
  sprite_editor_.setGlobalPos(Pos(32, 16));
  color_picker_.setGlobalPos(Pos(32, 320));
  color_picker_.initPalette();

  sprite_picker_.reset(new SpritePicker(engine, sprites_, palette_));
  sprite_picker_->setGlobalPos(Pos(380, 16));
}

PaintView::PaintView(Engine &engine, std::unique_ptr<Chr> &&chr) : View(engine),
  chr_(std::move(chr)),
  sprites_(chr_->sprites()),
  sprite_editor_(engine, palette_, sprites_[0]),
  color_picker_(engine, palette_)
{
  sprite_editor_.setGlobalPos(Pos(32, 16));
  color_picker_.setGlobalPos(Pos(32, 320));
  color_picker_.initPalette();

  sprite_picker_.reset(new SpritePicker(engine, sprites_, palette_));
  sprite_picker_->setGlobalPos(Pos(380, 16));
}

PaintView::~PaintView(){}

View::Action PaintView::render() {
  if(engine().eventsListener().quit()){
    return View::Action(View::Action::QUIT);
  }
  if(engine().eventsListener().keyboardEvent(SDLK_s).pressed){
    if(rom_){
      rom_->save();
    }
    else if(chr_){
      chr_->save();
    }
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
