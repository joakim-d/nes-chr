#ifndef idD48C21575D5E443AAA70BC5D36C81327_H
#define idD48C21575D5E443AAA70BC5D36C81327_H

#include <memory>

class View;
using ViewUPtr = std::unique_ptr<View>;

class SDL_Renderer;
class Texture;

class Rect;
class Color;

/*!
 * \brief The Renderer class
 */
//! TODO DOCUMENTING!!!

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool render();
  void setView(ViewUPtr &&view);

  void renderTexture(const Texture& texture);
  void renderTexture(const Texture &texture, const Rect &src, const Rect &dst);
  void drawFillRect(const Rect &rect);
  void drawFillRect(Rect &&rect);
  void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void setDrawColor(const Color &color);
  SDL_Renderer *rawRenderer();

private:
  class RendererPrivate;
  std::unique_ptr<RendererPrivate> d_;
};

#endif // idD48C21575D5E443AAA70BC5D36C81327_H
