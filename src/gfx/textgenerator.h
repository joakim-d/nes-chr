#ifndef id4B04E926C03C4056A38FAEDA87972796_H
#define id4B04E926C03C4056A38FAEDA87972796_H

#include <string>
#include "texture.h"

class Color;
class Renderer;
typedef struct _TTF_Font TTF_Font;
/*!
 * \brief The TextGenerator class
 */
//! TODO DOCUMENTING!!!

class TextGenerator {
public:
  TextGenerator(Renderer &renderer, const std::string &ttf_path, int32_t point_size);
  ~TextGenerator();

  Texture textureFromText(const std::string &text, const Color &color);
private:
  TTF_Font* font_;
  Renderer &renderer_;
};

#endif // id4B04E926C03C4056A38FAEDA87972796_H
