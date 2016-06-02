#ifndef id1D92E37592F246BEB8E6256F84C59750_H
#define id1D92E37592F246BEB8E6256F84C59750_H

#include <memory>

class Renderer;
class Sprite;
class SDL_Texture;
/*!
 * \brief The Texture class
 */
//! TODO DOCUMENTING!!!

class Texture {
public:
  Texture(Renderer &renderer, Sprite &sprite);
  ~Texture();

  Texture(Texture &&rhs);
  Texture& operator=(Texture &&rhs);

  SDL_Texture* rawTexture() const;
private:
  class TexturePrivate;
  std::unique_ptr<TexturePrivate> d_;
};

#endif // id1D92E37592F246BEB8E6256F84C59750_H