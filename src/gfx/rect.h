#ifndef idE10DBBA14779488A99EA170C3879B653_H
#define idE10DBBA14779488A99EA170C3879B653_H

#include <memory>

class SDL_Rect;

/*!
 * \brief The Rect class
 */
//! TODO DOCUMENTING!!!


class Rect {
public:
  Rect(int32_t x, int32_t y, int32_t width, int32_t height);
  ~Rect();

  Rect(Rect &&rhs);
  Rect(const Rect &c);

  Rect & operator =(Rect &&rect);
  Rect & operator =(const Rect &rect);

  SDL_Rect &rect() const;
private:
  class RectPrivate;
  std::unique_ptr<RectPrivate> d_;
};

#endif // idE10DBBA14779488A99EA170C3879B653_H
