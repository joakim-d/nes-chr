#ifndef id510DEB9FFA554300A13C8D69E08AB8C2_H
#define id510DEB9FFA554300A13C8D69E08AB8C2_H

#include <memory>
#include "pos.h"

class Engine;
class Palette;

/*!
 * \brief The ColorPicker class
 */
//! TODO DOCUMENTING!!!

class ColorPicker {
public:
  ColorPicker(Engine &engine, Palette &palette);
  ~ColorPicker();
  void handleEvents();
  void render();
  void setGlobalPos(const Pos &pos);
  void initPalette();
  uint32_t selectedPaletteColorIndex() const;
private:
  class ColorPickerPrivate;
  std::unique_ptr<ColorPickerPrivate> d_;
};

#endif // id510DEB9FFA554300A13C8D69E08AB8C2_H
