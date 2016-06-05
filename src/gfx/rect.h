#ifndef idE10DBBA14779488A99EA170C3879B653_H
#define idE10DBBA14779488A99EA170C3879B653_H

#include <memory>
#include <vector>

class SDL_Rect;
class Pos;
/*!
 * \brief The Rect class
 */
//! TODO DOCUMENTING!!!


class Rect {
public:
  Rect();
  Rect(int32_t x, int32_t y, int32_t width, int32_t height);
  ~Rect();

  Rect(Rect &&rhs);
  Rect(const Rect &c);

  Rect & operator =(Rect &&rect);
  Rect & operator =(const Rect &rect);

  SDL_Rect &rect() const;

  bool contains(const Pos& pos) const;
  std::vector<Rect> split(uint32_t w, uint32_t h) const;
  void adjust(int32_t pixels);
private:
  class RectPrivate;
  std::unique_ptr<RectPrivate> d_;
};

#endif // idE10DBBA14779488A99EA170C3879B653_H
