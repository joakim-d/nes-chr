#include "palette.h"

Palette::Palette(){

}

Color& Palette::operator [](uint32_t index){
  return colors_[index];
}
