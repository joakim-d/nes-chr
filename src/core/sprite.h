#ifndef id049C1D2F914A40D382C1CA5402374970_H
#define id049C1D2F914A40D382C1CA5402374970_H

#include <cstdint>
#include <vector>

class Sprite {
public:
  Sprite(uint32_t width, uint32_t height, std::vector<uint8_t> &&pixels);

  uint32_t width() const;
  uint32_t height() const;

  uint8_t* data();

private:
  uint32_t width_{};
  uint32_t height_{};
  std::vector<uint8_t> pixels_;
};

#endif // id049C1D2F914A40D382C1CA5402374970_H
