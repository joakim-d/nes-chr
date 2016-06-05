#ifndef idD73BC808C99D4D25B79BB3777CA3AB9D_H
#define idD73BC808C99D4D25B79BB3777CA3AB9D_H

#include <cstdint>
#include <SDL2/SDL.h>
/*!
 * \brief The Color class
 */
//! TODO DOCUMENTING!!!

class Color {
public:
  Color();
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  SDL_Color toSDLColor() const;

  bool operator!=(const Color &rhs) const;
  uint8_t r{};
  uint8_t g{};
  uint8_t b{};
  uint8_t a{};
};

#endif // idD73BC808C99D4D25B79BB3777CA3AB9D_H
