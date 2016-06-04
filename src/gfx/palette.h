#ifndef idE93CF0A8182646E6AD0D3D7272E5D2B5_H
#define idE93CF0A8182646E6AD0D3D7272E5D2B5_H

#include <array>
#include "color.h"
/*!
 * \brief The Palette class
 */
//! TODO DOCUMENTING!!!

class Palette {
public:
  Palette();
  Color& operator [](uint32_t index);

private:
  std::array<Color, 4> colors_;
};

#endif // idE93CF0A8182646E6AD0D3D7272E5D2B5_H
